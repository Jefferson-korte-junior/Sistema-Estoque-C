#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "Produto.h"
#include "Fornecedor.h"
#include "Structs.h"

// Protótipos
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
    Menu Principal:
*/
int menuPrincipal() {
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
    return menuPrincipal();
}

/*
    Menu do Estoque:
*/
int menuEstoque() {
    Produto* produto = NULL;
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Estoque\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Pesquisar\n");
    printf("[2] Ver todos os Produtos\n");
    printf("[3] Cadastrar novo Produto\n");
    printf("[4] Voltar\n");
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        system("cls");
        printf("-> NADA FEITO AINDA <-\n");
        system("pause");
        break;
    case 2:
        system("cls");
        if (verProdutos() == 1) {
            printf("-> Erro ao listar produtos!\n");
        }
        system("pause");
        break;
    case 3: 
        produto = novoProduto();
        if (produto != NULL && cadastrarProduto(produto) == 0) {
            printf("-> Produto cadastrado com sucesso!\n");
        } else {
            printf("-> Erro ao cadastrar produto!\n");
        }
        system("pause");
        break;
    case 4:
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
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Clientes\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver Clientes\n");
    printf("[2] Cadastrar novo Cliente\n");
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
    return novoCliente;
}

/*
    Menu dos Fornecedores:
*/
int menuFornecedores() {
    Fornecedor* fornecedor = NULL;
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Fornecedores\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver Fornecedores\n");
    printf("[2] Cadastrar novo Fornecedor\n");
    printf("[3] Voltar\n");
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        system("cls");
        printf("-> NADA FEITO AINDA <-\n");
        system("pause");
        break;
    case 2:
        system("cls");
        if (verFornecedores() == 1) {
            printf("-> Erro ao listar produtos!\n");
        }
        system("pause");
        break;
    case 3: 
        fornecedor = novoFornecedor();
        if (fornecedor != NULL && cadastrarFornecedor(fornecedor) == 0) {
            printf("-> Produto cadastrado com sucesso!\n");
        } else {
            printf("-> Erro ao cadastrar produto!\n");
        }
        system("pause");
        break;
    case 4:
        printf("-> Voltando...\n");
        return 0;
    default:
        printf("-> Opção inválida!\n");
        system("pause");
    }
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
    int menu = 0;
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Ambiente Notas Fiscais\n");
    printf("-----------------------------------------------------\n");
    printf("[1] Ver Notas Fiscais\n");
    printf("[2] Abrir nova Nota Fiscal\n");
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
    // Aloca Endereço
    Endereco* novoEndereco = (Endereco*) malloc(sizeof(Endereco));
    if (novoEndereco == NULL) {
        return NULL;
    }
    // Rua
    printf("> Digite a rua:\n");
    if (scanf(" %[^\n]", (*novoEndereco).rua) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Bairro
    printf("> Digite o bairro:\n");
    if (scanf("%s", (*novoEndereco).bairro) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Cidade
    printf("> Digite a cidade:\n");
    if (scanf("%s", (*novoEndereco).cidade) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Estado
    printf("> Digite o estado:\n");
    if (scanf("%s", (*novoEndereco).estado) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Número
    printf("> Digite o número:\n");
    if (scanf("%d", &(*novoEndereco).numeroCasa) == 0) {
        free(novoEndereco);
        return NULL;
    }
    return novoEndereco;
}

#endif