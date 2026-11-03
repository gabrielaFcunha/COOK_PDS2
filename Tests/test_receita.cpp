#include "doctest.h"
#include "receita.hpp"
#include "ingredientes.hpp"
#include "categoria.hpp"
#include <stdexcept>
#include <string>
#include <vector>

TEST_CASE("Teste 01 - Criar uma receita e verificar seus atributos") {
    std::vector<Ingredientes> ingredientes = { Ingredientes("Farinha", 200, Unidade::Grama), Ingredientes("Ovos", 3, Unidade::Unidade) };
    Receita receita("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa, ingredientes);

    CHECK(receita.getNome() == "Bolo de Chocolate");
    CHECK(receita.getTempo() == 60);
    CHECK(receita.getModo() == "Misture os ingredientes e asse.");
    CHECK(receita.getCategoria() == Categoria::Sobremesa);
    CHECK(receita.getIngredientes().size() == 2);
}

TEST_CASE("Teste 02 - Construção sem ingredientes") {
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);

    CHECK(receita.getNome() == "Salada");
    CHECK(receita.getTempo() == 15);
    CHECK(receita.getModo() == "Misture os ingredientes.");
    CHECK(receita.getCategoria() == Categoria::Entrada);
    CHECK(receita.getIngredientes().empty());
}

TEST_CASE("Teste 03 - Construir com ingredientes iniciais mantém a ordem"){
    std::vector<Ingredientes> ingredientes = { Ingredientes("Farinha", 200, Unidade::Grama), Ingredientes("Ovos", 3, Unidade::Unidade) };
    Receita receita("Bolo de Chocolate", 60, "Misture os ingredientes e asse.", Categoria::Sobremesa, ingredientes);

    CHECK(receita.getIngredientes()[0].getNome() == "Farinha");
    CHECK(receita.getIngredientes()[1].getNome() == "Ovos");
}

TEST_CASE("Teste 04 - Enum é armazenado corretamente") {
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    CHECK(receita.getCategoria() == Categoria::Entrada);
}

TEST_CASE("Teste 05 - Parâmetros vazios"){
    Receita receita("", 0, "", Categoria::Entrada);
    CHECK(receita.getNome() == "");
    CHECK(receita.getTempo() == 0);
    CHECK(receita.getModo() == "");
    CHECK(receita.getCategoria() == Categoria::Entrada);
}

TEST_CASE("Teste 06 - Modo de preparo com várias linhas") {
    std::string modoPreparo = "1. Misture os ingredientes.\n2. Asse por 30 minutos.\n3. Deixe esfriar.";
    Receita receita("Bolo", 45, modoPreparo, Categoria::Sobremesa);

    CHECK(receita.getModo() == modoPreparo);
}

TEST_CASE("Teste 07 - Adicionar ingrediente"){
    //Adicionar aumenta o tamanho em 1
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente("Tomate", 2, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente);
    CHECK(receita.getIngredientes().size() == 1);
    CHECK(receita.getIngredientes()[0].getNome() == "Tomate");

    //O ingrediente adicionado mantém nome, quantidade e unidade
    CHECK(receita.getIngredientes()[0].getQuantidade() == 2);
    CHECK(receita.getIngredientes()[0].getUnidade() == Unidade::Unidade);

    //Ingredientes ficam na ordem em que foram adicionados
    Ingredientes ingrediente2("Alface", 100, Unidade::Grama);
    receita.adicionarIngrediente(ingrediente2);
    CHECK(receita.getIngredientes().size() == 2);
    CHECK(receita.getIngredientes()[1].getNome() == "Alface");

    //Adicionar ingrediente com mesmo nome
    Ingredientes ingrediente3("Tomate", 3, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente3);
    CHECK(receita.getIngredientes().size() == 3);
    CHECK(receita.getIngredientes()[2].getNome() == "Tomate");
}

TEST_CASE("Teste 08 - Remover ingrediente") {
    //remover ingrediente existente
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente("Tomate", 2, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente);
    bool removed = receita.removerIngrediente("Tomate");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().empty());

    //remover ingrediente não existente
    removed = receita.removerIngrediente("Alface");
    CHECK(removed == false);

    //remover de lista vazia
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == false);

    //remover o mesmo ingrediente duas vezes
    receita.adicionarIngrediente(ingrediente);
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == true);
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == false);

    //remover não afeta outros ingredientes nem a ordem deles
    Ingredientes ingrediente2("Alface", 100, Unidade::Grama);
    receita.adicionarIngrediente(ingrediente);
    receita.adicionarIngrediente(ingrediente2);
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().size() == 1);
    CHECK(receita.getIngredientes()[0].getNome() == "Alface");

    //remover não diferencia maiúsculas de minúsculas
    Ingredientes ingrediente3("tomate", 3, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente3);
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().size() == 1);
    CHECK(receita.getIngredientes()[0].getNome() == "Alface");

    //remover ingrediente com nome parcialmente igual
    Ingredientes ingrediente4("TomateSeco", 50, Unidade::Grama);
    receita.adicionarIngrediente(ingrediente4);
    removed = receita.removerIngrediente("Tomate");
    CHECK(removed == false);
    CHECK(receita.getIngredientes().size() == 2);

    //remover ingredientes de mesmo nome
    Ingredientes ingrediente5("Alface", 50, Unidade::Grama);
    receita.adicionarIngrediente(ingrediente5);
    removed = receita.removerIngrediente("Alface");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().size() == 2);
}

TEST_CASE("Teste 09 - Manipular cópias não altera a original"){
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente("Tomate", 2, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente);

    Receita copia = receita; // Cópia da receita
    copia.adicionarIngrediente(Ingredientes("Alface", 100, Unidade::Grama));
    copia.removerIngrediente("Tomate");

    // A cópia foi alterada
    CHECK(copia.getIngredientes().size() == 1);
    CHECK(copia.getIngredientes()[0].getNome() == "Alface");

    // A original permanece inalterada
    CHECK(receita.getIngredientes().size() == 1);
    CHECK(receita.getIngredientes()[0].getNome() == "Tomate");
}

TEST_CASE("Teste 10 - Argumentos inválidos"){
    //nome vazio, tempo negativo, modo de preparo vazio lançam std::invalid_argument
    CHECK_THROWS_AS(Receita("", -10, "", Categoria::Entrada), std::invalid_argument);
    CHECK_THROWS_AS(Receita("Salada", -5, "Misture os ingredientes.", Categoria::Entrada), std::invalid_argument);
    CHECK_THROWS_AS(Receita("Salada", 15, "", Categoria::Entrada), std::invalid_argument);
}

TEST_CASE("Teste 11 - Tempo 0"){
    Receita receita2("Salada", 0, "Misture os ingredientes.", Categoria::Entrada);
    CHECK(receita2.getTempo() == 0);
    CHECK(receita2.getNome() == "Salada");
    CHECK(receita2.getModo() == "Misture os ingredientes.");
}

TEST_CASE("Teste 12 - Remover ingrediente ignora caixa e acentos"){
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente("Tomate", 2, Unidade::Unidade);
    Ingredientes ingrediente2("Alface", 100, Unidade::Grama);
    Ingredientes ingrediente3("Cebola", 1, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente);
    receita.adicionarIngrediente(ingrediente2);
    receita.adicionarIngrediente(ingrediente3);

    // Remover com caixa diferente
    bool removed = receita.removerIngrediente("tomate");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().size() == 2);

    // Remover com acento diferente
    Ingredientes ingrediente4("Pão", 1, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente4);
    removed = receita.removerIngrediente("Pao");
    CHECK(removed == true);
    CHECK(receita.getIngredientes().size() == 2);
}

TEST_CASE("Teste 13 - adicionar ingrediente repetido não duplica"){
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente("Tomate", 2, Unidade::Unidade);
    receita.adicionarIngrediente(ingrediente);
    receita.adicionarIngrediente(ingrediente);

    CHECK(receita.getIngredientes().size() == 1);
    CHECK(receita.getIngredientes()[0].getNome() == "Tomate");
    CHECK(receita.getIngredientes()[0].getQuantidade() == 2);
}

TEST_CASE("Teste 14 - Ingredientes de mesmo nome e unidades distintas"){
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    Ingredientes ingrediente1("Tomate", 2, Unidade::Unidade);
    Ingredientes ingrediente2("Tomate", 100, Unidade::Grama);
    receita.adicionarIngrediente(ingrediente1);
    receita.adicionarIngrediente(ingrediente2);

    CHECK(receita.getIngredientes().size() == 2);
    CHECK(receita.getIngredientes()[0].getNome() == "Tomate");
    CHECK(receita.getIngredientes()[0].getQuantidade() == 2);
    CHECK(receita.getIngredientes()[0].getUnidade() == Unidade::Unidade);

    CHECK(receita.getIngredientes()[1].getNome() == "Tomate");
    CHECK(receita.getIngredientes()[1].getQuantidade() == 100);
    CHECK(receita.getIngredientes()[1].getUnidade() == Unidade::Grama);
}

TEST_CASE("Teste 15 - Avaliar uma receita"){
    Receita receita("Salada", 15, "Misture os ingredientes.", Categoria::Entrada);
    
    // Avaliar com valor válido
    bool avaliou = receita.avaliar(4);
    CHECK(avaliou == true);
    CHECK(receita.getAvaliacao() == 4);

    // Avaliar com valor inválido (negativo)
    avaliou = receita.avaliar(-1);
    CHECK(avaliou == false);
    CHECK(receita.getAvaliacao() == 4); // Avaliação não deve mudar

    // Avaliar com valor inválido (maior que 5)
    avaliou = receita.avaliar(6);
    CHECK(avaliou == false);
    CHECK(receita.getAvaliacao() == 4); // Avaliação não deve mudar
}