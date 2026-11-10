#ifndef TEXTO_HPP
#define TEXTO_HPP
#include <string>

std::string paraMinusculas(std::string texto);
std::string tirarAcentosParaOrdenar(std::string texto);
void substituir(std::string& texto, const std::string& letraAntiga, const std::string& letraNova);
std::string normalizar(const std::string& texto);
bool nomeValido(const std::string& nome);

#endif