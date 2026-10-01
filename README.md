# COOK++

Sistema de gerenciamento de receitas desenvolvido como projeto da disciplina de **Programação e Desenvolvimento de Sistemas II (PDS2)**.

O COOK++ permite que o usuário cadastre, organize e encontre receitas de forma simples, utilizando filtros por características das receitas e pelos ingredientes disponíveis em sua despensa.

---

## Sobre o projeto

O COOK++ foi desenvolvido com o objetivo de criar uma aplicação para gerenciamento de receitas, aplicando conceitos de *Programação Orientada a Objetos*.

O sistema permite que o usuário mantenha um histórico de receitas, consulte seus detalhes, realize buscas e filtros e verifique quais receitas podem ser preparadas utilizando os ingredientes que possui em casa. Também é possível avaliar e favoritar as receitas que o usuário mais gosta.

Os dados do sistema serão armazenados em arquivos, não sendo utilizado banco de dados.

---

## Funcionalidades

### Gerenciamento de receitas

- Adicionar novas receitas;
- Visualizar receitas cadastradas;
- Editar receitas;
- Remover receitas;
- Consultar detalhes de uma receita;
- Manter um histórico das receitas cadastradas.
- Avaliar receitas

### Busca e filtros

O usuário poderá encontrar receitas utilizando diferentes critérios, como:

- Nome da receita;
- Categoria: doce ou salgado;
- Avaliação;
- Favoritos;
- Ingredientes disponíveis.


### Despensa

O usuário poderá cadastrar os ingredientes que possui em casa.

A partir dessas informações, o sistema poderá comparar os ingredientes disponíveis com os ingredientes necessários para cada receita.

Assim, será possível identificar:

- Receitas que podem ser preparadas completamente;
- Receitas que possuem parte dos ingredientes disponíveis;
- Ingredientes que estão faltando para preparar uma determinada receita.

---

## Estrutura do sistema

O projeto será organizado em classes, cada uma com uma responsabilidade específica:

| Classe | Responsabilidade |
|--------|------------------|
| `Receita` | Representar e armazenar as informações de uma receita |
| `Ingrediente` | Representar os ingredientes e suas informações |
| `Despensa` | Gerenciar os ingredientes disponíveis para o usuário |
| `Catálogo` | Adicionar, editar e remover receitas |
| `Filtro` | Realizar buscas e filtros de receitas e ingredientes |
| `Interface` | Gerenciar as páginas, botões e interação com o usuário |

---

## Armazenamento

As informações serão armazenadas em arquivos locais, permitindo que os dados cadastrados sejam mantidos mesmo após o encerramento do programa.
---