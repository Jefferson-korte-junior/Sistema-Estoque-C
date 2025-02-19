#include <stdio.h>

// Estrutura que define as características de um produto
typedef struct {
    char nome[50];        // Nome do produto
    float valorCompra;    // Valor de compra do produto
    float valorVenda;     // Valor de venda do produto
    float lucro;          // Lucro obtido com a venda do produto
    int qtdVendas;        // Quantidade de vendas do produto
} Produto;

typedef struct {
    char rua[50];
    char bairro[20];
    char cidade[20];
    char estado[50];
    int numeroCasa;
} Endereco;

typedef struct{
    char nome[50];
    char cpf[15];
    char telefone;
    Endereco endereco;
    char Email[50];

} Cliente;


typedef struct {
    Produto produto;
    int qtdProduto;
    float valor;
} Compras;
 

typedef struct {
    Compras *compras;
    float valorTotal; 
    Cliente cliente;
    char formaPagamento[25];
    char status[30];
} NotaFiscal;


typedef struct {
    char nomeFantasia[50];
    char CNPJ[15];
    Endereco endereco;
    char email[25];
    char telefone[25];
} Fornecedor;


int main() {

    
    return 0;
}
