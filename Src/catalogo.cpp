#include "catalogo.hpp"
#include "categoria.hpp"
#include "texto.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Catalogo::Catalogo(){
}
/**
 * @brief Adiciona uma receita ao catálogo.
 * @param receita A receita a ser adicionada.
 * @return true se a receita foi adicionada com sucesso, false se já existe uma receita com o mesmo nome.
 */
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
/**
 * @brief remove uma receita do catálogo com base no nome da receita.
 * @param nome nome da receita a ser removida.
 * @return true se a receita foi encontrada e removida com sucesso, false caso contrário.
 */
bool Catalogo::removerReceita(const std::string& nome){
    for (size_t i = 0; i < receitas.size(); i++) {
        if (tirarAcentosParaOrdenar(receitas[i].getNome()) == tirarAcentosParaOrdenar(nome)){
            receitas.erase(receitas.begin() + i);
            return true;
        }
    }
    return false;
}
/**
 * @brief pesquisa receitas no catálogo com base no nome da receita.
 * @param nome nome a ser comparado para a busca; pode ser só uma parte.
 * @return const Receita*: ponteiro para a receita encontrada, ou nullptr se não for encontrada.
 */
std::vector<const Receita*> Catalogo::pesquisarPorNome(const std::string& nome) const {
    std::vector<const Receita*> encontradas;

    std::string nomeBusca = tirarAcentosParaOrdenar(nome);

    for (size_t i = 0; i < receitas.size(); i++) {
        std::string nomeReceita = tirarAcentosParaOrdenar(receitas[i].getNome());

        for (size_t p = 0; p + nomeBusca.size() <= nomeReceita.size(); p++) {
            bool achou = true;

            for (size_t j = 0; j < nomeBusca.size(); j++) {
                if (nomeReceita[p + j] != nomeBusca[j]) {
                    achou = false;
                    break;
                }
            }

            if (achou) {
                encontradas.push_back(&receitas[i]);
                break;
            }
        }
    }

    return encontradas;
}
/**
 * @brief Ordena as receitas do catálogo com base em um critério de ordenação especificado.
 * @param criterio critério escolhido pelo usuário para ordenar as receitas.
 * @return std::vector<Receita> vetor ordenado de acordo com o critério escolhido.
 */
std::vector<Receita> Catalogo::ordenar(CriterioOrdenacao criterio) const{
    std::vector<Receita> resultado = receitas;

    for (size_t i = 0; i < resultado.size(); i++) {
        for (size_t j = 0; j + 1 < resultado.size() - i; j++) {
            const Receita& a = resultado[j];
            const Receita& b = resultado[j + 1];
            bool trocar = false;

            if (criterio == CriterioOrdenacao::NOME) {
                trocar = tirarAcentosParaOrdenar(b.getNome()) < tirarAcentosParaOrdenar(a.getNome());
            }
            if (criterio == CriterioOrdenacao::TEMPO_PREPARO) {
                trocar = b.getTempo() < a.getTempo();
            }
            if (criterio == CriterioOrdenacao::CATEGORIA) {
                if (a.getCategoria() == b.getCategoria()) {
                    trocar = tirarAcentosParaOrdenar(b.getNome()) < tirarAcentosParaOrdenar(a.getNome());
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
/**
 * @brief Carrega as receitas do usuário a partir de um arquivo
 * @param nomeArquivo nome do arquivo de onde as receitas serão carregadas
 * @return true se as receitas foram carregadas com sucesso, false caso contrário
 * @note used: std::ifstream da biblioteca <fstream> para abrir e ler o arquivo
 * @note "receitas.txt" é o nome do arquivo de onde as receitas serão carregadas
 */
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
/**
 * @brief Atualiza uma receita no catálogo com base no índice fornecido.
 * @param index índice da receita a ser atualizada.
 * @param receitaModificada a nova receita que substituirá a existente.
 * @return true se a receita foi atualizada com sucesso, false se o índice for inválido.
 */
bool Catalogo::atualizarReceita(size_t index, const Receita& receitaModificada) {
    if (index >= receitas.size()) {
        return false; // Índice inválido
    }
    receitas[index] = receitaModificada;
    return true;
}