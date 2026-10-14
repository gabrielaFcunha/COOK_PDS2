#include "receita.hpp"
#include <iostream>
#include <string>
#include <vector>


Receita::Receita (const std::string& nome, int tempoPreparo, const std::string& modoPreparo, std::vector<Ingredientes> ingredientes, Categoria categoria)
    : nome_(nome), tempoPreparo_(tempoPreparo), modoPreparo_(modoPreparo), ingrediente_(ingredientes), categoria_(categoria) {}
    

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