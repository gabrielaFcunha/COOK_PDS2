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
    Interface interface(false); // não toca em disco
    interface.menu();
    return io.out.str();
}

static bool contem(const std::string& texto, const std::string& trecho) {
    return texto.find(trecho) != std::string::npos;
}


//testes do menu prncipal
TEST_CASE("Teste 01 - Opção 4 encerra o menu" * doctest::timeout(2)) {
    std::string saida = executarMenu("4\n");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Catalogo de Receitas"));
    CHECK(contem(saida, "Sair"));
}

TEST_CASE("Teste 02 - Opção inválida mostra erro e volta ao menu" * doctest::timeout(2)) {
    std::string saida = executarMenu("9\n4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
}

TEST_CASE("Teste 03: - Texto no lugar de número é inválido" * doctest::timeout(2)) {
    std::string saida = executarMenu("abc\n\n4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
}

TEST_CASE("Teste 04 - Fim de entrada não trava" * doctest::timeout(2)) {
    std::string saida = executarMenu("");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 05 - Fim de entrada no meio do menu não trava" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 06 - Fim de entrada no meio do menu não trava (opção inválida)" * doctest::timeout(2)) {
    std::string saida = executarMenu("9\n");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Fim da entrada detectado"));
}

TEST_CASE("Teste 07 - Fim de entrada no meio do menu não trava (opção inválida com texto)" * doctest::timeout(2)) {
    std::string saida = executarMenu("abc\n");
    CHECK(contem(saida, "COOK++"));
    CHECK(contem(saida, "Fim da entrada detectado"));
}

//TESTES COM ENTRADA SIMULADA

//entradas reutilizáveis:
static const std::string CADASTRA_BOLO =
    "1\n"                    // cadastrar receita
    "Bolo\n40\n3\n"          // nome, tempo, categoria 3 = Sobremesa
    "Misture e asse.\n"      // modo de preparo
    "Farinha\n200\n1\n"      // ingrediente: 200, unidade 1 = gramas
    "fim\n";

// Estando no submenu da despensa: adiciona Farinha 500 g
static const std::string DESPENSA_FARINHA_500 =
    "2\nFarinha\n500\n1\n\n";   // opção 2, nome, qtd, unidade, Enter da pausa

// ---------- EXIBIR CATÁLOGO ----------

TEST_CASE("Teste 08 - Catálogo vazio" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n2\n0\n7\n4\n");
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

TEST_CASE("Teste 09 - Cadastrar e exibir receita" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n0\n7\n4\n");
    CHECK(contem(saida, "1) Bolo"));
    CHECK(contem(saida, "40 minutos"));
}

TEST_CASE("Teste 10 - Detalhes da receita" * doctest::timeout(2)) {
    // exibir, escolher 1, Enter da pausa, voltar
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n1\n\n0\n7\n4\n");
    CHECK(contem(saida, "Tempo de Preparo: 40"));
    CHECK(contem(saida, "Farinha"));
    CHECK(contem(saida, "200"));
    CHECK(contem(saida, "Misture e asse."));
}

TEST_CASE("Teste 11 - Receita sem ingredientes" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nSopa\n20\n1\nFerva.\nfim\n"   // cadastra sem ingredientes
        "2\n1\n\n0\n7\n4\n");
    CHECK(contem(saida, "nenhum ingrediente cadastrado"));
}

TEST_CASE("Teste 12 - Número fora do intervalo no catálogo" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "2\n5\n\n0\n7\n4\n");
    CHECK(contem(saida, "OPCAO INVALIDA"));
}

// ---------- CADASTRAR RECEITA ----------

TEST_CASE("Teste 13 - Quantidade inválida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n3\nMisture.\n"
        "Ovo\nabc\n0\n3\n3\n"                 // texto, zero, depois 3
        "fim\n7\n4\n");
    CHECK(contem(saida, "Valor invalido"));
}

TEST_CASE("Teste 14 - Categoria inválida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n1\nBolo\n40\n9\n3\nMisture.\nfim\n7\n4\n");
    CHECK(contem(saida, "Opcao invalida"));
}

TEST_CASE("Teste 15 - Unidade inválida pede de novo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n1\nBolo\n40\n3\nMisture.\nOvo\n2\n9\n3\nfim\n7\n4\n");
    CHECK(contem(saida, "Opcao invalida"));
}

// ---------- FILTRAR POR CATEGORIA ----------

TEST_CASE("Teste 16 - Filtrar por categoria com resultado" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "4\n3\n7\n4\n");
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 17 - Filtrar por categoria sem resultado" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "4\n1\n7\n4\n");   // 1 = Entrada
    CHECK_FALSE(contem(saida, "1) Bolo"));
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

// ---------- EXCLUIR ----------

TEST_CASE("Teste 18 - Excluir confirmando com 's'" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "6\n1\ns\n2\n0\n7\n4\n");
    CHECK(contem(saida, "excluida com sucesso"));
    CHECK(contem(saida, "Nenhuma receita cadastrada ainda"));
}

TEST_CASE("Teste 19 - Excluir respondendo 'n' cancela" * doctest::timeout(2)) {
    std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "6\n1\nn\n2\n0\n7\n4\n");
    CHECK(contem(saida, "Exclusao cancelada"));
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 20 - Cancelar a escolha na exclusão não trava nem cai" * doctest::timeout(2)) {
    CHECK_NOTHROW(executarMenu("1\n" + CADASTRA_BOLO + "6\n0\n7\n4\n"));
    CHECK_NOTHROW(executarMenu("1\n6\n0\n7\n4\n"));   // catálogo vazio
}

// ---------- EDITAR ----------

TEST_CASE("Teste 21 - Editar nome e salvar" * doctest::timeout(2)) {
    // editar, escolher 1, alterar nome, Enter, salvar, Enter, depois exibir
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\nTorta\n\n5\n\n2\n0\n7\n4\n");
    CHECK(contem(saida, "salva com sucesso"));
    CHECK(contem(saida, "1) Torta"));
}

TEST_CASE("Teste 22 - Cancelar edição não altera o catálogo" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\nTorta\n\n0\n\n2\n0\n7\n4\n");
    CHECK(contem(saida, "Edicao cancelada"));
    CHECK(contem(saida, "1) Bolo"));
    CHECK_FALSE(contem(saida, "1) Torta"));
}

TEST_CASE("Teste 23 - Nome vazio na edição é rejeitado" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "5\n1\n1\n\n\n0\n\n7\n4\n");
    CHECK(contem(saida, "Nome invalido"));
}

// ---------- DESPENSA ----------

TEST_CASE("Teste 24 - Despensa vazia" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n5\n4\n");
    CHECK(contem(saida, "despensa esta vazia"));
}

TEST_CASE("Teste 25 - Adicionar ingrediente à despensa" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + "5\n4\n");
    CHECK(contem(saida, "Ingrediente adicionado"));
    CHECK(contem(saida, "Farinha"));      // reaparece na listagem do menu
    CHECK(contem(saida, "500"));
}

TEST_CASE("Teste 26 - Nome vazio na despensa é recusado" * doctest::timeout(2)) {
    std::string saida = executarMenu("2\n2\n\n\n5\n4\n");
    CHECK(contem(saida, "nome nao pode ficar vazio"));
}

TEST_CASE("Teste 27 - Ingrediente repetido é recusado" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "2\n" + DESPENSA_FARINHA_500 + "2\nFarinha\n\n5\n4\n");
    CHECK(contem(saida, "ja esta na despensa"));
}

TEST_CASE("Teste 28 - Remover ingrediente" * doctest::timeout(2)) {
    SUBCASE("existente") {
        std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + "3\nFarinha\n\n5\n4\n");
        CHECK(contem(saida, "Ingrediente removido"));
    }
    SUBCASE("inexistente") {
        std::string saida = executarMenu("2\n3\nSal\n\n5\n4\n");
        CHECK(contem(saida, "nao encontrado"));
    }
    SUBCASE("Enter vazio cancela") {
        std::string saida = executarMenu("2\n3\n\n5\n4\n");
        CHECK_FALSE(contem(saida, "removido"));
        CHECK_FALSE(contem(saida, "nao encontrado"));
    }
}

TEST_CASE("Teste 29 - Editar quantidade" * doctest::timeout(2)) {
    SUBCASE("existente") {
        std::string saida = executarMenu("2\n" + DESPENSA_FARINHA_500 + "4\nFarinha\n900\n\n5\n4\n");
        CHECK(contem(saida, "Quantidade atualizada"));
        CHECK(contem(saida, "900"));
    }
    SUBCASE("inexistente") {
        std::string saida = executarMenu("2\n4\nSal\n\n5\n4\n");
        CHECK(contem(saida, "nao encontrado"));
    }
}

// ---------- O QUE POSSO COZINHAR ----------

TEST_CASE("Teste 30 - Sem receitas, nada é possível" * doctest::timeout(2)) {
    std::string saida = executarMenu("3\n2\n4\n");
    CHECK(contem(saida, "COZINHAR"));
    CHECK_FALSE(contem(saida, "1) "));
}

TEST_CASE("Teste 31 - Receita possível aparece" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "7\n"            // cadastra Bolo (Farinha 200 g)
        "2\n" + DESPENSA_FARINHA_500 + "5\n"     // despensa com 500 g
        "3\n2\n4\n");
    CHECK(contem(saida, "1) Bolo"));
}

TEST_CASE("Teste 32 - Receita impossível não aparece" * doctest::timeout(2)) {
    SUBCASE("falta o ingrediente") {
        std::string saida = executarMenu("1\n" + CADASTRA_BOLO + "7\n3\n2\n4\n");
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
    SUBCASE("quantidade insuficiente") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + "7\n"
            "2\nFarinha\n100\n1\n\n5\n"
            "3\n2\n4\n");
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
    SUBCASE("unidade diferente") {
        std::string saida = executarMenu(
            "1\n" + CADASTRA_BOLO + "7\n"
            "2\nFarinha\n500\n2\n\n5\n"          // 2 = mililitros
            "3\n2\n4\n");
        CHECK_FALSE(contem(saida, "1) Bolo"));
    }
}

TEST_CASE("Teste 33 - Possíveis filtradas por categoria" * doctest::timeout(2)) {
    std::string saida = executarMenu(
        "1\n" + CADASTRA_BOLO + "7\n"
        "2\n" + DESPENSA_FARINHA_500 + "5\n"
        "3\n1\n3\n0\n2\n4\n");                   // filtrar, Sobremesa, voltar, sair
    CHECK(contem(saida, "CATEGORIA SELECIONADA"));
    CHECK(contem(saida, "1) Bolo"));
}