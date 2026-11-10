
#include "doctest.h"
#include "categoria.hpp"

// Testes da conversão de Categoria para string
TEST_CASE("Categoria - Converter enum para string") {

    CHECK(categoriaToString(Categoria::Entrada) == "Entrada");

    CHECK(categoriaToString(Categoria::PratoPrincipal) == "PratoPrincipal");

    CHECK(categoriaToString(Categoria::Sobremesa) == "Sobremesa");

    CHECK(categoriaToString(Categoria::Lanche) == "Lanche");

    CHECK(categoriaToString(Categoria::Bebida) == "Bebida");
}

// Testes da conversão de string para Categoria
TEST_CASE("Categoria - Converter string para enum") {

    CHECK(stringToCategoria("Entrada") == Categoria::Entrada);

    CHECK(stringToCategoria("PratoPrincipal") == Categoria::PratoPrincipal);

    CHECK(stringToCategoria("Sobremesa") == Categoria::Sobremesa);

    CHECK(stringToCategoria("Lanche") == Categoria::Lanche);

    CHECK(stringToCategoria("Bebida") == Categoria::Bebida);
}

// Teste do comportamento para categorias inválidas
TEST_CASE("Categoria - Valores inválidos") {

    // String inválida deve retornar Entrada
    CHECK(stringToCategoria("CategoriaInexistente") == Categoria::Entrada);

    CHECK(stringToCategoria("") == Categoria::Entrada);

    // Valor inválido do enum deve retornar string vazia
    Categoria invalida = static_cast<Categoria>(999);

    CHECK(categoriaToString(invalida) == "");
}
