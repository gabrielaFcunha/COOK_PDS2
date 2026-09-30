#ifndef INGREDIENTES_HPP
#define INGREDIENTES_HPP
#include <string>

class ingredientes {
private:
    std::string nome;
    float quantidade;
    std::string unidade;

public:
    int cadastrar (std::string nome, float quantidade, std::string unidade);
    int editar(std::string nome, float quantidade, std::string unidade);
    int excluir(std::string nome, float quantidade, std::string unidade);
    int consultar(std::string nome);
    bool verificar(float quantidadeNecessaria);
};

#endif