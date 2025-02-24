#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

#define PATH_PRODUTO "../txt/Estoque.txt"

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
    printf("-----------------------------------------------------\n");
    printf("> %s\n", produto.nome);
    printf("-----------------------------------------------------\n");
    printf("  + Valor de Compra: %.2f\n", produto.valorCompra);
    printf("  + Valor de venda: %.2f\n", produto.valorVenda);
    printf("  + Lucro: %.2f\n", produto.lucro);
    printf("  + Quantidade: %d\n", produto.qtd);
    printf("  + Data de Cadastro: %02d/%02d/%02d\n\n", produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
}

/*
    Mostra a lista de cadastrados.
*/
int verEstoque() {
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
        mostrarProduto(produto);
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
