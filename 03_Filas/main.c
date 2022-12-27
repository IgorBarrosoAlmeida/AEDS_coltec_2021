/*****************************************************************************************  
* Igor Barroso Almeida / 203a
* 03/06/2022   
******************************************************************************************/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filas.h"

/* Definições */
#define SUCESSO        (0)
#define TAM_MAX_PLACA  (50)

/* -------------------------------------Funções------------------------------------- */

/* Função que insere um carro no estacionamento */
void Coloca_carro_fila(FilaL* estacionamento){
    char n_placa[TAM_MAX_PLACA];
    printf("Estacionamento: \n");
    fila_imprime_l(estacionamento);
    printf("\n");

    // Pede a placa nova enquanto o tamanho não estiver certo
    do{
        printf("Placa do carro: ");
        fgets(n_placa, TAM_MAX_PLACA, stdin);
        n_placa[strlen(n_placa) - 1] = '\0'; // Tira o \n

        if(strlen(n_placa) != TAMANHO_CERTO_PLACA - 1){ // -1 pois TAMANHO_PLACA inclui o \0, e o strlen não
            printf("A placa deve ter 3 letras e 4 numeros, e separados por '-'\n");
        }
    }while (strlen(n_placa) != TAMANHO_CERTO_PLACA - 1); // -1 pois TAMANHO_PLACA inclui o \0, e o strlen não
    
    fila_insere_l(estacionamento, n_placa); // Insere o carro no estacionamento

    printf("Estacionamento atual: \n");
    fila_imprime_l(estacionamento);
}

/* Função que retira um carro do estacionamento */
void Retira_carro_fila(FilaL* estacionamento){
    char placa_busca[TAM_MAX_PLACA];
    Lista* anterior;

    // Se o estacionamento ta vazio para a função
    if(fila_vazia_l(estacionamento)){ 
        printf("Estacionamento vazio.\n");
        return;
    }    
    printf("Estacionamento: \n");
    fila_imprime_l(estacionamento);
    printf("\n");

    // pega a placa do carro que deve ser retirado
    printf("Placa do carro a ser retirado: ");
    fgets(placa_busca, TAM_MAX_PLACA, stdin);
    placa_busca[strlen(placa_busca) - 1] = '\0'; // Tira o \n

    // Se tiver o carro no estacionamento o mesmo é modificada
    if(fila_busca_l(estacionamento, placa_busca) != NULL){
        if(estacionamento->ini->prox != NULL){ // Se não é o ultimo elemento
            anterior = fila_busca_anterior_l(estacionamento, placa_busca);
            estacionamento->fim->prox = estacionamento->ini;
            estacionamento->fim = anterior; // O fim da fila passa a ser o elemento anterior
            estacionamento->ini = anterior->prox->prox; // E o inicio o elemento posterior
            
            free(fila_busca_l(estacionamento, placa_busca));
            estacionamento->fim->prox = NULL;
        }
        else{ // Se é o ultimo elemento, simplesmente libera
            estacionamento->ini = estacionamento->fim = NULL; // ini e fim apontam pra null
            free(fila_busca_l(estacionamento, placa_busca));
        }
        
    } else{
        printf("A placa digitada nao foi encontrada\n");
    }
    printf("Estacionamento atual: \n");
    fila_imprime_l(estacionamento);
}

/* -----------------------------------Fim Funções----------------------------------- */

/* Main, estacionamento
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro s
*/
int main(int argc, char** argv){
    int escolha;
    FilaL* estacionameto = fila_cria_l();
    printf("Bem-vindo(a) ao estacionamento!\n");

    // Interação com usuario
    do{
        printf("\nDigite de acordo com o que voce deseja:\n");
        printf("1) Colocar um carro no estacionamento.\n2) Retirar um carro do estacionamento.\n0) Finalizar.\n");
        scanf("%d", &escolha);
        getchar();

        switch(escolha){
            case 1: 
                Coloca_carro_fila(estacionameto);
                break;
            case 2:
                Retira_carro_fila(estacionameto);
                break;
            case 0:
                break;
            default:
                printf("Numero invalido, tente novamente!\n");
                break;
        }
    }while(escolha != 0);

    fila_libera_l(estacionameto); // Libera a memoria alocada
    return SUCESSO;
}