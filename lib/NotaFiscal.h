#ifndef NOTAFISCAL_H
#define NOTAFISCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include "Cliente.h"
#include "Produto.h"

#define PATH_NOTAS_FISCAIS "../txt/NotasFiscais.txt"

// Funções
int novaNotaFiscal();
void mostrarNotaFiscal(NotaFiscal notaFiscal);
int listarNotasFiscais(int ver);
int zerarNotasFiscais();

int novaNotaFiscal() {  
    // Mostra
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                  Nova Nota Fiscal \n");
    printf("-----------------------------------------------------\n\n");
    // Data
    Data data;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    data.dia = tm.tm_mday;
    data.mes = tm.tm_mon + 1;
    data.ano = tm.tm_year + 1900;
    // Solicita o CPF do Cliente
    char cpf[15];
    printf("> Digite o CPF do cliente:\n");
    if (scanf(" %s", cpf) == 0 || strlen(cpf) != 11) {
        return 1;
    }
    // Variável de verificação
    int clienteEncontrado = 0;
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    FILE* txtCliente = fopen("../txt/Clientes.txt", "r");
    if (txtCliente == NULL || cliente.endereco == NULL) {
        printf("-> Erro ao abrir o arquivo de clientes.\n");
        free(cliente.endereco);
        return 1;
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
    // Fecha o Arquivo
    fclose(txtCliente);
    // Verifica se não foi encontrado
    system("cls");
    if (!clienteEncontrado) {
        printf("-> Cliente não encontrado.\n");
        free(cliente.endereco);
        return 1;
    }
    // Informa que encontrou o Cliente
    printf("\n-> Cliente encontrado:\n\n");
    printf("-----------------------------------------------------\n");
    printf("[CLIENTE]: %s\n", cliente.nome);
    printf("-----------------------------------------------------\n\n");
    float valorTotal = 0;
    Produto* produtosComprados = NULL;
    int* quantidades = NULL;
    int numProdutos = 0;
    int qtdPedidos = 0;
    // Solicita a observação da Nota Fiscal
    char observacao[100];
    system("pause && cls");
    printf("> Digite uma Observacao a Nota Fiscal:\n");
    if (scanf(" %s", observacao) == 0 || strlen(observacao) <= 0) {
        return 1;
    }
    // Solicita os Produtos
    while (1) {
        char continuar;
        printf("> Deseja adicionar um produto? (Digite 's' para continuar e 'n' para sair):\n");
        scanf(" %c", &continuar);
        if (continuar == 'n' || continuar == 'N') {
            return -1;
            break;
        } else if(continuar == 's' || continuar == 'S') {
            qtdPedidos++;
            produtosComprados = (Produto*) realloc(produtosComprados, (numProdutos + 1) * sizeof(Produto));
            quantidades = (int*) realloc(quantidades, (numProdutos + 1) * sizeof(int));
            if (produtosComprados == NULL || quantidades == NULL) {
                printf("-> Erro de alocação de memória.\n");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return 1;
            }
            // Mostra a Lista de Produtos para o Usuário visualizar
            system("cls");
            printf("\n-> Produtos a selecionar:\n\n");
            listarProdutos(1);
            // Solicita o Produto e Quantidade
            char nomeProduto[50];
            int quantidade;
            printf("> [Adicionar] Digite o nome do produto:\n");
            if (scanf(" %[^\n]", nomeProduto) == 0 || strlen(nomeProduto) <= 0) {
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return 1;
            }
            printf("> [Adicionar] Digite quantas unidades deseja:\n");
            if (scanf("%d", &quantidade) == 0 || quantidade <= 0) {
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return 1;
            }
            // Variável de verificação
            int produtoEncontrado = 0;
            // Variável Produto
            Produto produto;
            // Arquivos
            FILE* txtProduto = fopen(PATH_PRODUTO, "r");
            FILE* tempProduto = fopen("../txt/temp.txt", "w");
            if (txtProduto == NULL || tempProduto == NULL) {
                printf("-> Erro ao abrir o arquivo de produtos.\n");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return 1;
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

            system("cls");
            if (!produtoEncontrado) {
                printf("Produto %s não encontrado ou sem estoque suficiente.\n", nomeProduto);
                remove("../txt/temp.txt");
                free(cliente.endereco);
                free(produtosComprados);
                free(quantidades);
                return 1;
            }

            printf("\n-> Produto adicionado na Nota Fiscal com sucesso!\n\n");
            system("pause && cls");

            remove("../txt/Estoque.txt");
            rename("../txt/temp.txt", "../txt/Estoque.txt");
        } else {
            printf("Opcao invalida, digite novamente!\n");
        }
    }
    system("cls");
    printf("\n-> Nota Fiscal finalizada com sucesso!\n\n");
    printf("Cliente: %s\n", cliente.nome);
    printf("Quantidade de pedidos: %d\n\n", qtdPedidos);
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
        return 1;
    }
    // Escreve no arquivo
    fprintf(txt, "%s\n", observacao);
    fprintf(txt, "%s\n", cliente.nome);
    fprintf(txt, "%d\n", qtdPedidos);
    for (int i = 0; i < numProdutos; i++) {
        fprintf(txt, "%s\n%d\n%.2f\n", produtosComprados[i].nome, quantidades[i], produtosComprados[i].valorVenda * quantidades[i]);
    }
    fprintf(txt, "%.2f\n", valorTotal);
    fprintf(txt, "%02d/%02d/%02d\n\n", data.dia, data.mes, data.ano);
    // Fecha o arquivo
    fclose(txt);
    // Libera a memoria
    free(cliente.endereco);
    free(produtosComprados);
    free(quantidades);
    return 0;
}

/*
    Mostra a Nota Fiscal:
*/
void mostrarNotaFiscal(NotaFiscal notaFiscal) {
    // Mostra a Nota Fiscal
    printf("-----------------------------------------------------\n");
    printf(" [Nota Fiscal]: %s\n", notaFiscal.observacao);
    printf(" [Cliente]: %s\n", notaFiscal.cliente.nome);
    printf("-----------------------------------------------------\n");
    printf(" [Valor Total]: R$%.2f\n", notaFiscal.valorTotal);
    printf(" [Data Fechamento]: %02d/%02d/%02d\n", notaFiscal.dataFechamento.dia, notaFiscal.dataFechamento.mes, notaFiscal.dataFechamento.ano);
    printf("-----------------------------------------------------\n");
    printf("      PDT       /      QTD      /      VAL. TOTAL\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < notaFiscal.qtdCompras; i++) {
        printf("-> %s / %d / R$%.2f\n", notaFiscal.compras[i].produto.nome, notaFiscal.compras[i].qtdProduto, notaFiscal.compras[i].valor);
    }
    printf("-----------------------------------------------------\n\n");
}

/*
    Lista as Notas Fiscais:
*/
int listarNotasFiscais(int ver) {
    // Variavel de Verificação
    int vf = 0;
    // Abre o arquivo
    FILE* txt = fopen(PATH_NOTAS_FISCAIS, "r");
    if (txt == NULL) {
        printf("-> Erro ao abrir o arquivo de notas fiscais.\n");
        return 1;
    }
    // Nota Fiscal
    NotaFiscal notaFiscal;
    while (fscanf(txt, " %[^\n]", notaFiscal.observacao) != EOF) {
        fscanf(txt, " %[^\n]", notaFiscal.cliente.nome);
        fscanf(txt, " %d", &notaFiscal.qtdCompras);
        // Aloca a memória uma única vez
        notaFiscal.compras = (Compra *)malloc(notaFiscal.qtdCompras * sizeof(Compra));
        if (notaFiscal.compras == NULL) {
            return 1;
        }
        // Faz a leitura dos Produtos da Nota
        for (int i = 0; i < notaFiscal.qtdCompras; i++) {
            fscanf(txt, " %[^\n]", notaFiscal.compras[i].produto.nome);
            fscanf(txt, " %d", &notaFiscal.compras[i].qtdProduto);
            fscanf(txt, " %f", &notaFiscal.compras[i].valor);
        }
        fscanf(txt, " %f", &notaFiscal.valorTotal);
        fscanf(txt, " %02d/%02d/%04d", &notaFiscal.dataFechamento.dia, &notaFiscal.dataFechamento.mes, &notaFiscal.dataFechamento.ano);
        if (ver == 1) {
            mostrarNotaFiscal(notaFiscal);
        }
        free(notaFiscal.compras); // Liberar memória
        vf++;
    }
    // Libera memoria de Compras
    free(notaFiscal.compras);
    // Fecha o arquivo
    fclose(txt);
    // Verifica se houve alguma Nota Cadastrada
    if (vf == 0) {
        return -1;
    }
    return 0;
}

/*
    Zera a lista de Notas Fiscais:
*/
int zerarNotasFiscais() {
    // Abre o arquivo
    FILE* txt = fopen(PATH_NOTAS_FISCAIS, "w");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        printf("-> Erro ao abrir o arquivo de notas fiscais.\n");
        return 1;
    }
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

#endif