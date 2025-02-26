#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menus.h"
#include "Structs.h"
#include "Cliente.h"
#include "Endereco.h"

#define PATH_CLIENTE "../txt/Clientes.txt"

// Protótipos
Cliente* novoCliente();
int cadastrarCliente(Cliente* cliente);
int editarCliente();
int buscarCliente();
void mostrarCliente(Cliente cliente);
int listarClientes(int ver);
int zerarClientes();

/*
    Novo Cliente:
*/
Cliente* novoCliente() {
    // Aloca Cliente
    Cliente* novoCliente = (Cliente*) malloc(sizeof(Cliente));
    if (novoCliente == NULL) {
        return NULL;
    }
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                    Novo Cliente\n");
    printf("-----------------------------------------------------\n\n");
    printf("> Digite o nome:\n");
    if (scanf(" %[^\n]", novoCliente->nome) == 0 || strlen(novoCliente->nome) <= 0) {
        free(novoCliente);
        return NULL;
    }
    // Cnpj
    printf("> Digite o CPF: (SOMENTE NUMEROS)\n");
    if (scanf(" %s", novoCliente->cpf) == 0 || strlen(novoCliente->cpf) != 11) {
        free(novoCliente);
        return NULL;
    }
    // Telefone
    printf("> Digite o Telefone:\n");
    if (scanf(" %[^\n]", novoCliente->telefone) == 0 || (strlen(novoCliente->telefone) <= 0)) {
        free(novoCliente);
        return NULL;
    }
    // Email
    printf("> Digite o email:\n");
    if (scanf(" %s", novoCliente->email) == 0 || (strlen(novoCliente->email) <= 0 || strstr(novoCliente->email, "@") == NULL)) {
        free(novoCliente);
        return NULL;
    }
    // Endereço
    novoCliente->endereco = novoEndereco();
    if (novoCliente->endereco == NULL) {
        free(novoCliente);
        return NULL;
    }
    // Data de Cadastro
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    novoCliente->dataCadastro.dia = tm.tm_mday;
    novoCliente->dataCadastro.mes = tm.tm_mon + 1;
    novoCliente->dataCadastro.ano = tm.tm_year + 1900;
    return novoCliente;
}

/*
    Cadastra um cliente.
*/
int cadastrarCliente(Cliente* cliente) {
    // Abre o arquivo
    FILE* txt = fopen(PATH_CLIENTE, "a");
    // Verifica se o arquivo foi aberto 
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return 1;
    }
    // Escreve no arquivo os dados
    fprintf(txt, "%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
    cliente->nome,
    cliente->cpf,
    cliente->telefone,
    cliente->email, 
    cliente->endereco->rua,
    cliente->endereco->numero, 
    cliente->endereco->bairro, 
    cliente->endereco->cidade, cliente->endereco->estado, 
    cliente->dataCadastro.dia, 
    cliente->dataCadastro.mes, 
    cliente->dataCadastro.ano);
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Editar Cliente:
*/
int editarCliente() {
    char cpf[15];
    printf("-----------------------------------------------------\n");
    printf("                    Editar Cliente\n");
    printf("-----------------------------------------------------\n\n");
    printf("> Digite o CPF do cliente que deseja editar:\n");
    scanf(" %s", cpf);
    
    FILE* txt = fopen(PATH_CLIENTE, "r");
    if (txt == NULL) {
        return 1;
    }
    
    FILE* temp = fopen("../txt/temp.txt", "w");
    if (temp == NULL) {
        fclose(txt);
        return 1;
    }
    
    Cliente cliente;
    cliente.endereco = (Endereco*) malloc(sizeof(Endereco));
    if (cliente.endereco == NULL) {
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
            printf("> Digite os novos dados do cliente:\n");
            printf("> Nome: ");
            scanf(" %[^\n]", cliente.nome);
            printf("> Telefone: ");
            scanf(" %[^\n]", cliente.telefone);
            printf("> Rua: ");
            scanf(" %[^\n]", cliente.endereco->rua);
            printf("> Email: ");
            scanf(" %[^\n]", cliente.email);
            printf("> Número: ");
            scanf(" %d", &cliente.endereco->numero);
            printf("> Bairro: ");
            scanf(" %[^\n]", cliente.endereco->bairro);
            printf("> Cidade: ");
            scanf(" %[^\n]", cliente.endereco->cidade);
            printf(": Estado: ");
            scanf(" %[^\n]", cliente.endereco->estado);
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
    
    fclose(txt);
    fclose(temp);
    free(cliente.endereco);
    
    if (!encontrado) {
        printf("-> Cliente com CPF %s não encontrado.\n", cpf);
        remove("../txt/temp.txt");
        return 1;
    }
    
    remove(PATH_CLIENTE);
    rename("../txt/temp.txt", PATH_CLIENTE);
    printf("-> Cliente atualizado com sucesso!\n");
    return 0;
}

/*
    Buscar Cliente:
*/
int buscarCliente(){
    // Solicita o CPF do Cliente
    char cpf[15];
    printf("-----------------------------------------------------\n");
    printf("                    Buscar Cliente\n");
    printf("-----------------------------------------------------\n\n");
    printf("> Digite o CPF do cliente:\n");
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
        if (strcmp(cliente.cpf, cpf) == 0) {
            // Mostra o Cliente
            mostrarCliente(cliente);
            // Fecha o arquivo
            fclose(txt);
        }
        vf++;
    }
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Mostra um cliente.
*/
void mostrarCliente(Cliente cliente) {
    // Mostra o cliente
    printf("-----------------------------------------------------\n");
    printf("[Nome]: %s\n", cliente.nome);
    printf("-----------------------------------------------------\n");
    printf("[CPF]: %s\n", cliente.cpf);
    printf("[Telefone]: %s\n", cliente.telefone);
    printf("[Email]: %s\n", cliente.email);
    printf("[Rua]: %s\n", cliente.endereco->rua);
    printf("[Numero]: %d\n", cliente.endereco->numero);
    printf("[Bairro]: %s\n", cliente.endereco->bairro);
    printf("[Cidade]: %s\n", cliente.endereco->cidade);
    printf("[Estado]: %s\n", cliente.endereco->estado);
    printf("[Data de Cadastro]: %02d/%02d/%02d\n", cliente.dataCadastro.dia, cliente.dataCadastro.mes, cliente.dataCadastro.ano);
    printf("-----------------------------------------------------\n\n");
}

/*
    Mostra a lista de cadastrados.
*/
int listarClientes(int ver) {
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
        fscanf(txt, " %s", cliente.email);
        fscanf(txt, " %[^\n]", cliente.endereco->rua);
        fscanf(txt, " %d", &cliente.endereco->numero);
        fscanf(txt, " %[^\n]", cliente.endereco->bairro);
        fscanf(txt, " %[^\n]", cliente.endereco->cidade);
        fscanf(txt, " %[^\n]", cliente.endereco->estado);
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

/*
    Zera a lista de Clientes:
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

#endif
