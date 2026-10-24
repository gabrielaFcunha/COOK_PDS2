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
#include "unidade.hpp"
#include <list>
#include <string>

class Despensa {
private:
    std::list<Ingredientes> ingredientes;
    
    public:
    
    //Despensa();
    
    /**
     * @brief coloquei o retorno bool
     * para indicar se a operação foi bem-sucedida ou não, 
     * caso o ingrediente já exista na despensa, por exemplo.
     * 
     */
    bool possuiIngrediente(const std::string& nome) const;
    
    bool adicionarIngrediente(const Ingredientes& ingrediente);
    bool removerIngrediente(const std::string& nome);

    

    bool atualizarQuantidade(const std::string& nome, float novaQuantidade);

    void imprimirDespensa() const;

    const std::list<Ingredientes>& getIngredientesDisponiveis() const;

    /**
     * salvarEmArquivo e carregarDeArquivo:
     * @brief adicionei essas funções para salvar e carregar a despensa em um arquivo,
     * sera necessario para que os dados persistam entre execuções do programa.
     * @note INTERESSANTE PENSAR EM FAZER ISSO EM UMA NOVA CLASSE,
     * JÁ QUE A RECEITA TAMBÉM VAI PRECISAR.
     */
    bool salvarEmArquivo() const;

    bool carregarDeArquivo();

};
#endif