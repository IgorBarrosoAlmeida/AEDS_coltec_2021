/****************************************************************************************** 
* Igor Barroso Almeida
* 05/06/2022
* 2. Implemente uma função que receba duas listas encadeadas de
* valores reais como parâmetro e retorne a lista resultante da
* intercalação de seus nós.
* Lista *lst_intercala(Lista *l1, Lista *l2);
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

/* -------------------------------------Funções------------------------------------ */

Lista* lst_insere(Lista *l, int i){
	Lista *novo=(Lista *)malloc(sizeof(Lista));
	novo->info=i;
	novo->prox=l;
	return novo;
}

void lst_imprime(Lista *l){
	Lista *p;
	for(p=l;p!=NULL;p=p->prox){
		printf("%d\n", p->info);
	}
}

void lst_libera(Lista *l){
	Lista *p=l;
	while(p!=NULL){
		Lista *t=p->prox;
		free(p);
		p=t;
	}
}

/* -----------------------------------Fim Funções---------------------------------- */

/* -----------------------------------Exercicio------------------------------------ */

Lista* lst_intercala(Lista* l1, Lista* l2){
    Lista* l_inter = l1;
    Lista* aux_l1;
    Lista* aux_l2;

    while(l1 != NULL){
        // Salva o proximo elemento antes de intercalar:
        aux_l1 = l1->prox; 
        aux_l2 = l2->prox;
        // Intercala
        l1->prox = l2;
        l2->prox = aux_l1;

        // Anda na lista
        l1 = aux_l1;
        l2 = aux_l2;
    }
    return l_inter;
}

/* -----------------------------------Fim Exercicio-------------------------------- */

/* Main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro s
*/
int main(int argc, char** argv){
    Lista* l1 = NULL;
    Lista* l2 = NULL;
    Lista* intercalada = NULL;
    int i;

    for(i = 1; i <= 10; i++){
        l1 = lst_insere(l1, i);
    }
    for(i = -1; i >= -10; i--){
        l2 = lst_insere(l2, i);
    }
    // lst_imprime(l1);
    // lst_imprime(l2);

    intercalada = lst_intercala(l1, l2);
    lst_imprime(intercalada);

    lst_libera(intercalada);
    return SUCESSO;
}