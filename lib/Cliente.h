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
    Cliente clienteAux;
    clienteAux.endereco = (Endereco*) malloc(sizeof(Endereco)); // Aloca endereço

    FILE* txt = fopen(PATH_CLIENTE, "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }

    while (fscanf(txt, " %[^\n]", clienteAux.nome) != EOF) {
        fscanf(txt, " %s", clienteAux.cpf);
        fscanf(txt, " %[^\n]", clienteAux.telefone);
        fscanf(txt, " %[^\n]", clienteAux.endereco->rua);
        fscanf(txt, " %d", &clienteAux.endereco->numeroCasa);
        fscanf(txt, " %[^\n]", clienteAux.endereco->bairro);
        fscanf(txt, " %[^\n]", clienteAux.endereco->cidade); // Alterado
        fflush(stdin);
        fscanf(txt, " %[^\n]", clienteAux.endereco->estado); // Alterado
        fscanf(txt, " %s", clienteAux.email);
        fscanf(txt, " %d/%d/%d", &clienteAux.dataCadastro.dia, &clienteAux.dataCadastro.mes, &clienteAux.dataCadastro.ano);

        mostrarCliente(clienteAux);
        vf++;
    }

    free(clienteAux.endereco); // Libera memória alocada

    if (vf == 0) {
        return -1;
    }

    fclose(txt);
    return 0;
}


#endif
