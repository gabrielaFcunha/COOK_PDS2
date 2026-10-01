/**
 * @file ingredientes.hpp
 * @brief Declaração da classe Ingredientes.
 *
 * Este arquivo contém a declaração da classe Ingredientes, que representa os ingredientes utilizados em receitas.
 * A classe possui atributos para armazenar o nome, quantidade e unidade de medida do ingrediente, bem como métodos
 * para cadastrar, editar, excluir, consultar e verificar a quantidade necessária do ingrediente.
 *
 * @author Júlia Valamiel Formiga
 * @date 01/10/2026
 */
#ifndef INGREDIENTES_HPP
#define INGREDIENTES_HPP
#include <string>

class Ingredientes {
private:
    std::string nome;
    float quantidade;
    std::string unidade;

public:

    const std::string& getNome() const;
    float getQuantidade() const;
    const std::string& getUnidade() const;

    int cadastrar (std::string nome, float quantidade, std::string unidade);
    int editar(std::string nome, float quantidade, std::string unidade);
    int excluir(std::string nome, float quantidade, std::string unidade);
    int consultar(std::string nome);
    bool verificar(float quantidadeNecessaria);
};

#endif