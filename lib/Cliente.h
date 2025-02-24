#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menus.h"
#include "Structs.h"
#include "Cliente.h"

#define PATH_CLIENTE "../txt/Clientes.txt"

int buscarCliente(){
    char cpf[15];
    printf("Digite o CPF do cliente: ");
    scanf(" %s", cpf);
    // Variavel de verificação
    int vf = 0;
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    // Abre o arquivo
    FILE* txt = fopen(PATH_CLIENTE, "r");
    // Verifica se o arquivo foi aberto e se a alocação de memória do endereço foi feita
    if (txt == NULL || cliente.endereco == NULL) {
        return 1;
    }
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", cliente.nome) != EOF) {
        fscanf(txt, " %s", cliente.cpf);
        fscanf(txt, " %[^\n]", cliente.telefone);
        fscanf(txt, " %[^\n]", cliente.endereco->rua);
        fscanf(txt, " %d", &cliente.endereco->numero);
        fscanf(txt, " %[^\n]", cliente.endereco->bairro);
        fscanf(txt, " %[^\n]", cliente.endereco->cidade);
        fscanf(txt, " %[^\n]", cliente.endereco->estado);
        fscanf(txt, " %s", cliente.email);
        fscanf(txt, " %d/%d/%d", &cliente.dataCadastro.dia, &cliente.dataCadastro.mes, &cliente.dataCadastro.ano);
        // mostrarCliente(cliente);
        if (strcmp(cliente.cpf, cpf) == 0) {
            mostrarCliente(cliente);
            
        }
        vf++;
    }
}
/*
    Zera a lista de produtos.
*/
int zerarClientes() {
    // Abre o arquivo
    FILE* txt = fopen(PATH_CLIENTE, "w");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Cadastra um cliente.
*/
int cadastrarCliente(Cliente* cliente) {
    // Abre o arquivo
    FILE* txt = fopen(PATH_CLIENTE, "a");
    // Verifica se o arquivo foi aberto 
    if (txt == NULL) {
        return 1;
    }
    // Escreve no arquivo os dados
    fprintf(txt, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
    cliente->nome,
    cliente->cpf,
    cliente->telefone,
    cliente->endereco->rua,
    cliente->endereco->numero, 
    cliente->endereco->bairro, 
    cliente->endereco->cidade, cliente->endereco->estado, 
    cliente->email, 
    cliente->dataCadastro.dia, 
    cliente->dataCadastro.mes, 
    cliente->dataCadastro.ano);
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Mostra um cliente.
*/
void mostrarCliente(Cliente cliente) {
    // Numero da casa
    char numeroCasa[10];
    sprintf(numeroCasa, "%d", cliente.endereco->numero);
    // Data de cadastro
    char data[10];
    sprintf(data, "%02d/%02d/%02d", cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
    // Mostra o cliente
    printf("/////////////////////////////////////////////////////\n");
    msgCaixa("", 0, cliente.nome, strlen(cliente.nome));
    printf("/////////////////////////////////////////////////////\n");
    msgCaixa("[CPF]: ", 7, cliente.cpf, strlen(cliente.cpf));
    msgCaixa("[Telefone]: ", 12, cliente.telefone, strlen(cliente.telefone));
    msgCaixa("[Rua]: ", 7, cliente.endereco->rua, strlen(cliente.endereco->rua));
    msgCaixa("[Numero]: ", 10, numeroCasa, strlen(numeroCasa));
    msgCaixa("[Bairro]: ", 10, cliente.endereco->bairro, strlen(cliente.endereco->bairro));
    msgCaixa("[Cidade]: ", 10, cliente.endereco->cidade, strlen(cliente.endereco->cidade));
    msgCaixa("[Estado]: ", 10, cliente.endereco->estado, strlen(cliente.endereco->estado));
    msgCaixa("[Email]: ", 9, cliente.email, strlen(cliente.email));
    msgCaixa("[Data de Cadastro]: ", 20, data, strlen(data));
    printf("/////////////////////////////////////////////////////\n\n");
}

/*
    Mostra a lista de cadastrados.
*/
int verClientes(int ver) {
    // Variavel de verificação
    int vf = 0;
    // Vãriavel cliente para leitura e alocação de memória do endereco
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    // Abre o arquivo
    FILE* txt = fopen(PATH_CLIENTE, "r");
    // Verifica se o arquivo foi aberto e se a alocação de memória do endereço foi feita
    if (txt == NULL || cliente.endereco == NULL) {
        return 1;
    }
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", cliente.nome) != EOF) {
        fscanf(txt, " %s", cliente.cpf);
        fscanf(txt, " %[^\n]", cliente.telefone);
        fscanf(txt, " %[^\n]", cliente.endereco->rua);
        fscanf(txt, " %d", &cliente.endereco->numero);
        fscanf(txt, " %[^\n]", cliente.endereco->bairro);
        fscanf(txt, " %[^\n]", cliente.endereco->cidade);
        fscanf(txt, " %[^\n]", cliente.endereco->estado);
        fscanf(txt, " %s", cliente.email);
        fscanf(txt, " %d/%d/%d", &cliente.dataCadastro.dia, &cliente.dataCadastro.mes, &cliente.dataCadastro.ano);
        if (ver == 1) {
            mostrarCliente(cliente);
        }
        vf++;
    }
    // Libera a memória alocada para o endereço
    free(cliente.endereco);
    // Fecha o arquivo
    fclose(txt);
    // Verifica se houve algum cliente cadastrado
    if (vf == 0) {
        return -1;
    }
    return 0;
}

#endif
