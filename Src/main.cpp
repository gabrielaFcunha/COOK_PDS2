#include "interface.hpp"
/**
 * @brief A interface basicamente já faz todas as impressões e chamadas de funções, 
 * então o main só precisa instanciar a interface e chamar o menu.
 */
int main() {
    Interface site; 
    site.menu();      
    return 0;
}