#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include "funcao.c"

void listar(char *titulo)
{
    printf("Livros: \n %s \n", titulo);
}
void remover(char *titulo)
{
    printf("O livro foi removido");
}

/*void infLivros(char *titulo, int num_paginas, char *autor){
  printf("Todos os titulos s?o: %s \n O n?mero de paginas ?: %d \n Todos os Autores s?o: %s", titulo, num_paginas, autor);
}
*/

int main(void)
{

    setlocale(LC_ALL, "");
    int opcao, num_paginas;
    char titulo[50], autor[50];

    /* if( while = true){
      while (true)
      break;
    }
    */

    while (true)
    {
        printf("\n Digite um número:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n");
        scanf("%d", &opcao);
        if (opcao < 1 || opcao > 4)
        {
            printf("Opcao inválida!");
            continue;
        }
        switch (opcao)
        {
        case 1:
            // buscar livro
            printf("Digite o nome do Livro:\n");
            scanf("%s", titulo);
            printf("As informações do livro s?o: %s\n, %s\n, %d\n", titulo, autor, num_paginas);
            // buscar(titulo);
            break;

        case 2:
            // parte em teste
            printf("Digite o titulo do livro:\n");
            fflush(stdin);
            gets(titulo);
            while (strlen(titulo) > 50 ){
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
            inserir(titulo, autor, num_paginas);
            
            break;

        case 3:
            printf("Digite o nome do livro a ser removido:\n");
            scanf("%s", titulo);
            printf("O livro %s foi removido", titulo);
            remover(titulo);
            break;

        case 4:
            // listar livros
            printf("Os livros presentes na biblioteca são:\n");
            infLivros();
            break;

        default:
            break;
        }
    }
    return 0;
}