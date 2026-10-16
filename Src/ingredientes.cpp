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

Ingredientes::Ingredientes()
    : nome(""), quantidade(0), unidade("") {
}

Ingredientes::Ingredientes(const std::string& nome, float quantidade,
                           const std::string& unidade)
    : nome(nome), quantidade(quantidade), unidade(unidade) {
}

const std::string& Ingredientes::getNome() const {
    return nome;
}

float Ingredientes::getQuantidade() const {
    return quantidade;
}

const std::string& Ingredientes::getUnidade() const {
    return unidade;
}

bool Ingredientes::cadastrar(const std::string& nome, float quantidade, const std::string& unidade) {
/**
 * @brief funcao para cadastrar um ingrediente. Esse metodo deve ser chamado dentro
 * de uma receita, para que o ingrediente seja adicionado a ela. Ainda esta
 * em discussao se deve haver um banco que guarda todos esses ingredientes
 * @return true se o ingrediente foi cadastrado com sucesso, false se houve algum erro.
 * Faz mais sentido do que retornar um inteiro.
 * @note *.empty()* eh uma funcao da STL(biblioteca padrao do C++) 
 * que verifica se a string esta vazia.
 */

    if (nome.empty() || unidade.empty() || quantidade <= 0) {
        return false;
    }
    this->nome = nome;
    this->quantidade = quantidade;
    this->unidade = unidade;

    return true;
}

bool Ingredientes::editar(const std::string& nome, float quantidade, const std::string& unidade) {
/**
 * @brief funcao para editar um ingrediente. Esse metodo deve ser chamado dentro
 * de uma receita, para que o ingrediente seja editado nela.
 * @note funcao ainda em desenvolvimento
*/
    return cadastrar(nome, quantidade, unidade);
}


