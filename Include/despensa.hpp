/**
 * @file despensa.hpp
 * @brief Declaração da classe Despensa.
 *
 * Este arquivo contém a declaração da classe Despensa, que representa uma despensa de ingredientes.
 * A classe fornece métodos para adicionar, remover e verificar ingredientes, bem como imprimir o conteúdo da despensa.
 *
 * @author Gabriela Fialho Cunha
 * @date 01-10-2026
 */

#ifndef DESPENSA_HPP
#define DESPENSA_HPP
#include "ingredientes.hpp"
#include <vector>

class Despensa {
private:
    std::vector<Ingredientes> ingredientes;
    
    public:
    
    Despensa();
    
    
    void adicionarIngrediente();
    void removerIngrediente();
    bool possuiIngrediente();
    void imprimirDespensa();
    bool receitaPodeSerFeita();

    std::vector<Ingredientes>getIngredientesDisponiveis();

};
#endif