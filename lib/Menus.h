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
    printf("                    Nota Fiscal\n");
    printf("-----------------------------------------------------\n\n");
    printf("Selecione:\n");
    printf("[1] > Abrir nova Nota Fiscal\n");
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
        if (menuEstoque() != 0) {
            printf("Erro ao executar o menu de estoque.\n");
        }
        break;
    case 2:
        if (menuClientes() != 0) {
            printf("Erro ao executar o menu de clientes.\n");
        }
        break;
    case 3:
        if (menuFornecedores() != 0) {
            printf("Erro ao executar o menu de fornecedores.\n");
        }
        break;
    case 4:
        if (menuNotasFiscais() != 0) {
            printf("Erro ao executar o menu de notas fiscais.\n");
        }
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
    // Variavel de verificação
    int vf = 0;
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
        vf = listarProdutos(1);
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar itens do Estoque!\n");
        } 
        // Verifica se nao ha nenhum Item
        else if (vf == -1) {
            printf("\n-> Ainda nao ha nenhum Item cadastrado no Estoque!\n\n");
        }
        break;
    case 3: 
        // Cria um novo Produto
        produto = novoProduto();
        // Verifica se o Produto foi criado e se foi cadastrado
        if (produto != NULL && cadastrarProduto(produto) == 0) {
            system("cls");
            printf("\n-> Produto cadastrado com sucesso!\n\n");
        }
        // Se nao foi cadastrado 
        else {
            printf("-> Problema ao cadastrar Produto!\n");
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
    // Variavel de verificação
    int vf = 0;
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
        vf = listarClientes(1);
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar Clientes!\n");
        } 
        // Verifica se nao ha nenhum Cliente
        else if (vf == -1) {
            printf("\n-> Ainda nao ha nenhum Cliente cadastrado!\n\n");
        }
        break;
    case 3: 
        // Cria um novo Cliente
        cliente = novoCliente();
        // Verifica se o Cliente foi criado e se foi cadastrado
        if (cliente != NULL && cadastrarCliente(cliente) == 0) {
            system("cls");
            printf("\n-> Cliente cadastrado com sucesso!\n\n");
        } 
        // Se nao foi cadastrado
        else {
            printf("-> Problema ao cadastrar Cliente!\n");
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
    // Variavel de verificação
    int vf = 0;
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
        vf = listarFornecedores(1);
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar Fornecedores!\n");
        } 
        // Verifica se nao ha nenhum Fornecedor
        else if (vf == -1) {
            printf("\n-> Ainda nao ha nenhum Fornecedor cadastrado!\n\n");
        }
        break;
    case 3: 
        // Cria um novo Fornecedor
        fornecedor = novoFornecedor();
        // Verifica se o Fornecedor foi criado e se foi cadastrado
        if (fornecedor != NULL && cadastrarFornecedor(fornecedor) == 0) {
            system("cls");
            printf("\n-> Fornecedor cadastrado com sucesso!\n\n");
        } 
        // Se nao foi cadastrado
        else {
            printf("-> Problema ao cadastrar Fornecedor!\n");
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
    // Variavel de verificação
    int vf = 0;
    // Exibe o menu
    MenuCompra("Ambiente Nota Fiscal");
    // Lê a opção
    scanf("%d", &menu);
    // Verifica a opção escolhida
    switch(menu) {
    case 1:
        // Limpa a tela
        system("cls");
        // Verifica se ha Notas Fiscais e se tem ja mostra
        vf = listarNotasFiscais(1);
        // Verifica se houve algum problema
        if (vf == 1) {
            printf("-> Problema ao listar as Notas Fiscais!\n");
        } 
        // Verifica se nao ha nenhuma Nota Fiscal
        else if (vf == -1) {
            printf("\n-> Ainda nao ha nenhuma Nota Fiscal cadastrada!\n\n");
        }
        break;
    case 2:
        vf = novaNotaFiscal();
        if (vf == -1) {
            printf("-> Voce nao adicionou nenhum item a nota!\n");
        } else if (vf == 1) {
            printf("-> Problema ao abrir Nota Fiscal!");
        }
        break;
    case 3:
        // Volta a tela anterior
        return 0;
    default:
        printf("-> Opcao invalida!\n");
    }
    // Pausa para vizualizar
    system("pause");
    return menuNotasFiscais();
}

#endif