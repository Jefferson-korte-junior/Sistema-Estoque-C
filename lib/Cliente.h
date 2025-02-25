#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menus.h"
#include "Structs.h"
#include "Cliente.h"

#define PATH_CLIENTE "../txt/Clientes.txt"

int editarCliente() {
    char cpf[15];
    printf ("//////////////////////////////////////////\n");
    printf("Digite o CPF do cliente que deseja editar: ");
    scanf(" %s", cpf);
    printf ("\n//////////////////////////////////////////\n");
    
    FILE* txt = fopen(PATH_CLIENTE, "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return 1;
    }
    
    FILE* temp = fopen("../txt/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(txt);
        return 1;
    }
    
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    if (cliente.endereco == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(txt);
        fclose(temp);
        return 1;
    }
    
    int encontrado = 0;
    while (fscanf(txt, " %[^\n]", cliente.nome) != EOF) {
        fscanf(txt, " %s", cliente.cpf);
        fscanf(txt, " %[^\n]", cliente.telefone);
        fscanf(txt, " %[^\n]", cliente.endereco->rua);
        fscanf(txt, " %d", &cliente.endereco->numero);
        fscanf(txt, " %[^\n]", cliente.endereco->bairro);
        fscanf(txt, " %[^\n]", cliente.endereco->cidade);
        fscanf(txt, " %[^\n]", cliente.endereco->estado);
        fscanf(txt, " %[^\n]", cliente.email);
        fscanf(txt, " %d/%d/%d", &cliente.dataCadastro.dia, &cliente.dataCadastro.mes, &cliente.dataCadastro.ano);
        
        if (strcmp(cliente.cpf, cpf) == 0) {
            encontrado = 1;
            printf("Digite os novos dados do cliente:\n");
            printf("Nome: ");
            scanf(" %[^\n]", cliente.nome);
            printf("Telefone: ");
            scanf(" %[^\n]", cliente.telefone);
            printf("Rua: ");
            scanf(" %[^\n]", cliente.endereco->rua);
            printf("Número: ");
            scanf(" %d", &cliente.endereco->numero);
            printf("Bairro: ");
            scanf(" %[^\n]", cliente.endereco->bairro);
            printf("Cidade: ");
            scanf(" %[^\n]", cliente.endereco->cidade);
            printf("Estado: ");
            scanf(" %[^\n]", cliente.endereco->estado);
            printf("Email: ");
            scanf(" %[^\n]", cliente.email);
            // Data de Cadastro
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            cliente.dataCadastro.dia = tm.tm_mday;
            cliente.dataCadastro.mes = tm.tm_mon + 1;
            cliente.dataCadastro.ano = tm.tm_year + 1900;
        }
        
        fprintf(temp, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
                cliente.nome, cliente.cpf, cliente.telefone, cliente.endereco->rua, cliente.endereco->numero, 
                cliente.endereco->bairro, cliente.endereco->cidade, cliente.endereco->estado, 
                cliente.email, cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
    }
    printf ("\n//////////////////////////////////////////\n");
    
    fclose(txt);
    fclose(temp);
    free(cliente.endereco);
    
    if (!encontrado) {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
        remove("../txt/temp.txt");
        return 1;
    }
    
    remove(PATH_CLIENTE);
    rename("../txt/temp.txt", PATH_CLIENTE);
    printf("Cliente atualizado com sucesso!\n");
    return 0;
}

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
    return 0;
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
    // Data de cadastro
    char data[10];
    sprintf(data, "%02d/%02d/%02d", cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
    // Mostra o cliente
    printf("/////////////////////////////////////////////////////\n");
    printf ("[Cliente]: %s\n", cliente.nome);
    printf("/////////////////////////////////////////////////////\n");
    printf ("[CPF]: %s\n", cliente.cpf);
    printf ("[Telefone]: %s\n", cliente.telefone);
    printf ("[Rua]: %s, %d\n", cliente.endereco->rua, cliente.endereco->numero);
    printf ("[Numero]: %d\n", cliente.endereco->numero);
    printf ("[Bairro]: %s\n", cliente.endereco->bairro);
    printf ("[Cidade]: %s\n", cliente.endereco->cidade);
    printf ("[Estado]: %s\n", cliente.endereco->estado);
    printf ("[Email]: %s\n", cliente.email);
    printf ("[Data de Cadastro]: %s\n", data);
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
