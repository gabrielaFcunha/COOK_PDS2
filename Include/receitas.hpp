#ifndef RECEITAS_HPP
#define RECEITAS_HPP

#include <iostream>
#include <string>
#include <vector>

#include "filtro.hpp"
#include "ingredientes.hpp"


class Receitas {

private:

    std::string nome_;
    int tempoPreparo_;   //minutos
    std::string modoPreparo_;  //tem que decidir se vai querer passo a passo, que ai da pra usar vector
    std::vector<Ingredientes> ingrediente_;
    Filtro categoria_;


public:

    //construtor
    Receitas (const std::string& nome, int tempoPreparo, const std::string& modoPreparo, Filtro categoria);

    //getters
    const std::string& getNome () const;
    int getTempo () const;
    const std::string& getModo () const;
    const std::vector<Ingredientes>& getIngredientes () const;
    Filtro getCategoria () const;

    //outras operacoes
    void adicionarIngrediente (const Ingredientes& ingrediente);
    bool removerIngrediente (const std::string& nomeIngrediente);  

}

#endif