/*
 * @file interface.hpp
 * @brief Declaração da classe Interface.
 *
 * Este arquivo contém a declaração da classe Interface, que é responsável por gerenciar as interações com o usuário e fornecer funcionalidades relacionadas a receitas, despensa, filtro e catálogo.
 *
 * @author Julia V. F.
 * @date 2026-10-01
 */
#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include "receitas.hpp"
#include "despensa.hpp"
#include "filtro.hpp"
#include "catalogo.hpp"

class Interface {
private:
    std::vector<Receitas> receitas;
    std::vector<Despensa> despensa;
    std::vector<Filtro> filtro;
    std::vector<Catalogo> catalogo;
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