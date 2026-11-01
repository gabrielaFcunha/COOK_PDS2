/**
 * @file filtro.hpp
 * @brief Declaração da Classe Filtro.
 *
 * Este arquivo contém a declaração da classe Filtro, que é responsável por fornecer métodos para filtrar receitas 
 * com base em diferentes critérios, como categoria e ingredientes disponíveis.
 *
 * @author Amanda Gonçalves
 * @date 2026-10-01
 */

#ifndef FILTRO_HPP
#define FILTRO_HPP

#include <iostream>
#include <string>
#include <vector>

#include "ingredientes.hpp" 
#include "despensa.hpp"
#include "catalogo.hpp"

class Filtro {

private:

    //acho que nao precisa de atributos


public:
    //operacoes

    //"Filtrar receitas por categoria",
    std::vector<Receita> filtrarPorCategoria (Catalogo catalogo, const Categoria categoria);
    // tecnicamente std::vector<Receita> é o catalogo  sla

    //"Filtrar receitas pelo nome", 
    //eu tirei pq o catalogo ta fazendo a mesma coisa

    //"Filtrar receitas que podem ser feitas com os ingredientes disponíveis na despensa",
    std::vector<Receita> buscarReceitas (Catalogo catalogo, const Despensa& despensa);
    
    //"Comparar os ingredientes da despensa com os da receita",
    bool compararIngredientes (const Receita& receita, const Despensa& despensa);

    //"identificar quais ingredientes estão faltando para uma receita", 
    std::vector<Ingredientes> identificarIngredientesFaltando (const Receita& receita, const Despensa& despensa);

    //"identificar quais ingredientes estão com unidades diferentes entre a receita e a despensa",
    std::vector<Ingredientes> identificarUnidadesDiferentes (const Receita& receita, const Despensa& despensa);
    
 

};

#endif

