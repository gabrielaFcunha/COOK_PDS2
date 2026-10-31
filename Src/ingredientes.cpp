/**
 * @file ingredientes.cpp
 * @brief Implementação das funções de Ingredientes
 *
 * Este arquivo contém a implementação de todas as funções declaradas em "ingredientes.hpp"
 * A classe fornece métodos para criar, modificar e verificar ingredientes.
 *
 * @author Gabriela Fialho Cunha
 * @date 16-10-2026
 */

#include "ingredientes.hpp"
#include <stdexcept>

/*
Ingredientes::Ingredientes()
    : nome(""), quantidade(0), unidade("") {
}*/

Ingredientes::Ingredientes(const std::string& nome, float quantidade,
                           Unidade unidade) : _nome(nome), _quantidade(quantidade), _unidade(unidade) {
    if (nome.empty() || (unidade != Unidade::Grama &&
         unidade != Unidade::Mililitro && unidade != Unidade::Unidade) 
        || quantidade <= 0) {
        throw std::invalid_argument("Dados invalidos para ingrediente");
    }
}

const std::string& Ingredientes::getNome() const {
    return _nome;
}

float Ingredientes::getQuantidade() const {
    return _quantidade;
}

Unidade Ingredientes::getUnidade() const {
    return _unidade;
}



bool Ingredientes::editar(const std::string& nome, float quantidade, Unidade unidade) {
/**
 * @brief funcao para editar um ingrediente. Esse metodo deve ser chamado dentro
 * de uma receita, para que o ingrediente seja editado nela.
 * @note funcao ainda em desenvolvimento
*/
    if (nome.empty() || quantidade <= 0 ||
        (unidade != Unidade::Grama &&
         unidade != Unidade::Mililitro &&
         unidade != Unidade::Unidade)) {
        return false;
    }

    _nome = nome;
    _quantidade = quantidade;
    _unidade = unidade;

    return true;
}


