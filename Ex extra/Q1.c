/****************************************************************************************** 
* Igor Barroso Almeida
* 04/06/2022
* 1. Uma lista encadeada pode ser definida de maneira recursiva: A
* lista encadeada é representada por uma lista vazia ou um elemento
* seguido de uma sublista. Com base nesta definição recursiva,
* implemente as seguintes funções:
* void lst_imprime_rec (Lista *l): função recursiva que imprime os
* elementos da lista
* Lista * lst_retira_rec (Lista *l, int v): função recursiva que retira
* elemento da lista
* void lst_libera_rec (Lista *l): função recursiva que libera a lista
******************************************************************************************/

/* Estruturas */

typedef struct lista{
    int info;
    struct lista* prox;
} Lista;

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>

/* Definições */
#define SUCESSO        (0)

/* -------------------------------------Funções------------------------------------- */

Lista* lst_insere(Lista *l, int i){
	Lista *novo=(Lista *)malloc(sizeof(Lista));
	novo->info=i;
	novo->prox=l;
	return novo;
}

/* -----------------------------------Fim Funções----------------------------------- */

/* -----------------------------------Exercicios------------------------------------ */

// Imprime uma lista recursivamente
void lst_imprime_rec (Lista *l){
    Lista* aux = l;
    if(aux == NULL){
        return;
    }
    printf("%d\n", aux->info); 
    // Chama a função recursivamente com o proximo elemento:
    lst_imprime_rec(aux->prox); 
}

// Retira um elemento da lista recursivamente
Lista * lst_retira_rec (Lista* l, int v){
    Lista* aux = l;
    if(l->info == v){
        l = l->prox;
        free(aux);
        return l;
    } else if(l->prox != NULL){
        l->prox = lst_retira_rec(l->prox, v);
        return l;
    } else{
        printf("Elemento não encontrado\n");
        return l;
    }
}

// Libera uma lista recursivamente
void lst_libera_rec (Lista *l){
    Lista* aux = l;
    if(l->prox != NULL){
        l = l->prox;
        free(aux);
        lst_libera_rec(l);
    } else{
        free(l);
    }
}
/* -----------------------------------Fim Exercicios-------------------------------- */

/* Main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro s
*/
int main(int argc, char** argv){
    Lista* lst = NULL;
    int num;
    
    for(int i=0; i < 10; i++){ // Preenche a lista
        lst = lst_insere(lst, i);
    }
    lst_imprime_rec(lst); // imprime
    
    printf("digite o numero para ser retirado: ");
    scanf("%d", &num);
    lst = lst_retira_rec(lst, num);

    lst_imprime_rec(lst);
    lst_libera_rec(lst);
    return SUCESSO;
}