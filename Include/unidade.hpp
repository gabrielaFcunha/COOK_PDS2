#ifndef UNIDADE_HPP
#define UNIDADE_HPP

#include <string>

enum class Unidade {
    Grama,
    Mililitro,
    Unidade
};

std::string unidadeToString(Unidade unidade);

#endif