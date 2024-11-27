#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUTOS 3
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    float preco;
} Produto;

struct pedido {
    int carrinho;
    int quantidade;
    int total_itens; 
    float total;
    bool repeticao;
    int produtos[MAX_PRODUTOS];
};

void cadastrarProduto(Produto produtos[], int *quantidade);
void listarProdutos(Produto produtos[], int quantidade);
void editarProduto(Produto produtos[], int quantidade);
void excluirProduto(Produto produtos[], int *quantidade);
void listarItensPedido(int produto_1, int produto_2, int produto_3);
void processarPagamento();

int main() {
    Produto produtos[MAX_PRODUTOS] = {
        {"WHEY GROWTH 1KG SABOR CHOCOLATE", 189.99},
        {"CREATINA CONCENTRADA 250G MAX TITANIUM", 190.00},
        {"WHEY MAX TITANIUM 1KG SABOR MORANGO", 253.90}
    };
    
    struct pedido pedido1 = {0, 0, 0, 0.0, true, {0}};
    int opcao;

    do {
        printf("\n=== Menu de Pedidos de Suplementos ===\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Listar produtos cadastrados\n");
        printf("3. Editar produto existente\n");
        printf("4. Excluir produto existente\n");
        printf("5. Fazer um pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, MAX_PRODUTOS); // Aqui você pode implementar a lógica para adicionar novos produtos.
                break;
            case 2:
                listarProdutos(produtos, MAX_PRODUTOS);
                break;
            case 3:
                editarProduto(produtos, MAX_PRODUTOS);
                break;
            case 4:
                excluirProduto(produtos, MAX_PRODUTOS);
                break;
            case 5:
                // Aqui você pode chamar a lógica do pedido
                while (pedido1.repeticao) {
                    printf("----------------------------------------------------\n");
                    printf(" Tela de Pedido:\n");
                    listarProdutos(produtos, MAX_PRODUTOS);
                    printf("0. FINALIZAR COMPRA\n");
                    printf("----------------------------------------------------\n");
                    printf("Seu carrinho: %d itens \n", pedido1.total_itens);
                    printf("Escolha o produto para por no carrinho: ");
                    scanf("%d", &pedido1.carrinho);

                    if (pedido1.carrinho == 0) {
                        pedido1.repeticao = false;
                        break;
                    } else if (pedido1.carrinho < 1 || pedido1.carrinho > MAX_PRODUTOS) {
                        printf("Produto Não Encontrado!\n");
                        continue;
                    }

                    printf("Quantidade: ");
                    scanf("%d", &pedido1.quantidade);

                    if (pedido1.quantidade < 1) {
                        printf("Quantidade inválida! Deve ser maior que zero.\n");
                        continue;
                    }

                    pedido1.total_itens += pedido1.quantidade;
                    pedido1.total += pedido1.quantidade * produtos[pedido1.carrinho - 1].preco;
                    pedido1.produtos[pedido1.carrinho - 1] += pedido1.quantidade; // Atualiza o número de itens do produto
                }
                
                if (pedido1.total > 0) {
                    listarItensPedido(pedido1.produtos[0], pedido1.produtos[1], pedido1.produtos[2]);
                    printf("Total a pagar: R$%.2f \n", pedido1.total);
                    processarPagamento();
                } else {
                    printf("Nenhum produto foi adicionado ao carrinho.\n");
                }
                
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

void cadastrarProduto(Produto produtos[], int *quantidade) {
    if (*quantidade >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    
    getchar(); // Limpar o buffer
    printf("Digite o nome do novo produto: ");
    fgets(produtos[*quantidade].nome, MAX_NOME, stdin);
    produtos[*quantidade].nome[strcspn(produtos[*quantidade].nome, "\n")] = '\0';

    printf("Digite o preco do produto: ");
    scanf("%f", &produtos[*quantidade].preco);

    (*quantidade)++;
    printf("Produto cadastrado com sucesso!\n\n");
}

void listarProdutos(Produto produtos[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s - R$%.2f\n", i + 1, produtos[i].nome, produtos[i].preco);
    }
}

void editarProduto(Produto produtos[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum produto cadastrado para editar.\n");
        return;
    }

    int escolha;
    listarProdutos(produtos, quantidade);

    printf("Escolha o número do produto que deseja editar: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > quantidade) {
        printf("Escolha inválida.\n");
        return;
    }

    getchar(); // Limpar o buffer
    printf("Digite o novo nome para o produto %d: ", escolha);
    fgets(produtos[escolha - 1].nome, MAX_NOME, stdin);
    
    produtos[escolha - 1].nome[strcspn(produtos[escolha - 1].nome, "\n")] = '\0';
    
    printf("Digite o novo preço para o produto %d: ", escolha);
    scanf("%f", &produtos[escolha - 1].preco);

    printf("Produto editado com sucesso!\n\n");
}

void excluirProduto(Produto produtos[], int *quantidade) {
    if (*quantidade == 0) {
        printf("Nenhum produto cadastrado para ser excluído.\n");
        return;
    }

    int escolha;
    listarProdutos(produtos, *quantidade);
    
    printf("Escolha o número do produto que deseja excluir: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > *quantidade) {
        printf("Escolha inválida.\n");
        return;
    }

    for (int i = escolha - 1; i < *quantidade - 1; i++) {
        strcpy(produtos[i].nome, produtos[i + 1].nome);
        produtos[i].preco = produtos[i + 1].preco; // Atualiza o preço também
    }

    (*quantidade)--;

    printf("Produto excluído com sucesso!\n\n");
}

void listarItensPedido(int produto_1, int produto_2, int produto_3) {
   if (produto_1 > 0) {
       printf("%dX WHEY GROWTH 1KG SABOR CHOCOLATE\n", produto_1);
   }
   if (produto_2 > 0) {
       printf("%dX CREATINA CONCENTRADA 250G MAX TITANIUM\n", produto_2);
   }
   if (produto_3 > 0) {
       printf("%dX WHEY MAX TITANIUM 1KG SABOR MORANGO\n", produto_3);
   }
}

void processarPagamento() {
   int pagamento;

   printf("\nForma de pagamento:\n");
   printf("1. Cartão de Débito\n");
   printf("2. Cartão de Crédito\n");
   printf("3. Pix\n");

   scanf("%d", &pagamento);

   switch(pagamento) {
       case 1:
           printf("Pagamento via Cartão de Débito selecionado.\n");
           break;
       case 2:
           printf("Pagamento via Cartão de Crédito selecionado.\n");
           break;
       case 3:
           printf("Pagamento via Pix selecionado.\n");
           break;
       default:
           printf("Opção de pagamento inválida.\n");
           break;
   }
}