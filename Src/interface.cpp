

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "interface.hpp"
#include "despensa.hpp"
#include "filtro.hpp"
#include "catalogo.hpp"
#include "receita.hpp"
#include "unidade.hpp"
#include "texto.hpp"

//preciso que alguem me ajude com as questões dos arquivos, não entendi muito bem, tem que mexer no construtor e em menu
Interface::Interface() {
    //catalogo.carregarDeArquivo(arquivoReceitas);
    //despensa.carregarDeArquivo(arquivoDespensa);
}

//FUNÇÕES AUXILIARES
void Interface::limparTela () {
#ifdef _WIN32
    system("cls");  
#else
    system("clear"); 
#endif
}

void Interface::pausar() {
    std::cout << "\nPressione Enter para voltar...";
    std::cin.get();
}

int Interface::lerOpcao() {
    int opcao;
    if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return opcao;
}

int Interface::escolherReceita(const std::vector<Receita>& receitas) {
    if (receitas.empty()) {
        std::cout << "| Nenhuma receita disponivel.\n";
        return -1; // Retorna uma receita vazia
    }

    std::cout << "|================== ESCOLHER RECEITA ==================|\n";
    imprimirListaReceitas(receitas);
    std::cout << "|======================================================|\n"
                 "| Digite o numero da receita (ou 0 para cancelar): ";

    int opcao = lerOpcao();

    if (opcao == 0) {
        return -1; // Retorna uma receita vazia
    }

    if (opcao < 1 || opcao > (int)receitas.size()) {
        std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
        std::cin.get();
        return escolherReceita(receitas);
    }

    return opcao - 1; // retorna o indice da receita escolhida;
}

void Interface::exibirLista(const std::string& titulo, const std::vector<Receita>& receitas) {
    std::cout << "| " << titulo << "\n";

        imprimirListaReceitas(receitas);

        std::cout << "|======================================================|\n" 
                     "| Digite o numero de uma receita para ver detalhes     |\n"
                     "| ou digite 0 para voltar para CATALOGO                |\n"
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        const auto& receitas = catalogo.getReceitas(); 

        if (opcao == 0) return;

        if (opcao >= 1 && opcao <= (int)receitas.size()) {
            limparTela();
            exibirDetalhesReceita(receitas[opcao - 1]);
            pausar();
        } else {
            std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
            std::cin.get();
        }
}


//MENU PRINCIPAL
void Interface::menu() {

    bool rodando = true;

    while (rodando) {

        limparTela();

        std::cout << "|================= Bem Vindo Ao COOK++ ================|\n" 
                     "|                         MENU                         |\n"
                     "| 1) Catalogo de Receitas                              |\n"
                     "| 2) Despensa                                          |\n" 
                     "| 3) O que posso cozinhar agora?                       |\n" 
                     "| 4) Sair                                              |\n" 
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";

        int opcao = lerOpcao();

        switch (opcao) {
            case 1: menuCatalogo (); break;

            case 2: menuDespensa (); break;

            case 3: menuCozinhar (); break;

            case 4:
                //catalogo.salvarEmArquivo(arquivoReceitas);
                //despensa.salvarEmArquivo(arquivoDespensa);
                rodando = false;
                break;

            default:
                std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
                std::cin.get();
                break;
        }
    }
}

void Interface::menuCatalogo () {

    while (true) {

        limparTela();

        std::cout << "|====================== CATALOGO ======================|\n" 
                     "| 1) Cadastrar receita nova                            |\n"
                     "| 2) Exibir todas as receitas                          |\n"
                     "| 3) Buscar uma receita por nome                       |\n" 
                     "| 4) Filtrar receitas por categoria                    |\n" 
                     "| 5) Editar uma receita                                |\n"
                     "| 6) Remover uma receita                               |\n" 
                     "| 7) Voltar para o MENU                                |\n"  
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        switch (opcao) {
            case 1: limparTela(); cadastrarReceita(); break;

            case 2: limparTela(); exibirCatalogo(); break;

            case 3: limparTela(); procurarReceita(); break;

            case 4: limparTela(); filtrarReceitaPorCategoria(); break;

            case 5: limparTela(); editarReceita(); break;

            case 6: limparTela(); excluirReceita(); break;

            case 7: return;

            default:
                std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
                std::cin.get();
                break;
        }
    }
}

void Interface::menuDespensa () {

    while (true) {

        limparTela();

        std::cout << "|====================== DESPENSA ======================|\n" 
                     "|           Todos os ingredientes cadastrados          |\n";

        despensa.imprimirDespensa(); 

        std::cout << "|======================================================|\n" 
                     "| 1) Visualizar apenas os ingredientes de uma receita  |\n"
                     "| 2) Adicionar ingredientes                            |\n"
                     "| 3) Remover ingredientes                              |\n" 
                     "| 4) Editar a quantidade de um ingrediente             |\n" 
                     "| 5) Voltar para o MENU                                |\n"  
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        switch (opcao) {
            case 1: limparTela(); filtrarIngredientePorReceita(); break;

            case 2: limparTela(); adicionarNovoIngrediente(); break;

            case 3: limparTela(); removerIngredientes(); break;

            case 4: limparTela(); editarQuantidade(); break;

            case 5: return;

            default:
                std::cout << "| OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
                std::cin.get();
                break;


        }
    }
}

void Interface::menuCozinhar () {
    while (true) {

        limparTela();

        std::cout << "|============= O QUE POSSO COZINHAR AGORA? ============|\n" 
                     "|                                                      |\n";

        exibirReceitasPossiveis(); 

        std::cout << "|======================================================|\n" 
                     "| 1) Filtrar por categoria                             |\n"
                     "| 2) Voltar para o MENU                                |\n"
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        switch (opcao) {
            case 1: limparTela(); filtrarPossiveisPorCategoria(); break;

            case 2: return;



            default:
                std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
                std::cin.get();
                break;


        }
    }
}

//FUNÇÕES DO CATALOGO
void Interface::exibirCatalogo () {
    while (true) {

        limparTela();

        std::cout << "|================== TODAS AS RECEITAS =================|\n";

        imprimirListaReceitas(catalogo.getReceitas());

        std::cout << "|======================================================|\n" 
                     "| Digite o numero de uma receita para ver detalhes     |\n"
                     "| ou digite 0 para voltar para CATALOGO                |\n"
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        const auto& receitas = catalogo.getReceitas(); 

        if (opcao == 0) return;

        if (opcao >= 1 && opcao <= (int)receitas.size()) {
            limparTela();
            exibirDetalhesReceita(receitas[opcao - 1]);
            pausar();
        } else {
            std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
            std::cin.get();
        }
    }
}

void Interface::cadastrarReceita () {
    std::cout << "|===================== RECEITA NOVA ===================|\n";
    std::cout << "| Nome: ";
    std::string nome;
    std::getline(std::cin, nome);
    std::cout << "| Tempo de Preparo (em minutos): ";
    int tempo;
    tempo = lerOpcao();
    std::cout << "| Categoria: ";
    Categoria categoria = lerCategoria();
    std::cout << "| Modo de Preparo: ";
    std::string preparo;
    std::getline(std::cin, preparo);
    std::cout << "| Ingredientes: ";
    vector <Ingredientes> ingredientes = {};

    while (true) {
        std::cout << "  Nome do ingrediente (ou digite 'fim' para terminar): ";
        std::string nomeIngrediente;
        std::getline(std::cin, nomeIngrediente);

        if (nomeIngrediente == "fim" || nomeIngrediente.empty()) {
            break; // Sai do loop de ingredientes
        }

        std::cout << "  Quantidade: ";
        float quantidade = lerQuantidade();
        Unidade unidade = lerUnidade();

        ingredientes.push_back(Ingredientes(nomeIngrediente, quantidade, unidade));
    }

    Receita receita = Receita(nome, tempo, preparo, categoria, ingredientes);
    catalogo.adicionarReceita(receita);
            
}

void Interface::imprimirListaReceitas(const std::vector<Receita>& receitas) {

    if (receitas.empty()) {
        std::cout << "| Nenhuma receita cadastrada ainda\n";
        return;
    }

    for (size_t i = 0; i < receitas.size(); i++) {
        std::cout << "| " << i + 1 << ") " << receitas[i].getNome()
        <<  " - " << receitas[i].getTempo() << " minutos" <<  " - " << categoriaToString(receitas[i].getCategoria())
        << "\n";
    }
}

void Interface::exibirDetalhesReceita(const Receita& receita) {

    std::cout << "|======================================================|\n" 
              << " " << receita.getNome() << "\n"
              << "|======================================================|\n" 
              << "| Tempo de Preparo: " << receita.getTempo() << "min\n" 
              << "| Categoria: " << categoriaToString(receita.getCategoria()) << "\n" 
              << "| Ingredientes:\n";

            const auto& ingredientes = receita.getIngredientes();
            if (ingredientes.empty()) {
                std::cout << "| (nenhum ingrediente cadastrado)\n";
            } else {
                for (const auto& ing : ingredientes) {
                    std::cout << " - " << ing.getNome() << " (" << ing.getQuantidade() 
                              << " " << unidadeToString(ing.getUnidade()) << ")\n";
                }
            }
            
    std::cout << "\n Modo de Preparo :\n" << receita.getModo() << "\n";
}

void Interface::procurarReceita() {
    std::cout << "|============== DIGITE O NOME DA RECEITA ==============|\n"
              << "| Pesquisar: "; 
    string nome;
    std::getline(std::cin, nome); 
    vector<Receita> receitasEncontradas = catalogo.pesquisarPorNome(nome);
    exibirLista ("RESULTADOS DA PESQUISA", receitasEncontradas);         
}

void Interface::filtrarReceitaPorCategoria() {
    
    std::cout << "|====================== CATEGORIAS ====================|\n";
    Categoria categoria = lerCategoria();
    std::vector <Receita> receitas = filtro.filtrarPorCategoria(catalogo.getReceitas(), categoria);
    imprimirListaReceitas(receitas);

}

void Interface::editarReceita() {
    int indice = escolherReceita(catalogo.getReceitas());
    if (indice == -1) {
        return; // Usuário cancelou ou não há receitas
    }

    // Fazemos uma cópia da receita escolhida para editarmos com segurança
    Receita receitaEditada = catalogo.getReceitas()[indice];

    while (true) {
        limparTela();
        std::cout << "|=================== EDITAR RECEITA ===================|\n"
                  << "| Editando: " << receitaEditada.getNome() << "\n"
                  << "|------------------------------------------------------|\n"
                  << "| 1) Alterar Nome\n"
                  << "| 2) Alterar Tempo de Preparo\n"
                  << "| 3) Alterar Categoria\n"
                  << "| 4) Alterar Modo de Preparo\n"
                  << "| 5) Salvar alterações\n"
                  << "| 0) Cancelar edicao\n"
                  << "|======================================================|\n"
                  << "| Digite sua opcao: ";

        int opcao = lerOpcao();

        switch (opcao) {
            case 1: {
                std::cout << "| Novo nome: ";
                std::string novoNome;
                std::getline(std::cin, novoNome);
                if (receitaEditada.setNome(novoNome)) {
                    std::cout << "| Nome alterado na copia!\n";
                } else {
                    std::cout << "| Nome invalido (nao pode ser vazio).\n";
                }
                pausar();
                break;
            }
            case 2: {
                std::cout << "| Novo tempo de preparo (min): ";
                int novoTempo = lerOpcao();
                if (receitaEditada.setTempo(novoTempo)) {
                    std::cout << "| Tempo alterado!\n";
                } else {
                    std::cout << "| Tempo invalido (deve ser > 0).\n";
                }
                pausar();
                break;
            }
            case 3: {
                std::cout << "| Nova categoria:\n";
                Categoria novaCat = lerCategoria();
                receitaEditada.setCategoria(novaCat);
                std::cout << "| Categoria alterada!\n";
                pausar();
                break;
            }
            case 4: {
                std::cout << "| Novo modo de preparo: ";
                std::string novoModo;
                std::getline(std::cin, novoModo);
                if (receitaEditada.setModo(novoModo)) {
                    std::cout << "| Modo de preparo alterado!\n";
                } else {
                    std::cout << "| Modo nao pode ser vazio.\n";
                }
                pausar();
                break;
            }
            case 5: {
                // Salva definitivamente no catalogo
                if (catalogo.atualizarReceita(indice, receitaEditada)) {
                    std::cout << "| Receita salva com sucesso!\n";
                } else {
                    std::cout << "| Erro ao salvar receita.\n";
                }
                pausar();
                return;
            }
            case 0:
                std::cout << "| Edicao cancelada.\n";
                pausar();
                return;
            default:
                std::cout << "| Opcao invalida!\n";
                pausar();
                break;
        }
    }
}

void Interface::excluirReceita() {
    int indice = escolherReceita(catalogo.getReceitas());
    std::cout << "|======================================================|\n"
                 "| Tem certeza que deseja exluir essa receita? s/n: ";
    if (std::tolower(std::cin.get()) == 's') {
        if (catalogo.removerReceita(catalogo.getReceitas()[indice].getNome())) {
            std::cout << "| Receita excluida com sucesso!";
        } else {
            std::cout << "| Nao foi possivel excluir a receita. Tente novamente.";
        }
    } else {
        std::cout << "| Exclusao cancelada.";
    }             
}

//FUNCOES DO DESPENSA
void Interface::filtrarIngredientePorReceita() {
    int indice = escolherReceita(catalogo.getReceitas());
    Receita receita = catalogo.getReceitas()[indice];
    std::cout << "|=============== INGREDIENTES DA RECEITA ==============|\n";
    std::vector <Ingredientes> ingReceita = receita.getIngredientes();
    for(auto i = ingReceita.begin(); i != ingReceita.end(); ++i) {
        std::cout << i->getNome() << "-" << i->getQuantidade() << " " << unidadeToString(i->getUnidade()) << std::endl;
    }
}

float Interface::lerQuantidade() {
    float quantidade;
    while (!(std::cin >> quantidade) || quantidade <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << " Valor invalido. Digite um numero maior que zero: ";
    }
    std::cin.ignore(10000, '\n');
    return quantidade;
}

Unidade Interface::lerUnidade() {
    while (true) {
        std::cout << " Unidade: 1) gramas  2) mililitros  3) unidade(s)\n"
                     " Digite sua opcao: ";

        int opcao = lerOpcao();

        switch (opcao) {
            case 1: return Unidade::Grama;
            case 2: return Unidade::Mililitro;
            case 3: return Unidade::Unidade;
            default: std::cout << " Opcao invalida.\n"; break;
        }
    }
}

Categoria Interface::lerCategoria() {
    while (true) {
        std::cout << " Categoria: 1) entrada  2) prato principal  3) sobremesa 4) lanche 5) bebida\n"
                     " Digite sua opcao: ";

        int opcao = lerOpcao();

        switch (opcao) {
            case 1: return Categoria::Entrada;
            case 2: return Categoria::PratoPrincipal;
            case 3: return Categoria::Sobremesa;
            case 4: return Categoria::Lanche;
            case 5: return Categoria::Bebida;
            default: std::cout << " Opcao invalida.\n"; break;
        }
    }
}

void Interface::adicionarNovoIngrediente() {
    std::cout << "|================== NOVO INGREDIENTE ==================|\n"
                 " Nome do ingrediente: ";

    std::string nome;
    std::getline(std::cin, nome);

    if (nome.empty()) {
        std::cout << "\n O nome nao pode ficar vazio.\n";
        pausar();
        return;
    }

    if (despensa.possuiIngrediente(nome)) {
        std::cout << "\n Esse ingrediente ja esta na despensa.\n"
                     " Use a opcao 4 do menu para editar a quantidade.\n";
        pausar();
        return;
    }

    std::cout << " Quantidade: ";
    float quantidade = lerQuantidade();
    Unidade unidade = lerUnidade();

    if (despensa.adicionarIngrediente(Ingredientes(nome, quantidade, unidade))) {
        std::cout << "\n Ingrediente adicionado!\n";
    } else {
        std::cout << "\n Nao foi possivel adicionar o ingrediente.\n";
    }

    pausar();
}

void Interface::removerIngredientes() {
    std::cout << "|================= REMOVER INGREDIENTE ================|\n";
    despensa.imprimirDespensa();
    std::cout << "|======================================================|\n"
                 " Nome do ingrediente (Enter para cancelar): ";

    std::string nome;
    std::getline(std::cin, nome);
    if (nome.empty()) return;

    if (despensa.removerIngrediente(nome)) {
        std::cout << "\n Ingrediente removido!\n";
    } else {
        std::cout << "\n Ingrediente nao encontrado na despensa.\n";
    }
    pausar();
}

void Interface::editarQuantidade() {
    std::cout << "|================== EDITAR QUANTIDADE =================|\n";
    despensa.imprimirDespensa();
    std::cout << "|======================================================|\n"
                 "| Nome do ingrediente (Enter para cancelar): ";

    std::string nome;
    std::getline(std::cin, nome);
    if (nome.empty()) return;

    if (!despensa.possuiIngrediente(nome)) {
        std::cout << "\n Ingrediente nao encontrado na despensa.\n";
        pausar();
        return;
    }

    std::cout << " Nova quantidade: ";
    float quantidade = lerQuantidade();

    if (despensa.atualizarQuantidade(nome, quantidade)) {
        std::cout << "\n Quantidade atualizada!\n";
    } else {
        std::cout << "\n Nao foi possivel atualizar a quantidade.\n";
    }
    pausar();
}

//FUNCOES DO MENU COZINHAR
void Interface::exibirReceitasPossiveis() {
    imprimirListaReceitas(filtro.buscarReceitas(catalogo, despensa));
}

void Interface::filtrarPossiveisPorCategoria() {
    std::cout << "|================ FILTRAR POR CATEGORIA ===============|\n";
    Categoria categoria = lerCategoria();
    std::cout << "|======================================================|\n";
    std::vector <Receita> possiveis = filtro.buscarReceitas(catalogo, despensa);
    Catalogo catalogoPossiveis(possiveis);

    std::vector <Receita> filtradas = filtro.filtrarPorCategoria(catalogoPossiveis, categoria);

    std::cout << "| RECEITAS POSSIVEIS NA CATEGORIA SELECIONADA          |\n";

        imprimirListaReceitas(filtradas);

        std::cout << "|======================================================|\n" 
                     "| Digite o numero de uma receita para ver detalhes     |\n"
                     "| ou digite 0 para voltar para MENU                |\n"
                     "|======================================================|\n" 
                     "| Digite sua opcao: ";
 
        int opcao = lerOpcao();

        if (opcao == 0) return;

        if (opcao >= 1 && opcao <= (int)filtradas.size()) {
            limparTela();
            exibirDetalhesReceita(filtradas[opcao - 1]);
            pausar();
        } else {
            std::cout << "| OPCAO INVALIDA. Pressione Enter para tentar novamente... ";
            std::cin.get();
        }


}
