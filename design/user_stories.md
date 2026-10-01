# Cadastro de Receitas
    Descrição: 
        Como usuário, quero cadastrar uma nova receita no catálogo para que ela fique disponível para consulta futura.
    Critérios de aceitação:
        Permitir inserir nome, tempo de preparo, porções, categoria e modo de preparo da receita.
        Permitir adicionar uma lista de ingredientes (com quantidade e unidade) à receita.
        Impedir o cadastro de uma receita sem nome ou sem ao menos um ingrediente.

# Busca de Receitas por Ingredientes
    Descrição: 
        Como usuário, quero buscar receitas a partir dos ingredientes que tenho disponíveis para saber o que posso cozinhar no momento.
    Critérios de aceitação:
        Mostrar todas as receitas que podem ser feitas apenas com os ingredientes presentes na despensa do usuário.
        Indicar quais ingredientes estão faltando, caso a receita não possa ser feita por completo.
        Permitir busca mesmo com apenas parte dos ingredientes da receita disponíveis.

# Gerenciamento da Despensa
    Descrição: 
        Como usuário, quero cadastrar e atualizar os ingredientes que tenho em casa para manter minha despensa sempre atualizada.
    Critérios de aceitação:
        Permitir adicionar um novo ingrediente à despensa com nome, quantidade e unidade.
        Permitir remover ou atualizar a quantidade de um ingrediente existente.
        Impedir quantidades negativas de ingredientes.

# Filtro por Categoria
    Descrição: 
        Como usuário, quero filtrar as receitas por categoria para encontrar mais rápido o tipo de prato que desejo preparar.
    Critérios de aceitação:
        Mostrar apenas as receitas pertencentes à categoria escolhida.
        Permitir combinar o filtro de categoria com a busca por ingredientes.
        Exibir mensagem clara caso nenhuma receita seja encontrada na categoria escolhida.