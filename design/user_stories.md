# USER STORIES - COOK++
## Definições
* **Mesmo nome:** nomes iguais ignorando maiúsculas/minúsculas e acentos (ex.: "pao de queijo" = "Pão de Queijo").
* **Ingrediente disponível:** existe na despensa com o mesmo nome, a mesma unidade e quantidade maior ou igual à exigida pela receita. Não há conversão entre unidades.
* **Receita possível:** receita cujos ingredientes estão todos disponíveis.
* **Unidades aceitas:** gramas, mililitros e unidade(s).
## USO 1 - Cadastro de Receitas
### Descrição: 
Como usuário, quero cadastrar uma nova receita no catálogo para que ela fique disponível para consulta futura.
### Critérios de aceitação:
* Deve ser possível informar nome, tempo de preparo (minutos), porções, categoria, modo de preparo e a lista de ingredientes (nome, quantidade e unidade).
Categoria e unidade são escolhidas entre as opções oferecidas, não digitadas livremente.
* Dado um nome vazio (ou só com espaços), quando o usuário tentar salvar, então o cadastro é recusado e o motivo é exibido.
* Dado tempo de preparo ou porções menores ou iguais a zero, quando tentar salvar, então o cadastro é recusado.
* Dada uma quantidade de ingrediente menor ou igual a zero, quando tentar salvar, então o cadastro é recusado.
* Dada uma receita sem nenhum ingrediente, quando tentar salvar, então o cadastro é recusado.
* Dado um nome já existente no catálogo (mesmo nome), quando tentar salvar, então o cadastro é recusado, pois cada receita tem nome único.
* Dado texto digitado em um campo numérico, quando o usuário confirmar, então o sistema pede o valor novamente, sem encerrar o programa.
* Após um cadastro bem-sucedido, a receita aparece na listagem do catálogo.

## USO 2 - Consulta geral de receitas
### Descrição:
Como usuário, quero consultar as receitas cadastradas para visualizar suas informações e escolher o que preparar.
### Critérios de aceitação:
* A lista mostra, para cada receita, número, nome, tempo de preparo e categoria.
* Ao selecionar um número válido, são exibidos nome, ingredientes (com quantidade e unidade), modo de preparo, tempo de preparo, porções, categoria e avaliação.
* Dado um catálogo vazio, quando o usuário abrir a listagem, então é exibida uma mensagem informando que não há receitas.
* Dado um número fora da lista, quando o usuário confirmar, então é exibida mensagem de opção inválida e ele pode tentar novamente.
* O usuário pode voltar ao menu sem selecionar nenhuma receita.

## US03 — Busca de receita por nome
### Descrição:
 Como usuário, quero buscar uma receita pelo nome, para chegar nela rapidamente sem percorrer todo o catálogo.
### Critérios de aceitação:
* Dado um nome de receita existente (mesmo nome), quando o usuário pesquisar, então os detalhes da receita são exibidos.
* Dado um nome inexistente, quando o usuário pesquisar, então é exibida a mensagem "receita não encontrada".
* Dada uma busca vazia, quando o usuário confirmar, então o sistema pede o nome novamente, sem exibir resultados.

## USO 4 - O que posso cozinhar agora?
### Descrição: 
Como usuário, quero buscar receitas a partir dos ingredientes que tenho disponíveis na despensa, para saber o que posso cozinhar no momento.
### Critérios de aceitação:
* A lista mostra somente receitas possíveis (todos os ingredientes disponíveis em quantidade suficiente).
* Dado um ingrediente que existe na despensa com unidade diferente da exigida pela receita, então ele é tratado como indisponível.
* Dado que nenhuma receita é possível, quando o usuário abrir a opção, então é exibida uma mensagem informando isso.
* O resultado reflete sempre o estado atual da despensa e do catálogo, e não uma lista guardada de antes.

## USO 5 - Gerenciamento da Despensa
### Descrição: 
Como usuário, quero cadastrar e atualizar os ingredientes que tenho em casa para manter minha despensa sempre atualizada.
### Critérios de aceitação:
* Deve ser possível adicionar um ingrediente informando nome, quantidade e unidade.
* Dado um ingrediente que já está na despensa (mesmo nome), quando o usuário tentar adicioná-lo de novo, então a operação é recusada e o sistema orienta a editar a quantidade.
* Dada uma quantidade menor ou igual a zero (ao adicionar ou atualizar), então a operação é recusada. Para zerar um ingrediente, o usuário o remove.
* Deve ser possível atualizar a quantidade de um ingrediente existente.
* Deve ser possível remover um ingrediente pelo nome. Dado um nome inexistente, é exibida a mensagem "ingrediente não encontrado".
* Deve ser possível visualizar todos os ingredientes cadastrados (nome, quantidade e unidade). Dada uma despensa vazia, é exibida uma mensagem informando isso.

## USO 6 - Filtro por Categoria
### Descrição: 
Como usuário, quero filtrar as receitas por categoria para encontrar mais rápido o tipo de prato que desejo preparar.
### Critérios de aceitação:
* Mostrar apenas as receitas pertencentes à categoria escolhida.
* Permitir combinar o filtro de categoria com a busca por ingredientes.
* Exibir mensagem caso nenhuma receita seja encontrada na categoria escolhida.

## USO 7 - Gerenciamento de Receitas
### Descrição: 
Como usuário, quero editar ou excluir receitas cadastradas para manter o catálogo atualizado.
### Critérios de aceitação:
* Deve ser possível editar nome, categoria, modo de preparo e ingredientes (adicionar, remover ou alterar a quantidade).
* Dado um valor inválido na edição, então a alteração é recusada e a receita original permanece.
* Dado um novo nome igual ao de outra receita do catálogo, então a alteração é recusada.
* A exclusão pede confirmação (s/n). Dada a resposta "n", nenhuma receita é removida.
* Após editar ou excluir, a listagem do catálogo reflete a mudança imediatamente.

## USO 8 - Avaliação de Receitas
### Descrição: 
Como usuário, quero avaliar receitas cadastradas com base no quanto gosto delas.
### Critérios de aceitação:
* Deve ser possível avaliar uma receita de 1 a 5 estrelas. Uma receita nova aparece como "sem avaliação".
* Dada uma nota fora do intervalo de 1 a 5, então a avaliação é recusada e a nota anterior é mantida.
* Reavaliar uma receita substitui a nota anterior.
* Deve ser possível listar apenas as receitas bem avaliadas. Dado que nenhuma atende, é exibida uma mensagem informando isso.

## USO 9 — Persistência dos dados
### Descrição:
Como usuário, quero que minhas receitas e minha despensa sejam guardadas ao fechar o programa, para não precisar cadastrar tudo de novo a cada uso.
### Critérios de aceitação:
* Ao iniciar, o sistema carrega o catálogo e a despensa dos arquivos salvos. Dado que os arquivos não existem, ele inicia vazio, sem erro.
* Ao sair pelo menu, o sistema salva o catálogo e a despensa.
* Dado um arquivo ilegível ou inválido, então o sistema informa o problema e continua funcionando, sem encerrar de forma abrupta.
* Acentos e caracteres especiais são preservados após salvar e carregar.

## USO 10 — Ordenação de receitas
### Descrição:
Como usuário, quero ordenar as receitas por nome, tempo de preparo ou categoria, para localizar o que procuro com mais facilidade.
### Critérios de aceitação:
* O usuário escolhe o critério: nome (ordem alfabética, ignorando acentos), tempo de preparo (do menor para o maior) ou categoria.
* A ordenação não altera os dados cadastrados: ao sair da tela, o catálogo mantém sua ordem original.
* Dado um catálogo vazio, é exibida uma mensagem informando isso.