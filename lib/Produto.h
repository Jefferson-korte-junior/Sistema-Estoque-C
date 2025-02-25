#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include "Menus.h"	

#define PATH_PRODUTO "../txt/Estoque.txt"

int editarProduto() {
    char nome[35];
    printf("Digite o nome do Produto que deseja editar: ");
    scanf(" %[^\n]", nome);
    
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
    Zera a lista de produtos.
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
    Mostra um produto.
*/
void mostrarProduto(Produto produto) {
    char valorCompra[30], valorVenda[30], lucro[30], qtd[30];
    sprintf(valorCompra, "%.2f", produto.valorCompra);
    sprintf(valorVenda, "%.2f", produto.valorVenda);
    sprintf(lucro, "%.2f", produto.lucro);
    sprintf(qtd, "%d", produto.qtd);

    // Data de cadastro
    char data[10];
    sprintf(data, "%02d/%02d/%02d", produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
    // Mostra o cliente
    printf("/////////////////////////////////////////////////////\n");
    msgCaixa("[Produto]: ", 11, produto.nome, strlen(produto.nome));
    printf("/////////////////////////////////////////////////////\n");
    msgCaixa("[Valor de Compra]: R$", 21, valorCompra, strlen(valorCompra));
    msgCaixa("[Valor de Venda]: R$", 20, valorVenda, strlen(valorVenda));
    msgCaixa("[Lucro]: R$", 11, lucro, strlen(lucro));
    printf("// [Quantidade]: %d\n", produto.qtd);
    msgCaixa("[Data de Cadastro]: ", 20, data, strlen(data));
    printf("/////////////////////////////////////////////////////\n\n");
}

/*
    Mostra a lista de cadastrados.
*/
int verEstoque(int ver) {
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

#endif
