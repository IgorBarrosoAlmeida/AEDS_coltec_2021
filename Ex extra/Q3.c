/****************************************************************************************** 
* Igor Barroso Almeida
* 05/06/2022
* 3. Dada uma lista duplamente encadeada e circular (ou seja, o
* último elemento aponta para o primeiro e vice-versa) mantida
* ordenada.
* a) Defina os tipos necessários para representá-la.
* b) Faça uma função para inserção de um elemento na lista. Lembre-se
* que ela deve ser mantida ordenada.
* c) Faça uma função para imprimir os elementos da lista.
* d) Faça uma função para liberar a lista.
******************************************************************************************/

/* Estruturas */
// a)Defina os tipos necessários para representá-la.
typedef struct lista{
    int info;
    struct lista* ant;
    struct lista* prox;
} Lista2_circ;

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>

/* Definições */
#define SUCESSO        (0)

/* -------------------------------------Funções------------------------------------ */

Lista2_circ* lst_cria(){
    return NULL;
}

Lista2_circ* lst2_ordena_circ(Lista2_circ *l, int v){
	Lista2_circ *p = l;

    do{
        if(v < p->info){ // procura o elemento posterior            
            return p;
		} 
        p = p->prox;
    }while(p != l);

    return p;
}

/* -----------------------------------Fim Funções---------------------------------- */

/* -----------------------------------Exercicio------------------------------------ */

/* b) Faça uma função para inserção de um elemento na lista. Lembre-se
* que ela deve ser mantida ordenada.
*/
Lista2_circ* lst2_insere_ordenado(Lista2_circ* l, int v){
    Lista2_circ* novo = (Lista2_circ*)malloc(sizeof(Lista2_circ));
    
    if(l == NULL){ // Lista vazia
        printf("teste1\n");
        novo->info = v;
        novo->ant = novo;
        novo->prox = novo;
        return novo;
    }else if(l == l->prox){ // lista com 1 elemento
        printf("teste2\n");
        novo->prox = l;
        novo->ant = l;
        l->prox = novo;
        l->prox = novo;
        if(v < l->info){
            l = novo; // novo é o menor valor
        }
    } else{
        printf("teste3\n");
        Lista2_circ* ordem = lst2_ordena_circ(l, v); // Acha o valor posterior
    
        novo->prox = ordem;
        novo->ant = ordem->ant;
        ordem->ant->prox = novo;
        novo->ant->prox = novo;
    }
    return l;
}

void lst2_imprime_circ(Lista2_circ* l){
    Lista2_circ* aux = l;
    do{
        printf("%d\n", aux->info);
        aux = aux->prox;
    }while(aux != l);
}

void lst2_libera_circ(Lista2_circ* l){
    Lista2_circ* aux = l;
    Lista2_circ* aux_t;
    do{
        aux_t = aux->prox;
        free(aux);
        aux = aux_t;
    }while(aux != l);
}


/* -----------------------------------Fim Exercicio-------------------------------- */

/* Main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro s
*/
int main(int argc, char** argv){
    Lista2_circ* lista = lst_cria();

    lista = lst2_insere_ordenado(lista, 54);
    lista = lst2_insere_ordenado(lista, 1);
    lista = lst2_insere_ordenado(lista, 100);
    lista = lst2_insere_ordenado(lista, 10);
    printf("teste %d %d %d %d", lista->info, lista->prox->info, lista->prox->prox->info, lista->prox->prox->prox->info);

    // lst2_imprime_circ(lista);

    lst2_libera_circ(lista);

    
    return SUCESSO;
}