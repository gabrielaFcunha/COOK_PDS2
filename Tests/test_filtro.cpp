#include "doctest.h"
#include "filtro.hpp"

TEST_CASE("Teste 01 - Filtrar um catálogo vazio"){
    Filtro filtro;
    Catalogo catalogo;
    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    CHECK(resultado.size() == 0);
}

TEST_CASE("Teste 02 - Filtrar por categoria com receitas"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 03 - Filtrar por categoria sem resultados"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::PratoPrincipal);
    CHECK(resultado.size() == 0);
}

TEST_CASE("Teste 05 - Filtrar por categoria com resultados em ordem alfabética"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Baunilha", 50, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita3("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0].getNome() == "Bolo de Baunilha");
    CHECK(resultado[1].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 06 - Cada categoria filtra corretamente"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    Receita receita3("Suco de Laranja", 10, "Esprema as laranjas.", Categoria::Bebida);
    Receita receita4("Lasanha", 90, "Monte a lasanha e asse.", Categoria::PratoPrincipal);
    Receita receita5("Sanduíche Natural", 5, "Monte o sanduíche.", Categoria::Lanche);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);
    catalogo.adicionarReceita(receita3);
    catalogo.adicionarReceita(receita4);
    catalogo.adicionarReceita(receita5);

    auto resultadoSobremesa = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultadoSobremesa.size() == 1);
    CHECK(resultadoSobremesa[0].getNome() == "Bolo de Chocolate");

    auto resultadoEntrada = filtro.filtrarPorCategoria(catalogo, Categoria::Entrada);
    REQUIRE(resultadoEntrada.size() == 1);
    CHECK(resultadoEntrada[0].getNome() == "Salada de Frutas");

    auto resultadoBebida = filtro.filtrarPorCategoria(catalogo, Categoria::Bebida);
    REQUIRE(resultadoBebida.size() == 1);
    CHECK(resultadoBebida[0].getNome() == "Suco de Laranja");

    auto resultadoPratoPrincipal = filtro.filtrarPorCategoria(catalogo, Categoria::PratoPrincipal);
    REQUIRE(resultadoPratoPrincipal.size() == 1);
    CHECK(resultadoPratoPrincipal[0].getNome() == "Lasanha");

    auto resultadoLanche = filtro.filtrarPorCategoria(catalogo, Categoria::Lanche);
    REQUIRE(resultadoLanche.size() == 1);
    CHECK(resultadoLanche[0].getNome() == "Sanduíche Natural");
}

TEST_CASE("Teste 07 - Filtrar por categoria com receitas repetidas (se houverem)"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
}

TEST_CASE("Teste 08 - Alterações nos ingredientes dos resultados são espelhadas no vetor original"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    catalogo.adicionarReceita(receita1);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");

    resultado[0].adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    CHECK(resultado[0].getIngredientes().size() == 1);
    CHECK(catalogo.getReceitas()[0].getIngredientes().size() == 1);
}

TEST_CASE("Teste 09 - Filtrar não altera o catálogo original"){
    Filtro filtro;
    Catalogo catalogo;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    Receita receita2("Salada de Frutas", 15, "Misture os ingredientes.", Categoria::Entrada);
    catalogo.adicionarReceita(receita1);
    catalogo.adicionarReceita(receita2);

    auto resultado = filtro.filtrarPorCategoria(catalogo, Categoria::Sobremesa);
    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Bolo de Chocolate");
    // Verifica se o catálogo original ainda contém as receitas
    CHECK(catalogo.getReceitas().size() == 2);
    CHECK(catalogo.getReceitas()[0].getNome() == "Bolo de Chocolate");
    CHECK(catalogo.getReceitas()[1].getNome() == "Salada de Frutas");
}

//pesquisa por ingredientes faltando
TEST_CASE("Teste 10 - Receita sem ingredientes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0);
}

TEST_CASE("Teste 11 - Receita com ingredientes, despensa vazia"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 2);
}

TEST_CASE("Teste 12 - Receita com ingredientes, despensa com alguns ingredientes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama));
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 2); // Farinha está faltando e Chocolate está em quantidade insuficiente
}

TEST_CASE("Teste 13 - Receita com ingredientes, despensa com todos os ingredientes em quantidade suficiente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0); // Todos os ingredientes estão presentes em quantidade suficiente
}

TEST_CASE("Teste 14 - Ingrediente sobrando"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 300, Unidade::Grama)); // Quantidade maior que a necessária
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0); // Nenhum ingrediente está faltando
}

TEST_CASE("Teste 15 - Ingrediente com unidade diferente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 1); // Ingrediente está faltando devido à unidade diferente
}

TEST_CASE("Teste 16 - Ingrediente com unidade diferente e quantidade insuficiente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Mililitro)); // Unidade diferente e quantidade insuficiente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 1); // Ingrediente está faltando devido à unidade diferente e quantidade insuficiente
}

TEST_CASE("Teste 17 - Ingrediente com unidade diferente e quantidade suficiente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 300, Unidade::Mililitro)); // Unidade diferente mas quantidade suficiente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 1); // Ingrediente está faltando devido à unidade diferente
}

TEST_CASE("Teste 18 - Ordem da receita é preservada em ingredientes faltando"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Quantidade insuficiente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    REQUIRE(resultado.size() == 2); // Farinha está faltando e Chocolate está em quantidade insuficiente
    CHECK(resultado[0].getNome() == "Farinha"); // Ordem da receita é preservada
    CHECK(resultado[1].getNome() == "Chocolate");
}

TEST_CASE("Teste 19 - Ordem da receita é preservada em unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Mililitro)); // Unidade diferente
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    REQUIRE(resultado.size() == 1); // Farinha está com unidade diferente
    CHECK(resultado[0].getNome() == "Farinha"); // Ordem da receita é preservada
}

TEST_CASE("Teste 20 - Ingredientes com nomes diferentes não são considerados iguais"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Cacau", 200, Unidade::Grama)); // Nome diferente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 1); // Ingrediente está faltando devido ao nome diferente
}

TEST_CASE("Teste 21 - Ingredientes com nomes iguais mas unidades diferentes são considerados diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 1); // Ingrediente está com unidade diferente
}

TEST_CASE("Teste 22 - Letras maiusculas e acentos ignorados na receita e na despensa"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("chocolate", 200, Unidade::Grama)); // Nome em minúsculas
    receita1.adicionarIngrediente(Ingredientes("Pao", 1, Unidade::Unidade));
    despensa.adicionarIngrediente(Ingredientes("Pão", 1, Unidade::Unidade)); // Nome com acento
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0); // Ingrediente não está faltando
}

TEST_CASE("Teste 23 - Letras maiusculas e acentos ignorados na receita e na despensa para unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("chocolate", 200, Unidade::Mililitro)); // Nome em minúsculas e unidade diferente
    receita1.adicionarIngrediente(Ingredientes("Pao", 1, Unidade::Unidade));
    despensa.adicionarIngrediente(Ingredientes("Pão", 1, Unidade::Mililitro)); // Nome com acento e unidade diferente
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 2); // Ingredientes estão com unidades diferentes
}

TEST_CASE("Teste 24 - Receita e despensa não são alteradas pela pesquisa"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Quantidade insuficiente
    auto resultadoFaltando = filtro.identificarIngredientesFaltando(receita1, despensa);
    auto resultadoDiferentes = filtro.identificarUnidadesDiferentes(receita1, despensa);
    
    // Verifica se a receita e a despensa não foram alteradas
    CHECK(receita1.getIngredientes().size() == 1);
    CHECK(despensa.getIngredientesDisponiveis().size() == 1);
}

//Identificar unidades diferentes
TEST_CASE("Teste 25 - Receita sem ingredientes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 0);
}

TEST_CASE("Teste 26 - Despensa sem ingredientes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 0); // Nenhum ingrediente na despensa para comparar
}

TEST_CASE("Teste 27 - Mesma unidade em todos"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 0); // Nenhum ingrediente com unidade diferente
}

TEST_CASE("Teste 28 - Ingredientes com unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 1); // Apenas o Chocolate está com unidade diferente
    CHECK(resultado[0].getNome() == "Chocolate");
}

TEST_CASE("Teste 29 - Vários ingredientes com unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Leite", 500, Unidade::Mililitro));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Leite", 500, Unidade::Grama)); // Unidade diferente
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 2); // Chocolate e Leite estão com unidades diferentes
    //segue a ordem da receita
    CHECK(resultado[0].getNome() == "Chocolate");
    CHECK(resultado[1].getNome() == "Leite");
}

TEST_CASE("Teste 30 - Só os ingredientes diferentes aparecem (entre ingrdientes iguais, diferentes e ausentes)"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Leite", 500, Unidade::Mililitro));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama)); // Mesma unidade
    // Leite está ausente na despensa
    despensa.adicionarIngrediente(Ingredientes("Açúcar", 100, Unidade::Grama)); // Ingrediente não presente na receita
    auto resultado = filtro.identificarUnidadesDiferentes(receita1, despensa);
    CHECK(resultado.size() == 1); // Apenas o Chocolate está com unidade diferente
    CHECK(resultado[0].getNome() == "Chocolate");
}

TEST_CASE("Teste 31 - Comparação de nomes ignora maiúsculas"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("chocolate", 200, Unidade::Grama)); // Nome em minúsculas
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0); // Ingrediente não está faltando
}

TEST_CASE("Teste 32 - Comparação de nomes ignora acentos"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Pão", 1, Unidade::Unidade));
    despensa.adicionarIngrediente(Ingredientes("Pao", 1, Unidade::Unidade)); // Nome sem acento
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    CHECK(resultado.size() == 0); // Ingrediente não está faltando
}

TEST_CASE("Teste 33 - O item devolvido é o da receita"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("chocolate", 100, Unidade::Unidade)); // Unidade diferente
    auto resultado = filtro.identificarIngredientesFaltando(receita1, despensa);
    REQUIRE(resultado.size() == 1); // Ingrediente está faltando devido à quantidade insuficiente
    CHECK(resultado[0].getNome() == "Chocolate"); // O item devolvido é o da receita
    CHECK(resultado[0].getQuantidade() == 200); // Quantidade do item da receita
    CHECK(resultado[0].getUnidade() == Unidade::Grama); // Unidade do item da receita
}

//Comparação de ingredientes - receita pode ou não ser feita
TEST_CASE("Teste 34 - Receita sem ingredientes pode ser feita"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Água", 0, "Beba a água.", Categoria::Bebida);
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Receita sem ingredientes pode ser feita
}

TEST_CASE("Teste 35 - Receita com ingredientes, despensa vazia não pode ser feita"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Receita com ingredientes não pode ser feita
}

TEST_CASE("Teste 36 - Todos os ingredientes estão presentes na despensa com quantidades e unidades corretas"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Todos os ingredientes estão presentes com quantidades e unidades corretas
}

TEST_CASE("Teste 37 - Um ingrediente faltando"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Um ingrediente está faltando
}

TEST_CASE("Teste 38 - Um ingrediente com quantidade insuficiente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Quantidade insuficiente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Um ingrediente tem quantidade insuficiente
}

TEST_CASE("Teste 39 - Um ingrediente com unidade diferente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Um ingrediente tem unidade diferente
}

TEST_CASE("Teste 40 - Todos os ingredientes estão presentes, mas com unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Mililitro)); // Unidade diferente
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Mililitro)); // Unidade diferente
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Todos os ingredientes estão presentes, mas com unidades diferentes
}

TEST_CASE("Teste 41 - Quantidade exatamente igual à pedida"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama)); // Quantidade exatamente igual
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Ingrediente está presente com quantidade exatamente igual
}

TEST_CASE("Teste 42 - Quantidade maior do que a pedida"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 300, Unidade::Grama)); // Quantidade maior
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Ingrediente está presente com quantidade maior
}

TEST_CASE("Teste 43 - Despensa com ingredientes extras que não estão na receita"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama)); // Ingrediente necessário
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama)); // Ingrediente extra
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Receita pode ser feita mesmo com ingredientes extras na despensa
}

TEST_CASE("Teste 44 - Receita com ingredientes repetidos"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Ingrediente repetido
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 300, Unidade::Grama)); // Quantidade suficiente
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Receita pode ser feita mesmo com ingredientes repetidos
}

TEST_CASE("Teste 45 - Receita com ingredientes repetidos, mas despensa com quantidade insuficiente"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Ingrediente repetido
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 250, Unidade::Grama)); // Quantidade insuficiente
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Receita não pode ser feita devido à quantidade insuficiente
}

TEST_CASE("Teste 46 - Receita com ingredientes repetidos, mas despensa com unidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Ingrediente repetido
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 300, Unidade::Mililitro)); // Unidade diferente
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == false); // Receita não pode ser feita devido à unidade diferente
}

TEST_CASE("Teste 47 - A ordem dos ingredientes não importa"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Farinha", 300, Unidade::Grama));
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Receita pode ser feita mesmo com a ordem dos ingredientes diferente
}

TEST_CASE("Teste 48 - Comparação de nomes ignora maiúsculas e acentos"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Pão", 1, Unidade::Unidade));
    despensa.adicionarIngrediente(Ingredientes("pao", 1, Unidade::Unidade)); // Nome em minúsculas e sem acento
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Ingrediente está presente mesmo com diferenças de maiúsculas e acentos
}

TEST_CASE("Teste 49 - Despensa com ingredientes repetidos e quantidades diferentes"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 100, Unidade::Grama)); // Quantidade insuficiente
    despensa.adicionarIngrediente(Ingredientes("Chocolate", 150, Unidade::Grama)); // Quantidade suficiente
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Receita pode ser feita mesmo com ingredientes repetidos na despensa
}

TEST_CASE("Teste 50 - Nomes com espaços nas pontas"){
    Filtro filtro;
    Despensa despensa;
    Receita receita1("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa);
    receita1.adicionarIngrediente(Ingredientes("Chocolate", 200, Unidade::Grama));
    despensa.adicionarIngrediente(Ingredientes(" Chocolate ", 200, Unidade::Grama)); // Nome com espaços nas pontas
    auto resultado = filtro.compararIngredientes(receita1, despensa);
    CHECK(resultado == true); // Ingrediente está presente mesmo com espaços nas pontas
}