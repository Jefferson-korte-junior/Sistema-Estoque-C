#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

#define PATH_CLIENTE "../txt/Cliente.txt"

/*
    Zera a lista de produtos.
*/
int zerarListaCliente() {
    FILE* txt = fopen(PATH_CLIENTE, "w");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fclose(txt);
    return 0;
}

/*
    Mostra um cliente.
*/
void mostrarCliente(Cliente cliente) {
    printf("-----------------------------------------------------\n");
    printf("# %s #\n", cliente.nome);
    printf("-----------------------------------------------------\n");
    printf("    + CPF: %.2f\n", cliente.cpf);
    printf("    + Telefone: %s\n", cliente.telefone);
    printf("    + Endereco: %s\n%d\n%s\n%s\n%s\n",
    cliente->enderecoCliente->rua,
    cliente->enderecoCliente->numeroCasa,
    cliente->enderecoCliente->bairro,
    cliente->enderecoCliente->cidade,
    cliente->enderecoCliente->estado); //endereço
    printf("    + Email: %d\n", cleinte.email);
    printf("    + Data de Cadastro: %02d/%02d/%02d\n\n", cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
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
    fprintf(txt, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%a\n%s\n%02d/%02d/%02d\n\n",
    (*cliente).nome,
    (*cliente).cpf,
    (*cleinte).telefone,
    cliente->enderecoCliente->rua,
    cliente->enderecoCliente->numeroCasa,
    cliente->enderecoCliente->bairro,
    cliente->enderecoCliente->cidade,
    cliente->enderecoCliente->estado),
    (*Cliente).email,
    (*cliente).dataCadastro.dia,
    (*cliente).dataCadastro.mes,
    (*cliente).dataCadastro.ano);
    fclose(txt);
    return 0;
}

/*
    Mostra a lista de cadastrados.
*/
int verClientes() {
    Cliente clienteAux;
    FILE* txt = fopen(PATH_CLIENTE, "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    while (fscanf(txt, " %[^\n]", clienteAux.nome) != EOF) {
        fscanf(txt, "%[^\n]", &clienteAux.cpf);
        fscanf(txt, " %[^\n]", &clienteAux.telefone);
        fscanf(txt, " %[^\n],%d, %[^\n], %[^\n], %[^\n]", cliente->enderecoCliente->rua,
        &clienteAux->enderecoCliente->numeroCasa,
        &clienteAux->enderecoCliente->bairro,
        &clienteAux->enderecoCliente->cidade,
        &clienteAux->enderecoCliente->estado);
        fscanf(txt, " %[^\n]", &clienteAux.email);
        fscanf(txt, " %d/%d/%d", &clienteAux.dataCadastro.dia, &clienteAux.dataCadastro.mes, &clienteAux.dataCadastro.ano);
        mostrarcliente(clienteAux);
    }
    fclose(txt);
    return 0;
}

#endif
