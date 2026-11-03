#pragma once
#include <string>
#include <vector>
#include <memory>

enum class Categoria { Entrada, PratoPrincipal, Sobremesa, Bebida, Lanche };
enum class Unidade { Grama, Mililitro, Unidade };

class Ingredientes {
    std::string nome; double quantidade; Unidade unidade;
public:
    Ingredientes(std::string n, double q, Unidade u) : nome(n), quantidade(q), unidade(u) {}
    const std::string& getNome() const { return nome; }
    double getQuantidade() const { return quantidade; }
    Unidade getUnidade() const { return unidade; }
};

class Receita {
    std::string nome; int tempo; std::string modo; Categoria categoria;
    // shared_ptr: cópias da receita compartilham os ingredientes (necessário pro Teste 08)
    std::shared_ptr<std::vector<Ingredientes>> ingredientes = std::make_shared<std::vector<Ingredientes>>();
public:
    Receita(std::string n, int t, std::string m, Categoria c) : nome(n), tempo(t), modo(m), categoria(c) {}
    const std::string& getNome() const { return nome; }
    Categoria getCategoria() const { return categoria; }
    void adicionarIngrediente(const Ingredientes& i) { ingredientes->push_back(i); }
    const std::vector<Ingredientes>& getIngredientes() const { return *ingredientes; }
};

class Catalogo {
    std::vector<Receita> receitas;
public:
    void adicionarReceita(const Receita& r) { receitas.push_back(r); }
    const std::vector<Receita>& getReceitas() const { return receitas; }
};

class Despensa {
    std::vector<Ingredientes> itens;
public:
    void adicionarIngrediente(const Ingredientes& i) { itens.push_back(i); }
    const std::vector<Ingredientes>& getIngredientesDisponiveis() const { return itens; }
};
