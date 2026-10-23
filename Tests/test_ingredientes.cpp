#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ingredientes.hpp"
#include <string>

// TESTES DO MODULO DE INGREDIENTES

TEST_CASE("Teste 01: Ingrediente - Inicializacao padrao e acesso") {
    Ingredientes ingrediente("Tomate", 50, "gramas");
    CHECK(ingrediente.getNome() == "Tomate");
    CHECK(ingrediente.getQuantidade() == 50);
    CHECK(ingrediente.getUnidade() == "gramas");
}

TEST_CASE("Teste 02: Ingrediente - Atualizacao de quantidade") {
    Ingredientes ingrediente("Tomate", 50, "gramas");
    ingrediente.editar("Tomate", 100, "gramas");
    CHECK(ingrediente.getQuantidade() == 100);
}

TEST_CASE("Teste 03: Ingrediente - Nome vazio") {
    Ingredientes ingrediente("", 50, "gramas");
    CHECK(ingrediente.getNome() == "");
}

TEST_CASE("Teste 04: Quantidades inválidas") {
    Ingredientes ingrediente("Tomate", 50, "gramas");
    ingrediente.cadastrar("Tomate", 50, "gramas");
    ingrediente.editar("Tomate", -10, "gramas");
    
    // Complete com o valor esperado para esse teste
    CHECK(ingrediente.getQuantidade() == 50);
}

TEST_CASE("Teste 05: Cadastro inválido") {
    Ingredientes ingrediente("Tomate", 0, "gramas");
    ingrediente.cadastrar("Tomate", 0, "gramas");
    // Complete com o valor esperado para esse teste
    CHECK(ingrediente.cadastrar("Tomate", 0, "gramas") == false);
}
