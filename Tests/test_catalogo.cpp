#include "doctest.h"
#include "catalogo.hpp"
#include "receita.hpp"
#include <string>
#include <vector>
#include <algorithm>

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
    CHECK(catalogo.getReceitas().size() == 2);
    CHECK(catalogo.getReceitas()[0].getNome() == "Salada");
    CHECK(catalogo.getReceitas()[1].getNome() == "Sopa");

    // Remover a do meio (agora a primeira)
    CHECK(catalogo.removerReceita("Salada") == true);
    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Sopa");

    // Remover a última receita
    CHECK(catalogo.removerReceita("Sopa") == true);
    CHECK(catalogo.getReceitas().empty());

    //Remover somente a última de um catálogo cheio
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    CHECK(catalogo.removerReceita("Salada") == true);
    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");

    //Se houvessem nomes duplicados, removeria só a primeira
    catalogo.adicionarReceita(receita1);
    CHECK(catalogo.getReceitas().size() == 2);
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == true);
    CHECK(catalogo.getReceitas().size() == 1);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.removerReceita("Bolo de Chocolate") == true);
    CHECK(catalogo.getReceitas().empty());
}

TEST_CASE("Teste 14 - Pesquisar por nome completo"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Bolo de Chocolate");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 15 - Pesquisar por parte do nome"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita3("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado.size() == 2);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado[1].getNome() == "Bolo de Baunilha");
}

TEST_CASE("Teste 16 - Pesquisar por nome inexistente"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("Salada");
    CHECK(resultado.empty());
}

TEST_CASE("Teste 17 - Pesquisar por trecho no fim do nome"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Frutas");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 18 - Pesquisar por nome com caixa e acentos"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("bolo de chocolate");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    resultado = catalogo.pesquisarPorNome("salada de frutas");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Salada de Frutas");

    resultado = catalogo.pesquisarPorNome("SALADA DE FRUTAS");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Salada de Frutas");

    resultado = catalogo.pesquisarPorNome("SALÁDA DE FRUTAS");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Salada de Frutas");

    resultado = catalogo.pesquisarPorNome("saladA dE frutAs");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 19 - Pesquisar retorna várias receitas"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita3("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado.size() == 2);
    //resultado mantém a ordem de inserção
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado[1].getNome() == "Bolo de Baunilha");
}

TEST_CASE("Teste 20 - Nome vazio devolve todas as receitas"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("");
    CHECK(resultado.size() == 2);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado[1].getNome() == "Salada de Frutas");
}

TEST_CASE("Teste 21 - Alterar o resultado da pesquisa não altera o catálogo"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    // Alterar o resultado da pesquisa
    resultado[0] = Receita("Sopa", 30, "Cozinhe os ingredientes.", Categoria::PratoPrincipal);

    // O catálogo não deve ser alterado
    auto resultado2 = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado2.size() == 1);
    CHECK(resultado2[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 22 - Avaliar receitas resultadas de pesquisas avalia as originais"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    // Avaliar a receita resultante da pesquisa
    resultado[0].avaliar(5);

    // O catálogo deve refletir a avaliação
    auto resultado2 = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado2.size() == 1);
    CHECK(resultado2[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado2[0].getAvaliacao() == 5);
}

TEST_CASE("Teste 23 - Editar receita resultante da pesquisa edita a original"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    // Adicionar ingrediente à receita resultante da pesquisa
    Ingredientes ingrediente("Baunilha", 1, Unidade::Unidade);
    resultado[0].adicionarIngrediente(ingrediente); 
    // O catálogo deve refletir a edição
    auto resultado2 = catalogo.pesquisarPorNome("Bolo");
    CHECK(resultado2.size() == 1);
    CHECK(resultado2[0].getNome() == "Bolo de Chocolate");
    CHECK(resultado2[0].getIngredientes().size() == 1);
    CHECK(resultado2[0].getIngredientes()[0].getNome() == "Baunilha");
    CHECK(resultado2[0].getIngredientes()[0].getQuantidade() == 1);
    CHECK(resultado2[0].getIngredientes()[0].getUnidade() == Unidade::Unidade);
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

TEST_CASE("Teste 31 - Pesquisar ignora espaços desnecessários"){
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = catalogo.pesquisarPorNome("  Bolo de Chocolate  ");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    resultado = catalogo.pesquisarPorNome("Bolo   de   Chocolate");
    CHECK(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
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