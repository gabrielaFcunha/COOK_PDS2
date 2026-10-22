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