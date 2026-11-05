#include "catalogo.hpp"
#include "categoria.hpp"
#include "texto.hpp"

Catalogo::Catalogo(){
}

bool Catalogo::adicionarReceita(const Receita& receita){
    // Checa se já existe receita de mesmo nome
    for (const auto& r : receitas) {
        if (paraMinusculas(r.getNome()) == paraMinusculas(receita.getNome())) {
            return false;
        }
    }
    receitas.push_back(receita);
    return true;
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
     for (size_t i = 0; i < resultado.size(); i++) {
        for (size_t j = 0; j + 1 < resultado.size() - i; j++) {
            const Receita& a = resultado[j];
            const Receita& b = resultado[j + 1];
            bool trocar = false;   // true se b deve vir antes de a

            if (criterio == CriterioOrdenacao::NOME) {
                trocar = paraMinusculas(b.getNome()) < paraMinusculas(a.getNome());
            }
            if (criterio == CriterioOrdenacao::TEMPO_PREPARO) {
                trocar = b.getTempo() < a.getTempo();
            }
            if (criterio == CriterioOrdenacao::CATEGORIA) {
                if (a.getCategoria() == b.getCategoria()) {
                    trocar = paraMinusculas(b.getNome()) < paraMinusculas(a.getNome());
                } else {
                    trocar = b.getCategoria() < a.getCategoria();
                }
            }

            if (trocar) {
                Receita temp = resultado[j];
                resultado[j] = resultado[j + 1];
                resultado[j + 1] = temp;
            }
        }
    }
    return resultado;
}