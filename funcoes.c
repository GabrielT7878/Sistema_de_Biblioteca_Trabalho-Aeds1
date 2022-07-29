int verificarArquivo() {
    FILE *arquivo;
    int count = 0;
    //cria arquivo caso não exista e retorna 0
    if(fopen("database.txt", "rt") == NULL) {
        arquivo = fopen("database.txt", "wt");
        fclose(arquivo);
        return count;
    }else {
    //lê o arquivo existente e retorna a quantidade de linhas
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
    //mostrar menu e retorna a opção selecionada
    int opcao;
    setlocale(LC_ALL, "Portuguese");
    printf("\n Digite um numero:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n 5 - Sair do programa\n");
    limpar_input();
    scanf("%d", &opcao);
    return opcao;
}


int inserir(char *titulo, char *autor, int numeros_pag, int *linhas) {
    //insere livro e retorna o numero de linhas 
    FILE *arquivo;
    arquivo = fopen("database.txt", "a");
    fprintf(arquivo, "%s, %s, %d,\n", titulo, autor, numeros_pag);
    fclose(arquivo);
    (*linhas)++;
    return 0;
}

int listar(int linhas) {
    //lista os livros
    char infLivro[50];
    int vezes;
    FILE *arquivo;
    printf("\nQuantidade: %d\n",linhas);
    arquivo = fopen("database.txt", "rt");
    //lê o as linhas do arquivo e os lista livros
    for (int i=0; i < linhas; i++) {
        fgets(infLivro,50,arquivo);
        printf("%d - %s",i+1, infLivro);
    }
    fclose(arquivo);
}

int buscar(char *pesquisa,int linhas) {
    //busca por livro no arquivo e printa o nome dele caso exista
    char palavraLinha[100];
    FILE *arquivo;
    int count,encontrados=0;
    arquivo = fopen("database.txt", "rt");
     printf("\nlivros encontrados: \n\n");
    //percorre as linhas do arquivo
    for (int i=0; i < linhas; i++) {
        count=0;
        fgets(palavraLinha, 100, arquivo);
        //compara os caracteres do titulo com o input do usuário
        /*o usuario nao precisa necessariamente digitar o titulo completo, esse loop encontra os livros 
        com os caracteres iguais ao do input do usuário, exemplo: input="p", ele procura por livros com a inicial "p"*/
        for(int j=0; j < strlen(pesquisa); j++) {
            if(palavraLinha[j] == ',') {
                    //quebra o loop ao chegar no final do titulo
                    break;
            }else {
                if(tolower(palavraLinha[j]) == tolower(pesquisa[j])) {
                    //incrementa o count caso os caracteres forem iguais
                    count++;
                }
            }
        }
        //se o count for igual ao tamanho do input do usuário então o titulo tem todas as letras digitados pelo usuario
        if (count == strlen(pesquisa)) {
            //mostra as informações do livro encontrado e incrementa a variavel encontrados
            printf("%s", palavraLinha);
            encontrados++;
        }
    }
    //se encontrados == 0, entao nao achou nenhum livro correspondente
    if(encontrados == 0) {
        printf("0\n");
    } else {
        //caso contrário mostra a quantidade de livros encontrados
        printf("\ntotal de %d livros\n",encontrados);
    }
    return 0;
}

int remover(char *titulo,int *linhas) {
    //remove Livro e retorna a quantidade de linhas
    FILE *arquivo;
    bool removeu = false;
    arquivo = fopen("database.txt","rt");
    char copiaArquivo[(*linhas)][50],aux[50];
    //esvazia a string
    memset(aux,0,50);
    //copia as linhas do arquivo para uma matriz
    for(int i=0;i<(*linhas);i++) {
        fgets(copiaArquivo[i],50,arquivo);
    }
    //comparar as linhas com o input do usuário
    for(int i=0;i<(*linhas);i++) {
        //copia somente o titulo da string matriz para comparar com o input
        for(int j=0;copiaArquivo[i][j]!=',';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        // compara o input com titulo da linha
        //caso forem iguais copia o titulo de baixo e sobrescreve a linha atual a ser removida
        if(strcmp(aux,titulo) == 0 || removeu) {
            strcpy(copiaArquivo[i],copiaArquivo[i+1]);
            //variavel removeu recebe true para continuar a sobrescrevendo as linhas até chegar no final
            removeu = true;
        }
        memset(aux,0,50);
    }

    fclose(arquivo);

    if(removeu) {
        //atualiza o numero de linhas
        (*linhas)--;
        //reseta o arquivo "database"
        FILE *f = fopen("database.txt", "w");
        fclose(f);
        //abre o arquivo novamente para escrever a base de livros atualizado com o livro 
        f = fopen("database.txt", "a");
        //copia a matriz de livros para o arquivo
        for(int i=0;i<(*linhas);i++) {
            fprintf(f, "%s",copiaArquivo[i]);
        }
        fclose(f);
        puts("removido com sucesso");
    } else {
        //caso removeu estiver falso, o livro nao foi encontrado e printa o erro na tela
        puts("livro nao encontrado");
    }
    return 0;
}

