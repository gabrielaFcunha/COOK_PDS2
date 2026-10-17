#include "catalogo.hpp"
#include "categoria.hpp"
#include <algorithm>

std::string paraMinusculas(std::string texto){
    for(int i = 0; i < texto.size(); i++){
        if (texto[i] >= 'A' && texto[i] <= 'Z'){
            texto[i] = texto[i] + 32;
        }
    }
    return texto;
}

Catalogo::Catalogo(){
}

void Catalogo::adicionarReceita(const Receita& receita){
    receitas.push_back(receita);
}

const std::vector<Receita>& Catalogo::getReceitas() const{
    return receitas;
}

bool Catalogo::removerReceita(const std::string& nome){
    for (int i = 0; i < receitas.size(); i++) {
        if (paraMinusculas(receitas[i].getNome()) == paraMinusculas(nome)){
            receitas.erase(receitas.begin() + i);
            return true;
        }
    }
    return false;
}

std::vector<Receita> Catalogo::pesquisarPorNome(const std::string& nome) const{
    std::vector<Receita> resultado;
    for (int i = 0; i < receitas.size(); i++) {
        if (paraMinusculas(receitas[i].getNome()).find(paraMinusculas(nome)) != std::string::npos) { //vê se a busca por nome dentro do nome da receita não deu ‘não encontrado’
            resultado.push_back(receitas[i]);
        }
    }
    return resultado;
}

std::vector<Receita> Catalogo::ordenar(CriterioOrdenacao criterio) const{
    std::vector<Receita> resultado = receitas;
    std::sort(resultado.begin(), resultado.end(), [criterio](const Receita& a, const Receita& b){
        if ((criterio) == CriterioOrdenacao::NOME){
            return paraMinusculas(a.getNome()) < paraMinusculas(b.getNome());
        }
        if (criterio == CriterioOrdenacao::TEMPO_PREPARO){
            return a.getTempo() < b.getTempo();
        }
        if (criterio == CriterioOrdenacao::CATEGORIA){
            if(a.getCategoria() == b.getCategoria()){
                return paraMinusculas(a.getNome()) < paraMinusculas(b.getNome());
            }else{
                return a.getCategoria() < b.getCategoria();
            }
        }
        return false;
    });
    return resultado;
}