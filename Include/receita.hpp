/*
 * @file receita.hpp
 * @brief  Declaração da Classe Receita
 * 
 * A classe Receita representa uma receita culinária, contendo informações como nome, tempo de preparo, modo de preparo, ingredientes e categoria.
 * A classe fornece métodos para acessar e modificar essas informações, bem como para gerenciar os ingredientes associados à receita.
 * 
 * @author Amanda Gonçalves
 * @date 2026-10-01
 */

#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <iostream>
#include <string>
#include <vector>

#include "ingredientes.hpp"
#include "categoria.hpp" 


class Receita {

private:

    std::string nome_;
    int tempoPreparo_;   //minutos
    std::string modoPreparo_;  //tem que decidir se vai querer passo a passo, que ai da pra usar um vetor talvez
    std::vector<Ingredientes> ingrediente_;
    Categoria categoria_; 

public:

    //construtor
    Receita (const std::string& nome, int tempoPreparo, const std::string& modoPreparo, Categoria categoria);

    //getters
    const std::string& getNome () const;
    int getTempo () const;
    const std::string& getModo () const;
    const std::vector<Ingredientes>& getIngredientes () const;
    Categoria getCategoria () const;

    //outras operacoes
    void adicionarIngrediente (const Ingredientes& ingrediente);
    bool removerIngrediente (const std::string& nomeIngrediente);  

}

#endif