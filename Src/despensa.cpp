/**
 * @file despensa.cpp
 * @brief Implementação das funções de Despensa
 *
 * Este arquivo contém a implementação de todas as funções declaradas em "despensa.hpp"
 * A classe fornece métodos para adicionar, remover e verificar ingredientes, bem como imprimir o conteúdo da despensa.
 *
 * @author Gabriela Fialho Cunha
 * @date 01-10-2026
 */

#include "despensa.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <list>

bool Despensa::possuiIngrediente(const std::string& nome) const{
/**
 * @brief verifica se um ingrediente está disponível na despensa do usuário
 * @param nome nome do ingrediente a ser verificado
 * @return true se o ingrediente estiver disponível, false caso contrário
 */
    for(auto i = ingredientes.begin(); i != ingredientes.end(); ++i) {
        if(paraMinusculas(i->getNome()) == paraMinusculas(nome)) {
            return true;
        }
    }
    return false; 
}

bool Despensa::adicionarIngrediente(const Ingredientes& ingrediente) {
/**
 * @brief ingrediente é adicionado à despensa do usuário
 */
    if(possuiIngrediente(ingrediente.getNome())) {
        return false; // Ingrediente já existe na despensa
    }
    ingredientes.push_back(ingrediente);

    return true;
}
bool Despensa::removerIngrediente(const std::string& nome){
/**
 * @brief remove um ingrediente da despensa do usuário
 * @param nome nome do ingrediente a ser removido
 * @return true se o ingrediente foi removido com sucesso, false caso contrário
 * @note used: .erase() da biblioteca <list> para remover o ingrediente da lista
 * @note used: tipo auto para passar pela lista de ingredientes; mais fácil do que
 * determinar um tipo específico.
 */
    for(auto i = ingredientes.begin(); i != ingredientes.end(); ++i) {
        if(paraMinusculas(i->getNome()) == paraMinusculas(nome)) {
            ingredientes.erase(i);
            return true;
        }
    }
    return false;
}

bool Despensa::atualizarQuantidade(const std::string& nome, float novaQuantidade) {
/**
 * @brief atualiza a quantidade de um ingrediente na despensa do usuário
 * @param nome nome do ingrediente a ser atualizado
 * @param novaQuantidade nova quantidade do ingrediente
 * @return true se o ingrediente foi atualizado com sucesso, false caso contrário
 */
    if(novaQuantidade <= 0){
        return false; // Quantidade inválida
    }
    for(auto i = ingredientes.begin(); i != ingredientes.end(); ++i) {
        if(paraMinusculas(i->getNome()) == paraMinusculas(nome)) {
           
            return i->editar(i->getNome(), novaQuantidade, i->getUnidade());
        }
    }
    return false; // Ingrediente não encontrado
}

const std::list<Ingredientes>& Despensa::getIngredientesDisponiveis() const {
/**
 * @brief retorna a lista de ingredientes disponíveis na despensa do usuário
 * @return lista de ingredientes disponíveis
 */
    return ingredientes;
}

void Despensa::imprimirDespensa() const {
/**
 * @brief despensa inteira impressa para o usuário consultar
 * @note ainda não sei o que seria feito em interface, porém
 * deixarei a impressão bem desenvolvida aqui por enquanto.
 *  
 */
    if(ingredientes.empty()){
        std::cout << "A despensa esta vazia." << std::endl;
        return;
    }
    for(auto i = ingredientes.begin(); i != ingredientes.end(); ++i) {
        std::cout << i->getNome() << "-" << i->getQuantidade() << " " << unidadeToString(i->getUnidade()) << std::endl;
    }
}

bool Despensa::salvarEmArquivo() const {
/**
 * @brief salva a despensa do usuário em um arquivo
 * @param nomeArquivo nome do arquivo onde a despensa será salva
 * @return true se a despensa foi salva com sucesso, false caso contrário
 * @note used: std::ofstream da biblioteca <fstream> para criar e escrever no arquivo
 * @note "despensa.txt" é o nome do arquivo onde a despensa será salva; ainda não foi criado
 */
    std::ofstream arquivo("despensa.txt");
    if(!arquivo.is_open()) {
        return false; // Falha ao abrir o arquivo
    }
    for(auto i = ingredientes.begin(); i != ingredientes.end(); ++i) {
        arquivo << i->getNome() << ";" << i->getQuantidade() << ";" << unidadeToString(i->getUnidade()) << std::endl;
    }
    arquivo.close();
    return true;
}

bool Despensa::carregarDeArquivo() {
/**
 * @brief carrega a despensa do usuário de um arquivo - necessário
 * para que os dados persistam entre execuções do programa.
 * @param nomeArquivo nome do arquivo de onde a despensa será carregada
 * @return true se a despensa foi carregada com sucesso, false caso contrário
 */
    std::ifstream arquivo("despensa.txt");
    if(!arquivo.is_open()){
        return false; // Falha ao abrir o arquivo
    }
    ingredientes.clear(); //TESTE: acho que sem o clear pode deixar duplicado os ingredientes.
    
    std::string nome, unidadeTexto, quantidadeTexto;

    while(std::getline(arquivo, nome, ';')) {
        /**
         * @note coloquei esses "if" para caso algum ingrediente
         * esteja incompleto no aquivo da despensa, ele não seja carregado.
         */
        if(!std::getline(arquivo, quantidadeTexto, ';')) {
            break; // Falha ao ler a quantidade
        }
        if(!std::getline(arquivo, unidadeTexto)) {
            break; // Falha ao ler a unidade
        }
        float quantidade = std::stof(quantidadeTexto);
        Unidade unidade;

        if(converterUnidade(quantidade, unidadeTexto, unidade)) {
            Ingredientes ingrediente(nome, quantidade, unidade);

            if(!possuiIngrediente(nome)) {
                ingredientes.push_back(ingrediente);
            }
        
        }
    }
    arquivo.close();
    return true;
}




