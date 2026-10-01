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