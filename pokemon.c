/*
CODIGO POKEMON

MAPA : MATRIZ 20X20 OK
JOGADOR INICIA NA POSIÇÃO 10X10 OK
JOGADOR COMEÇA COM 2 POKEMONS NA MOCHILA
DISTRIBUIR 10 POKEMONS ALEATORIAMENTE NO MAPA
CADA POKEMON TEM STATS ALEATORIO, 
DEFESA : 5 A 10 
ATAQUE : 2 A 7
JOGADOR SEMPRE VAI BATALHAR COM OS POKEMONS MAIS PROXIMOS DELE
JOGADOR ESCOLHE QUAL POKEMON VAI COLOCAR NA BATALHA
JOGO ACABA QUANDO O JOGADOR CAPTURAR TODOS OS POKEMONS
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct s_pokemon {
    //int cod;
    char nome[30];
    int ataque;
    int defesa;
}pokemon;

void inicializarCampo(char [][20]);
void imprimirCampo(char [][20]);
void distribuirPokemons(char [][20]);
void iniciarPokemons(pokemon *);

int main(){
    /*
        O que falta fazer ?
            0) Adicionar um codigo na struct pokemon para vincular ao vetor opponents
            0) Terminar função iniciarPokemons.
            1) FUNÇÃO INICIAR POKEMON TALVEZ POSSA PRECISAR RETORNAR A QUANTIDADE DE POKEMONS
            2) Implementar função imprimir mochila
                2.1) Realizar o Vinculo do numero do mapa com a Struct
            3) Implementar função inicializar Mochila
            4) Implementar função calcular menor distancia
            5) Implementar função batalhar
                5.1) Escolher pokemon da Mochila para Duelar
                5.2) Se ganhar, colocar o pokemon no inventario novamente
    */
    char campo[20][20];    
    int vet[10];
    pokemon *opponents = NULL;
    
    /*Alocando Opponents*/
    opponents = (pokemon *) malloc(sizeof(pokemon));
    if(opponents == NULL){
        printf("ERRO DE ALOCACOA !! \n");
        exit(1);
    }

    inicializarCampo(campo);
    imprimirCampo(campo);
    distribuirPokemons(campo);
    imprimirCampo(campo);
    iniciarPokemons(opponents);
    
    return 0;
}
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
void iniciarPokemons(pokemon *deck){
    long tam;
    int flag, i;
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
  
    /*Realocação,*/
    deck = (pokemon *) realloc(deck, tam*sizeof(pokemon));
  
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
/*
    printf("Os Pokemons Distribuidos no Mapa foram\n\n");
    for(i=0;i<tam;i++){
        //printf("Cod.: %d\n", (deck+i)->cod);
        printf("Nome.: %s\n", (deck+i)->nome);
        printf("Ataque.: %d\n", (deck+i)->ataque);
        printf("Defesa.: %d\n", (deck+i)->defesa);
    }
*/  
    fclose(arquivo);
}