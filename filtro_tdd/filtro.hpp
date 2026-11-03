#pragma once
#include "modelos.hpp"

class Filtro {
public:
    std::vector<Receita> filtrarPorCategoria(const Catalogo& c, Categoria cat) {
        // TODO: filtrar, ordenar por nome, remover duplicadas
        return {};
    }
    std::vector<Ingredientes> identificarIngredientesFaltando(const Receita& r, const Despensa& d) {
        // TODO: faltando ou quantidade insuficiente ou unidade diferente (mantém ordem da receita)
        return {};
    }
    std::vector<Ingredientes> identificarUnidadesDiferentes(const Receita& r, const Despensa& d) {
        // TODO: mesmo nome, unidade diferente (ausente NÃO conta)
        return {};
    }
    bool compararIngredientes(const Receita& r, const Despensa& d) {
        // TODO: soma repetidos (receita e despensa), nome normalizado
        return false;
    }
};
