#include <stdio.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_DATA 11
#define MAX_CPF 12
#define MAX_CEP 9
#define MAX_USUARIOS 100

typedef struct {
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char data_nascimento[MAX_DATA];
    char cpf[MAX_CPF];
    char cep[MAX_CEP];
} Usuario;

void lerDadosUsuario(Usuario *usuario) {
    printf("Digite o nome completo: ");
    fgets(usuario->nome, MAX_NOME, stdin);
    usuario->nome[strcspn(usuario->nome, "\n")] = 0; // Remove a nova linha do final

    printf("Digite o email: ");
    fgets(usuario->email, MAX_EMAIL, stdin);
    usuario->email[strcspn(usuario->email, "\n")] = 0;

    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    fgets(usuario->data_nascimento, MAX_DATA, stdin);
    usuario->data_nascimento[strcspn(usuario->data_nascimento, "\n")] = 0;

    do {
        printf("Digite o CPF (11 dígitos): ");
        fgets(usuario->cpf, MAX_CPF, stdin);
        usuario->cpf[strcspn(usuario->cpf, "\n")] = 0;
    } while (strlen(usuario->cpf) != 11 || strspn(usuario->cpf, "0123456789") != 11); // Valida CPF

    do {
        printf("Digite o CEP (8 dígitos): ");
        fgets(usuario->cep, MAX_CEP, stdin);
        usuario->cep[strcspn(usuario->cep, "\n")] = 0;
    } while (strlen(usuario->cep) != 8 || strspn(usuario->cep, "0123456789") != 8); // Valida CEP
}

void exibirDadosUsuario(const Usuario *usuario) {
    printf("\nNome completo: %s\n", usuario->nome);
    printf("Email: %s\n", usuario->email);
    printf("Data de nascimento: %s\n", usuario->data_nascimento);
    printf("CPF: %s\n", usuario->cpf);
    printf("CEP: %s\n", usuario->cep);
}

void listarUsuarios(Usuario usuarios[], int total) {
    if (total == 0) {
        printf("\nNenhum cadastro encontrado.\n");
        return;
    }
    
    printf("\nLista de Cadastros:\n");
    for (int i = 0; i < total; i++) {
        printf("\nCadastro %d:\n", i + 1);
        exibirDadosUsuario(&usuarios[i]);
    }
}

void editarUsuario(Usuario *usuario) {
    printf("\nEditando Cadastro:\n");
    lerDadosUsuario(usuario); 
}

void excluirUsuario(Usuario usuarios[], int *total) {
    int index;
    
    listarUsuarios(usuarios, *total); 
    if (*total == 0) return; 
    
    printf("\nDigite o número do cadastro a ser excluído: ");
    scanf("%d", &index);
    
    if (index < 1 || index > *total) {
        printf("Número inválido!\n");
        return;
    }

    for (int i = index - 1; i < *total - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    
    (*total)--; 
    printf("Cadastro excluído com sucesso!\n");
}

int main() {
    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0; 
    int opcao;

    do {
        printf("\n==== Menu ====\n");
        printf("1. Adicionar Cadastro\n");
        printf("2. Listar Cadastros\n");
        printf("3. Editar Cadastro\n");
        printf("4. Excluir Cadastro\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                if (totalUsuarios < MAX_USUARIOS) {
                    lerDadosUsuario(&usuarios[totalUsuarios]);
                    totalUsuarios++;
                    printf("Cadastro adicionado com sucesso!\n");
                } else {
                    printf("Limite de cadastros atingido!\n");
                }
                break;
            case 2:
                listarUsuarios(usuarios, totalUsuarios);
                break;
            case 3:
                if (totalUsuarios == 0) {
                    printf("Nenhum cadastro disponível para editar.\n");
                } else {
                    int index;
                    listarUsuarios(usuarios, totalUsuarios); // Lista antes de editar
                    printf("\nDigite o número do cadastro a ser editado: ");
                    scanf("%d", &index);

                    if (index < 1 || index > totalUsuarios) {
                        printf("Número inválido!\n");
                    } else {
                        editarUsuario(&usuarios[index - 1]); // Edita o usuário escolhido
                        printf("Cadastro editado com sucesso!\n");
                    }
                }
                break;
            case 4:
                excluirUsuario(usuarios, &totalUsuarios);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 5);

    return 0;
}