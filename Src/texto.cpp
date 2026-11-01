#include "texto.hpp"
#include <string>

std::string paraMinusculas(std::string texto){
    for(int i = 0; i < texto.size(); i++){
        if (texto[i] >= 'A' && texto[i] <= 'Z'){
            texto[i] = texto[i] + 32;
        }
    }
    return texto;
}

/**
 * @brief em C++, pesquisei que a ordenação padrão
 * de strings com acentos podem aparecer em ordens 
 * inesperadas, dificultando a organização em ordem
 * alfabética. Para isso, pensamos em criar uma função
 * que remove os acentos apenas na hora de comparar
 * os textos e sem alterar o nome exibido ao usuário.
 * @note deve ser chamada em catalogo ou interface
 * na hora de fazer a ordenação alfabetica das receitas.
 * Também precisei fazer uma função substituir() para auxiliar
 * esse processo.
 */
void substituir(std::string& texto, const std::string& letraAntiga, const std::string& letraNova){
    std::size_t posicao = 0;
    while((posicao = texto.find(letraAntiga, posicao)) != std::string::npos){
        texto.replace(posicao, letraAntiga.size(), letraNova);
        posicao += letraNova.size();
    }
}
/*
como são muitos casos de acento, priorizei substituir apenas os que são mais normais 
na primeira letra do nome, que é a mais importante para a ordenação em ordem alfabética.
*/
void tirarAcentosParaOrdenar(std::string texto){
    texto = paraMinusculas(texto);
    substituir(texto, "á", "a");
    substituir(texto, "é", "e");
    substituir(texto, "ó", "o");
    substituir(texto, "ú", "u");
}