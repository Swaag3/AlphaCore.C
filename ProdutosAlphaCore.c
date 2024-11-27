#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100 // Limite máximo de produtos

// Estrutura para representar um produto
typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

// Variável global para armazenar os produtos
Produto produtos[MAX_PRODUTOS];
int numProdutos = 0;

// Função para cadastrar um novo produto
void cadastrarProduto() {
    if (numProdutos == MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("-------------------------------------\n");

    printf("Digite o código do produto: ");
    scanf("%d", &produtos[numProdutos].codigo);

    printf("Digite o nome do produto: ");
    scanf("%s", produtos[numProdutos].nome);

    printf("Digite o preço do produto: ");
    scanf("%f", &produtos[numProdutos].preco);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &produtos[numProdutos].quantidade);

    numProdutos++;
    printf("Produto cadastrado com sucesso!\n");
    printf("-------------------------------------\n");

}

// Função para consultar um produto pelo código
void consultarProduto() {
    int codigo;
    printf("-------------------------------------\n");
    printf("Digite o código do produto a ser consultado: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Produto encontrado:\n");
            printf("Código: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preço: R$ %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("-------------------------------------\n");

            return;
        }
    }

    printf("Produto não encontrado!\n");
}

// ... outras funções (listar, alterar, excluir)

int main() {
    int opcao;

    do {
        printf("=== Cadastro Produtos AlphaCore ===");

        printf("\nMenu:\n");
        printf("1. Cadastrar produto\n");
        printf("2. Consultar produto\n");
        // ... outras opções
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                consultarProduto(); 
                break;
            // ... outros casos
        }
    } while (opcao != 0);

    return 0; 
}