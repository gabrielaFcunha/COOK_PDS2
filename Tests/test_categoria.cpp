#include "doctest.h"
#include "categoria.hpp"
#include <stdexcept>
#include <string>

TEST_CASE("Teste 01: Categoria - toString de cada categoria") {
    CHECK(categoriaToString(Categoria::Entrada) == "Entrada");
    CHECK(categoriaToString(Categoria::PratoPrincipal) == "Prato Principal");
    CHECK(categoriaToString(Categoria::Sobremesa) == "Sobremesa");
    CHECK(categoriaToString(Categoria::Lanche) == "Lanche");
    CHECK(categoriaToString(Categoria::Bebida) == "Bebida");
}

TEST_CASE("Teste 02: Categoria - toString devolve texto diferente para cada categoria") {
    CHECK(categoriaToString(Categoria::Entrada) != categoriaToString(Categoria::Bebida));
    CHECK(categoriaToString(Categoria::Lanche) != categoriaToString(Categoria::Sobremesa));
}

TEST_CASE("Teste 03: Categoria - stringToCategoria de cada categoria") {
    CHECK(stringToCategoria("Entrada") == Categoria::Entrada);
    CHECK(stringToCategoria("Prato Principal") == Categoria::PratoPrincipal);  // ajuste se necessário
    CHECK(stringToCategoria("Sobremesa") == Categoria::Sobremesa);
    CHECK(stringToCategoria("Lanche") == Categoria::Lanche);
    CHECK(stringToCategoria("Bebida") == Categoria::Bebida);
}

TEST_CASE("Teste 04: Categoria - Ida e volta (toString e stringToCategoria)") {
    Categoria todas[] = { Categoria::Entrada, Categoria::PratoPrincipal,
                          Categoria::Sobremesa, Categoria::Lanche, Categoria::Bebida };
    for (Categoria c : todas) {
        CHECK(stringToCategoria(categoriaToString(c)) == c);
    }
}

TEST_CASE("Teste 05: Categoria - stringToCategoria ignora maiúsculas" * doctest::may_fail()) {
    CHECK(stringToCategoria("SOBREMESA") == Categoria::Sobremesa);
    CHECK(stringToCategoria("bebida") == Categoria::Bebida);
}

TEST_CASE("Teste 06: Categoria - String inválida lança exceção" * doctest::may_fail()) {
    // exceção (std::invalid_argument) ou outro
    CHECK_THROWS_AS(stringToCategoria("xyz"), std::invalid_argument);
    CHECK_THROWS_AS(stringToCategoria(""), std::invalid_argument);
}