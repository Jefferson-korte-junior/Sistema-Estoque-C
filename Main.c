#include <stdio.h>
#include <stdlib.h>

/*
    Structs:
*/
// Produto
typedef struct {
    char nome[50];        
    float valorCompra;  
    float valorVenda;   
    float lucro;         
    int qtdVendas;        
} Produto;

// Endereço
typedef struct {
    char rua[50];
    char bairro[20];
    char cidade[20];
    char estado[50];
    int numeroCasa;
} Endereco;

// Cliente
typedef struct{
    char nome[50];
    char cpf[15];
    char telefone;
    Endereco endereco;
    char Email[50];
} Cliente;

// Fornecedor
typedef struct {
    char nomeFantasia[50];
    char CNPJ[15];
    Endereco endereco;
    char email[25];
    char telefone[25];
} Fornecedor;

// Compras
typedef struct {
    Produto produto;
    int qtdProduto;
    float valor;
} Compra;
 
// Nota Fiscal
typedef struct {
    Compra *compras;
    float valorTotal; 
    Cliente cliente;
    char formaPagamento[25];
    char status[30];
} NotaFiscal;

/*
    Funções:
*/
void menuEstoque();
void menuClientes();
void menuFornecedores();
void menuNotasFiscais();
Produto* novoProduto();

/*
    Main:
*/
int main() {

    // Vars.
    int menu = 0;

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
    case 5:
        printf("-> Saindo...\n");
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
    system("cls");

    return main();
}

/*
    Menu do Estoque:
*/
void menuEstoque() {
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Estoque\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver lista de Produtos\n");
    printf("[2] Cadastrar\n");
    printf("[3] Voltar\n");
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        break;
    case 2: {
        Produto* produto = novoProduto();
        if (produto == NULL) {
            printf("-> Erro ao cadastrar produto!\n");
            system("pause");
        } else {
            printf("-> Produto cadastrado com sucesso!\n");
            system("pause");
        }
        break;
    }
    case 3:
        printf("-> Voltando...\n");
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
    return menuEstoque();
}

/*
    Novo Produto:
*/
Produto* novoProduto() {
    // Aloca Produto
    Produto* novoProduto = (Produto*) malloc(sizeof(Produto));
    if (novoProduto == NULL) {
        return NULL;
    }
    // Nome
    system("cls");
    printf("> Digite o nome:\n");
    if (scanf(" %[^\n]", (*novoProduto).nome) == 1) {
        free(novoProduto);
        return NULL;
    }
    // Valor Compra
    printf("> Digite o valor de Compra:\n");
    if (scanf("%f", &(*novoProduto).valorCompra) == 1) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite o valor de Venda:\n");
    if (scanf("%f", &(*novoProduto).valorVenda) == 1) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite o valor de Venda:\n");
    if (scanf("%f", &(*novoProduto).valorVenda) == 1) {
        free(novoProduto);
        return NULL;
    }
    // Valor de Lucro
    printf("> Digite o valor de Venda:\n");
    if (scanf("%f", &(*novoProduto).lucro) == 1) {
        free(novoProduto);
        return NULL;
    }
    return novoProduto;
}

/*
    Menu dos Clientes:
*/
void menuClientes() {
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Clientes\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver lista de Clientes\n");
    printf("[2] Cadastrar\n");
    printf("[3] Voltar\n");
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
    return menuClientes();
}

/*
    Menu dos Fornecedores:
*/
void menuFornecedores() {
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Fornecedores\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver lista de Fornecedores\n");
    printf("[2] Cadastrar\n");
    printf("[3] Voltar\n");
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
    return menuFornecedores();
}

/*
    Menu dos Notas Fiscais:
*/
void menuNotasFiscais() {
    int menu = 0;
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
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
    return menuNotasFiscais();
}