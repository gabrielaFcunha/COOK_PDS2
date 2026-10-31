#include "doctest.h"
#include "despensa.hpp"
#include <fstream>
#include <list>
#include <string>


TEST_CASE("Teste 01: Despensa - Estado inicial") {
    Despensa despensa;
    CHECK(despensa.possuiIngrediente("Tomate") == false);
    CHECK(despensa.possuiIngrediente("") == false);
    CHECK(despensa.getIngredientesDisponiveis().empty() == true);
}

TEST_CASE("Teste 02: Despensa - Adicionar ingrediente válido") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    CHECK(despensa.adicionarIngrediente(tomate) == true);
    CHECK(despensa.possuiIngrediente("Tomate") == true);
    CHECK(despensa.possuiIngrediente("tomate") == true);
    CHECK(despensa.possuiIngrediente("Cebola") == false);
    CHECK(despensa.possuiIngrediente("") == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);

    CHECK(despensa.adicionarIngrediente(tomate) == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);
}

TEST_CASE("Teste 03: Despensa - Adicionar ingrediente inválido") {
    Despensa despensa;
    Ingredientes invalido("", 2, Unidade::Unidade);
    Ingredientes invalido2("Cebola", -1, Unidade::Unidade);
    Ingredientes invalido3("Cenoura", 0, Unidade::Unidade);
    Ingredientes invalido4("Alface", 1, static_cast<Unidade>(-1)); // Unidade inválida
    CHECK(despensa.adicionarIngrediente(invalido) == false);
    CHECK(despensa.adicionarIngrediente(invalido2) == false);
    CHECK(despensa.adicionarIngrediente(invalido3) == false);
    CHECK(despensa.adicionarIngrediente(invalido4) == false);
    CHECK(despensa.possuiIngrediente("") == false);
    CHECK(despensa.possuiIngrediente("Cebola") == false);
    CHECK(despensa.possuiIngrediente("Cenoura") == false);
    CHECK(despensa.possuiIngrediente("Alface") == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 0);

    CHECK(despensa.removerIngrediente("") == false);
    CHECK(despensa.removerIngrediente("Cebola") == false);
    CHECK(despensa.removerIngrediente("Cenoura") == false);
    CHECK(despensa.removerIngrediente("Alface") == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 0);

    Ingredientes alfafa("Alfafa", 1, Unidade::Unidade);
    CHECK(despensa.adicionarIngrediente(alfafa) == true);
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);
}

TEST_CASE("Teste 04: Despensa - Remover ingrediente") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(tomate);
    despensa.adicionarIngrediente(cebola);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2);

    CHECK(despensa.removerIngrediente("Tomate") == true);
    CHECK(despensa.possuiIngrediente("Tomate") == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);

    CHECK(despensa.removerIngrediente("Cebola") == true);
    CHECK(despensa.possuiIngrediente("Cebola") == false);
    CHECK(despensa.getIngredientesDisponiveis().size() == 0);

    CHECK(despensa.removerIngrediente("Alface") == false);
}

TEST_CASE("Teste 05 - Despensa - Ordem se mantém"){
    Despensa despensa;
    Ingredientes ingrediente1("Tomate", 2, Unidade::Unidade);
    Ingredientes ingrediente2("Cebola", 3, Unidade::Unidade);
    Ingredientes ingrediente3("Alface", 1, Unidade::Unidade);
    despensa.adicionarIngrediente(ingrediente1);
    despensa.adicionarIngrediente(ingrediente2);
    despensa.adicionarIngrediente(ingrediente3);
    auto ingredientes = despensa.getIngredientesDisponiveis();
    auto it = ingredientes.begin();
    CHECK(it->getNome() == "Tomate");
    ++it;
    CHECK(it->getNome() == "Cebola");
    ++it;
    CHECK(it->getNome() == "Alface");

    despensa.removerIngrediente("Cebola");
    ingredientes = despensa.getIngredientesDisponiveis();
    CHECK(ingredientes.size() == 2);
    it = ingredientes.begin();
    CHECK(it->getNome() == "Tomate");
    ++it;
    CHECK(it->getNome() == "Alface");
}

TEST_CASE("Teste 06 - Despensa - Atualizar quantidade") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.atualizarQuantidade("Tomate", 5) == true);
    auto ingredientes = despensa.getIngredientesDisponiveis();
    auto it = ingredientes.begin();
    CHECK(it->getQuantidade() == 5);

    CHECK(despensa.atualizarQuantidade("Tomate", -1) == false);
    CHECK(it->getQuantidade() == 5);
    CHECK(despensa.atualizarQuantidade("Cebola", 3) == false);
}

TEST_CASE("Teste 07 - Despensa - Consultar ingrediente") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.possuiIngrediente("Tomate") == true);
    CHECK(despensa.possuiIngrediente("tomate") == true);
    CHECK(despensa.possuiIngrediente("Cebola") == false);
    CHECK(despensa.possuiIngrediente("") == false);

    CHECK(despensa.getIngredientesDisponiveis().size() == 1);
}

TEST_CASE("Teste 08 - Salvamento e carregamento") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(tomate);
    despensa.adicionarIngrediente(cebola);

    CHECK(despensa.salvarEmArquivo() == true);

    Despensa novaDespensa;
    CHECK(novaDespensa.carregarDeArquivo() == true);
    CHECK(novaDespensa.possuiIngrediente("Tomate") == true);
    CHECK(novaDespensa.possuiIngrediente("Cebola") == true);
    CHECK(novaDespensa.getIngredientesDisponiveis().size() == 2);
}

TEST_CASE("Teste 09 - Despensa - Carregar arquivo inexistente") {
    Despensa despensa;
    CHECK(despensa.carregarDeArquivo() == false);
}

TEST_CASE("Teste 10 - Despensa - Carregar descarta o conteúdo anterior") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(cebola);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2);
    CHECK(despensa.salvarEmArquivo() == true);
    despensa.removerIngrediente("Cebola");
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);
    CHECK(despensa.carregarDeArquivo() == true);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2); // Deve conter apenas os ingredientes do arquivo
}

TEST_CASE("Teste 11 - Despensa - Carregar arquivo com linha em branco") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(cebola);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2);
    CHECK(despensa.salvarEmArquivo() == true);

    // Adiciona uma linha em branco ao arquivo
    std::ofstream arquivo("despensa.txt", std::ios::app);
    arquivo << std::endl;
    arquivo.close();

    Despensa novaDespensa;
    CHECK(novaDespensa.carregarDeArquivo() == true);
    CHECK(novaDespensa.getIngredientesDisponiveis().size() == 2); // Deve conter apenas os ingredientes válidos
}

TEST_CASE("Teste 12 - Despensa - Carregar arquivo com ingrediente incompleto") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(cebola);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2);
    CHECK(despensa.salvarEmArquivo() == true);

    // Adiciona um ingrediente incompleto ao arquivo
    std::ofstream arquivo("despensa.txt", std::ios::app);
    arquivo << "Alface;5" << std::endl; // Falta a unidade
    arquivo.close();

    Despensa novaDespensa;
    CHECK(novaDespensa.carregarDeArquivo() == true);
    CHECK(novaDespensa.getIngredientesDisponiveis().size() == 2); // Deve conter apenas os ingredientes válidos
}

TEST_CASE("Teste 13 - Despensa - Carregar arquivo com fim de linha ou ';'"){
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(cebola);
    despensa.adicionarIngrediente(tomate);
    CHECK(despensa.getIngredientesDisponiveis().size() == 2);
    CHECK(despensa.salvarEmArquivo() == true);

    // Adiciona um ingrediente com fim de linha ou ';' ao arquivo
    std::ofstream arquivo("despensa.txt", std::ios::app);
    arquivo << "Alface;5;un;" << std::endl; // Fim de linha extra
    arquivo.close();

    Despensa novaDespensa;
    CHECK(novaDespensa.carregarDeArquivo() == true);
    CHECK(novaDespensa.getIngredientesDisponiveis().size() == 3); // Deve conter todos os ingredientes válidos
}

TEST_CASE("Teste 14 - Despensa - Adicionar, remover e procurar ignoram letras maiúsculas e acentos") {
    Despensa despensa;
    Ingredientes tomate("Tomate", 2, Unidade::Unidade);
    Ingredientes cebola("Cebola", 3, Unidade::Unidade);
    despensa.adicionarIngrediente(cebola);
    despensa.adicionarIngrediente(tomate);

    CHECK(despensa.possuiIngrediente("tômate") == true);
    CHECK(despensa.possuiIngrediente("Cebôla") == true);
    CHECK(despensa.possuiIngrediente("CEBOLA") == true);
    CHECK(despensa.possuiIngrediente("cEbOlA") == true);
    CHECK(despensa.possuiIngrediente("Álface") == false);

    CHECK(despensa.removerIngrediente("TOMÁTE") == true);
    CHECK(despensa.possuiIngrediente("Tomate") == false);
}