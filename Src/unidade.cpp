#include "unidade.hpp"
#include <string>

std::string unidadeToString(Unidade unidade){
    if (unidade == Unidade::Grama){
        return "g";
    }
    if (unidade == Unidade::Mililitro){
        return "mL";
    }
    return "un";
}
bool converterUnidade(float& quantidade, const std::string& unidadeTexto,
     Unidade& unidade) {
    if (unidadeTexto == "g") {
        unidade = Unidade::Grama;

    } else if (unidadeTexto == "kg") {
        quantidade *= 1000; // Converte de kg para g
        unidade = Unidade::Grama;

    } else if (unidadeTexto == "mL" || unidadeTexto == "ml") {
        unidade = Unidade::Mililitro;

    } else if (unidadeTexto == "L"|| unidadeTexto == "l") {
        quantidade *= 1000; // Converte de L para mL
        unidade = Unidade::Mililitro;

    }else if (unidadeTexto == "un") {
        unidade = Unidade::Unidade;
    }
    else {
        return false; // Unidade inválida
    }
    if(quantidade <= 0){
        return false; // Quantidade inválida
    }
    return true; // Conversão bem-sucedida
}