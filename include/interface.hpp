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
    Unidade unidade;
    Filtro filtro;
    Catalogo catalogo;
    Despensa despensa;


    void limparTela();
    void pausar();
    int lerOpcao();
    int escolherReceita(const std::vector<Receita>& receitas);
    void exibirLista(const std::string& titulo, const std::vector<Receita>& listaReceitas);

    void menuCatalogo();
    void menuDespensa();
    void menuCozinhar();

    void exibirCatalogo();
    void cadastrarReceita();
    void imprimirListaReceitas(const std::vector<Receita>& receitas);
    void exibirDetalhesReceita(const Receita& receita);

    void procurarReceita();
    void filtrarReceitaPorCategoria();
    void editarReceita();
    void excluirReceita();

    void filtrarIngredientePorReceita();
    float lerQuantidade();
    Unidade lerUnidade();
    Categoria lerCategoria();
    
    void adicionarNovoIngrediente();
    void removerIngredientes();
    void editarQuantidade();

    void exibirReceitasPossiveis();
    void filtrarPossiveisPorCategoria();

    void avaliacao();
    void verificarDisponibilidade();
    void filtrarAvaliacao();

public:
    Interface();
    void menu();

};

#endif