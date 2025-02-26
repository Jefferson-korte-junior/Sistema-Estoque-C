#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "Produto.h"
#include "Cliente.h"
#include "Fornecedor.h"
#include "Structs.h"
#include "NotaFiscal.h"

// Protótipos
int menuAmbiente(char* ambiente);
int menuPrincipal();  
int menuEstoque();
Produto* novoProduto();
int menuClientes();
Cliente* novoCliente();
int menuFornecedores();
Fornecedor* novoFornecedor();
int menuNotasFiscais();
NotaFiscal* novaNotaFiscal();


/*
    Cabecalho:
*/
int menuAmbiente(char* ambiente) {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                   %s\n", ambiente);
    printf("-----------------------------------------------------\n\n");
    printf("Selecione:\n");
    printf("[1] > Pesquisar\n");
    printf("[2] > Vizualizar\n");
    printf("[3] > Novo\n");
    printf("[4] > Editar\n");
    printf("[5] < Voltar\n");
    return 0;
}

/*
    Menu para Nota Fiscal:
*/
int MenuCompra() {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                   Nota Fiscal\n");
    printf("-----------------------------------------------------\n\n");
    printf("Selecione:\n");
    printf("[1] > Realizar Compra\n");
    printf("[2] > Vizualizar Notas Fiscais\n");
    printf("[3] < Voltar\n");
    return 0;
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
        buscarProduto();
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Itens no Estoque e se tem ja mostra
        int vf = verEstoque(1);
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
        system("cls");
        editarProduto();
        break;
    case 5:
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
    Menu dos Clientes:
*/
int menuClientes() {
    // Ponteiro para Cliente
    Cliente* cliente = NULL;
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Cliente");
    // Lê a opção
    scanf("%d", &menu);
    switch (menu) {
    case 1:
        system("cls");
        buscarCliente();
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Clientes e se tem ja mostra
        int vf = verClientes(1);
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
        system("cls");
        editarCliente();
        break;
    case 5:
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
    Menu dos Fornecedores:
*/
int menuFornecedores() {
    // Ponteiro para Fornecedor
    Fornecedor* fornecedor = NULL;
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    menuAmbiente("Ambiente Fornecedores");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch (menu) {
    case 1:
        system("cls");
        buscarFornecedor();
        system("pause");
        break;
    case 2:
        // Limpa a tela
        system("cls");
        // Verifica se ha Fornecedores e se tem ja mostra
        int vf = verFornecedores(1);
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
        system("cls");
        editarFornecedor();
        break;
    case 5:
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
    Menu dos Notas Fiscais:
*/
int menuNotasFiscais() {
    // Variável de Menu
    int menu = 0;
    // Exibe o menu
    MenuCompra("Ambiente Nota Fiscal");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch(menu) {
    case 1:
        realizarCompra();
        break;
    case 2:
        mostrarNotasFiscais();
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



#endif