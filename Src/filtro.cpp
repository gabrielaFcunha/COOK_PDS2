#include "filtro.hpp"
#include "catalogo.hpp"
#include "texto.hpp"
#include <list>

/**
 * @brief Filtra as receitas de um catálogo com base em uma categoria específica.
 *
 * Este método percorre todas as receitas presentes no catálogo e seleciona aquelas que pertencem à categoria especificada.
 *
 * @param catalogo O catálogo de receitas a ser filtrado.
 * @param categoria A categoria pela qual as receitas devem ser filtradas.
 * @return std::vector<Receita> Um vetor contendo todas as receitas que correspondem à categoria especificada.
 */
std::vector<Receita> Filtro::filtrarPorCategoria (Catalogo catalogo, const Categoria categoria){
    std::vector<Receita> resultado;
    for (int i = 0; i < catalogo.getReceitas().size(); i++) {
        if (catalogo.getReceitas()[i].getCategoria() == categoria) {
            resultado.push_back(catalogo.getReceitas()[i]);
        }
    }
    return resultado;
}
/**
 * @brief Identifica os ingredientes que estão faltando em relação a uma receita e uma despensa.
 * 
 * Este método compara os ingredientes necessários para preparar uma receita com os ingredientes disponíveis em uma despensa.
 *
 * @param receita A receita para a qual identificar ingredientes faltando.
 * @param despensa A despensa que contém os ingredientes disponíveis.
 * @return std::vector<Ingredientes> Um vetor contendo os ingredientes que estão faltando.
 */
std::vector<Ingredientes> Filtro::identificarIngredientesFaltando (const Receita& receita, const Despensa& despensa){
    std::vector<Ingredientes> faltando;
    const std::vector<Ingredientes>& pedidos = receita.getIngredientes(); //lista de ingredientes que a receita pede
    const std::list<Ingredientes>& naDespensa = despensa.getIngredientesDisponiveis();

    for (int i = 0; i < pedidos.size(); i++) {
        bool achou = false;
        for (const Ingredientes& item : naDespensa) {
            if (paraMinusculas(pedidos[i].getNome()) == paraMinusculas(item.getNome())) {
                if (pedidos[i].getUnidade() == item.getUnidade() && pedidos[i].getQuantidade() > item.getQuantidade()) {
                    faltando.push_back(pedidos[i]);
                }
                achou = true;
                break;
            }
        }
        if (achou == false) {
            faltando.push_back(pedidos[i]);
        }
    }
    return faltando;
}
/**
 * @brief   Identifica os ingredientes que possuem unidades diferentes entre uma receita e uma despensa.
 * 
 * Este método compara os ingredientes necessários para preparar uma receita com os ingredientes disponíveis em uma despensa, verificando se as unidades de medida são diferentes.
 * 
 * @param receita 
 * @param despensa 
 * @return std::vector<Ingredientes> Um vetor contendo os ingredientes que possuem unidades diferentes entre a receita e a despensa.
 */
std::vector<Ingredientes> Filtro::identificarUnidadesDiferentes (const Receita& receita, const Despensa& despensa){
    std::vector<Ingredientes> diferentes;
    const std::vector<Ingredientes>& pedidos = receita.getIngredientes();
    const std::list<Ingredientes>& naDespensa = despensa.getIngredientesDisponiveis();
    for (int i = 0; i < pedidos.size(); i++) {
        for (const Ingredientes& item : naDespensa) {
            if (paraMinusculas(pedidos[i].getNome()) == paraMinusculas(item.getNome())) {
                if (pedidos[i].getUnidade() != item.getUnidade()) {
                    diferentes.push_back(pedidos[i]);
                }
                break;
            }
        }
    }
    return diferentes;
}
/**
 * @brief Compara os ingredientes de uma receita com os ingredientes de uma despensa.
 * 
 * @param receita 
 * @param despensa 
 * @return true se todos os ingredientes da receita estão presentes na despensa com as quantidades e unidades corretas.
 * @return false caso contrário.
 */
bool Filtro::compararIngredientes (const Receita& receita, const Despensa& despensa){
    if (identificarIngredientesFaltando(receita, despensa).empty() && identificarUnidadesDiferentes(receita, despensa).empty()) {
        return true;
    }
    return false;
}
/**
 * @brief Lista receitas que podem ser feitas com os ingredientes disponíveis na despensa.
 * 
 * @param catalogo 
 * @param despensa 
 * @return std::vector<Receita> Um vetor contendo as receitas que podem ser feitas com os ingredientes disponíveis.
 */
std::vector<Receita> Filtro::buscarReceitas (Catalogo catalogo, const Despensa& despensa){
    std::vector<Receita> resultado;
    for (int i = 0; i < catalogo.getReceitas().size(); i++) {
        if (compararIngredientes(catalogo.getReceitas()[i], despensa)) {
            resultado.push_back(catalogo.getReceitas()[i]);
        }
    }
    return resultado;
}