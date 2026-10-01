#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include "receitas.hpp"
#include "despensa.hpp"
#include "filtro.hpp"
#include "catalogo.hpp"

class Interface {
private:
    Receitas receitas;
    Despensa despensa;
    Filtro filtro;
    Catalogo catalogo;
public:
    Interface();
    void exibirReceitas();
    void cadastrarReceita();
    void consultarReceita();
    void sugestaoReceita();
    void filtrarReceita();
    void editarReceita();
    void excluirReceita();
    void avaliarReceita();

};

#endif