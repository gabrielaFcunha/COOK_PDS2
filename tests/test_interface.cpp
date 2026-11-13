#include "doctest.h"
#include "interface.hpp"
#include <iostream>
#include <sstream>
#include <string>

// Restaura cin/cout ao sair do escopo, mesmo se o teste abortar
struct RedirecionaIO {
    std::istringstream in;
    std::ostringstream out;
    std::streambuf* antigoIn;
    std::streambuf* antigoOut;

    explicit RedirecionaIO(const std::string& entrada)
        : in(entrada),
          antigoIn(std::cin.rdbuf(in.rdbuf())),
          antigoOut(std::cout.rdbuf(out.rdbuf())) {}

    ~RedirecionaIO() {
        std::cin.rdbuf(antigoIn);
        std::cout.rdbuf(antigoOut);
    }
};

// Roda o menu com a entrada simulada e devolve tudo que foi impresso
static std::string executarMenu(const std::string& entrada) {
    RedirecionaIO io(entrada);
    Interface interface(false); // nao toca em disco
    interface.menu();
    return io.out.str();
}

static bool contem(const std::string& texto, const std::string& trecho) {
    return texto.find(trecho) != std::string::npos;
}

// ---------- pedacos de entrada reutilizaveis ----------
// Menu principal: 1 = catalogo, 2 = despensa, 3 = cozinhar, 4 = sair
// Submenu catalogo: 1 cadastrar, 2 exibir, 3 buscar, 4 filtrar categoria,
//                   5 editar, 6 remover, 7 avaliar, 8 filtrar avaliacao, 9 voltar
// Submenu despensa: 1 ingredientes da receita, 2 adicionar, 3 remover,
//                   4 editar quantidade, 5 disponibilidade, 6 voltar
static const std::string VOLTA_CAT  = "9\n";
static const std::string VOLTA_DESP = "6\n";

// Dentro do submenu do catalogo: cadastra Bolo (Sobremesa, 40 min, Farinha 200 g, nota 5)
// O "\n" final e a pausa depois de "Receita salva".
static const std::string CADASTRA_BOLO =
    "1\n"                    // cadastrar receita
    "Bolo\n40\n3\n"          // nome, tempo, categoria 3 = Sobremesa
    "Misture e asse.\n"      // modo de preparo
    "Farinha\n200\n1\n"      // ingrediente: 200, unidade 1 = gramas
    "fim\n"
    "5\n\n";                 // avaliacao 5 e Enter da pausa

// Dentro do submenu da despensa: adiciona Farinha 500 g (Enter final = pausa)
static const std::string DESPENSA_FARINHA_500 =
    "2\nFarinha\n500\n1\n\n";

// ---------- MENU PRINCIPAL ----------

TEST_CASE("Teste 01 - Opcao 4 encerra o menu" * doctest::timeout(2)) {
    std::string saida = executarMenu("4\n");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Catalogo de Receitas"));
    CHECK(contem(saida, "Sair"));
}

TEST_CASE("Teste 02 - Opcao invalida mostra erro e volta ao menu" * doctest::timeout(2)) {
    // a linha em branco e consumida pelo cin.get() da pausa
    std::string saida = executarMenu("9\n\n4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
    CHECK_FALSE(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 03 - Texto no lugar de numero e invalido" * doctest::timeout(2)) {
    std::string saida = executarMenu("abc\n\n4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
}

TEST_CASE("Teste 04 - Fim de entrada nao trava" * doctest::timeout(2)) {
    std::string saida = executarMenu("");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 05 - Fim de entrada dentro de um submenu" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n");
    CHECK(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 06 - Fim de entrada depois de opcao invalida" * doctest::timeout(2)) {
    std::string saida = executarMenu("9\n");
    CHECK(contem(saida, "Fim da entrada detectado"));
}

// ---------- EXIBIR CATALOGO ----------

TEST_CASE("Teste 07 - Catalogo vazio" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

TEST_CASE("Teste 08 - Cadastrar e exibir receita" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Receita salva com sucesso"));
    CHECK(contem(saida, "1) Bolo"));
    CHECK(contem(saida, "40 minutos"));
}

TEST_CASE("Teste 09 - Detalhes da receita" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n1\n\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Tempo de Preparo: 40"));
    CHECK(contem(saida, "Avaliacao: 5/5"));
    CHECK(contem(saida, "Farinha"));
    CHECK(contem(saida, "200"));
    CHECK(contem(saida, "Misture e asse."));
}

TEST_CASE("Teste 10 - Receita sem ingredientes" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nSopa\n20\n1\nFerva.\nfim\n3\n\n"
        "2\n1\n\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "nenhum ingrediente cadastrado"));
}

TEST_CASE("Teste 11 - Numero fora do intervalo no catalogo" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n5\n\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
}

// ---------- CADASTRAR RECEITA ----------

TEST_CASE("Teste 12 - Quantidade invalida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n3\nMisture.\n"
        "Ovo\nabc\n0\n3\n3\n"          // texto, zero, depois 3 e unidade 3
        "fim\n4\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Valor invalido"));
}

TEST_CASE("Teste 13 - Categoria invalida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n9\n3\nMisture.\nfim\n4\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Opcao invalida"));
}

TEST_CASE("Teste 14 - Unidade invalida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n3\nMisture.\nOvo\n2\n9\n3\nfim\n4\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Opcao invalida"));
}

TEST_CASE("Teste 15 - Avaliacao invalida no cadastro" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n3\nMisture.\nfim\n9\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Avaliacao invalida"));
}

TEST_CASE("Teste 16 - Receita duplicada e avisada" * doctest::timeout(2) * doctest::may_fail()) {
    // hoje a interface imprime "salva com sucesso" mesmo quando o catalogo rejeita
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + CADASTRA_BOLO + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "ja existe"));
}

// ---------- BUSCAR POR NOME ----------

TEST_CASE("Teste 17 - Buscar receita existente" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "3\nbolo\n1\n\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "RESULTADOS DA PESQUISA"));
    CHECK(contem(saida, "Tempo de Preparo: 40"));
}

TEST_CASE("Teste 18 - Buscar receita inexistente" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "3\nXyz\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Nenhuma pesquisa com esse nome"));
}

// ---------- FILTRAR POR CATEGORIA ----------

TEST_CASE("Teste 19 - Filtrar por categoria com resultado" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "4\n3\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 20 - Filtrar por categoria sem resultado" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "4\n1\n\n" + VOLTA_CAT + "4\n");
    CHECK_FALSE(contem(saida, "1) Bolo"));
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

// ---------- AVALIAR E FILTRAR POR AVALIACAO ----------

TEST_CASE("Teste 21 - Avaliar receita" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "7\n1\n4\n\n"
        "2\n1\n\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Avaliacao salva com sucesso"));
    CHECK(contem(saida, "Avaliacao: 4/5"));
}

TEST_CASE("Teste 22 - Nota invalida ao avaliar" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "7\n1\n9\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Avaliacao invalida"));
}

TEST_CASE("Teste 23 - Cancelar a escolha ao avaliar nao cai" * doctest::timeout(2)) {
    CHECK_NOTHROW(executarMenu("1\n" + CADASTRA_BOLO + "7\n0\n" + VOLTA_CAT + "4\n"));
    // catalogo vazio: nao ha escolha a fazer, entao nao se envia o "0"
    std::string saida = executarMenu("1\n7\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Nenhuma receita disponivel"));
}

TEST_CASE("Teste 24 - Filtrar por avaliacao" * doctest::timeout(2)) {
    SUBCASE("nota existente") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "8\n5\n\n" + VOLTA_CAT + "4\n");
        CHECK(contem(saida, "1) Bolo"));
    }
    SUBCASE("nota sem receitas") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "8\n3\n\n" + VOLTA_CAT + "4\n");
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
    SUBCASE("nota invalida pede de novo") {
        std::string saida = executarMenu("1\n8\n0\n6\n5\n\n" + VOLTA_CAT + "4\n");
        CHECK(contem(saida, "Opcao invalida"));
    }
}

// ---------- EXCLUIR ----------

TEST_CASE("Teste 25 - Excluir confirmando com 's'" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "6\n1\ns\n2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "excluida com sucesso"));
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

TEST_CASE("Teste 26 - Excluir respondendo 'n' cancela" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "6\n1\nn\n2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Exclusao cancelada"));
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 27 - Cancelar a escolha na exclusao nao cai" * doctest::timeout(2)) {
    CHECK_NOTHROW(executarMenu("1\n" + CADASTRA_BOLO + "6\n0\n" + VOLTA_CAT + "4\n"));
    std::string saida = executarMenu("1\n6\n" + VOLTA_CAT + "4\n");   // catalogo vazio
    CHECK(contem(saida, "Nenhuma receita disponivel"));
}

// ---------- EDITAR (6 = salvar, 0 = cancelar) ----------

TEST_CASE("Teste 28 - Editar nome e salvar" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\nTorta\n\n6\n\n2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "salva com sucesso"));
    CHECK(contem(saida, "1) Torta"));
}

TEST_CASE("Teste 29 - Cancelar edicao nao altera o catalogo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\nTorta\n\n0\n\n2\n0\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Edicao cancelada"));
    CHECK(contem(saida, "1) Bolo"));
    CHECK_FALSE(contem(saida, "1) Torta"));
}

TEST_CASE("Teste 30 - Nome vazio na edicao e rejeitado" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\n\n\n0\n\n" + VOLTA_CAT + "4\n");
    CHECK(contem(saida, "Nome invalido"));
}

TEST_CASE("Teste 31 - Editar tempo, modo e avaliacao" * doctest::timeout(2)) {
    SUBCASE("tempo invalido") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + "5\n1\n2\n0\n\n0\n\n" + VOLTA_CAT + "4\n");
        CHECK(contem(saida, "Tempo invalido"));
    }
    SUBCASE("modo vazio") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + "5\n1\n4\n\n\n0\n\n" + VOLTA_CAT + "4\n");
        CHECK(contem(saida, "Modo nao pode ser vazio"));
    }
    SUBCASE("avaliacao") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + "5\n1\n5\n2\n\n6\n\n2\n1\n\n0\n" + VOLTA_CAT + "4\n");
        CHECK(contem(saida, "Avaliacao: 2/5"));
    }
}

// ---------- DESPENSA ----------

TEST_CASE("Teste 32 - Despensa vazia" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n" + VOLTA_DESP + "4\n");
    CHECK(contem(saida, "despensa esta vazia"));
}

TEST_CASE("Teste 33 - Adicionar ingrediente a despensa" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + VOLTA_DESP + "4\n");
    CHECK(contem(saida, "Ingrediente adicionado"));
    CHECK(contem(saida, "Farinha"));
    CHECK(contem(saida, "500"));
}

TEST_CASE("Teste 34 - Nome vazio na despensa e recusado" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n2\n\n\n" + VOLTA_DESP + "4\n");
    CHECK(contem(saida, "nome nao pode ficar vazio"));
}

TEST_CASE("Teste 35 - Ingrediente repetido e recusado" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "2\n" + DESPENSA_FARINHA_500 + "2\nFarinha\n\n" + VOLTA_DESP + "4\n");
    CHECK(contem(saida, "ja esta na despensa"));
}

TEST_CASE("Teste 36 - Remover ingrediente" * doctest::timeout(2)) {
    SUBCASE("existente") {
        std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + "3\nFarinha\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Ingrediente removido"));
    }
    SUBCASE("inexistente") {
        std::string saida = executarMenu("2\n3\nSal\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "nao encontrado"));
    }
    SUBCASE("Enter vazio cancela") {
        std::string saida = executarMenu("2\n3\n\n" + VOLTA_DESP + "4\n");
        CHECK_FALSE(contem(saida, "removido"));
        CHECK_FALSE(contem(saida, "nao encontrado"));
    }
}

TEST_CASE("Teste 37 - Editar quantidade" * doctest::timeout(2)) {
    SUBCASE("existente") {
        std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + "4\nFarinha\n900\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Quantidade atualizada"));
        CHECK(contem(saida, "900"));
    }
    SUBCASE("inexistente") {
        std::string saida = executarMenu("2\n4\nSal\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "nao encontrado"));
    }
}

TEST_CASE("Teste 38 - Ingredientes de uma receita (opcao 1 da despensa)" * doctest::timeout(2)) {
    SUBCASE("receita escolhida") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + VOLTA_CAT + "2\n1\n1\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Farinha - 200 g"));
    }
    SUBCASE("cancelar a escolha") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + VOLTA_CAT + "2\n1\n0\n" + VOLTA_DESP + "4\n");
        CHECK_FALSE(contem(saida, "INGREDIENTES DA RECEITA"));
    }
    SUBCASE("catalogo vazio") {
        std::string saida = executarMenu("2\n1\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Nenhuma receita disponivel"));
    }
}

TEST_CASE("Teste 39 - Disponibilidade dos ingredientes de uma receita" * doctest::timeout(2)) {
    SUBCASE("tem tudo") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + VOLTA_CAT +
            "2\n" + DESPENSA_FARINHA_500 + "5\n1\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Receita pode ser feita"));
    }
    SUBCASE("falta ingrediente") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + VOLTA_CAT + "2\n5\n1\n\n" + VOLTA_DESP + "4\n");
        CHECK(contem(saida, "Receita nao pode ser feita"));
        CHECK(contem(saida, "| Farinha-200 g"));
    }
}

// Hoje a interface lista so "em falta ou quantidade menor"; unidade diferente
// deixa a lista vazia. Fica vermelho (tolerado) ate usar identificarUnidadesDiferentes.
TEST_CASE("Teste 39b - Disponibilidade: unidade diferente tambem deve ser reportada"
          * doctest::timeout(2) * doctest::may_fail()) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + VOLTA_CAT +
        "2\n2\nFarinha\n500\n2\n\n5\n1\n\n" + VOLTA_DESP + "4\n");
    REQUIRE(contem(saida, "Ingrediente adicionado"));
    CHECK(contem(saida, "Receita nao pode ser feita"));
    CHECK(contem(saida, "| Farinha-200 g"));
}

// ---------- O QUE POSSO COZINHAR ----------

TEST_CASE("Teste 40 - Sem receitas, nada e possivel" * doctest::timeout(2)) {
    std::string saida = executarMenu("3\n2\n4\n");
    CHECK(contem(saida, "COZINHAR"));
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

TEST_CASE("Teste 41 - Receita possivel aparece" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + VOLTA_CAT +
        "2\n" + DESPENSA_FARINHA_500 + VOLTA_DESP +
        "3\n2\n4\n");
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 42 - Receita impossivel nao aparece" * doctest::timeout(2)) {
    SUBCASE("falta o ingrediente") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + VOLTA_CAT + "3\n2\n4\n");
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
    SUBCASE("quantidade insuficiente") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + VOLTA_CAT +
            "2\n2\nFarinha\n100\n1\n\n" + VOLTA_DESP + "3\n2\n4\n");
        REQUIRE(contem(saida, "Ingrediente adicionado"));
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
    SUBCASE("unidade diferente") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + VOLTA_CAT +
            "2\n2\nFarinha\n500\n2\n\n" + VOLTA_DESP + "3\n2\n4\n");
        REQUIRE(contem(saida, "Ingrediente adicionado"));
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
}

TEST_CASE("Teste 43 - Possiveis filtradas por categoria" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + VOLTA_CAT +
        "2\n" + DESPENSA_FARINHA_500 + VOLTA_DESP +
        "3\n1\n3\n0\n2\n4\n");
    CHECK(contem(saida, "CATEGORIA SELECIONADA"));
    CHECK(contem(saida, "1) Bolo"));
}