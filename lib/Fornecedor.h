#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdio.h>
#include <stdlib.h>

#include "Structs.h"
#include "Endereco.h"

#define PATH_FORNECEDOR "../txt/Fornecedores.txt"

// Protótipos
Fornecedor* novoFornecedor();
int cadastrarFornecedor(Fornecedor* fornecedor);
int editarFornecedor();
int buscarFornecedor();
void mostrarFornecedor(Fornecedor fornecedor);
int listarFornecedores(int ver);
int zerarFornecedores();

/*
    Novo Fornecedor:
*/
Fornecedor* novoFornecedor() {
    // Aloca Fornecedor
    Fornecedor* novoFornecedor = (Fornecedor*) malloc(sizeof(Fornecedor));
    if (novoFornecedor == NULL) {
        return NULL;
    }
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("                   Novo Fornecedor\n");
    printf("-----------------------------------------------------\n\n");
    // Nome Fantasia
    printf("> Digite o nome Fantasia:\n");
    if (scanf(" %[^\n]", novoFornecedor->nomeFantasia) == 0 || strlen(novoFornecedor->nomeFantasia) <= 0) {
        free(novoFornecedor);
        return NULL;
    }
    // Cnpj
    printf("> Digite o CNPJ:\n");
    if (scanf(" %s", novoFornecedor->cnpj) == 0 || strlen(novoFornecedor->cnpj) != 11) {
        free(novoFornecedor);
        return NULL;
    }
    // Telefone
    printf("> Digite o Telefone:\n");
    if (scanf(" %s", novoFornecedor->telefone) == 0 || (strlen(novoFornecedor->telefone) <= 0)) {
        free(novoFornecedor);
        return NULL;
    }
    // Endereço
    novoFornecedor->endereco = novoEndereco();
    if (novoFornecedor->endereco == NULL) {
        free(novoFornecedor);
        return NULL;
    }
    // Email
    printf("> Digite o email:\n");
    if (scanf(" %s", novoFornecedor->email) == 0 || (strlen(novoFornecedor->email) <= 0 || strstr(novoFornecedor->email, "@") == NULL)) {
        free(novoFornecedor);
        return NULL;
    }
    // Data de Cadastro
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    novoFornecedor->dataCadastro.dia = tm.tm_mday;
    novoFornecedor->dataCadastro.mes = tm.tm_mon + 1;
    novoFornecedor->dataCadastro.ano = tm.tm_year + 1900;
    return novoFornecedor;
}

/*
    Cadastra um fornecedor.
*/
int cadastrarFornecedor(Fornecedor* fornecedor) {
    // Abre o arquivo
    FILE* txt = fopen(PATH_FORNECEDOR, "a");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Escreve no arquivo os dados
    fprintf(txt, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
    fornecedor->nomeFantasia,
    fornecedor->cnpj,
    fornecedor->telefone,
    fornecedor->endereco->rua,
    fornecedor->endereco->numero,
    fornecedor->endereco->bairro,
    fornecedor->endereco->cidade,
    fornecedor->endereco->estado,
    fornecedor->email,
    fornecedor->dataCadastro.dia,
    fornecedor->dataCadastro.mes,
    fornecedor->dataCadastro.ano);
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

/*
    Função para editar fornecedor.
*/
int editarFornecedor() {
    char cnpj[15];
    printf("-----------------------------------------------------\n");
    printf("                   Editar Fornecedor\n");
    printf("-----------------------------------------------------\n\n");
    printf("> Digite o CNPJ do fornecedor que deseja editar:\n");
    scanf(" %s", cnpj);
    
    FILE* txt = fopen(PATH_FORNECEDOR, "r");
    if (txt == NULL) {
        return 1;
    }
    
    FILE* temp = fopen("../txt/temp.txt", "w");
    if (temp == NULL) {
        fclose(txt);
        return 1;
    }
    
    Fornecedor fornecedor;
    fornecedor.endereco = (Endereco*) malloc(sizeof(Endereco));
    if (fornecedor.endereco == NULL) {
        fclose(txt);
        fclose(temp);
        return 1;
    }
    
    int encontrado = 0;
    while (fscanf(txt, " %[^\n]", fornecedor.nomeFantasia) != EOF) {
        fscanf(txt, " %s", fornecedor.cnpj);
        fscanf(txt, " %[^\n]", fornecedor.telefone);
        fscanf(txt, " %[^\n]", fornecedor.endereco->rua);
        fscanf(txt, " %d", &fornecedor.endereco->numero);
        fscanf(txt, " %[^\n]", fornecedor.endereco->bairro);
        fscanf(txt, " %[^\n]", fornecedor.endereco->cidade);
        fscanf(txt, " %[^\n]", fornecedor.endereco->estado);
        fscanf(txt, " %[^\n]", fornecedor.email);
        fscanf(txt, " %d/%d/%d", &fornecedor.dataCadastro.dia, &fornecedor.dataCadastro.mes, &fornecedor.dataCadastro.ano);
        
        if (strcmp(fornecedor.cnpj, cnpj) == 0) {
            encontrado = 1;
            printf("Digite os novos dados do fornecedor:\n");
            printf("Nome: ");
            scanf(" %[^\n]", fornecedor.nomeFantasia);
            printf("Telefone: ");
            scanf(" %[^\n]", fornecedor.telefone);
            printf("Rua: ");
            scanf(" %[^\n]", fornecedor.endereco->rua);
            printf("Número: ");
            scanf(" %d", &fornecedor.endereco->numero);
            printf("Bairro: ");
            scanf(" %[^\n]", fornecedor.endereco->bairro);
            printf("Cidade: ");
            scanf(" %[^\n]", fornecedor.endereco->cidade);
            printf("Estado: ");
            scanf(" %[^\n]", fornecedor.endereco->estado);
            printf("Email: ");
            scanf(" %[^\n]", fornecedor.email);
            // Data de Cadastro
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            fornecedor.dataCadastro.dia = tm.tm_mday;
            fornecedor.dataCadastro.mes = tm.tm_mon + 1;
            fornecedor.dataCadastro.ano = tm.tm_year + 1900;
        }
        
        fprintf(temp, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%02d/%02d/%02d\n\n",
                fornecedor.nomeFantasia, fornecedor.cnpj, fornecedor.telefone, fornecedor.endereco->rua, fornecedor.endereco->numero, 
                fornecedor.endereco->bairro, fornecedor.endereco->cidade, fornecedor.endereco->estado, 
                fornecedor.email, fornecedor.dataCadastro.dia, fornecedor.dataCadastro.mes, fornecedor.dataCadastro.ano);
    }
    
    fclose(txt);
    fclose(temp);
    free(fornecedor.endereco);
    
    if (!encontrado) {
        printf("Fornecedor com CNPJ %s não encontrado.\n", cnpj);
        remove("../txt/temp.txt");
        return 1;
    }
    
    remove(PATH_FORNECEDOR);
    rename("../txt/temp.txt", PATH_FORNECEDOR);
    printf("Fornecedor atualizado com sucesso!\n");
    return 0;
}

/*
    Função para buscar fornecedor.
*/
int buscarFornecedor(){
    char cnpj[15];
    printf("-----------------------------------------------------\n");
    printf("                  Buscar FOrnecedor\n");
    printf("-----------------------------------------------------\n\n");
    printf("> Digite o CNPJ do fornecedor:\n");
    scanf(" %s", cnpj);
    // Variavel de verificação
    int vf = 0;
    Fornecedor fornecedor;
    fornecedor.endereco = (Endereco*) malloc(sizeof(Endereco));
    // Abre o arquivo
    FILE* txt = fopen(PATH_FORNECEDOR, "r");
    if (txt == NULL || fornecedor.endereco == NULL) {
        return 1;
    }
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        printf("-> Problema ao tentar abrir arquivo...\n");
        return 1;
    }
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", fornecedor.nomeFantasia) != EOF) {
        fscanf(txt, " %s", fornecedor.cnpj);
        fscanf(txt, " %[^\n]", fornecedor.telefone);
        fscanf(txt, " %[^\n]", fornecedor.endereco->rua);
        fscanf(txt, " %d", &fornecedor.endereco->numero);
        fscanf(txt, " %[^\n]", fornecedor.endereco->bairro);
        fscanf(txt, " %[^\n]", fornecedor.endereco->cidade);
        fscanf(txt, " %[^\n]", fornecedor.endereco->estado);
        fscanf(txt, " %s", fornecedor.email);
        fscanf(txt, " %d/%d/%d", &fornecedor.dataCadastro.dia, &fornecedor.dataCadastro.mes, &fornecedor.dataCadastro.ano);
        // mostrarFornecedor(fornecedor);
        if (strcmp(fornecedor.cnpj, cnpj) == 0) {
            // Mostra o Fornecedor
            mostrarFornecedor(fornecedor);
            // Fecha o arquivo
            fclose(txt);
            return 0;
        }
        vf++;
    }
    // Fecha o arquivo
    fclose(txt);
    return 1;
}

/*
    Mostra um fornecedor.
*/
void mostrarFornecedor(Fornecedor fornecedor) {
    // Data de cadastro
    char data[10];
    sprintf(data, "%02d/%02d/%02d", fornecedor.dataCadastro.dia, fornecedor.dataCadastro.mes, fornecedor.dataCadastro.ano);
    // Mostra o fornecedor
    printf("-----------------------------------------------------\n");
    printf ("[Fornecedor]: %s\n", fornecedor.nomeFantasia);
    printf("-----------------------------------------------------\n");
    printf ("[CNPJ]: %s\n", fornecedor.cnpj);
    printf ("[Telefone]: %s\n", fornecedor.telefone);
    printf ("[Rua]: %s, %d\n", fornecedor.endereco->rua, fornecedor.endereco->numero);
    printf ("[Numero]: %d\n", fornecedor.endereco->numero);
    printf ("[Bairro]: %s\n", fornecedor.endereco->bairro);
    printf ("[Cidade]: %s\n", fornecedor.endereco->cidade);
    printf ("[Estado]: %s\n", fornecedor.endereco->estado);
    printf ("[Email]: %s\n", fornecedor.email);
    printf ("[Data de Cadastro]: %s\n", data);
    printf("-----------------------------------------------------\n");
}

/*
    Mostra um fornecedor.
*/
void mostrarfornecedor(Fornecedor fornecedor) {
    printf("-----------------------------------------------------\n");
    printf("> %s\n", fornecedor.nomeFantasia);
    printf("-----------------------------------------------------\n");
    printf(" CNPJ: %s\n", fornecedor.cnpj);
    printf(" Telefone: %s\n", fornecedor.telefone);
    printf(" Endereco: %s, %d, %s, %s, %s\n", fornecedor.endereco->rua, fornecedor.endereco->numero, fornecedor.endereco->bairro, fornecedor.endereco->cidade, fornecedor.endereco->estado);
    printf(" Email: %s\n", fornecedor.email);
    printf(" Data de Cadastro: %02d/%02d/%02d\n\n", fornecedor.dataCadastro.dia, fornecedor.dataCadastro.mes, fornecedor.dataCadastro.ano);
    printf("-----------------------------------------------------\n");
}

/*
    Mostra a lista de cadastrados.
*/
int listarFornecedores(int ver) {
    // Variavel Fornecedor
    int vf = 0;
    // Variavel Fornecedor para leitura
    Fornecedor fornecedor;
    fornecedor.endereco = (Endereco*) malloc(sizeof(Endereco));
    // Abre o arquivo
    FILE* txt = fopen(PATH_FORNECEDOR, "r");
    if (txt == NULL || fornecedor.endereco == NULL) {
        return 1;
    }
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Faz a leitura do arquivo
    while (fscanf(txt, " %[^\n]", fornecedor.nomeFantasia) != EOF) {
        fscanf(txt, " %s", fornecedor.cnpj);
        fscanf(txt, " %[^\n]", fornecedor.telefone);
        fscanf(txt, " %[^\n]", fornecedor.endereco->rua);
        fscanf(txt, " %d", &fornecedor.endereco->numero);
        fscanf(txt, " %[^\n]", fornecedor.endereco->bairro);
        fscanf(txt, " %[^\n]", fornecedor.endereco->cidade);
        fscanf(txt, " %[^\n]", fornecedor.endereco->estado);
        fscanf(txt, " %s", fornecedor.email);
        fscanf(txt, " %d/%d/%d", &fornecedor.dataCadastro.dia, &fornecedor.dataCadastro.mes, &fornecedor.dataCadastro.ano);
        if (ver == 1) {
            mostrarfornecedor(fornecedor);
        }
        vf++;
    }
    // Fecha o arquivo
    fclose(txt);
    // Verifica se houve algum fornecedor cadastrado
    if (vf == 0) {
        return -1;
    }
    return 0;
}

/*
    Zera a lista de fornecedores.
*/
int zerarFornecedores() {
    // Abre o arquivo
    FILE* txt = fopen(PATH_FORNECEDOR, "w");
    // Verifica se o arquivo foi aberto
    if (txt == NULL) {
        return 1;
    }
    // Fecha o arquivo
    fclose(txt);
    return 0;
}

#endif
