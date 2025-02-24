#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "Produto.h"
#include "Cliente.h"
#include "Fornecedor.h"
#include "Structs.h"

// Protótipos
void msgCaixa(char* preMsg, int tamanhoString, char* msg, int tamanhoString2);
void menuAmbiente(char* ambiente);
int menuPrincipal();  
int menuEstoque();
Produto* novoProduto();
int menuClientes();
Cliente* novoCliente();
int menuFornecedores();
Fornecedor* novoFornecedor();
int menuNotasFiscais();
NotaFiscal* novaNotaFiscal();
Endereco* novoEndereco();

/*
    Caixa:
*/
void msgCaixa(char* preMsg, int tamanhoString, char* msg, int tamanhoString2) {
    printf("// %s%s", preMsg, msg);
    for (int i = tamanhoString+tamanhoString2+9; i < 57; i++) {
        printf(" ");
    }
    printf("//\n");
}

/*
    Cabecalho:
*/
void menuAmbiente(char* ambiente) {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                   %s\n", ambiente);
    printf("-----------------------------------------------------\n\n");
    printf("Selecione:\n");
    printf("[1] > Pesquisar\n");
    printf("[2] > Vizualizar\n");
    printf("[3] > Novo\n");
    printf("[4] < Voltar\n");
}

/*
    Menu Principal:
*/
int menuPrincipal() {
    // Vars.
    int menu = 0;
    printf("-----------------------------------------------------\n");
    printf("                Sistema Estoque IBJM\n");
    printf("-----------------------------------------------------\n\n");
    printf("Selecione:\n");
    printf("[1] > Estoque\n");
    printf("[2] > Clientes\n");
    printf("[3] > Fornecedores\n");
    printf("[4] > Notas Fiscais\n");
    printf("[5] < Sair\n");
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
        printf("-> Opcao invalida!\n");
        system("pause");
    }
    system("cls");
    return menuPrincipal();
}

/*
    Menu do Estoque:
*/
int menuEstoque() {
    // Ponteiro para Produto
    Produto* produto = NULL;
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Estoque");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch (menu) {
    case 1:
        system("cls");
        printf("-> NADA FEITO AINDA <-\n");
        system("pause");
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Itens no Estoque e se tem ja mostra
        int vf = verEstoque();
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar itens do Estoque!\n");
        } 
        // Verifica se nao ha nenhum Item
        else if (vf == -1) {
            printf("-> Ainda nao ha nenhum Item cadastrado no Estoque!\n");
        }
        break;
    case 3: 
        // Cria um novo Produto
        produto = novoProduto();
        // Verifica se o Produto foi criado e se foi cadastrado
        if (produto != NULL && cadastrarProduto(produto) == 0) {
            printf("-> Produto cadastrado com sucesso!\n");
        }
        // Se nao foi cadastrado 
        else {
            printf("-> Erro ao cadastrar Produto!\n");
        }
        break;
    case 4:
        // Volta a tela inicial
        return 0;
    default:
        printf("-> Opcao invalida!\n");
    }
    // Pausa para vizualizar
    system("pause");
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
    if (scanf(" %[^\n]", (*novoProduto).nome) == 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor Compra
    printf("> Digite o valor de Compra:\n");
    if (scanf("%f", &(*novoProduto).valorCompra) == 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite o valor de Venda:\n");
    if (scanf("%f", &(*novoProduto).valorVenda) == 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite a quantidade em Estoque:\n");
    if (scanf("%d", &(*novoProduto).qtd) == 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor de Lucro
    (*novoProduto).lucro = (*novoProduto).valorVenda - (*novoProduto).valorCompra;
    if ((*novoProduto).lucro < 0) {
        free(novoProduto);
        return NULL;
    }
    // Data de Cadastro
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    (*novoProduto).dataCadastro.dia = tm.tm_mday;
    (*novoProduto).dataCadastro.mes = tm.tm_mon + 1;
    (*novoProduto).dataCadastro.ano = tm.tm_year + 1900;
    return novoProduto;
}

/*
    Menu dos Clientes:
*/
int menuClientes() {
    // Ponteiro para Cliente
    Cliente* cliente = NULL;
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Estoque");
    // Lê a opção
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        // Nada feito ainda
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Clientes e se tem ja mostra
        int vf = verClientes();
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar Clientes!\n");
        } 
        // Verifica se nao ha nenhum Cliente
        else if (vf == -1) {
            printf("-> Ainda nao ha nenhum Cliente cadastrado!\n");
        }
        break;
    case 3: 
        // Cria um novo Cliente
        cliente = novoCliente();
        // Verifica se o Cliente foi criado e se foi cadastrado
        if (cliente != NULL && cadastrarCliente(cliente) == 0) {
            printf("-> Cliente cadastrado com sucesso!\n");
        } 
        // Se nao foi cadastrado
        else {
            printf("-> Erro ao cadastrar Cliente!\n");
        }
        break;
    case 4:
        // Volta a tela anterior
        return 0;
    default:
        printf("-> Opcao invalida!\n");
    }
    // Pausa para vizualizar
    system("pause");
    return menuClientes();
}

/*
    Novo Cliente:
*/
Cliente* novoCliente() {
    // Aloca Cliente
    Cliente* novoCliente = (Cliente*) malloc(sizeof(Cliente));
    if (novoCliente == NULL) {
        return NULL;
    }
    // Nome
    system("cls");
    printf("> Digite o nome:\n");
    if (scanf(" %[^\n]", (*novoCliente).nome) == 0) {
        free(novoCliente);
        return NULL;
    }
    // Cnpj
    printf("> Digite o CPF:\n");
    if (scanf(" %s", (*novoCliente).cpf) == 0) {
        free(novoCliente);
        return NULL;
    }
    // Telefone
    printf("> Digite o Telefone:\n");
    if (scanf(" %s", (*novoCliente).telefone) == 0) {
        free(novoCliente);
        return NULL;
    }
    // Endereço
    (*novoCliente).endereco = novoEndereco();
    if ((*novoCliente).endereco == NULL) {
        free(novoCliente);
        return NULL;
    }
    // Email
    printf("> Digite o email:\n");
    if (scanf(" %s", (*novoCliente).email) == 0) {
        free(novoCliente);
        return NULL;
    }
    // Data de Cadastro
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    (*novoCliente).dataCadastro.dia = tm.tm_mday;
    (*novoCliente).dataCadastro.mes = tm.tm_mon + 1;
    (*novoCliente).dataCadastro.ano = tm.tm_year + 1900;
    return novoCliente;
}

/*
    Menu dos Fornecedores:
*/
int menuFornecedores() {
    // Ponteiro para Fornecedor
    Fornecedor* fornecedor = NULL;
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Estoque");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch (menu) {
    case 1:
        system("cls");
        printf("-> NADA FEITO AINDA <-\n");
        system("pause");
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Fornecedores e se tem ja mostra
        int vf = verFornecedores();
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar Fornecedores!\n");
        } 
        // Verifica se nao ha nenhum Fornecedor
        else if (vf == -1) {
            printf("-> Ainda nao ha nenhum Fornecedor cadastrado!\n");
        }
        break;
    case 3: 
        // Cria um novo Fornecedor
        fornecedor = novoFornecedor();
        // Verifica se o Fornecedor foi criado e se foi cadastrado
        if (fornecedor != NULL && cadastrarFornecedor(fornecedor) == 0) {
            printf("-> Fornecedor cadastrado com sucesso!\n");
        } 
        // Se nao foi cadastrado
        else {
            printf("-> Erro ao cadastrar Fornecedor!\n");
        }
        break;
    case 4:
        // Volta a tela anterior
        return 0;
    default:
        printf("-> Opcao invalida!\n");
    }
    // Pausa para vizualizar
    system("pause");
    return menuFornecedores();
}

/*
    Novo Fornecedor:
*/
Fornecedor* novoFornecedor() {
    // Aloca Fornecedor
    Fornecedor* novoFornecedor = (Fornecedor*) malloc(sizeof(Fornecedor));
    if (novoFornecedor == NULL) {
        return NULL;
    }
    // Nome Fantasia
    system("cls");
    printf("> Digite o nome Fantasia:\n");
    if (scanf(" %[^\n]", (*novoFornecedor).nomeFantasia) == 0) {
        free(novoFornecedor);
        return NULL;
    }
    // Cnpj
    printf("> Digite o CNPJ:\n");
    if (scanf(" %s", (*novoFornecedor).cnpj) == 0) {
        free(novoFornecedor);
        return NULL;
    }
    // Telefone
    printf("> Digite o Telefone:\n");
    if (scanf(" %s", (*novoFornecedor).telefone) == 0) {
        free(novoFornecedor);
        return NULL;
    }
    // Endereço
    (*novoFornecedor).endereco = novoEndereco();
    if ((*novoFornecedor).endereco == NULL) {
        free(novoFornecedor);
        return NULL;
    }
    // Email
    printf("> Digite o email:\n");
    if (scanf(" %s", (*novoFornecedor).email) == 0) {
        free(novoFornecedor);
        return NULL;
    }
    return novoFornecedor;
}

/*
    Menu dos Notas Fiscais:
*/
int menuNotasFiscais() {
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Estoque");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch(menu) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        return 0;
    default:
        printf("-> Opcao invalida!\n");
    }
    // Pausa para vizualizar
    system("pause");
    return menuNotasFiscais();
}

NotaFiscal* novaNotaFiscal() {
    // Aloca Nota Fiscal
    NotaFiscal* novaNotaFiscal = (NotaFiscal*) malloc(sizeof(NotaFiscal));
    if (novaNotaFiscal == NULL) {
        return NULL;
    }
    // Compras
    return novaNotaFiscal;
}

/*
    Novo Endereço:
*/
Endereco* novoEndereco() {
    // Aloca memória para o endereço
    Endereco* novoEndereco = (Endereco*) malloc(sizeof(Endereco));
    if (novoEndereco == NULL) {
        return NULL;
    }
    // Rua
    printf("> Digite a rua:\n");
    if (scanf(" %[^\n]", novoEndereco->rua) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Bairro
    printf("> Digite o bairro:\n");
    if (scanf(" %[^\n]", novoEndereco->bairro) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Cidade
    printf("> Digite a cidade:\n");
    if (scanf(" %[^\n]", novoEndereco->cidade) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Estado
    printf("> Digite o estado:\n");
    if (scanf(" %[^\n]", novoEndereco->estado) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Número
    printf("> Digite o numero da casa:\n");
    if (scanf("%d", &novoEndereco->numeroCasa) == 0) {
        free(novoEndereco);
        return NULL;
    }
    return novoEndereco;
}

#endif