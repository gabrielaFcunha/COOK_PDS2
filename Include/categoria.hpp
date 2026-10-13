#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <string>

enum class Categoria {
    Sobremesa,
    Lanche,
    PratoPrincipal,
    Entrada,
    Bebida
};

std::string categoriaToString(Categoria categoria);
std::string stringToCategoria(const std::string& categoriaStr);

#endif