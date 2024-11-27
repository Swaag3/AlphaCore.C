#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char nome[100];
    char telefone[15];
    char cnpj[20];
    char cep[10];
    char dataCadastro[11];
    char email[100];
    char contato[100];
} Fornecedor;

int validarCNPJ(char *cnpj) {
    char cnpjLimpo[20];
    int j = 0;
    for (int i = 0; cnpj[i] != '\0'; i++) {
        if (isdigit(cnpj[i])) {
            cnpjLimpo[j++] = cnpj[i];
        }
    }
    cnpjLimpo[j] = '\0';
    
    if (strlen(cnpjLimpo) != 14) {
        return 0; 
    }

    return 1; 
}

int main() {
    Fornecedor fornecedor; 

    printf("==== Cadastro de Fornecedores - AlphaCore ====\n\n");

    printf("ID do Fornecedor: ");
    scanf("%d", &fornecedor.id);
    getchar(); 

    printf("Nome do Fornecedor: ");
    fgets(fornecedor.nome, sizeof(fornecedor.nome), stdin);

    printf("Telefone (XX XXXXX-XXXX): ");
    fgets(fornecedor.telefone, sizeof(fornecedor.telefone), stdin);

    while (1) {
        printf("CNPJ (XX.XXX.XXX/XXXX-XX): ");
        fgets(fornecedor.cnpj, sizeof(fornecedor.cnpj), stdin);
        if (validarCNPJ(fornecedor.cnpj)) {
            break; 
        } else {
            printf("CNPJ inválido. Tente novamente.\n");
        }
    }

    printf("CEP (XXXXX-XXX): ");
    fgets(fornecedor.cep, sizeof(fornecedor.cep), stdin);

    printf("Data de Cadastro (DD/MM/AAAA): ");
    fgets(fornecedor.dataCadastro, sizeof(fornecedor.dataCadastro), stdin);

    printf("Email: ");
    fgets(fornecedor.email, sizeof(fornecedor.email), stdin);

    printf("Contato do Fornecedor: ");
    fgets(fornecedor.contato, sizeof(fornecedor.contato), stdin);

    printf("\n==== Fornecedor Cadastrado ====\n");
    printf("ID: %d\n", fornecedor.id);
    printf("Nome: %s", fornecedor.nome);
    printf("Telefone: %s", fornecedor.telefone);
    printf("CNPJ: %s", fornecedor.cnpj);
    printf("CEP: %s", fornecedor.cep);
    printf("Data de Cadastro: %s", fornecedor.dataCadastro);
    printf("Email: %s", fornecedor.email);
    printf("Contato: %s", fornecedor.contato);

    return 0;
}