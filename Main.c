#include <stdio.h>
#include <string.h>
#include "Structs.h"
#include "Funcoes.h"

int main() {
    FILE *txt;
    int opcao = 0;

    while (opcao != 4) {
        system("cls");
        printf("------------------------------------------------\n");
        printf("                     SISTEMA\n");
        printf("------------------------------------------------\n\n");
        printf("> O que deseja fazer?\n");
        printf("[1] Cadastrar\n");
        printf("[2] Visualizar lista\n");
        printf("[3]Zerar lista\n");
        printf("[4] Sair\n\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrar(txt);
        } else if (opcao == 2) {
            mostrarLista(txt);
        } else if (opcao == 3){
            zerarLista(txt);
        } else if (opcao != 4) {
            printf("-> Opcao invalida!\n");
        }
    }

    printf("-> Saindo...\n");

    return 0;
}
