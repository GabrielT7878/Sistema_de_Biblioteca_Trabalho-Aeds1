/* 
Biblioteca de livros em linguagem C
Integrantes: Gabriel Thiago Fernandes e Vitor Oliveira Ricci
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>
#define limpar_input() __fpurge(stdin)
#define limpar_tela() system("clear")

void listar(int linhas);
int inserir(char *titulo, char *autor, int numeros_pag, int *linhas);
void remover(char *titulo,int *linhas);
void buscar(char *pesquisa,int linhas);
int verificarArquivo(void);
int menu(void);
void mostrarLivro(char *infLivro);
bool isNumber(char *number);


int main(void) {
    struct Livro {
      char titulo[50];
      char autor[50];
      int num_paginas;
    }livro;
    int opcao;
    bool sair = false;
    //verificar a quantidade de linhas do arquivo
    int linhas = verificarArquivo();
    while (!sair) {
        opcao = menu();
        if (opcao < 1 || opcao > 5) {
            printf("Opcao Invalida!");
            continue;
        }
        switch (opcao) {
        case 1:
            // buscar livro
            limpar_tela();
            printf("--------- Buscar Livro --------\n");
            printf("Digite o nome do Livro:\n");
            limpar_input();
            fgets(livro.titulo,50,stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = 0;
            buscar(livro.titulo,linhas);
            break;
        case 2:
            // Adicionar Livro
            limpar_tela();
            printf("--------- Adicionar Livro --------\n");
            printf("Digite o titulo do livro:\n");
            limpar_input();
            fgets(livro.titulo,50,stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = 0;
            printf("Digite o nome do autor:\n");
            limpar_input();
            fgets(livro.autor,50,stdin);
            livro.autor[strcspn(livro.autor, "\n")] = 0;
            while (isNumber(livro.autor)) {
              puts("entrada inválida, digite um nome de um autor:");
              fgets(livro.autor,50,stdin);
              livro.autor[strcspn(livro.autor, "\n")] = 0;
            }
            printf("Digite o numero de paginas:\n");
            char paginas[50];
            fgets(paginas,50,stdin);
            paginas[strcspn(paginas, "\n")] = 0;
            //verifica se o input não é um numero ou menor que 0 
            while (!isNumber(paginas) || atoi(paginas) < 0) {
              puts("numero inválido, digite um numero válido!");
              fgets(paginas,50,stdin);
              paginas[strcspn(paginas, "\n")] = 0;
            }
            livro.num_paginas = atoi(paginas);
            inserir(livro.titulo, livro.autor, livro.num_paginas,&linhas);
            break;

        case 3:
            //remover livro
            limpar_tela();
            printf("Digite o nome do livro a ser removido:\n");
            limpar_input();
            fgets(livro.titulo,50,stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = 0;
            remover(livro.titulo,&linhas);
            break;

        case 4:
            //listar livros
            limpar_tela();
            printf("Os livros presentes na biblioteca sao:\n");
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

void listar(int linhas) {
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
        for (int j=0;copiaArquivo[i][j] != '/';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        //compara a string aux com o input do usuário
        if(strcmp(aux,titulo) == 0) {
            puts("O livro ja existe da base de dados!");
            return 0;
        }
    }
    //reseta o arquivo
    arquivo = fopen("database.txt", "w");
    fclose(arquivo);
    //abre o arquivo para escrita
    arquivo = fopen("database.txt", "a");
    if((*linhas) == 0) {
        fprintf(arquivo,"%s/ %s/ %d/\n",titulo, autor, numeros_pag);
        fclose(arquivo);
        (*linhas)++;
        return 0;
    }
    //escreve no arquivo
    for(int i = 0; i < (*linhas); i++) {
        //copia apenas o titulo para a string aux
        memset(aux, 0, 50);
        for (int j=0;copiaArquivo[i][j] != '/';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        //verifica se o input  do usuario é menor que o titulo atual
        if(strcmp(titulo,aux) < 0 && !teste) {
            fprintf(arquivo,"%s/ %s/ %d/\n",titulo,autor,numeros_pag);
            fprintf(arquivo,"%s",copiaArquivo[i]);
            teste = true;
        }else {
            fprintf(arquivo,"%s",copiaArquivo[i]);
        }
    }
    if(!teste) {
        fprintf(arquivo,"%s/ %s/ %d/\n",titulo,autor,numeros_pag);
    }
    fclose(arquivo);
    printf("\nLivro adicionado com sucesso!");
    (*linhas)++;
    return 0;
}


void buscar(char *pesquisa,int linhas) {
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
}

void remover(char *titulo,int *linhas) {
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
        for(int j=0;copiaArquivo[i][j]!='/';j++) {
            aux[j] = copiaArquivo[i][j];
        }
        // compara o input com titulo da linha
        //caso forem iguais copia o livro de baixo e sobrescreve a linha atual a ser removida
        if(strcmp(aux,titulo) == 0 || removeu) {
            strcpy(copiaArquivo[i],copiaArquivo[i+1]);
            //variavel removeu recebe true para continuar a sobrescrever as linhas até chegar no final
            removeu = true;
        }
        memset(aux,0,50);
    }

    fclose(arquivo);

    if(removeu) {
        //atualiza o numero de linhas
        (*linhas)--;
        //reseta/apaga o arquivo "database"
        FILE *f = fopen("database.txt", "w");
        fclose(f);
        //abre o arquivo novamente para escrever a base de livros atualizado com o livro a ser adicionado
        f = fopen("database.txt", "a");
        //copia a matriz de livros para o arquivo
        for(int i=0;i<(*linhas);i++) {
            fprintf(f, "%s",copiaArquivo[i]);
        }
        fclose(f);
        puts("------- removido com sucesso ------");
    } else {
        //caso variavel removeu == falso, o livro nao foi encontrado e printa o erro na tela
        puts("---------- livro nao foi removido, pois nao foi encontrado na base de dados --------");
    }
}

int menu() {
    //mostrar menu e retorna a opção selecionada
    int opcao;
    printf("\n Digite um numero:\n 1 - Buscar um  Livro \n 2 - Adicionar um Livro \n 3 - Remover um Livro \n 4 - Listar todos os Livros \n 5 - Sair do programa\n");
    limpar_input();
    scanf("%d", &opcao);
    return opcao;
}

void mostrarLivro(char *infLivro) {
        //mostra as informações do livro formatadas, sem o separador "/"
        int j = 0;
        for(;infLivro[j]!='/';j++) {
            printf("%c",infLivro[j]);
        }
        j++;
        printf(", ");
        printf("autor:");
        for(;infLivro[j]!='/';j++) {
            printf("%c",infLivro[j]);
        }
        j++;
        printf(", ");
        printf("paginas:");
        for(;infLivro[j]!='/';j++) {
            printf("%c",infLivro[j]);
        }
        printf("\n");
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

bool isNumber(char *number) {
    int i = 0;

    //checar numero negativo
    if (number[0] == '-')
        i++;
    for (; number[i] != 0; i++)
    {
        //se (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}