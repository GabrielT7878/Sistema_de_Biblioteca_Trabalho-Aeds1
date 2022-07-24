int verificarArquivo() {
    FILE *file;
    int count = 0;
    if(fopen("database.txt", "rt") == NULL) {
        file = fopen("database.txt", "wt");
        fclose(file);
        return count;
    }else {
        file = fopen("database.txt", "rt");
        char buf[50];
        while(fgets(buf,50,file) != NULL) {
            count++;
        }
        fclose(file);
        return count;
    }
}

int menu() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");
    printf("\n Digite um numero:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n 5 - Sair do programa\n");
    fflush(stdin);
    scanf("%d", &opcao);
    return opcao;
}


int inserir(char *titulo, char *autor, int numeros_pag, int *linhas) {
    FILE *arq;
    char teste[100];
    arq = fopen("database.txt", "a");
    fprintf(arq, "%s, %s, %d,", titulo, autor, numeros_pag);
    fprintf(arq, "\n");
    fclose(arq);
    (*linhas)++;
    return 0;
}

int listar(int linhas) {
    char infLivro[50];
    int vezes;
    FILE *arq;
    printf("\nQuantidade: %d\n",linhas);
    arq = fopen("database.txt", "rt");
    for (int i=0; i < linhas; i++) {
        fgets(infLivro,50,arq);
        printf("%d - %s",i+1, infLivro);
    }
    fclose(arq);
}

int buscar(char *search,int linhas) {
    char buf[100];
    FILE *arq;
    int count,encontrados;
    arq = fopen("database.txt", "rt");
     printf("\nlivros encontrados: \n\n");
    //percorrendo o arquivo linha a linha 
    for (int i=0; i < linhas; i++) {
        count=0;
        fgets(buf, 100, arq);
        //percorrendo a string da linha
        for(int j=0; j < strlen(search); j++) {
            if(buf[j] == ',') {
                j = strlen(search);
            }else {
                if(buf[j] == search[j]) {
                    count++;
                }
            }
        }
        if (count == strlen(search)) {
            printf("%s", buf);
            encontrados++;
        }
    }
    if(encontrados == 0) {
        printf("0\n");
    } else {
        printf("\ntotal de %d livros\n",encontrados);
    }
    return 0;
}

/*
pegar string da linha
pegar o tamanho da string recebida
while string arquivo != ',' && i < tamnhanho da string 
continuo comparando
se igual count ++;
termina o loop
se count == tamnhanho da string
//printo o fgets// peguei e falo que falo que foi encontrado
printar sem as virgulas
*/
