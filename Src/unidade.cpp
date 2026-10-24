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