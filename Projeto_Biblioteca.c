#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cabecalho.h"

// Define o número máximo de usuários e livros permitidos
#define max_usuarios 250
#define max_livros 250

int main() {
    // Declaração de variáveis
    struct cadastro info[max_usuarios];
    struct livro info_livro[max_livros];
    // Inicializa o número de usuários e livros com zero
    int livros = 0;
    int usuarios = 0;

    // Pré-cadastro de um livro de literatura brasileira
    strcpy(info_livro[livros].codigo, "001");
    strcpy(info_livro[livros].titulo, "Dom Casmurro");
    strcpy(info_livro[livros].autor, "Machado de Assis");
    strcpy(info_livro[livros].paginas, "256");
    strcpy(info_livro[livros].status, "Disponivel");
    info_livro[livros].disponivel = 1;
    info_livro[livros].emprestado = 0;
    strcpy(info_livro[livros].data_emprestimo, "");
    strcpy(info_livro[livros].data_devolucao, "");
    livros++;

    // Pré-cadastro de um usuario
    strcpy(info[usuarios].usuario, "user");
    strcpy(info[usuarios].senha, "123");
    strcpy(info[usuarios].confirmacao, "123");
    strcpy(info[usuarios].status, "Ativo");
    usuarios++;

    menu_entrada(info, info_livro, usuarios, livros);
    return 0;
}