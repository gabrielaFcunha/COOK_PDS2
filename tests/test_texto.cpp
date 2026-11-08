#include "doctest.h"
#include "texto.hpp"
#include <string>

// TESTES DO MODULO DE TEXTO

TEST_CASE("Teste 01: Para minusculas") {
    std::string texto = "TOMATE";
    std::string resultado = paraMinusculas(texto);
    CHECK(resultado == "tomate");
    
}

TEST_CASE("Teste 02: Tirar os acentos") {
    std::string texto = "TÓMATE";
    std::string texto2 = "TÓMÁtê";
    std::string resultado = tirarAcentosParaOrdenar(texto);
    std::string resultado2 = tirarAcentosParaOrdenar(texto2);
    CHECK(resultado == "tomate");
    CHECK(resultado2 == "tomate");
}
