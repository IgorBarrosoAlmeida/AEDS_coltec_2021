/*  Igor Barroso Almeida / 203a
*   24/04/2022   
*   Aula 01 - Implementação das funções de listas
*/

/*Inclusões*/
#include <stdio.h>
#include <stdlib.h>
#include "Listas.h"

/*Definições*/
#define SUCESSO     0

//  -----------------------------------------------------------------------

/*  Exercicio 1: */

void exercicio01(){
    Lista * l = lst_cria();
    Lista* l2 = lst_cria();
    int i, N_itens, item, ehigual;

    printf("Quantos elementos tem a primeira lista?\n");
    scanf("%d", &N_itens);
    getchar(); //Tira o \n do buffer

    // preenchimento da primeira lista
    for(i = 1; i <= N_itens; i++){
        printf("Número %d: ", i);
        scanf("%d", &item);
        l = lst_insere(l, item);
    }

    printf("Quantos elementos tem a segunda lista?\n");
    scanf("%d", &N_itens);
    getchar(); //Tira o \n do buffer    

    // preenchimento da segunda lista
    for(i = 1; i <= N_itens; i++){
        printf("Número %d: ", i);
        scanf("%d", &item);
        l2 = lst_insere(l2, item);
    }

    // verifica se as listas são iguais e informa o usuario
    if(lst_iguais(l,l2)){
        printf("As listas são iguais\n\n");
    } else{
        printf("As listas são diferentes\n\n");
    }
    // Ambas as listas são liberadas
    lst_libera(l);
    lst_libera(l2);
}

/*  Exercicio 2: */
void Josephus(int qnt_rebelde, int passos){
    Lista* rebeldes = lst_cria();
    int i, rebeldes_vivos = qnt_rebelde, count_mata = 1;

    // preenche o circulo/lista de rebeldes
    for(i = 1; i <= qnt_rebelde; i++){
        rebeldes = lst_insere_ordenado(rebeldes, i);
    }
    if(lst_vazia(rebeldes)){
        printf("Quantidade de rebeldes não pode ser 0\n");
        return;
    }
    rebeldes = lcirc_transforma(rebeldes); // Transforma lista encadeada em lista circular

    lcirc_imprime(rebeldes);
    /*
    // inclui a posição que mata, não só quantos são pulados
    passos += 1;    // para funcionar no exemplo que a virginia mostrou que pula a quantidade de passos
                    // por exemplo, se passo = 2 pula 2 e mata o terceiro
    */
    Lista* ant;
    while(rebeldes_vivos > 1){
        if(count_mata % passos == 0){ // Se é divisivel está na posição de matar
            ant->prox = rebeldes->prox; 
            printf("Mata posição %d\n", rebeldes->info);
            free(rebeldes); // mata a posição atual
            rebeldes = ant->prox;    
            rebeldes_vivos--;
        }else{
            // move o ant e o aux na lista
            ant = rebeldes;
            rebeldes = rebeldes->prox;
        }
        
        count_mata++;
    }

    printf("Josephus deve estar na posição %d a partir de onde começaram a execução\n", rebeldes->info); // imprime o que sobrou, ou seja, o josephus
    free(rebeldes); // Libera o josephus
}

//  -----------------------------------------------------------------------

/*  Função main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro 
*/
int main(){
    int escolha, J_rebeldes, J_passos;

    //Menu para o usuario escolher o exercicio
    do{
        printf("\nQual dos exercicios você deseja?\n1.Comparar listas iguais\n2.Problema de Josephus\n0.Finalizar\n");
        scanf("%d", &escolha);
        getchar(); //Tira o \n do buffer

        switch (escolha)
        {
        case 1:
            exercicio01();
            break;
        case 2:
            printf("Rebeldes: ");
            scanf("%d", &J_rebeldes);
            getchar();
            
            printf("Passos: ");
            scanf("%d", &J_passos);
            getchar();

            Josephus(J_rebeldes, J_passos);
            break;
        case 0:
            break;
        default:
            printf("Número invalido, tente novamente!\n");
            break;
        }
    }while(escolha != 0);

    return SUCESSO;
}