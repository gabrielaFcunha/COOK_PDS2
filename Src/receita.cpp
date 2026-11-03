#include "receita.hpp"
#include <iostream>
#include <string>
#include <vector>


Receita::Receita (const std::string& nome, int tempoPreparo, const std::string& modoPreparo, Categoria categoria, const std::vector<Ingredientes>& ingredientes)
    : nome_(nome), tempoPreparo_(tempoPreparo), modoPreparo_(modoPreparo), ingrediente_(ingredientes), categoria_(categoria), avaliacao_(0) {}
    

const std::string& Receita::getNome () const {
    return nome_;
}

int Receita::getTempo () const {
    return tempoPreparo_;
}

const std::string& Receita::getModo () const {
    return modoPreparo_;
}

const std::vector<Ingredientes>& Receita::getIngredientes () const {
    return ingrediente_;
}

Categoria Receita::getCategoria () const {
    return categoria_;
}

void Receita::adicionarIngrediente (const Ingredientes& ingrediente) {
    ingrediente_.push_back(ingrediente);
}

bool Receita::removerIngrediente (const std::string& nomeIngrediente) {
    for (size_t i = 0; i < ingrediente_.size();i++) {
        if (ingrediente_[i].getNome() == nomeIngrediente) {
            ingrediente_.erase(ingrediente_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Receita::avaliar(int avaliacao) {
    if(avaliacao >= 1 && avaliacao <= 5) {
        avaliacao_ = avaliacao;
        return true;
    }
    return false;
}

int Receita::getAvaliacao() const {
    return avaliacao_;
}
/**
 * @brief no FILTRO, devemos depois criar um método que percorre o vetor
 * de receitas e seleciona aquelas cuja getAvaliação seja igual a que
 * o usuario escolheu.
 * @details o filtro poderia ser tipo assim:
 * std::vector<Receita> Filtrar::filtrarPorAvaliacao(
    const std::vector<Receita>& receitas, int avaliacao) {
    std::vector<Receita> resultado;
    for(const auto& receita : receitas) {
        if(receita.getAvaliacao() == avaliacao) {
            resultado.push_back(receita);
        }
    }
    return resultado;
}
 * 
 */