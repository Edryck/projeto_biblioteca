#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef CABECALHO_H // Verifica se o cabeçalho foi definido
#define CABECALHO_H // Define o cabeçalho

// Struct para armazenar dados dos usuários, admin e livros
struct cadastro {
    char usuario[45];
    char senha[15];
    char confirmacao[15];
    char status[15];
    char livros_emprestados[5][45];
    char data_emprestimo[5][15];
    char data_devolucao[5][15];
};
struct admin {
    char nome[45];
    char senha[15];
};
struct livro {
    char titulo[45];
    char codigo[5];
    char autor[45];
    char paginas[10];
    char status[10];
    int disponivel;
    int emprestado;
    char data_emprestimo[15];
    char data_devolucao[15];
};

// Função para calcular a data de emprestimo e definir a devolucao daqui 15 dias
void calcular_datas(char data_retirada[], char data_devolucao[]);
// Função para o menu de entrada
int menu_entrada(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para o menu de login 
void menu_login(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para o menu de admin
void menu_admin(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para o menu de usuário
void menu_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario);
// Função para cadastrar usuários
void cadastrar_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para cadastrar livros
void cadastrar_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para listar usuários
void listar_usuarios(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para pesquisa de livros do administrador
void pesquisa_livros(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para pesquisar livros
void pesquisa_livros_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario);
// Função para o administrador listar livros
void catalogo_livros_admin(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para listar livros
void catalogo_livros(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario);
// Função para excluir usuários
void excluir_usuario(struct cadastro info[], int usuarios);
// Função para excluir livros
void excluir_livro(struct livro info_livro[], int livros);
// Função para listar todos os livros
void catalago_livros(struct livro info_livro[], int livros);
// Função para ordenar os livros por título (ordem alfabética)
void ordenar_livros(struct livro info_livro[], int livros);
// Função para ordenar livros por autor (ordem alfabética)
void ordenar_livros_autor(struct livro info_livro[], int livros);
// Função para ordenar livros pelo código (ordem crescente)
void ordenar_livros_codigo(struct livro info_livro[], int livros);
// Função para listar os livros emprestados pelo usuário e exibir o usuario que pegou
void listar_livros_emprestados(struct cadastro info[], struct livro info_livro[], int usuarios, int livros);
// Função para emprestar um livro
void emprestar_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int indice_usuario, int livros);
// Função para devolver um livro
void devolver_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int indice_usuario, int livros);

#endif // Fim do cabeçalho