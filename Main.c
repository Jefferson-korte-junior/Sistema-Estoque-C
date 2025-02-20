#include <stdio.h>
#include <stdlib.h>

// Funções
void menuEstoque();
void menuClientes();
void menuFornecedores();
void menuNotasFiscais();

int main() {

    // Vars.
    int sair = 0;
    int menu = 0;

    // Menu Principal
    while (sair == 0) {
        printf("-----------------------------------------------------\n");
        printf("                Sistema Estoque IBJM\n");
        printf("-----------------------------------------------------\n");
        printf("> Selecione o Ambiente:\n");
        printf("[1] Estoque\n");
        printf("[2] Clientes\n");
        printf("[3] Fornecedores\n");
        printf("[4] Notas Fiscais\n");
        printf("[5] Sair\n");
        scanf("%d", &menu);

        switch(menu) {
        case 1:
            menuEstoque();
            break;
        case 2:
            menuClientes();
            break;
        case 3:
            menuFornecedores();
            break;
        case 4:
            menuNotasFiscais();
            break;
        default:
            printf("-> Opção inválida!\n");
            system("pause");
        }
        system("cls");
    }

    return 0;
}

/*
    Menu do Estoque.
*/
void menuEstoque() {
    int menu = 0;
    int voltar = 0;
    while (voltar == 0) {
        system("cls");
        printf("-----------------------------------------------------\n");
        printf("                  Ambiente Estoque\n");
        printf("-----------------------------------------------------\n");
        printf("[1] Ver lista de Produtos\n");
        printf("[2] Cadastrar\n");
        printf("[3] Voltar\n");
        scanf("%d", &menu);

        switch(menu) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            voltar = 1;
            break;
        default:
            printf("-> Opção inválida!\n");
            system("pause");
        }
    }
}

/*
    Menu dos Clientes.
*/
void menuClientes() {
    int menu = 0;
    int voltar = 0;
    while (voltar == 0) {
        system("cls");
        printf("-----------------------------------------------------\n");
        printf("                  Ambiente Clientes\n");
        printf("-----------------------------------------------------\n");
        printf("[1] Ver lista de Clientes\n");
        printf("[2] Cadastrar\n");
        printf("[3] Voltar\n");
        scanf("%d", &menu);

        switch(menu) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            voltar = 1;
            break;
        default:
            printf("-> Opção inválida!\n");
            system("pause");
        }
    }
}

/*
    Menu dos Fornecedores.
*/
void menuFornecedores() {
    int menu = 0;
    int voltar = 0;
    while (voltar == 0) {
        system("cls");
        printf("-----------------------------------------------------\n");
        printf("                  Ambiente Fornecedores\n");
        printf("-----------------------------------------------------\n");
        printf("[1] Ver lista de Fornecedores\n");
        printf("[2] Cadastrar\n");
        printf("[3] Voltar\n");
        scanf("%d", &menu);

        switch(menu) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            voltar = 1;
            break;
        default:
            printf("-> Opção inválida!\n");
            system("pause");
        }
    }
}

/*
    Menu dos Notas Fiscais.
*/
void menuNotasFiscais() {
    int menu = 0;
    int voltar = 0;
    while (voltar == 0) {
        system("cls");
        printf("-----------------------------------------------------\n");
        printf("                  Ambiente Notas Fiscais\n");
        printf("-----------------------------------------------------\n");
        printf("[1] Ver lista de Fornecedores\n");
        printf("[2] Cadastrar\n");
        printf("[3] Voltar\n");
        scanf("%d", &menu);

        switch(menu) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            voltar = 1;
            break;
        default:
            printf("-> Opção inválida!\n");
            system("pause");
        }
    }
}