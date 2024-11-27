#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define MAX_USUARIOS 100
#define MAX_FORNECEDORES 100
#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_DATA 11
#define MAX_CPF 12
#define MAX_CEP 9

typedef struct {
    char nome[MAX_NOME];
    float preco;
} Produto;

typedef struct {
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char data_nascimento[MAX_DATA];
    char cpf[MAX_CPF];
    char cep[MAX_CEP];
} Usuario;

typedef struct {
    int id;
    char nome[MAX_NOME];
    char telefone[15];
    char cnpj[20];
    char cep[10];
    char dataCadastro[11];
    char email[MAX_EMAIL];
    char contato[MAX_NOME];
} Fornecedor;

typedef struct {
    int carrinho;
    int quantidade;
    int total_itens;
    float total;
    bool repeticao;
    int produtos[MAX_PRODUTOS]; // Armazena a quantidade de cada produto no pedido
} Pedido;

// Variáveis globais
Produto produtos[MAX_PRODUTOS];
Usuario usuarios[MAX_USUARIOS];
Fornecedor fornecedores[MAX_FORNECEDORES];
Pedido pedidos[MAX_USUARIOS];
int numProdutos = 0;
int numUsuarios = 0;
int numFornecedores = 0;
int numPedidos = 0;

// Funções de Produto
void cadastrarProduto();
void listarProdutos();
void editarProduto();
void excluirProduto();
void fazerPedido();

// Funções de Usuário
void lerDadosUsuario(Usuario *usuario);
void exibirDadosUsuario(const Usuario *usuario);
void cadastrarUsuario();
void listarUsuarios();
void editarUsuario();
void excluirUsuario();

// Funções de Fornecedor
int validarCNPJ(char *cnpj);
void cadastrarFornecedor();
void listarFornecedores();
void editarFornecedor();
void excluirFornecedor();

// Funções de Pedido
void listarPedidos();

// Funções de Pagamento
void processarPagamento();

// Função Principal
int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento ===\n");
        printf("1. Gerenciar Produtos\n");
        printf("2. Gerenciar Usuários\n");
        printf("3. Gerenciar Fornecedores\n");
        printf("4. Fazer um Pedido\n");
        printf("5. Listar Produtos\n");
        printf("6. Listar Usuários\n");
        printf("7. Listar Fornecedores\n");
        printf("8. Listar Pedidos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                cadastrarUsuario();
                break;
            case 3:
                cadastrarFornecedor();
                break;
            case 4:
                fazerPedido();
                break;
            case 5:
                listarProdutos();
                break;
            case 6:
                listarUsuarios();
                break;
            case 7:
                listarFornecedores();
                break;
            case 8:
                listarPedidos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Implementação das funções de Produto
void cadastrarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("Digite o nome do produto: ");
    fgets(produtos[numProdutos].nome, MAX_NOME, stdin);
    produtos[numProdutos].nome[strcspn(produtos[numProdutos].nome, "\n")] = '\0'; // Remove nova linha

    printf("Digite o preço do produto: ");
    scanf("%f", &produtos[numProdutos].preco);

    numProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("%d. %s - R$%.2f\n", i + 1, produtos[i].nome, produtos[i].preco);
    }
}

void editarProduto() {
    listarProdutos();

    int escolha;
    printf("Escolha o número do produto que deseja editar: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numProdutos) {
        printf("Escolha inválida.\n");
        return;
    }

    getchar(); // Limpar o buffer
    printf("Digite o novo nome para o produto %d: ", escolha);
    fgets(produtos[escolha - 1].nome, MAX_NOME, stdin);

    produtos[escolha - 1].nome[strcspn(produtos[escolha - 1].nome, "\n")] = '\0';

    printf("Digite o novo preço para o produto %d: ", escolha);
    scanf("%f", &produtos[escolha - 1].preco);

    printf("Produto editado com sucesso!\n");
}

void excluirProduto() {
    listarProdutos();

    int escolha;
    printf("Escolha o número do produto que deseja excluir: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numProdutos) {
        printf("Escolha inválida.\n");
        return;
    }

    for (int i = escolha - 1; i < numProdutos - 1; i++) {
        produtos[i] = produtos[i + 1]; // Move os produtos para preencher o espaço vazio
    }

    numProdutos--;
    printf("Produto excluído com sucesso!\n");
}

void fazerPedido() {
    Pedido pedido = {0, 0, 0, 0.0, true, {0}};

    while (pedido.repeticao) {
        listarProdutos();
        printf("\nEscolha o produto para adicionar ao carrinho (0 para finalizar): ");
        scanf("%d", &pedido.carrinho);

        if (pedido.carrinho == 0) {
            pedido.repeticao = false;
            break;
        } else if (pedido.carrinho < 1 || pedido.carrinho > numProdutos) {
            printf("Produto não encontrado!\n");
            continue;
        }

        printf("Quantidade: ");
        scanf("%d", &pedido.quantidade);

        if (pedido.quantidade < 1) {
            printf("Quantidade inválida! Deve ser maior que zero.\n");
            continue;
        }

        pedido.total_itens += pedido.quantidade;
        pedido.total += pedido.quantidade * produtos[pedido.carrinho - 1].preco;
        pedido.produtos[pedido.carrinho - 1] += pedido.quantidade; // Atualiza a quantidade do produto no pedido
    }

    if (pedido.total > 0) {
        for (int i = 0; i < numProdutos; i++) {
            if (pedido.produtos[i] > 0) {
                printf("%dX %s\n", pedido.produtos[i], produtos[i].nome);
            }
        }
        printf("Total a pagar: R$%.2f \n", pedido.total);
        processarPagamento();
    } else {
        printf("Nenhum produto foi adicionado ao carrinho.\n");
    }

    // Armazenar o pedido
    pedidos[numPedidos++] = pedido;
}

// Funções de Usuário
void lerDadosUsuario(Usuario *usuario) {
    printf("Digite o nome completo: ");
    fgets(usuario->nome, MAX_NOME, stdin);
    usuario->nome[strcspn(usuario->nome, "\n")] = '\0';

    printf("Digite o email: ");
    fgets(usuario->email, MAX_EMAIL, stdin);
    usuario->email[strcspn(usuario->email, "\n")] = '\0';

    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    fgets(usuario->data_nascimento, MAX_DATA, stdin);
    usuario->data_nascimento[strcspn(usuario->data_nascimento, "\n")] = '\0';

    do {
        printf("Digite o CPF (11 dígitos): ");
        fgets(usuario->cpf, MAX_CPF, stdin);
        usuario->cpf[strcspn(usuario->cpf, "\n")] = '\0';
    } while (strlen(usuario->cpf) != 11 || strspn(usuario->cpf, "0123456789") != strlen(usuario->cpf));

    do {
        printf("Digite o CEP (8 dígitos): ");
        fgets(usuario->cep, MAX_CEP, stdin);
        usuario->cep[strcspn(usuario->cep, "\n")] = '\0';
    } while (strlen(usuario->cep) != 8 || strspn(usuario->cep, "0123456789") != strlen(usuario->cep));
}

void exibirDadosUsuario(const Usuario *usuario) {
    printf("\nNome completo: %s\n", usuario->nome);
    printf("Email: %s\n", usuario->email);
    printf("Data de Nascimento: %s\n", usuario->data_nascimento);
    printf("CPF: %s\n", usuario->cpf);
    printf("CEP: %s\n", usuario->cep);
}

void cadastrarUsuario() {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido!\n");
        return;
    }

    printf("Cadastro de Usuário\n");
    lerDadosUsuario(&usuarios[numUsuarios]);
    numUsuarios++;

    printf("Usuário cadastrado com sucesso!\n");
}

void listarUsuarios() {
    if (numUsuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("\nUsuários cadastrados:\n");
    for (int i = 0; i < numUsuarios; i++) {
        printf("%d. %s - %s\n", i + 1, usuarios[i].nome, usuarios[i].email);
    }
}

void editarUsuario() {
    listarUsuarios();

    int escolha;
    printf("Escolha o número do usuário que deseja editar: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numUsuarios) {
        printf("Escolha inválida.\n");
        return;
    }

    getchar(); // Limpar o buffer
    lerDadosUsuario(&usuarios[escolha - 1]);
    printf("Usuário editado com sucesso!\n");
}

void excluirUsuario() {
    listarUsuarios();

    int escolha;
    printf("Escolha o número do usuário que deseja excluir: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numUsuarios) {
        printf("Escolha inválida.\n");
        return;
    }

    for (int i = escolha - 1; i < numUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1]; // Move os usuários para preencher o espaço vazio
    }

    numUsuarios--;
    printf("Usuário excluído com sucesso!\n");
}

// Funções de Fornecedor
int validarCNPJ(char *cnpj) {
    return (strlen(cnpj) == 14 && strspn(cnpj, "0123456789") == strlen(cnpj));
}

void cadastrarFornecedor() {
    if (numFornecedores >= MAX_FORNECEDORES) {
        printf("Limite de fornecedores atingido!\n");
        return;
    }

    Fornecedor fornecedor;
    printf("Digite o nome do fornecedor: ");
    fgets(fornecedor.nome, MAX_NOME, stdin);
    fornecedor.nome[strcspn(fornecedor.nome, "\n")] = '\0';

    printf("Digite o CNPJ do fornecedor (14 dígitos): ");
    fgets(fornecedor.cnpj, 20, stdin);
    fornecedor.cnpj[strcspn(fornecedor.cnpj, "\n")] = '\0';
    
    while (!validarCNPJ(fornecedor.cnpj)) {
        printf("CNPJ inválido! Tente novamente.\n");
        printf("Digite o CNPJ do fornecedor: ");
        fgets(fornecedor.cnpj, 20, stdin);
        fornecedor.cnpj[strcspn(fornecedor.cnpj, "\n")] = '\0';
    }

    printf("Digite o telefone do fornecedor: ");
    fgets(fornecedor.telefone, 15, stdin);
    fornecedor.telefone[strcspn(fornecedor.telefone, "\n")] = '\0';

    printf("Digite o email do fornecedor: ");
    fgets(fornecedor.email, MAX_EMAIL, stdin);
    fornecedor.email[strcspn(fornecedor.email, "\n")] = '\0';

    printf("Digite o contato do fornecedor: ");
    fgets(fornecedor.contato, MAX_NOME, stdin);
    fornecedor.contato[strcspn(fornecedor.contato, "\n")] = '\0';

    fornecedores[numFornecedores++] = fornecedor;
    printf("Fornecedor cadastrado com sucesso!\n");
}

void listarFornecedores() {
    if (numFornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("\nFornecedores cadastrados:\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("%d. %s - %s\n", i + 1, fornecedores[i].nome, fornecedores[i].email);
    }
}

void editarFornecedor() {
    listarFornecedores();

    int escolha;
    printf("Escolha o número do fornecedor que deseja editar: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numFornecedores) {
        printf("Escolha inválida.\n");
        return;
    }

    getchar(); // Limpar o buffer
    printf("Digite o novo nome do fornecedor: ");
    fgets(fornecedores[escolha - 1].nome, MAX_NOME, stdin);

    fornecedores[escolha - 1].nome[strcspn(fornecedores[escolha - 1].nome, "\n")] = '\0';

    printf("Digite o novo CNPJ do fornecedor: ");
    fgets(fornecedores[escolha - 1].cnpj, 20, stdin);

    fornecedores[escolha - 1].cnpj[strcspn(fornecedores[escolha - 1].cnpj, "\n")] = '\0';
    printf("Fornecedor editado com sucesso!\n");
}

void excluirFornecedor() {
    listarFornecedores();

    int escolha;
    printf("Escolha o número do fornecedor que deseja excluir: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > numFornecedores) {
        printf("Escolha inválida.\n");
        return;
    }

    for (int i = escolha - 1; i < numFornecedores - 1; i++) {
        fornecedores[i] = fornecedores[i + 1]; // Move os fornecedores para preencher o espaço vazio
    }

    numFornecedores--;
    printf("Fornecedor excluído com sucesso!\n");
}

// Funções de Pedido
void listarPedidos() {
    if (numPedidos == 0) {
        printf("Nenhum pedido realizado.\n");
        return;
    }

    printf("\nPedidos realizados:\n");
    for (int i = 0; i < numPedidos; i++) {
        printf("Pedido %d - Total: R$%.2f\n", i + 1, pedidos[i].total);
    }
}

// Funções de Pagamento
void processarPagamento() {
    printf("Pagamento processado com sucesso!\n");
}
