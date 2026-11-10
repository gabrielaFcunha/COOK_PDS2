
#include "doctest.h"
#include "ingredientes.hpp"
#include <string>
#include <stdexcept>

// TESTES DO MODULO DE INGREDIENTES

TEST_CASE("Teste 01: Ingrediente - Inicializacao e acesso") {
    Ingredientes ingrediente("Tomate", 50, Unidade::Grama);

    CHECK(ingrediente.getNome() == "Tomate");
    CHECK(ingrediente.getQuantidade() == 50);
    CHECK(ingrediente.getUnidade() == Unidade::Grama);
}

TEST_CASE("Teste 02: Ingrediente - Atualizacao de quantidade") {
    Ingredientes ingrediente("Tomate", 50, Unidade::Grama);

    CHECK(ingrediente.editar("Tomate", 100, Unidade::Grama) == true);
    CHECK(ingrediente.getQuantidade() == 100);
}

TEST_CASE("Teste 03: Ingrediente - Nome vazio") {
    CHECK_THROWS_AS(
        Ingredientes("", 50, Unidade::Grama),
        std::invalid_argument
    );
}

TEST_CASE("Teste 04: Quantidades invalidas") {
    Ingredientes ingrediente("Tomate", 50, Unidade::Grama);

    CHECK(ingrediente.editar("Tomate", -10, Unidade::Grama) == false);
    CHECK(ingrediente.getQuantidade() == 50);
}

TEST_CASE("Teste 05: Ingrediente - Quantidade inicial zero") {
    CHECK_THROWS_AS(
        Ingredientes("Tomate", 0, Unidade::Grama),
        std::invalid_argument
    );
}

TEST_CASE("Teste 06: Ingrediente - Edicao valida") {
    Ingredientes ingrediente("Tomate", 50, Unidade::Grama);

    CHECK(ingrediente.editar("Cebola", 100, Unidade::Unidade) == true);

    CHECK(ingrediente.getNome() == "Cebola");
    CHECK(ingrediente.getQuantidade() == 100);
    CHECK(ingrediente.getUnidade() == Unidade::Unidade);
}

TEST_CASE("Teste 07: Ingrediente - Edicao com nome vazio") {
    Ingredientes ingrediente("Tomate", 50, Unidade::Grama);

    CHECK(ingrediente.editar("", 100, Unidade::Grama) == false);

    CHECK(ingrediente.getNome() == "Tomate");
    CHECK(ingrediente.getQuantidade() == 50);
    CHECK(ingrediente.getUnidade() == Unidade::Grama);
}
