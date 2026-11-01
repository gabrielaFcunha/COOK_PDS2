#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include <string>
#include <vector>

#include "receita.hpp"

/**
 * @brief definição de critérios de ordenação para as receitas, utilizado na função Catalogo::ordenar.
 * 
 */
enum class CriterioOrdenacao {
    NOME,
    TEMPO_PREPARO,
    CATEGORIA
};

/**
 * @brief Classe que representa um catálogo de receitas, permitindo adicionar, remover, pesquisar e ordenar receitas.
 * 
 */
class Catalogo {
private:
    /**
     * @brief vetor que armazena as receitas do catálogo.
     * 
     */
    std::vector<Receita> receitas;

public:

    /**
     * @brief Método construtor padrão de um objeto catálogo;
     * 
     */
    Catalogo();

    /**
     * @brief adiciona uma nova receita ao vetor catálogo.
     * 
     * @param receita A receita a ser adicionada.
     */
    bool adicionarReceita(const Receita& receita);

    /**
     * @brief remove uma receita do vetor catálogo com base no nome da receita.

     * @param nome nome da receita a ser removida.
     * @return true se a receita foi encontrada e removida com sucesso
     * @return false caso contrário.
     */
    bool removerReceita(const std::string& nome);
    
    /**
     * @brief pesquisa receitas no vetor catálogo com base no nome da receita.
     * 
     * @param nome nome a ser comparado para a busca; pode ser so uma parte.
     * @return std::vector<Receita>: vetor contendo as receitas que correspondem ao nome pesquisado.
     */
    std::vector<Receita> pesquisarPorNome(const std::string& nome) const;

    /**
     * @brief função que ordena as receitas do catálogo com base em um critério de ordenação especificado.
     *        essa função não altera o vetor receitas original, mas retorna um novo vetor ordenado.
     * @param criterio criterio escolhido pelo usuario para ordenar as receitas.
     * @return std::vector<Receita> vetor ordenado de acordo com o critério escolhido.
     */
    std::vector<Receita> ordenar(CriterioOrdenacao criterio) const;

    /**
     * @brief pega o vetor de receitas original do catálogo.
     * 
     * @return const std::vector<Receita>& referência constante para o vetor de receitas do catálogo.
     */
    const std::vector<Receita>& getReceitas() const;
};

#endif // CATALOGO_HPP