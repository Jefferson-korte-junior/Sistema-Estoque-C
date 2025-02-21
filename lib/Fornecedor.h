#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

#define PATH_FORNECEDOR "../txt/Fornecedor.txt"

/*
    Zera a lista de fornecedores.
*/
int zerarFornecedores() {
    FILE* txt = fopen(PATH_FORNECEDOR, "w");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fclose(txt);
    return 0;
}

/*
    Mostra um fornecedor.
*/
void mostrarfornecedor(Fornecedor fornecedor) {
    printf("-----------------------------------------------------\n");
    printf("# %s #\n", fornecedor.nomeFantasia);
    printf("-----------------------------------------------------\n");
    printf("    + CNPJ: %s\n", fornecedor.cnpj);
    printf("    + Telefone: %s\n", fornecedor.telefone);
    printf("    + Endereço: %s, %d, %s, %s, %s\n", fornecedor.endereco->rua, fornecedor.endereco->numeroCasa, fornecedor.endereco->bairro, fornecedor.endereco->cidade, fornecedor.endereco->estado);
    printf("    + Email: %s\n", fornecedor.email);
    printf("    + Data de Cadastro: %02d/%02d/%02d\n\n", fornecedor.dataCadastro.dia, fornecedor.dataCadastro.mes, fornecedor.dataCadastro.ano);
}

/*
    Cadastra um fornecedor.
*/
int cadastrarFornecedor(Fornecedor* fornecedor) {
    FILE* txt = fopen(PATH_FORNECEDOR, "a");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    fprintf(txt, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
    fornecedor->nomeFantasia,
    fornecedor->cnpj,
    fornecedor->telefone,
    fornecedor->endereco->rua,
    fornecedor->endereco->numeroCasa,
    fornecedor->endereco->bairro,
    fornecedor->endereco->cidade,
    fornecedor->endereco->estado,
    fornecedor->email,
    fornecedor->dataCadastro.dia,
    fornecedor->dataCadastro.mes,
    fornecedor->dataCadastro.ano);
    fclose(txt);
    return 0;
}

/*
    Mostra a lista de cadastrados.
*/
int verFornecedores() {
    Fornecedor fornecedorAux;
    FILE* txt = fopen(PATH_FORNECEDOR, "r");
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    while (fscanf(txt, " %[^\n]", fornecedorAux.nomeFantasia) != EOF) {
        fscanf(txt, "%s", fornecedorAux.cnpj);
        fscanf(txt, " %s", fornecedorAux.telefone);
        fscanf(txt, " %s", fornecedorAux.endereco->rua);
        fscanf(txt, " %d", &fornecedorAux.endereco->numeroCasa);
        fscanf(txt, " %s", fornecedorAux.endereco->bairro);
        fscanf(txt, " %s", fornecedorAux.endereco->cidade);
        fscanf(txt, " %s", fornecedorAux.endereco->estado);
        fscanf(txt, " %s", fornecedorAux.email);
        fscanf(txt, "%d/%d/%d", &fornecedorAux.dataCadastro.dia, &fornecedorAux.dataCadastro.mes, &fornecedorAux.dataCadastro.ano);
        mostrarfornecedor(fornecedorAux);
    }
    fclose(txt);
    return 0;
}

#endif
