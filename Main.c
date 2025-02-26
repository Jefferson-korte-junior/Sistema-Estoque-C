#include <stdio.h>
#include <stdlib.h>

#include "lib/Menus.h"

int main() {
    if (menuPrincipal() != 0) {
        printf("Erro ao executar o menu principal.\n");
        return 1;
    }
    return 0;
}