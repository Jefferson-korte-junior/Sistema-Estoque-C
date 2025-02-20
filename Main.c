#include <stdio.h>
#include <string.h>
#include "Structs.h"
#include "Funcoes.h"

int main() {
    int opcao = 0;

    while (opcao != 4) {
        system("cls");
        printf("------------------------------------------------\n");
        printf("                     SISTEMA\n");
        printf("------------------------------------------------\n\n");
        printf("> O que deseja fazer?\n");
        printf("[1] Cadastrar\n");
        printf("[2] Visualizar lista\n");
        printf("[3]Zerar lista");
        printf("[4] Sair\n\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            mostrarLista();
        } else if (opcao == 3){
            zerarLista();
        } else if (opcao != 4) {
            printf("-> Opcao invalida!\n");
        }
    }

    printf("-> Saindo...\n");

    return 0;
}
