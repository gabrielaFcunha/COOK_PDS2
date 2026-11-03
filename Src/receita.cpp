#include "receita.hpp"
#include "texto.hpp"
#include <iostream>
#include <string>
#include <vector>


Receita::Receita (const std::string& nome, int tempoPreparo, const std::string& modoPreparo, Categoria categoria, const std::vector<Ingredientes>& ingredientes)
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

bool Receita::setNome(const std::string& nome) {
    if (nome.empty()) {
        return false;
    }
    nome_ = nome;
    return true;
}

bool Receita::setTempo(int tempoPreparo) {
    if (tempoPreparo <= 0) {
        return false;
    }
    tempoPreparo_ = tempoPreparo;
    return true;
}

bool Receita::setModo(const std::string& modoPreparo) {
    if (modoPreparo.empty()) {
        return false;
    }
    modoPreparo_ = modoPreparo;
    return true;
}

void Receita::setCategoria(Categoria categoria) {
    categoria_ = categoria;
} 


bool Receita::adicionarIngrediente (const Ingredientes& ingrediente) {
    for (size_t i = 0; i < ingrediente_.size(); i++) {
        if (tirarAcentosParaOrdenar(ingrediente_[i].getNome()) == tirarAcentosParaOrdenar(ingrediente.getNome())) {
            return false;
        }
    }
    ingrediente_.push_back(ingrediente);
    return true;
}

bool Receita::removerIngrediente (const std::string& nomeIngrediente) {
    for (size_t i = 0; i < ingrediente_.size(); i++) {
        if (tirarAcentosParaOrdenar(ingrediente_[i].getNome()) == tirarAcentosParaOrdenar(nomeIngrediente)) {
            ingrediente_.erase(ingrediente_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Receita::editarIngrediente (const std::string& nomeIngrediente,
                                 float quantidade, Unidade unidade) {
    for (size_t i = 0; i < ingrediente_.size(); i++) {
        if (tirarAcentosParaOrdenar(ingrediente_[i].getNome()) == tirarAcentosParaOrdenar(nomeIngrediente)) {
            return ingrediente_[i].editar(ingrediente_[i].getNome(), quantidade, unidade);
        }
    }
    return false;
}

