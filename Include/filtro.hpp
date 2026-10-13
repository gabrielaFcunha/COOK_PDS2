/**
 * @file filtro.hpp
 * @brief Declaração da Classe Filtro.
 *
 * Este arquivo contém a declaração da classe Filtro, que é responsável por fornecer métodos para filtrar receitas 
 * com base em diferentes critérios, como categoria, nome e ingredientes disponíveis.
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
    std::vector<Receita> filtrarPorCategoria (Catalogo catalogo, const std::string& categoria);
    // tecnicamente std::vector<Receita> é o catalogo  sla

    //"Filtrar receitas pelo nome", 
    std::vector<Receita> filtrarPorNome (Catalogo catalogo, const std::string& nome);

    //"Buscar receitas a partir do catalogo",
    std::vector<Receita> buscarReceitas (Catalogo catalogo, std::vector<Ingredientes> ingredientesDisponiveis);
    
    //"Comparar os ingredientes da despensa com os da receita",
    bool compararIngredientes (const Receita& receita, const Despensa& despensa);

    //"identificar quais ingredientes estão faltando para uma receita", 
    std::vector<Ingredientes> identificarIngredientesFaltando (const Receita& receita, const Despensa& despensa);
    
 

}

#endif

