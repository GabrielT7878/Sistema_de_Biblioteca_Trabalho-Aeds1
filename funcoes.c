int verificarArquivo() {
    FILE *arquivo;
    int count = 0;
    if(fopen("database.txt", "rt") == NULL) {
        arquivo = fopen("database.txt", "wt");
        fclose(arquivo);
        return count;
    }else {
        arquivo = fopen("database.txt", "rt");
        char contaLinha[50];
        while(fgets(contaLinha,50,arquivo) != NULL) {
            count++;
        }
        fclose(arquivo);
        return count;
    }
}

int menu() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");
    printf("\n Digite um numero:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n 5 - Sair do programa\n");
    limpar_input();
    scanf("%d", &opcao);
    return opcao;
}


int inserir(char *titulo, char *autor, int numeros_pag, int *linhas) {
    FILE *arquivo;
    arquivo = fopen("database.txt", "a");
    fprintf(arquivo, "%s, %s, %d,\n", titulo, autor, numeros_pag);
    fclose(arquivo);
    (*linhas)++;
    return 0;
}

int listar(int linhas) {
    char infLivro[50];
    int vezes;
    FILE *arquivo;
    printf("\nQuantidade: %d\n",linhas);
    arquivo = fopen("database.txt", "rt");
    for (int i=0; i < linhas; i++) {
        fgets(infLivro,50,arquivo);
        printf("%d - %s",i+1, infLivro);
    }
    fclose(arquivo);
}

int buscar(char *pesquisa,int linhas) {
    char palavraLinha[100];
    FILE *arquivo;
    int count,encontrados=0;
    arquivo = fopen("database.txt", "rt");
     printf("\nlivros encontrados: \n\n");
    for (int i=0; i < linhas; i++) {
        count=0;
        fgets(palavraLinha, 100, arquivo);
        for(int j=0; j < strlen(pesquisa); j++) {
            if(palavraLinha[j] == ',') {
                    break;
            }else {
                if(tolower(palavraLinha[j]) == tolower(pesquisa[j])) {
                    count++;
                }
            }
        }
        if (count == strlen(pesquisa)) {
            printf("%s", palavraLinha);
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

