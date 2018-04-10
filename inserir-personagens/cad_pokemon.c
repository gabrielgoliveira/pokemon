#include <stdio.h>
#include <stdlib.h>

typedef struct s_pokemon {
    char nome[30];
    int ataque;
    int defesa;
}pokemon;

int verAbertura(FILE *);
void cadPokemon();
void  imprimirArquivo();
int quantidadePokemons(FILE *arquivo);

int main(){

    int opc;

    do{
        system("cls");
        printf("1 - Cadastrar Pokemon\n");
        printf("2 - Imprimir Pokemons Cadastrados\n");
        printf("3 - Sair do Programa\n");
        printf("Insira a Opcao: ");
        scanf(" %d", &opc);

        switch(opc){
            case 1:
                system("cls");
                cadPokemon();
            break;
            case 2:
                system("cls");
                imprimirArquivo();
            break;
            case 3:
                opc = -1;
            break;
            default:
                printf("Opcao Invalida\n");
                system("pause");
                system("cls");
        }
    }while(opc != -1);

    return 0;
}

int verAbertura(FILE *arquivo){
    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO !!\n");
        system("pause");
        exit(1);
    }else {
        printf("\nSuceso ao Abrir o Arquivo\n\n");
    }
}

void cadPokemon(){
    
    FILE *arquivo = NULL;
    pokemon mochila;

    /*Abrindo Arquivo*/
    arquivo = fopen("cad_pokemon.bin", "ab");
    /*Verificar Abertura*/
    verAbertura(arquivo);

    /*entrada de dados*/
    printf("Digite o nome: ");
    scanf(" %29[^\n]s", mochila.nome);
    printf("Digite o Ataque: ");
    scanf(" %d", &mochila.ataque);
    printf("Digite a Defesa: ");
    scanf(" %d", &mochila.defesa);
    
    /*Gravando os Dados no Arquivo*/
    fwrite(&mochila, sizeof(pokemon), 1, arquivo);
    /*Fechando o Arquivo*/
    fclose(arquivo);
    
}
void imprimirArquivo(){

    FILE *arquivo = NULL;
    pokemon mochila;
    int quantidade;
    int i;

     /*Abrindo Arquivo*/
    arquivo = fopen("cad_pokemon.bin", "rb");
    /*Verificar Abertura*/
    verAbertura(arquivo);
    
    quantidade = quantidadePokemons(arquivo);
    
    for(i=0;i<quantidade;i++){
        fseek(arquivo, i*sizeof(pokemon), SEEK_SET);
        fread(&mochila, sizeof(pokemon), 1, arquivo);
        printf("Pokemon: %s\n", mochila.nome);
        printf("Ataque: %d\n", mochila.ataque);
        printf("Defesa: %d\n\n\n", mochila.defesa);

    }
  /*Fecha o Arquivo*/
  fclose(arquivo);
  system("pause");
}
int quantidadePokemons(FILE *arquivo){

    int quantidade;

    /*Posicionar o Arquivo no final*/
    fseek(arquivo, 0, SEEK_END);
    /*Achar a quantidade de Pokemons Cadastrados*/
    quantidade = ftell(arquivo)/sizeof(pokemon);
    /*Voltar o Arquivo para o Inicio*/
    fseek(arquivo, 0, SEEK_SET);

    return quantidade;
}