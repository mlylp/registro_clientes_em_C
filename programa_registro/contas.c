#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    unsigned int numero_conta;
    float saldo;
} Cliente;

FILE *arqptr = NULL;

void cadastrar_cliente() {
    Cliente c;
    int posicao;

    printf("\nPosicao do registro: ");
    scanf("%d", &posicao);
    getchar();

    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Numero da conta: ");
    scanf("%u", &c.numero_conta);

    printf("Saldo: ");
    scanf("%f", &c.saldo);

    fseek(arqptr, posicao * sizeof(Cliente), SEEK_SET);

    fwrite(&c, sizeof(Cliente), 1, arqptr);

    if (ferror(arqptr)) {
        printf("\nErro ao gravar cliente.\n");
    } else {
        printf("\nCliente cadastrado com sucesso!\n");
    }
}

void consultar_cliente() {
    Cliente c;
    unsigned int conta;
    int encontrou = 0;

    printf("\nDigite o numero da conta: ");
    scanf("%u", &conta);

    rewind(arqptr);

    while (fread(&c, sizeof(Cliente), 1, arqptr) == 1) {
        if (c.numero_conta == conta) {
            printf("\n--- CLIENTE ENCONTRADO ---\n");
            printf("Nome: %s\n", c.nome);
            printf("Conta: %u\n", c.numero_conta);
            printf("Saldo: R$ %.2f\n", c.saldo);
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("\nCliente nao encontrado.\n");
    }
}

void atualizar_saldo() {
    Cliente c;
    unsigned int conta;
    float novo_saldo;
    int encontrou = 0;

    printf("\nDigite o numero da conta: ");
    scanf("%u", &conta);

    rewind(arqptr);

    while (fread(&c, sizeof(Cliente), 1, arqptr) == 1) {

        if (c.numero_conta == conta) {

            printf("Saldo atual: R$ %.2f\n", c.saldo);

            printf("Novo saldo: ");
            scanf("%f", &novo_saldo);

            c.saldo = novo_saldo;

            fseek(arqptr, -sizeof(Cliente), SEEK_CUR);

            fwrite(&c, sizeof(Cliente), 1, arqptr);

            printf("\nSaldo atualizado com sucesso!\n");

            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("\nConta nao encontrada.\n");
    }
}

void encerrar_conta() {
    Cliente c;
    Cliente vazio = {"", 0, 0.0};
    unsigned int conta;
    int encontrou = 0;

    printf("\nDigite o numero da conta: ");
    scanf("%u", &conta);

    rewind(arqptr);

    while (fread(&c, sizeof(Cliente), 1, arqptr) == 1) {

        if (c.numero_conta == conta) {

            fseek(arqptr, -sizeof(Cliente), SEEK_CUR);

            fwrite(&vazio, sizeof(Cliente), 1, arqptr);

            printf("\nConta encerrada com sucesso!\n");

            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("\nConta nao encontrada.\n");
    }
}

void listar_clientes() {
    Cliente c;
    int encontrou = 0;

    printf("\n=== LISTA DE CLIENTES ===\n");

    while (fread(&c, sizeof(Cliente), 1, arqptr) == 1) {

        if (c.numero_conta != 0) {

            printf("\nNome: %s\n", c.nome);
            printf("Conta: %u\n", c.numero_conta);
            printf("Saldo: R$ %.2f\n", c.saldo);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("\nNenhum cliente cadastrado.\n");
    }
}

void restaurar_leitura() {
    rewind(arqptr);
    printf("\nLeitura reposicionada para o inicio do arquivo.\n");
}

int main() {

    int opcao;

    arqptr = fopen("usuarios.dat", "rb+");

    if (arqptr == NULL) {
        arqptr = fopen("usuarios.dat", "wb+");

        if (arqptr == NULL) {
            printf("Erro ao criar arquivo.\n");
            return 1;
        }
    }

    do {

        printf("\n============================");
        printf("\n SISTEMA DE CONTAS BANCARIAS");
        printf("\n============================");
        printf("\n1 - Cadastrar cliente");
        printf("\n2 - Consultar cliente");
        printf("\n3 - Atualizar saldo");
        printf("\n4 - Encerrar conta");
        printf("\n5 - Listar clientes");
        printf("\n6 - Restaurar leitura (rewind)");
        printf("\n7 - Encerrar sistema");
        printf("\n\nEscolha uma opcao: ");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                cadastrar_cliente();
                break;

            case 2:
                consultar_cliente();
                break;

            case 3:
                atualizar_saldo();
                break;

            case 4:
                encerrar_conta();
                break;

            case 5:
                listar_clientes();
                break;

            case 6:
                restaurar_leitura();
                break;

            case 7:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 7);

    fclose(arqptr);

    return 0;
}