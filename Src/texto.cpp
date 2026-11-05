#include "texto.hpp"
#include <string>

/**
 * @brief Converte todas as letras de uma string para minúsculas.
 * @param texto A string a ser convertida.
 * @return A string convertida para minúsculas.
 */
std::string paraMinusculas(std::string texto){
    for(size_t i = 0; i < texto.size(); i++){
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
std::string tirarAcentosParaOrdenar(std::string texto){
    // Letras maiúsculas
    substituir(texto, "Á", "a");
    substituir(texto, "À", "a");
    substituir(texto, "Â", "a");
    substituir(texto, "Ã", "a");
    substituir(texto, "É", "e");
    substituir(texto, "Ê", "e");
    substituir(texto, "Í", "i");
    substituir(texto, "Ó", "o");
    substituir(texto, "Ô", "o");
    substituir(texto, "Õ", "o");
    substituir(texto, "Ú", "u");
    substituir(texto, "Ü", "u");
    substituir(texto, "Ç", "c");

    // Letras minúsculas
    texto = paraMinusculas(texto);

    substituir(texto, "á", "a");
    substituir(texto, "à", "a");
    substituir(texto, "â", "a");
    substituir(texto, "ã", "a");
    substituir(texto, "é", "e");
    substituir(texto, "ê", "e");
    substituir(texto, "í", "i");
    substituir(texto, "ó", "o");
    substituir(texto, "ô", "o");
    substituir(texto, "õ", "o");
    substituir(texto, "ú", "u");
    substituir(texto, "ü", "u");
    substituir(texto, "ç", "c");

    return texto;
}

std::string normalizar(const std::string& texto){
    std::string textoNormalizado = tirarAcentosParaOrdenar(texto);

    size_t inicio = textoNormalizado.find_first_not_of(' '); // acha a primeira posição que NÃO é espaço
    size_t fim = textoNormalizado.find_last_not_of(' '); // acha a última posição que NÃO é espaço

    if (inicio == std::string::npos) {
        return "";   // string vazia ou só de espaços
    }
    return textoNormalizado.substr(inicio, fim - inicio + 1);
}