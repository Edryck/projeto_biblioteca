#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cabecalho.h"

// Função para calcular as datas de empréstimo e devolução (15 dias depois)
void calcular_datas(char data_retirada[100], char data_devolucao[100]) {
    time_t agora;
    struct tm dataAtual, dataDevolucaoStruct;
    
    time(&agora);
    dataAtual = *localtime(&agora);
    
    // Preenche data de retirada com a data atual
    strftime(data_retirada, 100, "%d/%m/%Y", &dataAtual);
    
    // Copia data atual para data de devolução e adiciona 15 dias
    dataDevolucaoStruct = dataAtual;
    dataDevolucaoStruct.tm_mday += 15;
    // mktime normaliza a data (ajustando mês e ano se necessário)
    mktime(&dataDevolucaoStruct);
    strftime(data_devolucao, 100, "%d/%m/%Y", &dataDevolucaoStruct);
}

// Função menu de entrada
int menu_entrada(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    int opcao;
    do{
        printf("=========================================\n");
        printf("                                         \n");
        printf("           BIBLIOTECA VIRTUAL            \n");
        printf("                                         \n");
        printf("=========================================\n");
        printf("                                         \n");
        printf("          1 - Login                      \n");
        printf("          2 - Sair                       \n");
        printf("                                         \n");
        printf("=========================================\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                menu_login(info, info_livro, usuarios, livros);
                break;
            case 2:
                printf("Saindo...\n");
                getchar();
                return 0;
            default:
                printf("Opção inválida!\n");
                system("cls");
        } 
    } while (opcao != 2);
}

// Função para o menu de login
void menu_login(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    int usuario_encontrado = 0;
    int indice_usuario = -1;
    char login[45];
    char senha[15];
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("             AREA DE LOGIN               \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o nome de usuario: ");
    scanf("%s", login);
    printf("                                         \n");
    //Se for o administrador pede a senha
    if (strcmp(login, "admin") == 0){
        printf("Digite a senha: ");
        scanf("%s", senha);
        // Se a for a senha correta direciona para o menu de administrador
        if (strcmp(senha, "admin") == 0){
            system("cls");
            printf("Login efetuado com sucesso!\n");
            printf("Tecle ENTER para continuar...");
            getchar();
            system("cls");
            menu_admin(info, info_livro, usuarios, livros);
        // Se não for a senha correta, volta para o menu de login
        } else {
            printf("Senha incorreta!\n");
            printf("Voce sera redirecionado para o menu de login!\n");
            getchar();
            printf("Tecle ENTER para continuar...");
            getchar();
            system("cls");
            menu_login(info, info_livro, usuarios, livros);
        } 
    } else {
            // Procura o usuario digitado pelo vetor
            for (int i = 0; i < usuarios; i++) {
                // Se encontrado prossegue para pedir a senha
                if (strcmp(info[i].usuario, login) == 0) {
                    printf("Digite a senha: ");
                    scanf("%s", senha);
                    // Direciona para o menu do usuario
                    if (strcmp(info[i].senha, senha) == 0) {
                        printf("Login efetuado com sucesso!\n");
                        getchar();
                        printf("Tecle ENTER para continuar...");
                        getchar();
                        system("cls");
                        printf("Bem-vindo, %s!\n", info[i].usuario);
                        indice_usuario = i;
                        menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
                        break;
                    // Volta ao menu de login em caso de senha incorreta
                    } else {
                        printf("Senha incorreta!\n");
                        printf("Voce sera redirecionado para o menu de login!");
                        printf("Tecle ENTER para continuar...");
                        getchar();
                        system("cls");
                    }
                }
            }
            // Volta ao menu inicial caso o usuario não seja encontrado
            if (usuario_encontrado == 0) {
            printf("Usuario nao encontrado!\n");
            printf("-----------------------------------------\n");
            printf("Em caso de nao ter cadastro no sistema\n    entre em contato com o administrador\npara realizar seu cadastro.\n");
            printf("-----------------------------------------\n");
            getchar();
            printf("Tecle ENTER para voltar a Tela de Inicio...");
            getchar();
            system("cls");
            menu_entrada(info, info_livro, usuarios, livros);
            }
    }
}

// Função para o menu de admin
void menu_admin(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    int opcao;
    do {
        system("cls");
        printf("=========================================\n");
        printf("                                         \n");
        printf("           BIBLIOTECA VIRTUAL            \n");
        printf("                                         \n");
        printf("=========================================\n");
        printf("                                         \n");
        printf("          MENU DO ADMINISTRADOR          \n");
        printf("                                         \n");
        printf("-----------------------------------------\n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Cadastrar Livro\n");
        printf("3 - Lista de Usuarios\n");
        printf("4 - Catalogo de Livros\n");
        printf("5 - Lista de Livros Emprestados\n");
        printf("6 - Pesquisar Livros\n");
        printf("7 - Excluir Usuario\n");
        printf("8 - Excluir Livro\n");
        printf("9 - Voltar a Tela Inicial\n");
        printf("-----------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: // check
                cadastrar_usuario(info, info_livro, usuarios, livros);
                usuarios++;
                system("cls");
                break;
            case 2: // check
                cadastrar_livro(info, info_livro, usuarios, livros);
                livros++;
                system("cls");
                break;
            case 3: // check
                listar_usuarios(info, info_livro, usuarios, livros);
                break;
            case 4: // check
                catalogo_livros_admin(info, info_livro, usuarios, livros);
                break;
            case 5: // +- check
                listar_livros_emprestados(info, info_livro, usuarios, livros);
                break;
            case 6: // check
                pesquisa_livros(info, info_livro, usuarios, livros);
                break;
            case 7: // Em andamento
                excluir_usuario(info, usuarios);
                break;
            case 8: // Em andamento
                excluir_livro(info_livro, livros);
                break;
            case 9: // check
                menu_entrada(info, info_livro, usuarios, livros);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);
}

// Funcões para o menu de usuário
void menu_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario) {
    int opcao;
    do {
        system("cls");
        printf("=========================================\n");
        printf("                                         \n");
        printf("           BIBLIOTECA VIRTUAL            \n");
        printf("                                         \n");
        printf("=========================================\n");
        printf("                                         \n");
        printf("             MENU DO USUARIO             \n");
        printf("                                         \n");
        printf("-----------------------------------------\n");
        printf("1 - Mostrar o catalogo de livros\n");
        printf("2 - Pesquisar livros\n");
        printf("3 - Emprestar livro\n");
        printf("4 - Devolver livro\n");
        printf("5 - Voltar a Tela Inicial\n");
        printf("-----------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: 
                catalogo_livros(info, info_livro, usuarios, livros, indice_usuario);
                break;
            case 2: 
                pesquisa_livros_usuario(info, info_livro, usuarios, livros, indice_usuario);
                break;
            case 3: 
                emprestar_livro(info, info_livro, usuarios, indice_usuario, livros);
                break;
            case 4:
                devolver_livro(info, info_livro, usuarios, indice_usuario, livros);
                break;
            case 5:
                menu_entrada(info, info_livro, usuarios, livros);
                break;
            default:
                printf("Opcao invalida!\n");
                getchar();
                printf("Tecle ENTER para continuar...");
                getchar();
                system("cls");
        }
    } while (opcao != 5);
}

// Função para cadastrar usuários
void cadastrar_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    char novo_usuario[45];
    int usuario_existe;
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           CADASTRO DE USUARIO           \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    // Confere se o nome do usuário já existe
    printf("Deseja cadastrar um novo usuario ou reativar\num usuario inativo?\nDigite: [1] para cadastrar\n\t[2] para reativar\n");
    char opcao;
    scanf(" %c", &opcao);
    if (opcao == '1') {
        do {
            usuario_existe = 0; // Assume que o usuário não existe
            printf("Digite o seu nome de usuario:\n ");
            scanf("%s", novo_usuario);
            // Verificar se o nome de usuário já existe
            for (int i = 0; i < usuarios; i++) {
                if (strcmp(info[i].usuario, novo_usuario) == 0) {
                    usuario_existe = 1; // Usuário já existe
                    break;
                }
            }
            if (usuario_existe) {
                printf("Usuario ja existe! Tente outro nome.\n");
            }
        } while (usuario_existe);
        strcpy(info[usuarios].usuario, novo_usuario);
        // Define a senha para o usuário
        do {
            printf("Defina uma senha:\n ");
            scanf("%s", info[usuarios].senha);
            printf("Confirme a senha:\n ");
            scanf("%s", info[usuarios].confirmacao);
            if (strcmp(info[usuarios].senha, info[usuarios].confirmacao) != 0) {
                printf("As senhas nao correspondem! Tente novamente.\n");
            }
        } while (strcmp(info[usuarios].senha, info[usuarios].confirmacao) != 0);
        usuarios++;
        strcpy(info[usuarios - 1].status, "Ativo");
        printf("-----------------------------------------\n");
        printf("\nUsuario cadastrado com sucesso!\n\n");
        printf("Usuario: %s \n", info[usuarios - 1].usuario);
        printf("Senha: %s \n", info[usuarios - 1].senha);
        printf("Status atual: %s \n", info[usuarios - 1].status);
        printf("-----------------------------------------\n");
        getchar();
        printf("\nTecle ENTER para voltar ao menu principal...");
        getchar();
        system("cls");
        menu_admin(info, info_livro, usuarios, livros);
    } else if (opcao == '2') {
        printf("Digite o nome do usuario que deseja\nreativar: ");
        scanf("%s", novo_usuario);
        for (int i = 0; i < usuarios; i++) {
            if (strcmp(info[i].usuario, novo_usuario) == 0 && strcmp(info[i].status, "Inativo") == 0) {
                strcpy(info[i].status, "Ativo");
                printf("Usuario  reativado com sucesso!\n");
                getchar();
                printf("Tecle ENTER para voltar ao menu principal...");
                getchar();
                system("cls");
            }
        }
    } else {
        printf("Opcao invalida!\n");
        getchar();
        printf("Tecle ENTER para voltar ao menu principal...");
        getchar();
        system("cls");
    }
}

// Função para cadastrar livros
void cadastrar_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           CADASTRO DE LIVROS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    char novo_livro[45];
    int livro_existe;
    do {
        livro_existe = 0; // Assume que o livro não existe
        printf("Digite o codigo do livro:\n ");
        scanf("%s", novo_livro);
        // Verifica se o Codigo do livro já existe
        for (int i = 0; i < livros; i++) {
            if (strcmp(info_livro[i].codigo, novo_livro) == 0) {
                livro_existe = 1; // Livro já existe
                break;
            }
        } if (livro_existe) {
            printf("Livro ja cadastrado!\n");
        }
    } while (livro_existe);
    strcpy(info_livro[livros].codigo, novo_livro);
    char titulo[75];
    do {
        livro_existe = 0; // Inicia como livro inexistente
        // Adiciona titulo do livro
        printf("Digite o titulo do livro:\n ");
        scanf("%s", titulo);
        // Verifica se o titulo do livro já existe
        for (int i = 0; i < livros; i++) {
            if (strcmp(info_livro[livros].titulo, novo_livro) == 0) {
                livro_existe = 1; // Livro já existe
                break;
            }
        }
        if (livro_existe) {
            printf("Livro ja cadastrado!\n");
        }
    } while (livro_existe);
    strcpy(info_livro[livros].titulo, titulo);
    // Adiciona o nome do autor
    printf("Digite o nome do autor:\n ");
    scanf("%s", info_livro[livros].autor);
    // Adiciona o número de páginas
    printf("Digite o numero de paginas:\n ");
    scanf("%s", info_livro[livros].paginas);
    // Incrementa a quantidade de livros cadastrados
    livros++;
    printf("-----------------------------------------\n");
    printf("Livro cadastrado com sucesso!\n");
    printf("        Informacoes do livro\n\n");
    printf("Codigo: %s\n", info_livro[livros - 1].codigo);
    printf("Titulo: %s\n", info_livro[livros - 1].titulo);
    printf("Autor: %s\n", info_livro[livros - 1].autor);
    printf("Paginas: %s\n", info_livro[livros - 1].paginas);
    printf("-----------------------------------------\n");
    getchar();
    printf("Tecle ENTER para voltar ao menu anterior...");
    getchar();
    system("cls");
    menu_admin(info, info_livro, usuarios, livros);
}

// Função para listar usuários
void listar_usuarios(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("            LISTA DE USUARIOS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < usuarios; i++) {
        printf("Usuário: %s\n", info[i].usuario);
        printf("Senha: %s\n", info[i].senha);
        printf("Status: %s\n", info[i].status);
        printf("-----------------------------------------\n");
    }
    printf("Total de Usuario cadastrados: %d\n", usuarios);
    getchar();
    printf("Tecle ENTER para volta ao menu anterior...");
    getchar();
    menu_admin(info, info_livro, usuarios, livros);
}

// Função para listar os livros emprestados pelo usuário e exibir o usuario que pegou
void listar_livros_emprestados(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           LIVROS EMPRESTADOS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n"); 
    int livros_emprestados = 0;
    for (int i = 0; i < usuarios; i++) {
        if (strcmp(info[i].status, "Ativo") == 0) {
            printf("Usuario: %s\n", info[i].usuario);
            for (int j = 0; j < 5; j++) {
                if (strcmp(info[i].livros_emprestados[j], "") != 0) {
                    printf("Livro: %s\n", info[i].livros_emprestados[j]);
                    printf("Data de Emprestimo: %s\n", info[i].data_emprestimo[j]);
                    printf("Data de Devolucao: %s\n", info[i].data_devolucao[j]);
                    printf("-----------------------------------------\n"); 
                    livros_emprestados++;
                }
            }
        }
    }
    if (livros_emprestados == 0) {
        printf("Nao ha livros emprestados!\n");
    }
    getchar();
    printf("Tecle ENTER para voltar ao menu inicial...");
    getchar();
    system("cls");
    menu_admin(info, info_livro, usuarios, livros);
}

// Função para excluir usuários
void excluir_usuario(struct cadastro info[], int usuarios) {
    char usuario[45];
    int usuario_encontrado = 0;
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           EXCLUSAO DE USUARIO           \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o nome do usuario que deseja\nexcluir: ");
    scanf("%s", usuario);
    for (int i = 0; i < usuarios; i++) {
        if (strcmp(usuario, "admin") == 0) {
            printf("Nao e possivel excluir o usuario admin!\n");
            printf("Tecle ENTER para voltar ao menu inicial...");
            getchar();
            getchar();
            break;
        } else if (strcmp(info[i].usuario, usuario) == 0 && strcmp(info[i].usuario, "") != 0) {
            printf("Confirma a exclusao do usuario %s? (S/N): ", info[i].usuario);
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 'S' || confirmacao == 's') {
                usuario_encontrado = 1;
                strcpy(info[i].status, "Inativo");
                getchar();
                printf("Usuario excluido com sucesso!\n");
                getchar();
                printf("Tecle ENTER para voltar ao menu inicial...");
                break;
            } else {
                printf("Exclusao cancelada!\n");
                printf("Tecle ENTER para voltar ao menu inicial...");
                getchar();
                getchar();
                break;
            }
            
        }
    }
    if (usuario_encontrado == 0) {
        printf("Usuario nao encontrado!\n");
    }
}

// Função para excluir livros
void excluir_livro(struct livro info_livro[], int livros) {
    char codigo[10];
    int livro_encontrado = 0;
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           EXCLUSAO DE LIVROS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o codigo do livro que deseja excluir: ");
    scanf("%s", codigo);
    for (int i = 0; i < livros; i++) {
        if (strcmp(info_livro[i].codigo, codigo) == 0 && info_livro[i].disponivel == 1) {
            livro_encontrado = 1;
            strcpy(info_livro[i].status, "Indisponivel");
            printf("-----------------------------------------\n");
            printf("Livro excluido com sucesso!\n");
            getchar();
            printf("Tecle ENTER para voltar ao menu inicial...");
            getchar();
            system("cls");
            break;
        }
    }
    if (livro_encontrado == 0) {
        printf("Livro nao encontrado!\n");
    }
}

// Função para o administrador ver todos os livros
void catalogo_livros_admin(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           CATALOGO DE LIVROS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < livros; i++) {
        printf("Codigo: %s\n", info_livro[i].codigo);
        printf("Titulo: %s\n", info_livro[i].titulo);
        printf("Autor: %s\n", info_livro[i].autor);
        printf("Paginas: %s\n", info_livro[i].paginas);
        if (info_livro[i].disponivel == 1) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Indisponivel\n");
        }
        printf("-----------------------------------------\n");
    }
    printf("Total de Livros no Catalogo: %d \n", livros);
    printf("-----------------------------------------\n");
    int opcao;
    do{
        printf("1 - Ordenar livros pelo titulo\n");
        printf("2 - Ordenar livros pelo autor\n");
        printf("3 - Ordenar livros pelo codigo\n");
        printf("4 - Pesquisar livros\n");
        printf("5 - Voltar ao menu principal\n");
        printf("-----------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                ordenar_livros(info_livro, livros);
                break;
            case 2:
                ordenar_livros_autor(info_livro, livros);
                break;
            case 3:
                ordenar_livros_codigo(info_livro, livros);
                break;
            case 4:
                pesquisa_livros(info, info_livro, usuarios, livros);
                break;
            case 5:
                menu_admin(info, info_livro, usuarios, livros);
                break;
            default:
                printf("Digito invalido!\n");
                break;
        }
    } while (opcao != 5);
}

// Função para listar todos os livros
void catalogo_livros(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario) {
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           CATALOGO DE LIVROS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < livros; i++) {
        printf("Codigo: %s\n", info_livro[i].codigo);
        printf("Titulo: %s\n", info_livro[i].titulo);
        printf("Autor: %s\n", info_livro[i].autor);
        printf("Paginas: %s\n", info_livro[i].paginas);
        if (info_livro[i].disponivel == 1) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Indisponivel\n");
        }
        printf("-----------------------------------------\n");
    }
    printf("Total de Livros no Catalogo: %d \n", livros);
    printf("-----------------------------------------\n");
    int opcao;
    do{
        printf("1 - Ordenar livros pelo titulo\n");
        printf("2 - Ordenar livros pelo autor\n");
        printf("3 - Ordenar livros pelo codigo\n");
        printf("4 - Pesquisar livros\n");
        printf("5 - Voltar ao menu principal\n");
        printf("-----------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                ordenar_livros(info_livro, livros);
                break;
            case 2:
                ordenar_livros_autor(info_livro, livros);
                break;
            case 3:
                ordenar_livros_codigo(info_livro, livros);
                break;
            case 4:
                pesquisa_livros_usuario(info, info_livro, usuarios, livros, indice_usuario);
                break;
            case 5:
                menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
                break;
            default:
                printf("Digito invalido!\n");
                break;
        }
    } while (opcao != 5);
}

// Função de pesquisa do usuário para buscar livros pelo titulo, autor ou código
void pesquisa_livros(struct cadastro info[], struct livro info_livro[], int usuarios, int livros) {
    int opcao;
    int encontrou = 0;
    char pesquisa[45];
    do {
        system("cls");
        printf("=========================================\n");
        printf("                                         \n");
        printf("           BIBLIOTECA VIRTUAL            \n");
        printf("                                         \n");
        printf("=========================================\n");
        printf("                                         \n");
        printf("           PESQUISA DE LIVROS            \n");
        printf("                                         \n");
        printf("-----------------------------------------\n");
        printf("Digite o titulo, autor ou código do livro: ");
        scanf("%44s", pesquisa);
        for (int i = 0; i < livros; i++) {
            if (strstr(info_livro[i].titulo, pesquisa) != 0 || strstr(info_livro[i].autor, pesquisa) != 0 || strstr(info_livro[i].codigo, pesquisa) != 0) {
                printf("Código: %s\n", info_livro[i].codigo);
                printf("Título: %s\n", info_livro[i].titulo);
                printf("Autor: %s\n", info_livro[i].autor);
                printf("Páginas: %s\n", info_livro[i].paginas);
                printf("Status: %s\n\n", (info_livro[i].disponivel == 1) ? "Disponível" : "Indisponível");
                encontrou = 1;
            }
        }
        if (!encontrou) {
            printf("Nenhum livro encontrado com o critério informado.\n");
        }
        printf("-----------------------------------------\n");
        printf("Deseja pesquisar outro livro?\n");
        printf("1 - Pesquisar Novamente\n");
        printf("2 - Catalogo de Livros\n");
        printf("3 - Voltar ao menu principal\n");
        printf("-----------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                pesquisa_livros(info, info_livro, usuarios, livros);
                break;
            case 2:
                catalogo_livros_admin(info, info_livro, usuarios, livros);
                break;
            case 3:
                menu_admin(info, info_livro, usuarios, livros);
                break;
            default:
                printf("Digito invalido\n");
                getchar();
                printf("Tecle ENTER para continuar...");
                getchar();
                system("cls");
                break;
        }
    } while (opcao != 3);
}

// Função de pesquisa do usuário para buscar livros pelo titulo, autor ou código
void pesquisa_livros_usuario(struct cadastro info[], struct livro info_livro[], int usuarios, int livros, int indice_usuario) {
    int opcao;
    int encontrou;
    char pesquisa[45];
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           PESQUISA DE LIVROS            \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o titulo, autor ou codigo do livro: ");
    scanf(" %[^\n]s", pesquisa);
    pesquisa[strcspn(pesquisa, "\n")] = '\0';
    encontrou = 0;
    for (int i = 0; i < livros; i++) {
        if (strstr(info_livro[i].titulo, pesquisa) != NULL || strstr(info_livro[i].autor, pesquisa) != NULL || strstr(info_livro[i].codigo, pesquisa) != NULL) {
            printf("-----------------------------------------\n");
            printf("Codigo: %s\n", info_livro[i].codigo);
            printf("Titulo: %s\n", info_livro[i].titulo);
            printf("Autor: %s\n", info_livro[i].autor);
            printf("Paginas: %s\n", info_livro[i].paginas);
            printf("Status: %s\n\n", (info_livro[i].disponivel == 1) ? "Disponivel" : "Indisponivel");
            printf("-----------------------------------------\n");
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum livro encontrado.\n");
    }
    printf("-----------------------------------------\n");
    printf("Deseja pesquisar outro livro?\n");
    printf("1 - Pesquisar Novamente\n");
    printf("2 - Catalogo de Livros\n");
    printf("3 - Emprestar Livro\n");
    printf("4 - Voltar ao menu principal\n");
    printf("-----------------------------------------\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            pesquisa_livros_usuario(info, info_livro, usuarios, livros, indice_usuario);
            break;
        case 2:
            catalogo_livros(info, info_livro, usuarios, livros, indice_usuario);
            break;
        case 3:
            emprestar_livro(info, info_livro, usuarios, indice_usuario, livros);
            break;
        case 4:
            menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
            break;
        default:
        printf("Digito invalido");
        getchar();
        printf("Tecle ENTER para continuar...");
        getchar();
        system("cls");
        return;
    }
}

// Função para ordenar os livros por título (ordem alfabética)
void ordenar_livros(struct livro info_livro[], int livros) {
    struct livro temp;
    for (int i = 0; i < livros; i++) {
        for (int j = i + 1; j < livros; j++) {
            if (strcmp(info_livro[i].titulo, info_livro[j].titulo) > 0) {
                temp = info_livro[i];
                info_livro[i] = info_livro[j];
                info_livro[j] = temp;
            }
        }
    }
    printf("\n\tCatálogo de Livros Ordenado\n");
    for (int i = 0; i < livros; i++) {
        printf("Codigo: %s\n", info_livro[i].codigo);
        printf("Titulo: %s\n", info_livro[i].titulo);
        printf("Autor: %s\n", info_livro[i].autor);
        printf("Paginas: %s\n", info_livro[i].paginas);
        if (info_livro[i].disponivel == 1) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Indisponivel\n");
        }
        printf("\n");
    }
}

// Função para ordenar livros por autor (ordem alfabética)
void ordenar_livros_autor(struct livro info_livro[], int livros) {
    struct livro temp;
    for (int i = 0; i < livros; i++) {
        for (int j = i + 1; j < livros; j++) {
            if (strcmp(info_livro[i].autor, info_livro[j].autor) > 0) {
                temp = info_livro[i];
                info_livro[i] = info_livro[j];
                info_livro[j] = temp;
            }
        }
    }
    printf("\n\tCatálogo de Livros Ordenado por Autor\n");
    for (int i = 0; i < livros; i++) {
        printf("Codigo: %s\n", info_livro[i].codigo);
        printf("Titulo: %s\n", info_livro[i].titulo);
        printf("Autor: %s\n", info_livro[i].autor);
        printf("Paginas: %s\n", info_livro[i].paginas);
        if (info_livro[i].disponivel == 1) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Indisponivel\n");
        }
        printf("\n");
    }
}

// Função para ordenar livros pelo código (ordem crescente)
void ordenar_livros_codigo(struct livro info_livro[], int livros) {
    struct livro temp;
    for (int i = 0; i < livros; i++) {
        for (int j = i + 1; j < livros; j++) {
            if (strcmp(info_livro[i].codigo, info_livro[j].codigo) > 0) {
                temp = info_livro[i];
                info_livro[i] = info_livro[j];
                info_livro[j] = temp;
            }
        }
    }
    printf("\n\tCatálogo de Livros Ordenado por Código\n");
    for (int i = 0; i < livros; i++) {
        printf("Codigo: %s\n", info_livro[i].codigo);
        printf("Titulo: %s\n", info_livro[i].titulo);
        printf("Autor: %s\n", info_livro[i].autor);
        printf("Paginas: %s\n", info_livro[i].paginas);
        if (info_livro[i].disponivel == 1) {
            printf("Status: Disponivel\n");
        } else {
            printf("Status: Indisponivel\n");
        }
        printf("\n");
    }
}

// Função para emprestar um livro
void emprestar_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int indice_usuario, int livros) {
    char codigo[10];
    
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("          EMPRESTIMO DE LIVROS           \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o codigo do livro que deseja: ");
    scanf("%s", codigo);
    // Procura o livro com o código informado
    for (int i = 0; i < livros; i++) {
        if (strcmp(info_livro[i].codigo, codigo) == 0) {
            // Verifica se o livro está disponível para empréstimo
            if (info_livro[i].disponivel == 1) {
                // Marca o livro como emprestado
                info_livro[i].disponivel = 0;
                info_livro[i].emprestado = 1;
                // Calcula as datas de empréstimo (hoje) e devolução (15 dias depois)
                calcular_datas(info_livro[i].data_emprestimo, info_livro[i].data_devolucao);
                // Armazena os dados do livro emprestado no cadastro do usuário
                for (int j = 0; j < 5; j++) {
                    if (strcmp(info[indice_usuario].livros_emprestados[j], "") == 0) {
                        strcpy(info[indice_usuario].livros_emprestados[j], info_livro[i].titulo);
                        strcpy(info[indice_usuario].data_emprestimo[j], info_livro[i].data_emprestimo);
                        strcpy(info[indice_usuario].data_devolucao[j], info_livro[i].data_devolucao);
                        break;
                    }
                }
                printf("-----------------------------------------\n");
                printf("\nLivro emprestado com sucesso!\n");
                printf("Data de Emprestimo: %s\n", info_livro[i].data_emprestimo);
                printf("Data de Devolucao: %s\n", info_livro[i].data_devolucao);
                // Aguarda o usuário pressionar ENTER e retorna ao menu
                getchar();
                printf("\nTecle ENTER para voltar para o menu inicial...");
                getchar();
                system("cls");
                menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
                return;
            } else {
                printf("-----------------------------------------\n");
                printf("\nLivro indisponivel!\n");
                // Aguarda o usuário pressionar ENTER e retorna ao menu
                getchar();
                printf("\nTecle ENTER para voltar para o menu inicial...");
                getchar();
                system("cls");
                menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
                return;
            }
        }
    }
    // Se nenhum livro foi encontrado com o código informado
    printf("-----------------------------------------\n");
    printf("\nLivro nao encontrado!\n");
    getchar(); // Consome o ENTER
    printf("\nTecle ENTER para voltar para o menu inicial...");
    getchar();
    system("cls");
    menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
}

// Função para devolver um livro
void devolver_livro(struct cadastro info[], struct livro info_livro[], int usuarios, int indice_usuario, int livros) {
    char codigo[10];
    int livro_emprestado = 0;
    system("cls");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           BIBLIOTECA VIRTUAL            \n");
    printf("                                         \n");
    printf("=========================================\n");
    printf("                                         \n");
    printf("           DEVOLUCAO DE LIVROS           \n");
    printf("                                         \n");
    printf("-----------------------------------------\n");
    printf("Digite o codigo do livro: ");
    scanf("%s", codigo);
    getchar();
    for (int i = 0; i < livros; i++) {
        if (strcmp(info_livro[i].codigo, codigo) == 0) {
            if (info_livro[i].emprestado == 1) {
                info_livro[i].disponivel = 1;
                info_livro[i].emprestado = 0;
                strcpy(info_livro[i].data_emprestimo, "");
                strcpy(info_livro[i].data_devolucao, "");
                for (int j = 0; j < 5; j++) {
                    if (strcmp(info[indice_usuario].livros_emprestados[j], info_livro[i].titulo) == 0) {
                        strcpy(info[indice_usuario].livros_emprestados[j], "");
                        strcpy(info[indice_usuario].data_emprestimo[j], "");
                        strcpy(info[indice_usuario].data_devolucao[j], "");
                        break;
                    }
                }
                printf("Livro devolvido com sucesso!\n");
                printf("Tecle ENTER para voltar para o menu inicial...");
                getchar();
                system("cls");
                menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
            } else {
                printf("Livro nao foi emprestado por voce!\n");
                printf("Tecle ENTER para voltar para o menu inicial...");
                getchar();
                system("cls");
                menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
            }
            livro_emprestado = 1;
            break;
        }
    }
    if (livro_emprestado == 0) {
        printf("Livro nao encontrado!\n");
        printf("Tecle ENTER para voltar para o menu inicial...");
        getchar();
        system("cls");
        menu_usuario(info, info_livro, usuarios, livros, indice_usuario);
    }
}