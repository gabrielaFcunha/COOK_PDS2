#include "catalogo.hpp"
#include "categoria.hpp"
#include "texto.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
Catalogo::Catalogo(){
}

bool Catalogo::adicionarReceita(const Receita& receita){
    // Checa se já existe receita de mesmo nome
    for (const auto& r : receitas) {
        if (tirarAcentosParaOrdenar(r.getNome()) == tirarAcentosParaOrdenar(receita.getNome())) {
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

/*
std::vector<Receita> Catalogo::pesquisarPorNome(const std::string& nome) const{
    std::vector<Receita> resultado;
    for (int i = 0; i < receitas.size(); i++) {
        if (paraMinusculas(receitas[i].getNome()).find(paraMinusculas(nome)) != std::string::npos) { //vê se a busca por nome dentro do nome da receita não deu ‘não encontrado’
            resultado.push_back(receitas[i]);
        }
    }
    return resultado;
}
*/
const Receita* Catalogo::pesquisarPorNome(const std::string& nome) const {
    std::string nomeBusca = tirarAcentosParaOrdenar(nome);
    for (size_t i = 0; i < receitas.size(); i++) {
        if (tirarAcentosParaOrdenar(receitas[i].getNome()) == nomeBusca) {
            return &receitas[i];
        }
    }
    return nullptr;
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

bool Catalogo::salvarEmArquivo() const {
/**
 * @brief salva as receitas do usuário em um arquivo
 * @param nomeArquivo nome do arquivo onde as receitas serão salvas
 * @return true se as receitas foram salvas com sucesso, false caso contrário
 * @note used: std::ofstream da biblioteca <fstream> para criar e escrever no arquivo
 * @note "receitas.txt" é o nome do arquivo onde as receitas serão salvas; ainda não foi criado
 */
    std::ofstream arquivo("receitas.txt");
    if(!arquivo.is_open()) {
        return false; // Falha ao abrir o arquivo
    }
    for(const auto& receita : receitas) {
        arquivo << receita.getNome() << ";"
                << receita.getTempo() << ";"
                << receita.getModo() << ";"
                << categoriaToString(receita.getCategoria()) << ";"
                << receita.getAvaliacao() << ";"
                << receita.getIngredientes().size();

        for(const auto& ingrediente : receita.getIngredientes()) {
            arquivo << ";" << ingrediente.getNome()
                    << ";" << ingrediente.getQuantidade()
                    << ";" << unidadeToString(ingrediente.getUnidade());
        }

        arquivo << std::endl;
    }
    arquivo.close();
    return true;
}

bool Catalogo::carregarDeArquivo() {
    std::ifstream arquivo("receitas.txt");
    if(!arquivo.is_open()) {
        return false; // Falha ao abrir o arquivo
    }
    receitas.clear();

    std::string linha;

    while(std::getline(arquivo, linha)) {
        std::stringstream dados(linha);

        std::string nome, tempoTexto, modo, categoriaTexto;
        std::string avaliacaoTexto, quantidadeIngredientesTexto;

        std::getline(dados, nome, ';');
        std::getline(dados, tempoTexto, ';');
        std::getline(dados, modo, ';');
        std::getline(dados, categoriaTexto, ';');
        std::getline(dados, avaliacaoTexto, ';');
        std::getline(dados, quantidadeIngredientesTexto, ';');

        int tempo = std::stoi(tempoTexto);
        int avaliacao = std::stoi(avaliacaoTexto);
        int quantidadeIngredientes = std::stoi(quantidadeIngredientesTexto);

        Categoria categoria = stringToCategoria(categoriaTexto);    

        std::vector<Ingredientes> ingredientes;

        for(int i = 0; i < quantidadeIngredientes; i++) {
            std::string nomeIngrediente, quantidadeTexto, unidadeTexto;

            std::getline(dados, nomeIngrediente, ';');
            std::getline(dados, quantidadeTexto, ';');
            std::getline(dados, unidadeTexto, ';');

            float quantidade = std::stof(quantidadeTexto);
            Unidade unidade;

            if(converterUnidade(quantidade, unidadeTexto, unidade)) {
                Ingredientes ingrediente(nomeIngrediente, quantidade, unidade);
                ingredientes.push_back(ingrediente);
            }
        }

        Receita receita(nome, tempo, modo, categoria, ingredientes);
        receita.avaliar(avaliacao);

        adicionarReceita(receita);
    }
    arquivo.close();
    return true;
}

bool Catalogo::atualizarReceita(size_t index, const Receita& receitaModificada) {
    if (index >= receitas.size()) {
        return false; // Índice inválido
    }
    receitas[index] = receitaModificada;
    return true;
}