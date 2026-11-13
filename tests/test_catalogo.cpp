#include "doctest.h"
#include "catalogo.hpp"
#include "receita.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>

TEST_CASE("Teste 01 - Catálogo novo"){
    Catalogo catalogo;
    CHECK(catalogo.pesquisarPorNome("Qualquer coisa").empty());
    //ordenar devolve vazio 
    CHECK(catalogo.ordenar(CriterioOrdenacao::NOME).empty());
    CHECK(catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO).empty());
    CHECK(catalogo.ordenar(CriterioOrdenacao::CATEGORIA).empty());
    //remover receita de catálogo vazio retorna false
    CHECK(catalogo.removerReceita("Qualquer coisa") == false);
}

TEST_CASE("Teste 02 - Adicionar receitas"){
    //adicionar receitas aumenta o tamanho do vetor
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.getReceitas().size() == 1);
    catalogo.adicionarReceita(receita2);
    CHECK(catalogo.getReceitas().size() == 2);
}

TEST_CASE("Teste 03 - A receita adicionada é preservada"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.getReceitas()[0].getTempo() == 60);
    CHECK(catalogo.getReceitas()[0].getModo() == "Misture os ingredientes e asse.");
    CHECK(catalogo.getReceitas()[0].getCategoria() == Categoria::Sobremesa);
}

TEST_CASE("Teste 04 - Ordem de inserção mantida"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.getReceitas()[1].getNome() == "Salada");
}

TEST_CASE("Teste 05 - Adicionar mantém os ingredientess"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Ingredientes ingrediente1("Farinha", 200, Unidade::Grama);
    Ingredientes ingrediente2("Ovos", 3, Unidade::Unidade);
    receita1.adicionarIngrediente(ingrediente1);
    receita1.adicionarIngrediente(ingrediente2);
    catalogo.adicionarReceita(receita1);

    CHECK(catalogo.getReceitas()[0].getIngredientes().size() == 2);
    CHECK(catalogo.getReceitas()[0].getIngredientes()[0].getNome() == "Farinha");
    CHECK(catalogo.getReceitas()[0].getIngredientes()[1].getNome() == "Ovos");
}

TEST_CASE("Teste 06 - Nome duplicado rejeitado"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Chocolate", 45, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 07 - Adicionar receita com nome duplicado e diferente caixa"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("bolo de chocolate", 45, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(!catalogo.adicionarReceita(receita2));

    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 08 - Remover receita existente"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == true);
    CHECK(catalogo.getReceitas().empty());
}

TEST_CASE("Teste 09 - Remover receita inexistente"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.removerReceita("Salada") == false);
    CHECK(catalogo.getReceitas().size() == 1);
}

TEST_CASE("Teste 10 - Remover a mesma receita duas vezes"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == true);
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == false);
    CHECK(catalogo.getReceitas().empty());
}

TEST_CASE("Teste 11 - Remover ignora maiúsculas e acentos"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.removerReceita("bolo de chocolate") == true);
    CHECK(catalogo.getReceitas().empty());

    Receita receita2("Pão de Queijo", 30, "Misture os ingredientes e asse.", Categoria::Lanche);
    catalogo.adicionarReceita(receita2);
    CHECK(catalogo.removerReceita("Pao de Queijo") == true);
    CHECK(catalogo.getReceitas().empty());
}

TEST_CASE("Teste 12 - Remoção não altera outras receitas nem sua ordem"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    CHECK(catalogo.removerReceita("Salada") == true);
    CHECK(catalogo.getReceitas().size() == 2);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.getReceitas()[1].getNome() == "Sopa");
}

TEST_CASE("Teste 13 - Casos de borda (primeira, do meio e última receita)"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    // Remover a primeira receita
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == true);
    REQUIRE(catalogo.getReceitas().size() == 2);
    CHECK(catalogo.getReceitas()[0].getNome() == "Salada");
    CHECK(catalogo.getReceitas()[1].getNome() == "Sopa");

    // Remover a do meio (agora a primeira)
    CHECK(catalogo.removerReceita("Salada") == true);
    REQUIRE(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Sopa");

    // Remover a última receita
    CHECK(catalogo.removerReceita("Sopa") == true);
    CHECK(catalogo.getReceitas().empty());

    //Remover somente a última de um catálogo cheio
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    CHECK(catalogo.removerReceita("Salada") == true);
    REQUIRE(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");

}

TEST_CASE("Teste 14 - Pesquisar por nome completo") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 15 - Pesquisar por parte do nome") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita3("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.pesquisarPorNome("Bolo");

    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado[1]->getNome() == "Bolo de Baunilha");
}

TEST_CASE("Teste 16 - Pesquisar por nome inexistente") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("Salada");

    CHECK(resultado.empty());
}

TEST_CASE("Teste 17 - Pesquisar por trecho no fim do nome") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Frutas");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0]->getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 18 - Pesquisar por nome ignora maiúsculas") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado1 = catalogo.pesquisarPorNome("bolo de chocolate");

    REQUIRE(resultado1.size() == 1);
    CHECK(resultado1[0]->getNome() == "Bolo de Chocolate");

    auto resultado2 = catalogo.pesquisarPorNome("SALADA DE FRUTAS");

    REQUIRE(resultado2.size() == 1);
    CHECK(resultado2[0]->getNome() == "Salada de Frutas");

    auto resultado3 = catalogo.pesquisarPorNome("saladA dE frutAs");

    REQUIRE(resultado3.size() == 1);
    CHECK(resultado3[0]->getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 19 - Pesquisar por nome ignora acentos") {
    Catalogo catalogo;

    catalogo.adicionarReceita(Receita("Salada de Frutas", 15, "x", Categoria::Entrada));
    catalogo.adicionarReceita(Receita("Pão de Queijo", 30, "x", Categoria::Lanche));

    auto resultado1 = catalogo.pesquisarPorNome("SALÁDA DE FRUTAS");

    REQUIRE(resultado1.size() == 1);
    CHECK(resultado1[0]->getNome() == "Salada de Frutas");

    auto resultado2 = catalogo.pesquisarPorNome("pao de queijo");

    REQUIRE(resultado2.size() == 1);
    CHECK(resultado2[0]->getNome() == "Pão de Queijo");
}

TEST_CASE("Teste 20 - Pesquisar retorna várias receitas") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita3("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.pesquisarPorNome("Bolo");

    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado[1]->getNome() == "Bolo de Baunilha");
}

TEST_CASE("Teste 21 - Nome vazio devolve todas as receitas") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("");

    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado[1]->getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 22 - Resultado da pesquisa aponta para as receitas originais") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");

    // O ponteiro aponta para a receita original do catálogo.
    CHECK(resultado[0] == &catalogo.getReceitas()[0]);

    auto resultado2 = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado2.size() == 1);
    CHECK(resultado2[0] == &catalogo.getReceitas()[0]);
}

TEST_CASE("Teste 23 - Avaliar receitas resultantes de pesquisas acessa as originais") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado[0] == &catalogo.getReceitas()[0]);

    auto resultado2 = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado2.size() == 1);
    CHECK(resultado2[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado2[0]->getAvaliacao() == catalogo.getReceitas()[0].getAvaliacao());
}

TEST_CASE("Teste 24 - Pesquisa não permite modificar as receitas originais") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado[0] == &catalogo.getReceitas()[0]);

    // O ponteiro é const: permite consultar, mas não modificar a receita.
    auto resultado2 = catalogo.pesquisarPorNome("Bolo de Chocolate");

    REQUIRE(resultado2.size() == 1);
    CHECK(resultado2[0]->getNome() == "Bolo de Chocolate");
    CHECK(resultado2[0]->getIngredientes().empty());
}

TEST_CASE("Teste 24 - Ordenar por nome"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.ordenar(CriterioOrdenacao::NOME);
    CHECK(resultado.size() == 3);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado[1].getNome() == "Salada de Frutas");
    CHECK(resultado[2].getNome() == "Sopa");

    //ordenar por nome deve ignorar letras maiúsculas
    Receita receita4("bolo de baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita4);
    auto resultado2 = catalogo.ordenar(CriterioOrdenacao::NOME);
    CHECK(resultado2.size() == 4);
    CHECK(resultado2[0].getNome() == "bolo de baunilha");
    CHECK(resultado2[1].getNome() == "Bolo de Chocolate");
    CHECK(resultado2[2].getNome() == "Salada de Frutas");
    CHECK(resultado2[3].getNome() == "Sopa");

    //deve ignorar acentos
    Receita receita5("Sálada de Alface", 20, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita6("Éclair", 40, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita5);
    catalogo.adicionarReceita(receita6);
    auto resultado3 = catalogo.ordenar(CriterioOrdenacao::NOME);
    CHECK(resultado3.size() == 6);
    CHECK(resultado3[0].getNome() == "bolo de baunilha");
    CHECK(resultado3[1].getNome() == "Bolo de Chocolate");
    CHECK(resultado3[2].getNome() == "Éclair");
    CHECK(resultado3[3].getNome() == "Sálada de Alface");
    CHECK(resultado3[4].getNome() == "Salada de Frutas");
    CHECK(resultado3[5].getNome() == "Sopa");
}

TEST_CASE("Teste 25 - Ordenar um catálogo com um único elemento"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.ordenar(CriterioOrdenacao::NOME);
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 26 - Ordenar um catálogo vazio"){
    Catalogo catalogo;

    auto resultado = catalogo.ordenar(CriterioOrdenacao::NOME);
    CHECK(resultado.empty());
}

TEST_CASE("Teste 27 - Ordenar pelos diferentes critérios não altera o vetor original"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultadoNome = catalogo.ordenar(CriterioOrdenacao::NOME);
    auto resultadoTempo = catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO);
    auto resultadoCategoria = catalogo.ordenar(CriterioOrdenacao::CATEGORIA);

    // O vetor original não deve ser alterado
    CHECK(catalogo.getReceitas().size() == 3);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.getReceitas()[1].getNome() == "Salada de Frutas");
    CHECK(catalogo.getReceitas()[2].getNome() == "Sopa");
}

TEST_CASE("Teste 28 - Ordenar por tempo crescente de preparo"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO);
    CHECK(resultado.size() == 3);
    CHECK(resultado[0].getNome() == "Salada de Frutas");
    CHECK(resultado[1].getNome() == "Sopa");
    CHECK(resultado[2].getNome() == "Bolo de Chocolate");

    //tempo zero entra normalmente

    Receita receita4("Receita Rápida", 0, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita4);
    auto resultado2 = catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO);
    CHECK(resultado2.size() == 4);
    CHECK(resultado2[0].getNome() == "Receita Rápida");
    CHECK(resultado2[1].getNome() == "Salada de Frutas");
    CHECK(resultado2[2].getNome() == "Sopa");
    CHECK(resultado2[3].getNome() == "Bolo de Chocolate");

    //para tempos iguais, a ordem alfabética desempata
    Receita receita5("Sopa de Legumes", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita5);
    auto resultado3 = catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO);
    CHECK(resultado3.size() == 5);
    CHECK(resultado3[0].getNome() == "Receita Rápida");
    CHECK(resultado3[1].getNome() == "Salada de Frutas");
    CHECK(resultado3[2].getNome() == "Sopa");
    CHECK(resultado3[3].getNome() == "Sopa de Legumes");
    CHECK(resultado3[4].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 29 - Ordenar por categoria"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    Receita receita4("Sanduíche", 10, "Monte o sanduíche.", Categoria::Lanche);
    Receita receita5("Suco de Laranja", 5, "Esprema as laranjas.", Categoria::Bebida);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);
    catalogo.adicionarReceita(receita4);
    catalogo.adicionarReceita(receita5);
 //resultado deve seguir a ordem do ENUM: Entrada -> Pr.Princ. -> Sobremesa -> Lanche -> Bebida
    auto resultado = catalogo.ordenar(CriterioOrdenacao::CATEGORIA);
    CHECK(resultado.size() == 5);
    CHECK(resultado[0].getCategoria() == Categoria::Entrada);
    CHECK(resultado[1].getCategoria() == Categoria::PratoPrincipal);
    CHECK(resultado[2].getCategoria() == Categoria::Sobremesa);
    CHECK(resultado[3].getCategoria() == Categoria::Lanche);
    CHECK(resultado[4].getCategoria() == Categoria::Bebida);

    //para categorias iguais, a ordem alfabética desempata
    Receita receita6("Salada de Alface", 10, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita6);
    auto resultado2 = catalogo.ordenar(CriterioOrdenacao::CATEGORIA);
    CHECK(resultado2.size() == 6);
    CHECK(resultado2[0].getNome() == "Salada de Alface");
    CHECK(resultado2[1].getNome() == "Salada de Frutas");
    CHECK(resultado2[2].getNome() == "Sopa");
    CHECK(resultado2[3].getNome() == "Bolo de Chocolate");
    CHECK(resultado2[4].getNome() == "Sanduíche");
    CHECK(resultado2[5].getNome() == "Suco de Laranja");
}

TEST_CASE("Teste 30 - Consistência de Ordenar"){
    //O resultado tem o mesmo tamanho e receitas que o original, só muda a ordem
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultadoNome = catalogo.ordenar(CriterioOrdenacao::NOME);
    auto resultadoTempo = catalogo.ordenar(CriterioOrdenacao::TEMPO_PREPARO);
    auto resultadoCategoria = catalogo.ordenar(CriterioOrdenacao::CATEGORIA);

    CHECK(resultadoNome.size() == catalogo.getReceitas().size());
    CHECK(resultadoTempo.size() == catalogo.getReceitas().size());
    CHECK(resultadoCategoria.size() == catalogo.getReceitas().size());

    //verifica se todas as receitas do resultado estão no original
    for (const auto& receita : resultadoNome) {
        auto it = std::find_if(catalogo.getReceitas().begin(), catalogo.getReceitas().end(), [&](const Receita& r) {
            return r.getNome() == receita.getNome();
        });
        CHECK(it != catalogo.getReceitas().end());
    }
    for (const auto& receita : resultadoTempo) {
        auto it = std::find_if(catalogo.getReceitas().begin(), catalogo.getReceitas().end(), [&](const Receita& r) {
            return r.getTempo() == receita.getTempo();
        });
        CHECK(it != catalogo.getReceitas().end());
    }
    for (const auto& receita : resultadoCategoria) {
        auto it = std::find_if(catalogo.getReceitas().begin(), catalogo.getReceitas().end(), [&](const Receita& r) {
            return r.getCategoria() == receita.getCategoria();
        });
        CHECK(it != catalogo.getReceitas().end());
    }
}

TEST_CASE("Teste 31 - Pesquisar ignora espaços desnecessários") {
    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado1 = catalogo.pesquisarPorNome("  Bolo de Chocolate  ");
    CHECK(resultado1.empty());

    auto resultado2 = catalogo.pesquisarPorNome("Bolo   de   Chocolate");
    CHECK(resultado2.empty());
}


TEST_CASE("Teste 32 - Salvar e carregar catálogo com receitas e ingredientes") {
    std::remove("receitas.txt");

    Catalogo catalogo;

    Receita receita1("Bolo de Chocolate", 60,
                     "Misture os ingredientes e asse.",
                     Categoria::Sobremesa);

    Ingredientes farinha("Farinha", 200, Unidade::Grama);
    Ingredientes ovos("Ovos", 3, Unidade::Unidade);

    receita1.adicionarIngrediente(farinha);
    receita1.adicionarIngrediente(ovos);
    receita1.avaliar(4);

    Receita receita2("Salada", 15,
                     "Misture os ingredientes.",
                     Categoria::Entrada);

    receita2.avaliar(5);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    // Salvar o catálogo
    CHECK(catalogo.salvarEmArquivo());

    // Carregar em um novo catálogo
    Catalogo novoCatalogo;
    CHECK(novoCatalogo.carregarDeArquivo());

    REQUIRE(novoCatalogo.getReceitas().size() == 2);

    // Verificar dados da primeira receita
    const Receita& carregada1 = novoCatalogo.getReceitas()[0];

    CHECK(carregada1.getNome() == "Bolo de Chocolate");
    CHECK(carregada1.getTempo() == 60);
    CHECK(carregada1.getModo() == "Misture os ingredientes e asse.");
    CHECK(carregada1.getCategoria() == Categoria::Sobremesa);
    CHECK(carregada1.getAvaliacao() == 4);

    // Verificar ingredientes
    REQUIRE(carregada1.getIngredientes().size() == 2);

    CHECK(carregada1.getIngredientes()[0].getNome() == "Farinha");
    CHECK(carregada1.getIngredientes()[0].getQuantidade() == 200);
    CHECK(carregada1.getIngredientes()[0].getUnidade() == Unidade::Grama);

    CHECK(carregada1.getIngredientes()[1].getNome() == "Ovos");
    CHECK(carregada1.getIngredientes()[1].getQuantidade() == 3);
    CHECK(carregada1.getIngredientes()[1].getUnidade() == Unidade::Unidade);

    // Verificar segunda receita
    const Receita& carregada2 = novoCatalogo.getReceitas()[1];

    CHECK(carregada2.getNome() == "Salada");
    CHECK(carregada2.getTempo() == 15);
    CHECK(carregada2.getCategoria() == Categoria::Entrada);
    CHECK(carregada2.getAvaliacao() == 5);

    std::remove("receitas.txt");
}


TEST_CASE("Teste 33 - Salvar e carregar catálogo vazio") {
    std::remove("receitas.txt");

    Catalogo catalogo;

    CHECK(catalogo.salvarEmArquivo());

    Catalogo novoCatalogo;

    CHECK(novoCatalogo.carregarDeArquivo());
    CHECK(novoCatalogo.getReceitas().empty());

    std::remove("receitas.txt");
}


TEST_CASE("Teste 34 - Carregar arquivo inexistente") {
    std::remove("receitas.txt");

    Catalogo catalogo;

    CHECK(catalogo.carregarDeArquivo() == false);
    CHECK(catalogo.getReceitas().empty());
}


TEST_CASE("Teste 35 - Carregar substitui receitas anteriores") {
    std::remove("receitas.txt");

    // Criar arquivo com uma receita
    Catalogo catalogoArquivo;

    Receita receitaArquivo("Bolo", 40,
                           "Misture e asse.",
                           Categoria::Sobremesa);

    catalogoArquivo.adicionarReceita(receitaArquivo);

    REQUIRE(catalogoArquivo.salvarEmArquivo());

    // Criar catálogo com outra receita
    Catalogo catalogoExistente;

    Receita receitaAntiga("Salada", 15,
                           "Misture tudo.",
                           Categoria::Entrada);

    catalogoExistente.adicionarReceita(receitaAntiga);

    // Carregar deve substituir o conteúdo anterior
    CHECK(catalogoExistente.carregarDeArquivo());

    REQUIRE(catalogoExistente.getReceitas().size() == 1);

    CHECK(catalogoExistente.getReceitas()[0].getNome() == "Bolo");

    std::remove("receitas.txt");
}

TEST_CASE("Teste 36 - Ordenar com criterio invalido") {
    Catalogo catalogo;

    Receita receita1("Bolo", 40, "Assar.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misturar.", Categoria::Entrada);

    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    CriterioOrdenacao criterioInvalido =
        static_cast<CriterioOrdenacao>(999);

    std::vector<Receita> resultado = catalogo.ordenar(criterioInvalido);

    CHECK(resultado.size() == 2);
}

TEST_CASE("Teste 37 - Falha ao salvar arquivo") {
    Catalogo catalogo;

    std::remove("receitas.txt");

    // Cria um diretório com o nome do arquivo esperado.
    int resultado = mkdir("receitas.txt", 0700);
    REQUIRE(resultado == 0);

    CHECK(catalogo.salvarEmArquivo() == false);

    // Remove o diretório criado.
    CHECK(rmdir("receitas.txt") == 0);
}

TEST_CASE("Teste 38 - Atualizar receita com indice invalido") {
    Catalogo catalogo;

    Receita receita("Bolo", 40, "Assar.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita);

    Receita modificada("Bolo novo", 50, "Assar novamente.", Categoria::Sobremesa);

    CHECK(catalogo.atualizarReceita(1, modificada) == false);
    CHECK(catalogo.atualizarReceita(100, modificada) == false);

    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo");
}

TEST_CASE("Teste 39 - Carregar receita com unidade invalida") {
    std::ofstream arquivo("receitas.txt");

    REQUIRE(arquivo.is_open());

    arquivo << "Receita teste;10;Modo de preparo;Entrada;4;1;"
            << "Ingrediente;2;UNIDADE_INVALIDA\n";

    arquivo.close();

    Catalogo catalogo;

    CHECK(catalogo.carregarDeArquivo() == true);

    REQUIRE(catalogo.getReceitas().size() == 1);

    // O ingrediente com unidade inválida deve ser ignorado.
    CHECK(catalogo.getReceitas()[0].getIngredientes().empty());

    std::remove("receitas.txt");
}

//TESTE DE FUNÇÕES FUTURAS
/*
TEST_CASE("Teste 32 - Editar receita resultante de pesquisa/ordenação")
TEST_CASE("Teste 33 - Favoritar receita resultante de pesquisa/ordenação")
TEST_CASE("Teste 34 - Salvar e carregar catálogo de um arquivo")
TEST_CASE("Teste 35 - Salvar e carregar receitas de um arquivo inexistente")
TEST_CASE("Teste 36 - Salvar e carregar receitas de um arquivo com formato inválido")
TEST_CASE("Teste 37 - Carregar descarta o conteúdo anterior")

SE A LÓGICA DE ADICIONAR/REMOVER MANIPULAR O CATÁLOGO RESULTANTE DE UMA PESQUISA, 
É NECESSÁRIO FAZER OS TESTES DISSO. MAS O MAIS SEGURO É QUE SÓ SEJA POSSÍVEL ADICIONAR RECEITAS AO
CATÁLOGO ORIGINAL.
*/