#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include <string>
#include <vector>

#include "receita.hpp"
#include "filtro.hpp"

enum class CriterioOrdenacao {
    NOME,
    TEMPO_PREPARO,
    CATEGORIA
};

class Catalogo {
private:
    std::vector<Receita> receitas;

public:

    Catalogo();

    void adicionarReceita(const Receita&);

    bool removerReceita(const std::string&);

    std::vector<Receita> pesquisarPorNome(const std::string&) const;

    std::vector<Receita> pesquisar(const Filtro&) const;

    std::vector<Receita> ordenar(CriterioOrdenacao) const;

    const std::vector<Receita>& getReceitas() const;
};

#endif // CATALOGO_HPP