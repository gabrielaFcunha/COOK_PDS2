#include "doctest.h"
#include "unidade.hpp"

// Testes da função unidadeToString()

TEST_CASE("Conversao de Unidade para string") {
    CHECK(unidadeToString(Unidade::Grama) == "g");
    CHECK(unidadeToString(Unidade::Mililitro) == "mL");
    CHECK(unidadeToString(Unidade::Unidade) == "un");
}

// Testes da função converterUnidade()

TEST_CASE("Conversao de gramas") {
    float quantidade = 250.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "g", unidade));
    CHECK(quantidade == doctest::Approx(250.0));
    CHECK(unidade == Unidade::Grama);
}

TEST_CASE("Conversao de quilogramas para gramas") {
    float quantidade = 2.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "kg", unidade));
    CHECK(quantidade == doctest::Approx(2000.0));
    CHECK(unidade == Unidade::Grama);
}

TEST_CASE("Conversao de mililitros") {
    float quantidade = 250.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "mL", unidade));
    CHECK(quantidade == doctest::Approx(250.0));
    CHECK(unidade == Unidade::Mililitro);
}

TEST_CASE("Conversao de mililitros em letras minusculas") {
    float quantidade = 250.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "ml", unidade));
    CHECK(quantidade == doctest::Approx(250.0));
    CHECK(unidade == Unidade::Mililitro);
}

TEST_CASE("Conversao de litros para mililitros") {
    float quantidade = 2.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "L", unidade));
    CHECK(quantidade == doctest::Approx(2000.0));
    CHECK(unidade == Unidade::Mililitro);
}

TEST_CASE("Conversao de litros em letras minusculas") {
    float quantidade = 2.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "l", unidade));
    CHECK(quantidade == doctest::Approx(2000.0));
    CHECK(unidade == Unidade::Mililitro);
}

TEST_CASE("Conversao de unidades") {
    float quantidade = 3.0;
    Unidade unidade;

    CHECK(converterUnidade(quantidade, "un", unidade));
    CHECK(quantidade == doctest::Approx(3.0));
    CHECK(unidade == Unidade::Unidade);
}

TEST_CASE("Unidade invalida") {
    float quantidade = 10.0;
    Unidade unidade;

    CHECK_FALSE(converterUnidade(quantidade, "xyz", unidade));
}

TEST_CASE("Quantidade igual a zero") {
    float quantidade = 0.0;
    Unidade unidade;

    CHECK_FALSE(converterUnidade(quantidade, "g", unidade));
}

TEST_CASE("Quantidade negativa") {
    float quantidade = -5.0;
    Unidade unidade;

    CHECK_FALSE(converterUnidade(quantidade, "g", unidade));
}