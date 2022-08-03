#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_input() fflush(stdin)
#define limpar_tela() system("cls")
#else
#include <stdio_ext.h>
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")
#endif

int listar(int linhas);
int inserir(char *titulo, char *autor, int numeros_pag, int *linhas);
int remover(char *titulo,int *linhas);
int buscar(char *pesquisa,int linhas);
int verificarArquivo();
int menu();
int mostrarLivro(char *infLivro);


int main() {
    int opcao, num_paginas;
    bool sair = false;
    char titulo[50], autor[50];
    //verificar a quantidade de linhas do arquivo
    int linhas = verificarArquivo();
    setlocale(LC_ALL, "");
    while (!sair) {
        opcao = menu();
        if (opcao < 1 || opcao > 5) {
            printf("Op��o Inv�lida!");
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
            printf("Digite o numero de p�ginas:\n");
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

int listar(int linhas) {
    //lista os livros
    char infLivro[linhas][50];
    int vezes;
    FILE *arquivo;
    printf("\nQuantidade: %d\n\n",linhas);
    arquivo = fopen("database.txt", "rt");
    //lê o as linhas do arquivo e os lista livros
    for (int i=0; i<linhas; i++) {
        //loop para mostrar os livros
        printf(" %d - ",i+1);
        //lê a linha do arquivo
        fgets(infLivro[i],50,arquivo);
        //e mostra formatado com a funcao mostrarLivro
        mostrarLivro(infLivro[i]);
    }
    fclose(arquivo);
}


int inserir(char *titulo, char *autor, int numeros_pag, int *linhas) {
    //insere livro e retorna o numero de linhas 
    FILE *arquivo;
    char copiaArquivo[(*linhas)][50];
    char aux[50];
    int count;
    bool teste = false;
    arquivo = fopen("database.txt", "r");
    //preenche a matriz com os livros da base de dados
    for(int i=0;i<(*linhas);i++) {
        fgets(copiaArquivo[i],50,arquivo);
    }
    //fecha o arquivo
    fclose(arquivo);
    //verifica se o titulo já existe na base de dados 
    for(int i=0;i<(*linhas);i++) {
        //reseta a string aux
        memset(aux,0,50);
        //copia apenas o titulo para a string aux
        for (int j=0;copiaArquivo[i][j] != ',';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        //compara a string aux com o input do usuário
        if(strcmp(aux,titulo) == 0) {
            puts("O livro já existe da base de dados!");
            return 0;
        }
    }
    //reseta o arquivo
    arquivo = fopen("database.txt", "w");
    fclose(arquivo);
    //abre o arquivo para escrita
    arquivo = fopen("database.txt", "a");
    if((*linhas) == 0) {
        fprintf(arquivo,"%s, %s, %d,\n",titulo, autor, numeros_pag);
        fclose(arquivo);
        (*linhas)++;
        return 0;
    }
    //escreve no arquivo
    for(int i = 0; i < (*linhas); i++) {
        //copia apenas o titulo para a string aux
        memset(aux, 0, 50);
        for (int j=0;copiaArquivo[i][j] != ',';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        //verifica se o input  do usuario é menor que o titulo atual
        if(strcmp(titulo,aux) < 0 && !teste) {
            fprintf(arquivo,"%s, %s, %d,\n",titulo,autor,numeros_pag);
            fprintf(arquivo,"%s",copiaArquivo[i]);
            teste = true;
        }else {
            fprintf(arquivo,"%s",copiaArquivo[i]);
        }
    }
    if(!teste) {
        fprintf(arquivo,"%s, %s, %d,\n",titulo,autor,numeros_pag);
    }
    fclose(arquivo);
    (*linhas)++;
    return 0;
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
            mostrarLivro(palavraLinha);
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
    setlocale(LC_ALL, "");
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
        puts("------- removido com sucesso ------");
    } else {
        //caso removeu estiver falso, o livro nao foi encontrado e printa o erro na tela
        puts("---------- livro nao foi removido, pois nao foi encontrado na base de dados --------");
    }
    return 0;
}

int menu() {
    //mostrar menu e retorna a opção selecionada
    int opcao;
    setlocale(LC_ALL, "");
    printf("\n Digite um numero:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n 5 - Sair do programa\n");
    limpar_input();
    scanf("%d", &opcao);
    return opcao;
}

int mostrarLivro(char *infLivro) {
        int j = 0;
        for(j;infLivro[j]!=',';j++) {
            printf("%c",infLivro[j]);
        }
        j++;
        printf(", ");
        printf("autor:");
        for(j;infLivro[j]!=',';j++) {
            printf("%c",infLivro[j]);
        }
        j++;
        printf(", ");
        printf("paginas:");
        for(j;infLivro[j]!=',';j++) {
            printf("%c",infLivro[j]);
        }
        printf("\n");
        return 0;
}



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