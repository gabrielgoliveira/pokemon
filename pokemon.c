#include "functions.h"

int main(){

    char campo[20][20];    
    int vet[10], quant_mochila, pos_op[2];
    pokemon *opponents = NULL;
    pokemon *mochila = NULL;
    
    /*Alocando Opponents*/
    opponents = (pokemon *) malloc(12*sizeof(pokemon));
    if(opponents == NULL){
        printf("ERRO DE ALOCACOA !! \n");
        exit(1);
    }
    mochila = (pokemon*) malloc(12*sizeof(pokemon));
    if(mochila == NULL){
        printf("ERRO DE ALOCACOA !! \n");
        exit(1);
    }
    inicializarCampo(campo);
    distribuirPokemons(campo);
    system("cls");
    printf("====================================== Pokemom ======================================\n");
    printf("By: Gabriel Oliveira\n\n");

    imprimirCampo(campo);
    opponents = iniciarPokemons();

    /*Inicializando com 2 pokemons na mochila*/
    mochila[0].cod = opponents[10].cod;
    strcpy(mochila[0].nome, opponents[10].nome);
    mochila[0].ataque = opponents[10].ataque;
    mochila[0].defesa = opponents[10].defesa;

    mochila[1].cod = opponents[11].cod;
    strcpy(mochila[1].nome, opponents[11].nome);
    mochila[1].ataque = opponents[11].ataque;
    mochila[1].defesa = opponents[11].defesa;
    quant_mochila = 2;

/*
    printf("Opponents Distributed\n");
    for(int i=0;i<12;i++){
        printf("Cod.: %d\n", (opponents+i)->cod);
        printf("Nome.: %s\n", (opponents+i)->nome);
        printf("Ataque.: %d\n", (opponents+i)->ataque);
        printf("Defesa.: %d\n", (opponents+i)->defesa);
    }
*/
    imprimirMochila(mochila, quant_mochila);
    menorDistancia(campo, pos_op);
    printf("POKEMON: %c\n", campo[pos_op[0]][pos_op[1]]);

    return 0;
}
