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

/*
Ingredientes::Ingredientes()
    : nome(""), quantidade(0), unidade("") {
}*/

Ingredientes::Ingredientes(const std::string& nome, float quantidade,
                           Unidade unidade)
    : _nome(nome), _quantidade(quantidade), _unidade(unidade) {
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

bool Ingredientes::cadastrar(const std::string& nome, float quantidade, Unidade unidade) {
/**
 * @brief funcao para cadastrar um ingrediente. Esse metodo deve ser chamado dentro
 * de uma receita, para que o ingrediente seja adicionado a ela. Ainda esta
 * em discussao se deve haver um banco que guarda todos esses ingredientes
 * @return true se o ingrediente foi cadastrado com sucesso, false se houve algum erro.
 * Faz mais sentido do que retornar um inteiro.
 * @note *.empty()* eh uma funcao da STL(biblioteca padrao do C++) 
 * que verifica se a string esta vazia.
 */

    if (nome.empty() || (unidade != Unidade::Grama &&
         unidade != Unidade::Mililitro && unidade != Unidade::Unidade) 
        || quantidade <= 0) {
        return false;
    }
    this->_nome = nome;
    this->_quantidade = quantidade;
    this->_unidade = unidade;

    return true;
}

bool Ingredientes::editar(const std::string& nome, float quantidade, Unidade unidade) {
/**
 * @brief funcao para editar um ingrediente. Esse metodo deve ser chamado dentro
 * de uma receita, para que o ingrediente seja editado nela.
 * @note funcao ainda em desenvolvimento
*/
    return cadastrar(nome, quantidade, unidade);
}


