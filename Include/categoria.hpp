#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <string>

enum class Categoria {
    Entrada,
    PratoPrincipal,
    Sobremesa,
    Lanche,
    Bebida
};

std::string categoriaToString(Categoria categoria);
std::string stringToCategoria(const std::string& categoriaStr);

#endif