#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <math.h>

typedef struct s_pokemon {
    int cod;
    char nome[30];
    int ataque;
    int defesa;
}pokemon;

void inicializarCampo(char [][20]);
void imprimirCampo(char [][20]);
void distribuirPokemons(char [][20]);
pokemon *iniciarPokemons();
void imprimirMochila(pokemon *, int);
void menorDistancia(char [][20], int []);


void inicializarCampo(char campo[][20]){
    int i, j;
 
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            campo[i][j] = ' ';
        }
    }
    campo[9][9] = '*';
}
void imprimirCampo(char campo[][20]){
    int i, j=0;
    printf("\n----------------- Mapa ---------------- \n\n");
    for(i=0;i<20;i++){
        if(i == 0){
            printf("X | %d ", i+1);
        }else {
            printf("%d ", i+1);
        }
        
    }printf("\n");
    for(i=0;i<20;i++){
        printf("%2d| ", i+1);
        for(j=0;j<20;j++){
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
}

void distribuirPokemons(char campo[][20]){

    int i, linha, coluna, ver=0;
    srand(time(NULL));

    do{
        linha = rand()%19;
        coluna = rand()%19;
        if(linha != 9 && coluna != 9 && campo[linha][coluna] == ' '){
            campo[linha][coluna] = ver+48;
            ver++;
        }
    }while(ver<10);

}
/*Essa função (iniciarPokemons) depende do arquivo cad_pokemon*/
pokemon *iniciarPokemons(){
    long tam;
    int flag, i;
    pokemon *deck;
    FILE *arquivo;
    arquivo = fopen("inserir-personagens/cad_pokemon.bin", "rb");
    if(arquivo == NULL){
        printf("ERRO: Falha na inicializacao dos Pokemons \n");
        printf("Nao foi possivel abrir o arquivo cad_pokemon.bin\n\n");
        system("pause");
        exit(1);
    }
    /*Pegando quantas pokemons tem cadastrados*/
    fseek(arquivo, 0, SEEK_END); /*posiciona o arquivo no final*/
    tam = ftell(arquivo)/sizeof(pokemon); /*divide seu tamnho pelo tamanho da estrutura*/
  
    /*Alocação*/
    deck = (pokemon *) malloc(tam*sizeof(pokemon));
  
    /*voltar o arquivo para o inicio*/
    rewind(arquivo);
  
    /*alocacao*/
    flag = fread(deck, sizeof(pokemon), tam, arquivo);
    
    /*Log de erro*/
    if(flag != tam){
        printf("ERRO: Falha na inicializacao dos Pokemons \n");
        printf("Falha na alocacao\n\n");
        printf("A quantidade de valores alocados foi: %d\n", flag);
        system("pause");
        exit(1);
    }

  
    fclose(arquivo);

    return deck;
}
void imprimirMochila(pokemon *bag, int quant){
    int i;
    printf("\nYour Bag: \n");
    for(i=0;i<quant;i++){
        //printf("Cod.: %d\n", (bag+i)->cod);
        printf("\nNome.: %s\n", (bag+i)->nome);
        printf("Ataque.: %d\n", (bag+i)->ataque);
        printf("Defesa.: %d\n", (bag+i)->defesa);
    }
}
void menorDistancia(char campo[][20], int pos_op[]){

    int i, j, pos_x, pos_y, menor_x, menor_y;
    double aux, menor_distancia=99999999;
    /*Descobrindo posição atual no mapa*/
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            if(campo[i][j] == '*'){
                pos_x = i+1;
                pos_y = j+1;
            }
        }
    }

    /*Calculando menor Distancia*/
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            if(campo[i][j] != ' ' && campo[i][j] != '*'){
                aux = sqrt(pow(((i+1)-pos_x), 2) + pow(((j+1)-pos_y), 2));
                printf("Dist ate ponto (%d,  %d) Valor [%c] = %f\n", i+1, j+1, campo[i][j], aux);
                if(menor_distancia > aux){
                    menor_distancia = aux;
                    menor_x = i;
                    menor_y = j;
                }
            }
        }
    }

    /*Imprimindo Elemento mais proximo*/
    printf("Elemento Mais proximo do Jogador: %c", campo[menor_x][menor_y]);
    pos_op[0] = menor_x;
    pos_op[1] = menor_y;
}