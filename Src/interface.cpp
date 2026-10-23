

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "interface.hpp"
#include "despensa.hpp"
#include "filtro.hpp"
#include "catalogo.hpp"
#include "receita.hpp"


Interface::Interface() {
    catalogo.carregarDeArquivo(arquivoReceitas);
    despensa.carregarDeArquivo(arquivoDespensa);
}

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
                     " Digite sua opcao: ";

        int opcao;
        if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: menuCatalogo (); break;

            case 2: menuDespensa (); break;

            case 3: menuCozinhar (); break;

            case 4:
                catalogo.salvarEmArquivo(arquivoReceitas);
                despensa.salvarEmArquivo(arquivoDespensa);
                rodando = false;
                break;

            default:
                std::cout << "OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
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
                     " Digite sua opcao: ";
 
        int opcao;
        if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: limparTela(); cadastrarReceita(); break;

            case 2: limparTela(); exibirCatalogo(); break;

            case 3: limparTela(); procurarReceita(); break;

            case 4: limparTela(); filtrarReceitaPorCategoria(); break;

            case 5: limparTela(); editarReceita(); break;

            case 6: limparTela(); excluirReceita(); break;

            case 7: return;

            default:
                std::cout << "OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
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
                     " Digite sua opcao: ";
 
        int opcao;
        if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: limparTela(); filtrarIngredientePorReceita(); break;

            case 2: limparTela(); adicionarNovoIngrediente(); break;

            case 3: limparTela(); removerIngredientes(); break;

            case 4: limparTela(); editarQuantidade(); break;

            case 5: return;

            default:
                std::cout << "OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
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
                     " Digite sua opcao: ";
 
        int opcao;
        if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: limparTela(); filtrarPossiveisPorCategoria(); break;

            case 2: return;



            default:
                std::cout << "OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
                std::cin.get();
                break;


        }
    }
}

void Interface::exibirCatalogo () {
    while (true) {

        limparTela();

        std::cout << "|================== TODAS AS RECEITAS =================|\n";

        imprimirListaReceitas(catalogo.getReceitas());

        std::cout << "|======================================================|\n" 
                     "| Digite o numero de uma receita para ver detalhes     |\n"
                     "| ou digite 0 para voltar para CATALOGO                |\n"
                     "|======================================================|\n" 
                     " Digite sua opcao: ";
 
        int opcao;
        if (!(std::cin >> opcao)) opcao = -1;   // digitou letra
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        const auto& receitas = catalogo.getReceitas(); 

        if (opcao == 0) return;

        if (opcao >= 1 && opcao <= (int)receitas.size()) {
            limparTela();
            exibirDetalhesReceita(receitas[opcao - 1]);
            pausar();
        } else {
            std::cout << "OPÇÃO INVÁLIDA. Pressione Enter para tentar novamente... ";
            std::cin.get();
        }
    }
}

void Interface::cadastrarReceita () {
}

void Interface::imprimirListaReceitas(const std::vector<Receita>& receitas) {
    const auto& receitas = catalogo.getReceitas();

    if (receitas.empty()) {
        std::cout << "| Nenhuma receita cadastrada ainda                |\n";
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
              << "Tempo de Preparo: " << receita.getTempo() << "min\n" 
              << "Categoria: " << categoriaToString(receita.getCategoria()) << "\n" 
              << "Ingredientes:\n";

            const auto& ingredientes = receita.getIngredientes();
            if (ingredientes.empty()) {
                std::cout << "(nenhum ingrediente cadastrado)\n";
            } else {
                for (const auto& ing : ingredientes) {
                    std::cout << " - " << ing.getNome() << " (" << ing.getQuantidade() << ")\n";
                }
            }
            
    std::cout << "\n Modo de Preparo :\n" << receita.getModo() << "\n";
}

void Interface::procurarReceita() {
}

void Interface::filtrarReceitaPorCategoria() {
    
    limparTela();

    std::cout << "|====================== CATEGORIAS ====================|\n";

    imprimirListaReceitas();

    std::cout << "|======================================================|\n" 
                 "| Digite o numero de uma receita para ver detalhes     |\n"
                 "| ou digite 0 para voltar para CATALOGO                |\n"
                 "|======================================================|\n" 
                 " Digite a categoria escolhida: ";

}

void Interface::editarReceita() {
}

void Interface::excluirReceita() {
}




void Interface::filtrarIngredientePorReceita() {
}

void Interface::adicionarNovoIngrediente(){
}

void Interface::removerIngredientes(){
}

void Interface::editarQuantidade() {
}

void Interface::exibirReceitasPossiveis() {
}

void Interface::filtrarPossiveisPorCategoria() {
}
