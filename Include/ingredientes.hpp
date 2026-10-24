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
#include "unidade.hpp"

class Ingredientes {
private:
    std::string _nome;
    float _quantidade;
    Unidade _unidade;

public:
    //Ingredientes();
    Ingredientes(const std::string& nome, float quantidade, Unidade unidade);
    
    //getters:
    const std::string& getNome() const;
    float getQuantidade() const;
    Unidade getUnidade() const;
    /**
     * bool cadastrar:
     * @brief Cadastra uma instância ainda vazia; exige nome/unidade
     *  e quantidade finita não negativa.
     */
    bool cadastrar(const std::string& nome, float quantidade, Unidade unidade);

    /**
     * bool editar:
     * @brief Atualiza uma instância cadastrada; 
     * @return false para dados inválidos ou instância vazia.
     */
    bool editar(const std::string& nome, float quantidade, Unidade unidade);
    
    //bool excluir();-> RECEITA QUE E RESPONSAVEL POR ESSA FUNCAO
//    bool consultar(const std::string& nome) const; -> NAO SEI SE FAZ SENTIDO TER EM INGREDIENTES
   
//    bool verificar(float quantidadeNecessaria) const; -> NAO SEI SE FAZ SENTIDO TER EM INGREDIENTES
};

#endif