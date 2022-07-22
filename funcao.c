#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int inserir(char *titulo, char *autor, int numeros_pag)
{
    FILE *arq;
    char teste[100];
    arq = fopen("ArqTeste.txt", "a");
    fprintf(arq, "%s %s %d", titulo, autor, numeros_pag);
    fprintf(arq, "\n");
    fclose(arq);
    return 0;
}

int infLivros()
{
    char teste[100], c, count=0,aux[100];
    int vezes;
    // teste ="teste";
    FILE *arq;
    arq = fopen("ArqTeste.txt", "rt");
    // fscanf(arq, "%s", teste);
      for (c = getc(arq); c != EOF; c = getc(arq))
    {
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    }

    printf("%d",count-1);
    
    fclose(arq);
    arq = fopen("ArqTeste.txt", "rt");
    for (int i = 0; i < count; i++) {
        fgets(teste,50,arq);
        printf("%s", teste);
    }
    fclose(arq);
}

/*if (arq == NULL) // Se houve erro na abertura
   {
       printf("Problemas na abertura do arquivo\n");
       return 0;
   }
   */

// fclose (arq);
// fscanf (arq, "%s", teste);
// printf("%s",teste);
