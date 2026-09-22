#ifndef DESPENSA_HPP
#define DESPENSA_HPP

class Despensa {
private:
    Ingrediente* ingredientes;
    
    public:
    
    Despensa();
    
    
    void adicionarIngrediente();
    void removerIngrediente();
    bool possuiIngrediente();
    void imprimirDespensa();
    //bool receitaPodeSerFeita(); -> FILTRO

    ingredientes = getIngredientesDisponiveis();

};
#endif