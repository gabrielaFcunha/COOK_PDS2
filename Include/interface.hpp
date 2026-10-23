/**
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
#include "receita.hpp"
#include "despensa.hpp"
#include "filtro.hpp"
#include "catalogo.hpp"
#include <vector>
#include <string>

class Interface {
private:
    //Usuario Usuario;
    Filtro filtro;
    Catalogo catalogo;
    Despensa despensa;

    const std::string arquivoReceitas = "receitas.txt";
    const std::string arquivoDespensa = "despensa.txt";


    void limparTela();
    void pausar();

    void menuCatalogo();
    void menuDespensa();
    void menuCozinhar();


    void cadastrarReceita();

    void exibirCatalogo();
    void imprimirListaReceitas(const std::vector<Receita>& receitas);
    void exibirDetalhesReceita(const Receita&);

    void procurarReceita();
    void filtrarReceitaPorCategoria();
    void editarReceita();
    void excluirReceita();

    void filtrarIngredientePorReceita();
    void adicionarNovoIngrediente();
    void removerIngredientes();
    void editarQuantidade();

    void exibirReceitasPossiveis();
    void filtrarPossiveisPorCategoria();

public:
    Interface();
    void menu();

};

#endif