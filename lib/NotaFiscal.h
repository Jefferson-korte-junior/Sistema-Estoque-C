#ifndef NOTAFISCAL_H
#define NOTAFISCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "Cliente.h"
#include "Produto.h"

#define PATH_NOTAS_FISCAIS "../txt/NotasFiscais.txt"

void realizarCompra() {
    system("cls");
    char cpf[15];
    printf("Digite o CPF do cliente: ");
    scanf(" %s", cpf);

    // Variável de verificação
    int clienteEncontrado = 0;
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    FILE* txtCliente = fopen("../txt/Clientes.txt", "r");
    if (txtCliente == NULL || cliente.endereco == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        free(cliente.endereco);
        return;
    }

    // Busca o cliente pelo CPF
    while (fscanf(txtCliente, " %[^\n]", cliente.nome) != EOF) {
        fscanf(txtCliente, " %s", cliente.cpf);
        fscanf(txtCliente, " %[^\n]", cliente.telefone);
        fscanf(txtCliente, " %[^\n]", cliente.endereco->rua);
        fscanf(txtCliente, " %d", &cliente.endereco->numero);
        fscanf(txtCliente, " %[^\n]", cliente.endereco->bairro);
        fscanf(txtCliente, " %[^\n]", cliente.endereco->cidade);
        fscanf(txtCliente, " %[^\n]", cliente.endereco->estado);
        fscanf(txtCliente, " %s", cliente.email);
        fscanf(txtCliente, " %d/%d/%d", &cliente.dataCadastro.dia, &cliente.dataCadastro.mes, &cliente.dataCadastro.ano);
        if (strcmp(cliente.cpf, cpf) == 0) {
            clienteEncontrado = 1;
            break;
        }
    }
    fclose(txtCliente);

    if (!clienteEncontrado) {
        printf("Cliente não encontrado.\n");
        free(cliente.endereco);
        return;
    }
    printf("\n/////////////////////////////////////////////////\n");
    printf("[CLIENTE]: %s\n", cliente.nome);
    printf("/////////////////////////////////////////////////\n\n");
    float valorTotal = 0;
    Produto* produtosComprados = NULL;
    int* quantidades = NULL;
    int numProdutos = 0;
    int qtdPedidos = 0;

    while (1) {
        char continuar;
        printf("Deseja adicionar um produto? (Digite 's' para continuar e 'n' para sair): ");
        scanf(" %c", &continuar);
        if (continuar == 'n' || continuar == 'N') {
            break;
        }
        else if(continuar == 's' || continuar == 'S') {
            qtdPedidos++;
            produtosComprados = (Produto*) realloc(produtosComprados, (numProdutos + 1) * sizeof(Produto));
            quantidades = (int*) realloc(quantidades, (numProdutos + 1) * sizeof(int));
            if (produtosComprados == NULL || quantidades == NULL) {
                printf("Erro de alocação de memória.\n");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return;
            }

            char nomeProduto[50];
            int quantidade;
            printf("Digite o nome do produto #%d: ", numProdutos + 1);
            scanf(" %[^\n]", nomeProduto);
            printf("Digite a quantidade do produto #%d: ", numProdutos + 1);
            scanf("%d", &quantidade);

            // Variável de verificação
            int produtoEncontrado = 0;
            Produto produto;
            FILE* txtProduto = fopen("../txt/Estoque.txt", "r");
            FILE* tempProduto = fopen("../txt/temp.txt", "w");

            if (txtProduto == NULL || tempProduto == NULL) {
                printf("Erro ao abrir o arquivo de produtos.\n");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                if (txtProduto != NULL) fclose(txtProduto);
                if (tempProduto != NULL) fclose(tempProduto);
                return;
            }

            // Busca o produto pelo nome e atualiza a quantidade no estoque
            while (fscanf(txtProduto, " %[^\n]", produto.nome) != EOF) {
                fscanf(txtProduto, " %f", &produto.valorCompra);
                fscanf(txtProduto, " %f", &produto.valorVenda);
                fscanf(txtProduto, " %f", &produto.lucro);
                fscanf(txtProduto, " %d", &produto.qtd);
                fscanf(txtProduto, " %d/%d/%d", &produto.dataCadastro.dia, &produto.dataCadastro.mes, &produto.dataCadastro.ano);

                if (strcmp(produto.nome, nomeProduto) == 0 && produto.qtd >= quantidade) {
                    produtoEncontrado = 1;
                    produto.qtd -= quantidade;
                    produtosComprados[numProdutos] = produto;
                    quantidades[numProdutos] = quantidade;
                    valorTotal += produto.valorVenda * quantidade;
                    numProdutos++;
                }

                fprintf(tempProduto, "%s\n%.2f\n%.2f\n%.2f\n%d\n%02d/%02d/%02d\n\n",
                        produto.nome, produto.valorCompra, produto.valorVenda, produto.lucro, produto.qtd,
                        produto.dataCadastro.dia, produto.dataCadastro.mes, produto.dataCadastro.ano);
            }
            fclose(txtProduto);
            fclose(tempProduto);

            if (!produtoEncontrado) {
                printf("Produto %s não encontrado ou sem estoque suficiente.\n", nomeProduto);
                remove("../txt/temp.txt");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return;
            }

            remove("../txt/Estoque.txt");
            rename("../txt/temp.txt", "../txt/Estoque.txt");
        }
        else{
            printf("Opcao invalida, digite novamente!\n");
        }
    }
    system("cls");
    printf("\nCompra realizada com sucesso!\n");
    printf("Cliente: %s\n", cliente.nome);
    printf("Quantidade de pedidos: %d\n", qtdPedidos);
    printf("Produtos comprados:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf(" - %s (Quantidade: %d): R$%.2f\n", produtosComprados[i].nome, quantidades[i], produtosComprados[i].valorVenda * quantidades[i]);
    }
    printf("Valor total: R$%.2f\n", valorTotal);

    //abre arquivo
    FILE* txt = fopen(PATH_NOTAS_FISCAIS, "a");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        free(cliente.endereco);
        free(produtosComprados);
        free(quantidades);
        return;
    }
    // Escreve no arquivo
    fprintf(txt, "%s\n", cliente.nome);
    fprintf(txt, "%d\n", qtdPedidos);
    for (int i = 0; i < numProdutos; i++) {
        fprintf(txt, " %s\n %d %.2f\n", produtosComprados[i].nome, quantidades[i], produtosComprados[i].valorVenda * quantidades[i]);
    }
    fprintf(txt, "%.2f\n\n", valorTotal);
    // Fecha o arquivo
    fclose(txt);

    free(cliente.endereco);
    free(produtosComprados);
    free(quantidades);
}

void mostrarNotasFiscais() {
    system("cls");
    FILE* txt = fopen(PATH_NOTAS_FISCAIS, "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de notas fiscais.\n");
        return;
    }

    char clienteNome[50];
    int qtdPedidos;
    char produtoNome[50];
    int quantidade;
    float valorProduto, valorTotal;

    while (fscanf(txt, " %[^\n]", clienteNome) != EOF) {
        printf("\nCliente: %s\n", clienteNome);
        fscanf(txt, "%d", &qtdPedidos);
        printf("Quantidade de pedidos: %d\n", qtdPedidos);
        printf("Produtos comprados:\n");
        for (int i = 0; i < qtdPedidos; i++) {
            fscanf(txt, " %[^\n] %d %f", produtoNome, &quantidade, &valorProduto);
            printf(" - Produto: %s, Quantidade: %d, Valor do Produto: R$%.2f, Valor Total: R$%.2f\n", produtoNome, quantidade, valorProduto / quantidade, valorProduto);
        }
        fscanf(txt, " %f", &valorTotal);
        printf("Valor total da compra: R$%.2f\n", valorTotal);
        printf("\n/////////////////////////////////////////////////\n");
    }

    fclose(txt);
}

#endif
