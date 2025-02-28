#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>

// Data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Produto
typedef struct {
    char nome[50];        
    float valorCompra;  
    float valorVenda;   
    float lucro;         
    int qtd;        
    Data dataCadastro;
} Produto;

// Endereço
typedef struct {
    char rua[50];
    char bairro[20];
    char cidade[20];
    char estado[50];
    int numero;
} Endereco;

// Cliente
typedef struct{
    char nome[50];
    char cpf[15];
    char telefone[15];
    Endereco* endereco;
    char email[50];
    Data dataCadastro;
} Cliente;

// Fornecedor
typedef struct {
    char nomeFantasia[50];
    char cnpj[15];
    char telefone[15];
    Endereco* endereco;
    char email[50];
    Data dataCadastro;              
} Fornecedor;

// Compras
typedef struct {
    Produto produto;
    int qtdProduto;
    float valor;
} Compra;
 
// Nota Fiscal
typedef struct {
    char observacao[100];
    Cliente cliente;
    int qtdCompras;
    Compra *compras;
    char formaPagamento[25];
    float valorTotal; 
    Data dataFechamento;
} NotaFiscal;

#endif