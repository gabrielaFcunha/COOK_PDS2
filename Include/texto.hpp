#ifndef TEXTO_HPP
#define TEXTO_HPP
#include <string>

std::string paraMinusculas(std::string texto);
void tirarAcentosParaOrdenar(std::string texto);
void substituir(std::string& texto, const std::string& letraAntiga, const std::string& letraNova);
#endif