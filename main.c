#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#else
#include <stdio_ext.h>
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#endif
#include "funcoes.c"

int main() {
    int opcao, num_paginas;
    bool sair = false;
    char titulo[50], autor[50];
    //verificar a quantidade de linhas do arquivo
    int linhas = verificarArquivo();

    while (!sair) {
        opcao = menu();
        if (opcao < 1 || opcao > 5) {
            printf("Op��o inv�lida!");
            continue;
        }
        switch (opcao) {
        case 1:
            // buscar livro
            limpar_tela();
            printf("--------- Buscar Livro --------\n");
            printf("Digite o nome do Livro:\n");
            limpar_input();
            gets(titulo);
            buscar(titulo,linhas);
            break;
        case 2:
            // Adicionar Livro
            limpar_tela();
            printf("--------- Adicionar Livro --------\n");
            printf("Digite o titulo do livro:\n");
            limpar_input();
            gets(titulo);
            while (strlen(titulo) > 50 ) {
            printf("\n O titulo � longo demais\n");
            printf("Digite o titulo do livro:\n");
            limpar_input();
            scanf("%s", titulo);
            }
            printf("Digite o nome do autor:\n");
            limpar_input();
            gets(autor);
            printf("Digite o numero de paginas:\n");
            scanf("%d", &num_paginas);
            inserir(titulo, autor, num_paginas,&linhas);
            break;

        case 3:
            //remover livro
            limpar_tela();
            printf("Digite o nome do livro a ser removido:\n");
            limpar_input();
            gets(titulo);
            remover(titulo,&linhas);
            break;

        case 4:
            //listar livros
            limpar_tela();
            printf("Os livros presentes na biblioteca s�o:\n");
            listar(linhas);
            break;
        case 5:
            //sair
             sair = true;
        default:
            break;
        }
    }
    return 0;
}

