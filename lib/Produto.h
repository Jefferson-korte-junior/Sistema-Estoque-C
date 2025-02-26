#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include "Menus.h"	
#include "Endereco.h"

#define PATH_PRODUTO "../txt/Produtos.txt"

// Protótipos
Produto* novoProduto();
int cadastrarProduto(Produto* produto);
int editarProduto();
int buscarProduto();
void mostrarProduto(Produto produto);
int listarProdutos(int ver);
int zerarProdutos();

/*
    Novo Produto:
*/
Produto* novoProduto() {
    // Aloca Produto
    Produto* novoProduto = (Produto*) malloc(sizeof(Produto));
    if (novoProduto == NULL) {
        return NULL;
    }
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                    Novo Produto\n");
    printf("-----------------------------------------------------\n\n");
    // Nome
    printf("> Digite o nome:\n");
    if (scanf(" %[^\n]", novoProduto->nome) == 0 || strlen(novoProduto->nome) <= 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor Compra
    printf("> Digite o valor de Compra:\n");
    if (scanf("%f", &novoProduto->valorCompra) == 0 || novoProduto->valorCompra <= 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite o valor de Venda:\n");
    if (scanf("%f", &novoProduto->valorVenda) == 0 || novoProduto->valorVenda < novoProduto->valorCompra) {
        free(novoProduto);
        return NULL;
    }
    // Valor Venda
    printf("> Digite a quantidade em Produtos:\n");
    if (scanf("%d", &novoProduto->qtd) == 0 || novoProduto->qtd <= 0) {
        free(novoProduto);
        return NULL;
    }
    // Valor de Lucro
    novoProduto->lucro = novoProduto->valorVenda - novoProduto->valorCompra;
    if (novoProduto->lucro < 0) {
        free(novoProduto);
        return NULL;
    }
    // Data de Cadastro
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    novoProduto->dataCadastro.dia = tm.tm_mday;
    novoProduto->dataCadastro.mes = tm.tm_mon + 1;
    novoProduto->dataCadastro.ano = tm.tm_year + 1900;
    return novoProduto;
}

/*
    Cadastra um produto.
*/
int cadastrarProduto(Produto* produto) {
    // Abre o arquivo
    FILE* txt = fopen(PATH_PRODUTO, "a");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Escreve no arquivo os dados
    fprintf(txt, "%s\n%.2f\n%.2f\n%.2f\n%d\n%02d/%02d/%02d\n\n",
    produto->nome,
    produto->valorCompra,
    produto->valorVenda,    
    produto->lucro, 
    produto->qtd,
    produto->dataCadastro.dia,
    produto->dataCadastro.mes,
    produto->dataCadastro.ano);
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Editar Produto:
*/
int editarProduto() {
    char nome[35];
    printf("--------------------------------------------\n");
    printf("Digite o nome do Produto que deseja editar: ");
    scanf(" %[^\n]", nome);
    printf("\n--------------------------------------------\n");
    
    FILE* txt = fopen(PATH_PRODUTO, "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return 1;
    }
    
    FILE* temp = fopen("../txt/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(txt);
        return 1;
    }
    
    Produto produto;
    
    int encontrado = 0;
    while (fscanf(txt, " %[^\n]", produto.nome) != EOF) {
        fscanf(txt, " %f", &produto.valorCompra);
        fscanf(txt, " %f", &produto.valorVenda);
        fscanf(txt, " %f", &produto.lucro);
        fscanf(txt, " %d", &produto.qtd);
        fscanf(txt, " %d/%d/%d", &produto.dataCadastro.dia, &produto.dataCadastro.mes, &produto.dataCadastro.ano);
        
        if (strcmp(produto.nome, nome) == 0) {
            encontrado = 1;
            printf("Digite os novos dados do produto:\n");
            printf("Nome: ");
            scanf(" %[^\n]", produto.nome);
            printf("Valor de compra: ");
            scanf(" %f", &produto.valorCompra);
            printf("Valor de Venda: ");
            scanf(" %f", &produto.valorVenda);
            produto.lucro = produto.valorVenda - produto.valorCompra;
            printf("Quantidade: ");
            scanf(" %d", &produto.qtd);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            produto.dataCadastro.dia = tm.tm_mday;
            produto.dataCadastro.mes = tm.tm_mon + 1;
            produto.dataCadastro.ano = tm.tm_year + 1900;
        }
        
        fprintf(temp, "%s\n%.2f\n%.2f\n%.2f\n%d\n%02d/%02d/%02d\n\n",
                produto.nome, produto.valorCompra, produto.valorVenda, produto.lucro, produto.qtd, 
                produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
    }
    printf("--------------------------------------------\n");
    
    fclose(txt);
    fclose(temp);
    
    if (!encontrado) {
        printf("Nome do produto %s não encontrado.\n", nome);
        remove("../txt/temp.txt");
        return 1;
    }
    
    remove(PATH_PRODUTO);
    rename("../txt/temp.txt", PATH_PRODUTO);
    printf("Produto atualizado com sucesso!\n");
    return 0;
}

/*
    Busca um Produto:
*/
int buscarProduto(){
    char nome[30];
    printf("Digite o nome do Produto: ");
    scanf(" %[^\n]", nome);
    // Variavel de verificação
    int vf = 0;
    Produto produto;
    // Abre o arquivo
    FILE* txt = fopen(PATH_PRODUTO, "r");
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", produto.nome) != EOF) {
        fscanf(txt, " %f", &produto.valorCompra);
        fscanf(txt, " %f", &produto.valorVenda);
        fscanf(txt, " %f", &produto.lucro);
        fscanf(txt, " %d", &produto.qtd);
        fscanf(txt, " %d/%d/%d", &produto.dataCadastro.dia, &produto.dataCadastro.mes, &produto.dataCadastro.ano);
        if (strcmp(produto.nome, nome) == 0) {
            mostrarProduto(produto);
        }
        vf++;
    }
    fclose(txt);
    return 0;
}

/*
    Mostra um produto:
*/
void mostrarProduto(Produto produto) {
    // Mostra o cliente
    printf("-----------------------------------------------------\n");
    printf ("[Produto]: %s\n", produto.nome);
    printf("-----------------------------------------------------\n");
    printf ("[Valor de Compra]: R$%.2f\n", produto.valorCompra);
    printf ("[Valor de Venda]: R$%.2f\n", produto.valorVenda);
    printf ("[Lucro]: R$%.2f\n", produto.lucro);
    printf ("[Quantidade]: %d\n", produto.qtd);
    printf ("[Data de Cadastro]: %02d/%02d/%02d \n", produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
    printf("-----------------------------------------------------\n\n");
}

/*
    Mostra a lista de cadastrados.
*/
int listarProdutos(int ver) {
    // Variável de verificação
    int vf = 0;
    // Variavel Produto para leitura
    Produto produto;
    // Abre o arquivo
    FILE* txt = fopen(PATH_PRODUTO, "r");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", produto.nome) != EOF) {
        fscanf(txt, " %f", &produto.valorCompra);
        fscanf(txt, " %f", &produto.valorVenda);
        fscanf(txt, " %f", &produto.lucro);
        fscanf(txt, " %d", &produto.qtd);
        fscanf(txt, " %d/%d/%d", &produto.dataCadastro.dia, &produto.dataCadastro.mes, &produto.dataCadastro.ano);
        if (ver == 1) {
            mostrarProduto(produto);
        }
        vf++;
    }
    // Fecha o arquivo
    fclose(txt);
    // Verifica se houve algum produto cadastrado
    if (vf == 0) {
        return -1;
    }
    return 0;
}

/*
    Zera a lista de Produtos:
*/
int zerarProdutos() {
    // Abre o arquivo
    FILE* txt = fopen(PATH_PRODUTO, "w");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

#endif
