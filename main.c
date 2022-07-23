#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include "funcoes.c"

int main() {
    int opcao, num_paginas;
    bool sair = false;
    char titulo[50], autor[50];
    int linhas;
    linhas = verificarArquivo();

    while (!sair) {
        opcao = menu();
        if (opcao < 1 || opcao > 5) {
            printf("Opção inválida!");
            continue;
        }
        switch (opcao) {
        case 1:
            // buscar livro
            printf("Digite o nome do Livro:\n");
            scanf("%s", titulo);
            buscar(titulo,linhas);
            break;
        case 2:
            // parte em teste
            printf("Digite o titulo do livro:\n");
            fflush(stdin);
            gets(titulo);
            while (strlen(titulo) > 50 ) {
            printf("\n O titulo é longo demais\n");
            printf("Digite o titulo do livro:\n");
            scanf("%s", titulo);
            }
            //printf("%d", strlen(titulo));
            printf("Digite o nome do autor:\n");
            fflush(stdin);
            gets(autor);
            printf("Digite o numero de paginas:\n");
            scanf("%d", &num_paginas);
            inserir(titulo, autor, num_paginas,&linhas);
            
            break;

        case 3:
            printf("Digite o nome do livro a ser removido:\n");
            scanf("%s", titulo);
            printf("O livro %s foi removido", titulo);
            //remover(titulo);
            break;

        case 4:
            // listar livros
            printf("Os livros presentes na biblioteca são:\n");
            listar(linhas);
            break;
        case 5:
             sair = true;
        default:
            break;
        }
    }
    return 0;
}