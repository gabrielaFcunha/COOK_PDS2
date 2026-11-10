#!/usr/bin/env bash
# verificar_interface.sh
#
# Roda cada TEST_CASE de Tests/test_interface.cpp num processo separado,
# com limite de tempo, e classifica o resultado:
#   OK       aprovado
#   FALHOU   algum CHECK/REQUIRE falhou (ou excecao nao tratada)
#   TRAVOU   estourou o limite de tempo (possivel laco infinito)
#   CRASH    o processo morreu por sinal (segfault, abort...)
#   TOLERADO aprovado, mas com asserts que falharam (teste marcado com may_fail:
#            falha esperada, ainda nao e comportamento correto)
#   SEM-TESTE o filtro nao encontrou nenhum test case com esse nome
# A saida de tudo que nao for OK e salva em arquivos de log.
#
# Uso: ./verificar_interface.sh [-f arquivo] [-e executavel] [-t segundos]
#                               [-l pasta_logs] [-m mem_kb] [-b] [-h]

set -u

ARQUIVO_TESTE="Tests/test_interface.cpp"
EXECUTAVEL="build/coverage/testes"
LIMITE=5
DIR_LOGS="logs_interface"
LIMITE_MEM_KB=1048576      # 1 GB: laco infinito que acumula saida vira erro, nao OOM
COMPILAR=0

uso() {
    cat <<USO
Uso: $0 [opcoes]
  -f ARQ    arquivo de testes de onde extrair os nomes (padrao: $ARQUIVO_TESTE)
  -e EXE    executavel de testes doctest              (padrao: $EXECUTAVEL)
  -t SEG    limite de tempo por teste, em segundos    (padrao: $LIMITE)
  -l DIR    pasta dos logs                            (padrao: $DIR_LOGS)
  -m KB     limite de memoria virtual por teste       (padrao: $LIMITE_MEM_KB)
  -b        roda 'make cobertura' antes (recompila o executavel de testes)
  -h        esta ajuda
Codigo de saida: 0 se tudo passou, 1 se algum teste teve problema, 2 se erro de uso.
USO
}

while getopts "f:e:t:l:m:bh" opcao; do
    case "$opcao" in
        f) ARQUIVO_TESTE="$OPTARG" ;;
        e) EXECUTAVEL="$OPTARG" ;;
        t) LIMITE="$OPTARG" ;;
        l) DIR_LOGS="$OPTARG" ;;
        m) LIMITE_MEM_KB="$OPTARG" ;;
        b) COMPILAR=1 ;;
        h) uso; exit 0 ;;
        *) uso; exit 2 ;;
    esac
done

# ---------- cores (so se a saida for um terminal) ----------
if [ -t 1 ]; then
    VERDE=$'\033[32m'; VERMELHO=$'\033[31m'; AMARELO=$'\033[33m'; NEGRITO=$'\033[1m'; FIM=$'\033[0m'
else
    VERDE=""; VERMELHO=""; AMARELO=""; NEGRITO=""; FIM=""
fi

# ---------- dependencias ----------
if command -v timeout >/dev/null 2>&1; then
    TIMEOUT_CMD=timeout
elif command -v gtimeout >/dev/null 2>&1; then
    TIMEOUT_CMD=gtimeout
else
    echo "Erro: comando 'timeout' nao encontrado (pacote coreutils; no macOS: brew install coreutils)." >&2
    exit 2
fi

if [ ! -f "$ARQUIVO_TESTE" ]; then
    echo "Erro: arquivo de testes nao encontrado: $ARQUIVO_TESTE" >&2
    exit 2
fi

if [ "$COMPILAR" -eq 1 ]; then
    echo "Compilando (make cobertura)..."
    make cobertura || { echo "Erro: a compilacao falhou." >&2; exit 2; }
fi

if [ ! -x "$EXECUTAVEL" ]; then
    echo "Erro: executavel de testes nao encontrado: $EXECUTAVEL" >&2
    echo "      Compile antes (make cobertura) ou use a opcao -b." >&2
    exit 2
fi
EXE_ABS="$(cd "$(dirname "$EXECUTAVEL")" && pwd)/$(basename "$EXECUTAVEL")"

# ---------- extrai os nomes dos TEST_CASE ----------
# Ignora comentarios de linha (//) e de bloco (/* ... */) e remove nomes repetidos.
extrair_nomes() {
    awk '
    {
        linha = $0
        while (1) {
            if (em_bloco) {
                i = index(linha, "*/")
                if (i == 0) { linha = ""; break }
                linha = substr(linha, i + 2); em_bloco = 0
            } else {
                i = index(linha, "/*")
                if (i == 0) break
                j = index(substr(linha, i + 2), "*/")
                if (j == 0) { linha = substr(linha, 1, i - 1); em_bloco = 1; break }
                linha = substr(linha, 1, i - 1) substr(linha, i + j + 3)
            }
        }
        print linha
    }' "$ARQUIVO_TESTE" \
    | sed -nE 's/^[[:space:]]*TEST_CASE\("([^"]*)".*/\1/p' \
    | awk '!visto[$0]++'
}

mapfile -t NOMES < <(extrair_nomes)

if [ "${#NOMES[@]}" -eq 0 ]; then
    echo "Nenhum TEST_CASE encontrado em $ARQUIVO_TESTE" >&2
    exit 2
fi

mkdir -p "$DIR_LOGS"
rm -f "$DIR_LOGS"/*.log

# ---------- executa um teste isolado ----------
# O doctest usa ',' para separar filtros e '*' como curinga; no nome eles viram '?'
# (curinga de um caractere), assim o filtro continua casando exatamente o teste.
executar_um() {
    local nome="$1" saida="$2" padrao tmpdir rc
    padrao="${nome//,/?}"
    padrao="${padrao//\*/?}"
    tmpdir="$(mktemp -d)"          # pasta descartavel: nada vaza entre testes nem toca nos dados reais
    {
        (
            ulimit -v "$LIMITE_MEM_KB" 2>/dev/null
            cd "$tmpdir" || exit 125
            exec "$TIMEOUT_CMD" -k 2 "$LIMITE" "$EXE_ABS" --no-colors -cs "--test-case=$padrao"
        ) > "$saida" 2>&1 < /dev/null
        rc=$?
    } 2>/dev/null
    rm -rf "$tmpdir"
    return $rc
}

TOTAL=${#NOMES[@]}
OK=0; FALHOU=0; TRAVOU=0; CRASH=0; SEMTESTE=0; TOLERADOS=0
LISTA_TOLERADOS=()
PROBLEMAS=()
LOGS_TOLERADOS=()
TMP_SAIDA="$(mktemp)"
trap 'rm -f "$TMP_SAIDA"' EXIT

echo "${NEGRITO}Verificando $TOTAL test cases de $ARQUIVO_TESTE${FIM}"
echo "Executavel: $EXECUTAVEL | limite: ${LIMITE}s por teste | logs em: $DIR_LOGS/"
echo

indice=0
for nome in "${NOMES[@]}"; do
    indice=$((indice + 1))
    executar_um "$nome" "$TMP_SAIDA" ; rc=$?

    status=""; motivo=""
    case "$rc" in
        0)
            if grep -Eq 'test cases: +0 ' "$TMP_SAIDA"; then
                status="SEM-TESTE"; motivo="o filtro nao encontrou test case com esse nome"
            elif grep -q 'ERROR:' "$TMP_SAIDA"; then
                status="TOLERADO"; motivo="asserts falharam, mas o teste e may_fail (falha esperada)"
            else
                status="OK"
            fi ;;
        124|137)
            status="TRAVOU"; motivo="excedeu ${LIMITE}s (codigo $rc): possivel laco infinito" ;;
        125|126|127)
            status="CRASH"; motivo="nao foi possivel executar o programa (codigo $rc)" ;;
        1)
            status="FALHOU"; motivo="algum teste falhou (codigo 1)" ;;
        *)
            if [ "$rc" -gt 128 ]; then
                sinal="$(kill -l $((rc - 128)) 2>/dev/null || echo "?")"
                status="CRASH"; motivo="morreu pelo sinal $sinal (codigo $rc)"
                [ "$rc" -eq 134 ] && motivo="$motivo; abort()/excecao nao tratada, ou memoria esgotada (limite ${LIMITE_MEM_KB} KB)"
            else
                status="FALHOU"; motivo="codigo de saida inesperado: $rc"
            fi ;;
    esac

    case "$status" in
        OK)        OK=$((OK + 1));             printf '%s[ OK      ]%s %s\n' "$VERDE" "$FIM" "$nome" ;;
        TOLERADO)  TOLERADOS=$((TOLERADOS + 1)); LISTA_TOLERADOS+=("$nome")
                   printf '%s[ TOLERADO]%s %s\n' "$AMARELO" "$FIM" "$nome" ;;
        FALHOU)    FALHOU=$((FALHOU + 1));     printf '%s[ FALHOU  ]%s %s\n' "$VERMELHO" "$FIM" "$nome" ;;
        TRAVOU)    TRAVOU=$((TRAVOU + 1));     printf '%s[ TRAVOU  ]%s %s\n' "$AMARELO" "$FIM" "$nome" ;;
        CRASH)     CRASH=$((CRASH + 1));       printf '%s[ CRASH   ]%s %s\n' "$VERMELHO" "$FIM" "$nome" ;;
        SEM-TESTE) SEMTESTE=$((SEMTESTE + 1)); printf '%s[ SEM-TESTE]%s %s\n' "$AMARELO" "$FIM" "$nome" ;;
    esac

    if [ "$status" != "OK" ]; then
        slug="$(printf '%s' "$nome" | tr -c 'A-Za-z0-9._-' '_' | cut -c1-60)"
        log="$(printf '%s/%03d_%s.log' "$DIR_LOGS" "$indice" "$slug")"
        {
            echo "Teste:    $nome"
            echo "Arquivo:  $ARQUIVO_TESTE"
            echo "Status:   $status"
            echo "Motivo:   $motivo"
            echo "Comando:  $TIMEOUT_CMD -k 2 $LIMITE $EXECUTAVEL --no-colors -cs --test-case=<nome>"
            echo "Data:     $(date '+%Y-%m-%d %H:%M:%S')"
            echo "-------------------------------------------------------------------------------"
            if [ "$status" = "TRAVOU" ]; then
                echo "O processo foi interrompido sem terminar. Causas comuns neste projeto:"
                echo " - roteiro de entrada desalinhado: a entrada acaba numa tela que repete a leitura"
                echo "   (ex.: Interface::lerQuantidade sem tratamento de EOF fica em laco infinito)"
                echo " - menu que espera uma opcao que o roteiro nao envia"
                echo "A saida abaixo e parcial."
                echo "-------------------------------------------------------------------------------"
            fi
            tamanho=$(wc -c < "$TMP_SAIDA")
            head -c 1000000 "$TMP_SAIDA"
            [ "$tamanho" -gt 1000000 ] && printf '\n[... saida truncada: %s bytes no total ...]\n' "$tamanho"
        } > "$log"
        if [ "$status" = "TOLERADO" ]; then
            LOGS_TOLERADOS+=("$nome|$log")
        else
            PROBLEMAS+=("$status|$nome|$log|$motivo")
        fi
    fi
done

# ---------- resumo ----------
echo
echo "${NEGRITO}================ RESUMO ================${FIM}"
printf 'Total:        %d\n' "$TOTAL"
printf '%sAprovados:    %d%s\n' "$VERDE" "$OK" "$FIM"
printf '%sTolerados:    %d%s  (may_fail: falha esperada, nao conta como problema)\n' "$AMARELO" "$TOLERADOS" "$FIM"
printf '%sReprovados:   %d%s  (falhou: %d, crash: %d, sem-teste: %d)\n' "$VERMELHO" $((FALHOU + CRASH + SEMTESTE)) "$FIM" "$FALHOU" "$CRASH" "$SEMTESTE"
printf '%sTravamentos:  %d%s  (excederam %ss)\n' "$AMARELO" "$TRAVOU" "$FIM" "$LIMITE"

if [ "${#LOGS_TOLERADOS[@]}" -gt 0 ]; then
    echo
    echo "${NEGRITO}Falhas toleradas (comportamento ainda nao implementado):${FIM}"
    for t in "${LOGS_TOLERADOS[@]}"; do
        IFS='|' read -r nm lg <<< "$t"
        printf '  %s\n      log: %s\n' "$nm" "$lg"
    done
fi

if [ "${#PROBLEMAS[@]}" -gt 0 ]; then
    echo
    echo "${NEGRITO}Testes com problema (logs em $DIR_LOGS/):${FIM}"
    for p in "${PROBLEMAS[@]}"; do
        IFS='|' read -r st nm lg mt <<< "$p"
        printf '  [%s] %s\n      %s\n      log: %s\n' "$st" "$nm" "$mt" "$lg"
    done
    exit 1
fi

echo
if [ "$TOLERADOS" -gt 0 ]; then
    echo "${VERDE}Nenhum teste reprovado${FIM}, mas ${AMARELO}$TOLERADOS com falha tolerada (may_fail)${FIM}."
else
    echo "${VERDE}Todos os testes passaram.${FIM}"
fi
exit 0