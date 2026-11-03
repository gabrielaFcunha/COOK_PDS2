#include "categoria.hpp"

std::string categoriaToString(Categoria categoria) {
    switch(categoria) {
        case Categoria::Entrada:
            return "Entrada";

        case Categoria::PratoPrincipal:
            return "PratoPrincipal";

        case Categoria::Sobremesa:
            return "Sobremesa";

        case Categoria::Lanche:
            return "Lanche";

        case Categoria::Bebida:
            return "Bebida";
    }

    return "";
}

Categoria stringToCategoria(const std::string& categoriaStr) {
    if(categoriaStr == "Entrada") {
        return Categoria::Entrada;
    }
    if(categoriaStr == "PratoPrincipal") {
        return Categoria::PratoPrincipal;
    }
    if(categoriaStr == "Sobremesa") {
        return Categoria::Sobremesa;
    }
    if(categoriaStr == "Lanche") {
        return Categoria::Lanche;
    }
    if(categoriaStr == "Bebida") {
        return Categoria::Bebida;
    }

    // Valor padrão caso a categoria recebida seja inválida.
    return Categoria::Entrada;
}