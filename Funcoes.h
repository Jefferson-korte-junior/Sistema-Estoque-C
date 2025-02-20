#ifndef FUNCOES
#define FUNCOES
#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

int zerarLista(FILE *txt) {
    txt = fopen(".\\arquivo.txt", "w");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    printf("-> Lista zerada!\n");
    fclose(txt);
    system("pause");

    return 0;
}


void mostrarproduto(Produto produto) {
    printf("-> %s\n", produto.nome);
    printf("Valor de Compra: %.2f\n", produto.valorCompra);
    printf("Valor de venda: %.2f\n", produto.valorVenda);
    printf("Lucro: : %.2f\n", produto.lucro);
    printf ("Quantidade de vendas : %d\n", produto.qtdVendas);
    printf("------------------------------------------------\n");
}

int cadastrar(FILE *txt) {
    int qtdProdutos;

    system("cls");
    printf("------------------------------------------------\n");
    printf("                    CADASTRO\n");
    printf("------------------------------------------------\n\n");

    printf("> Quantos produtos deseja cadastrar?\n");
    scanf("%d", &qtdProdutos);

    Produto produto[qtdProdutos];

    for (int p = 0; p < qtdProdutos; p++) {
        system("cls");
        printf("------------------------------------------------\n");
        printf("                    Produtos %d\n", p+1);
        printf("------------------------------------------------\n\n");

        printf("> Digite o nome:\n");
        scanf(" %[^\n]", produto[p].nome);
        printf("Teste: %s\n", produto[p].nome);
        printf("> Digite o valor da compras : \n");
        scanf("%f", &produto[p].valorCompra);
        printf("Teste: %.2f\n", produto[p].valorCompra);
        printf("> Digite o valor da venda:\n");
        scanf("%f", &produto[p].valorVenda);
        printf("Teste: %.2f\n", produto[p].valorVenda);
        printf("> Digite o lucro: \n");
        scanf("%f", &produto[p].lucro);
        printf("Teste: %.2f\n", produto[p].lucro);
        printf("> Digite a quantidade de vendas: \n");
        scanf("%d", &produto[p].qtdVendas);
        printf("Teste: %d\n", produto[p].qtdVendas);
    }

    txt = fopen(".\\arquivo.txt", "a");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }

    for (int p = 0; p < qtdProdutos; p++) {
        fprintf(txt, "%s\n %.2f\n %.2f\n %.2f\n %d\n\n",
        produto[p].nome,
        produto[p].valorCompra,
        produto[p].valorVenda,
        produto[p].lucro,
        produto[p].qtdVendas);
    }

    printf("-> Cadastrado(s) com sucesso!\n");

    fclose(txt);
    system("pause");
    getchar();
    return 0;
}

/*
    Mostra a lista de cadastrados.
*/
int mostrarLista(FILE *txt) {
    Produto produtoAux;

    system("cls");
    printf("------------------------------------------------\n");
    printf("                  CADASTRADOS\n");
    printf("------------------------------------------------\n");

    txt = fopen(".\\arquivo.txt", "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }

    while (fscanf(txt, " %[^\n]", produtoAux.nome) != EOF) {
        fscanf(txt, "%f", &produtoAux.valorCompra);
        fscanf(txt, " %f", &produtoAux.valorVenda);
        fscanf(txt, " %f", &produtoAux.lucro);
        fscanf(txt, " %d", &produtoAux.qtdVendas);
        mostrarproduto(produtoAux);
    }

    fclose(txt);
    system("pause");
    getchar();

    return 0;
}

#endif
