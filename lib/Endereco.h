#ifndef ENDERECO_H
#define ENDERECO_H

#include <stdio.h>
#include <stdlib.h>

#include "Structs.h"

/*
    Novo Endereço:
*/
Endereco* novoEndereco() {
    // Aloca memória para o endereço
    Endereco* novoEndereco = (Endereco*) malloc(sizeof(Endereco));
    if (novoEndereco == NULL) {
        return NULL;
    }
    // Rua
    printf("> Digite a rua:\n");
    if (scanf(" %[^\n]", novoEndereco->rua) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Bairro
    printf("> Digite o bairro:\n");
    if (scanf(" %[^\n]", novoEndereco->bairro) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Cidade
    printf("> Digite a cidade:\n");
    if (scanf(" %[^\n]", novoEndereco->cidade) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Estado
    printf("> Digite o estado:\n");
    if (scanf(" %[^\n]", novoEndereco->estado) == 0) {
        free(novoEndereco);
        return NULL;
    }
    // Número
    printf("> Digite o numero da casa:\n");
    if (scanf("%d", &novoEndereco->numero) == 0) {
        free(novoEndereco);
        return NULL;
    }
    return novoEndereco;
}

#endif