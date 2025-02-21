#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include "Cliente.h"

#define PATH_CLIENTE "../txt/Clientes.txt"

/*
    Zera a lista de produtos.
*/
int zerarClientes() {
    FILE* txt = fopen(PATH_CLIENTE, "w");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fclose(txt);
    return 0;
}

/*
    Cadastra um cliente.
*/
int cadastrarCliente(Cliente* cliente) {
    FILE* txt = fopen(PATH_CLIENTE, "a");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fprintf(txt, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
    cliente->nome,
    cliente->cpf,
    cliente->telefone,
    cliente->endereco->rua,
    cliente->endereco->numeroCasa, 
    cliente->endereco->bairro, 
    cliente->endereco->cidade, cliente->endereco->estado, 
    cliente->email, 
    cliente->dataCadastro.dia, 
    cliente->dataCadastro.mes, 
    cliente->dataCadastro.ano);
    fclose(txt);
    return 0;
}

/*
    Mostra um cliente.
*/
void mostrarCliente(Cliente cliente) {
    printf("-----------------------------------------------------\n");
    printf("> %s\n", cliente.nome);
    printf("-----------------------------------------------------\n");
    printf("    + CPF: %s\n", cliente.cpf);
    printf("    + Telefone: %s\n", cliente.telefone);
    printf("    + Endereco: %s\n%d\n%s\n%s\n%s\n", cliente.endereco->rua, cliente.endereco->numeroCasa, cliente.endereco->bairro, cliente.endereco->cidade, cliente.endereco->estado);
    printf("    + Email: %s\n", cliente.email);
    printf("    + Data de Cadastro: %02d/%02d/%02d\n\n", cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
}

/*
    Mostra a lista de cadastrados.
*/
int verClientes() {
    int vf = 0;
    Cliente cliente;
    FILE* txt = fopen(PATH_CLIENTE, "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    while (fscanf(txt, " %[^\n]", cliente.nome) != EOF) {
        fscanf(txt, " %s", cliente.cpf);
        fscanf(txt, " %[^\n]", cliente.telefone);
        fscanf(txt, " %[^\n]", cliente.endereco->rua);
        fscanf(txt, " %d", &cliente.endereco->numeroCasa);
        fscanf(txt, " %[^\n]", cliente.endereco->bairro);
        fscanf(txt, " %[^\n]", cliente.endereco->cidade);
        fscanf(txt, " %[^\n]", cliente.endereco->estado);
        fscanf(txt, " %s", cliente.email);
        fscanf(txt, " %d/%d/%d", &cliente.dataCadastro.dia, &cliente.dataCadastro.mes, &cliente.dataCadastro.ano);
        mostrarCliente(cliente);
        vf++;
    }
    if (vf == 0) {
        return -1;
    }
    fclose(txt);
    return 0;
}

#endif
