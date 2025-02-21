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
    FILE* txt = fopen(PATH_PRODUTO, "w");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fclose(txt);
    return 0;
}

/*
    Cadastra um produto.
*/
int cadastrarProduto(Produto* produto) {
    FILE* txt = fopen(PATH_PRODUTO, "a");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fprintf(txt, "%s\n%.2f\n%.2f\n%.2f\n%d\n%02d/%02d/%02d\n\n",
    produto->nome,
    produto->valorCompra,
    produto->valorVenda,    
    produto->lucro, 
    produto->qtd,
    produto->dataCadastro.dia,
    produto->dataCadastro.mes,
    produto->dataCadastro.ano);
    fclose(txt);
    return 0;
}

/*
    Mostra um produto.
*/
void mostrarProduto(Produto produto) {
    printf("-----------------------------------------------------\n");
    printf("# %s #\n", produto.nome);
    printf("-----------------------------------------------------\n");
    printf("    + Valor de Compra: %.2f\n", produto.valorCompra);
    printf("    + Valor de venda: %.2f\n", produto.valorVenda);
    printf("    + Lucro: %.2f\n", produto.lucro);
    printf("    + Quantidade: %d\n", produto.qtd);
    printf("    + Data de Cadastro: %02d/%02d/%02d\n\n", produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
}

/*
    Mostra a lista de cadastrados.
*/
int verEstoque() {
    Produto produtoAux;
    FILE* txt = fopen(PATH_PRODUTO, "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    while (fscanf(txt, " %[^\n]", produtoAux.nome) != EOF) {
        fscanf(txt, " %f", &produtoAux.valorCompra);
        fscanf(txt, " %f", &produtoAux.valorVenda);
        fscanf(txt, " %f", &produtoAux.lucro);
        fscanf(txt, " %d", &produtoAux.qtd);
        fscanf(txt, " %d/%d/%d", &produtoAux.dataCadastro.dia, &produtoAux.dataCadastro.mes, &produtoAux.dataCadastro.ano);
        mostrarProduto(produtoAux);
    }
    fclose(txt);
    return 0;
}

#endif
