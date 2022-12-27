/*
* @file main.c
* @brief implementando funções de arvores
* @author Igor Barroso Almeida
* @date 02-07-2022
*/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arvore.h"

/* Constantes */
#define SUCESSO     (0)

/*----------------------------------------------Funções----------------------------------------------*/

void imprime_pre_ordem(Arv* arvore){
    if(!arv_vazia(arvore)){
        printf("%d ", arvore->info);
        imprime_pre_ordem(arvore->esq);
        imprime_pre_ordem(arvore->dir);
    }
}
void imprime_simetrica(Arv* arvore){
    if(!arv_vazia(arvore)){
        imprime_simetrica(arvore->esq);
        printf("%d ", arvore->info);
        imprime_simetrica(arvore->dir);
    }
}
void imprime_pos_ordem(Arv* arvore){
    if(!arv_vazia(arvore)){
        imprime_pos_ordem(arvore->esq);
        imprime_pos_ordem(arvore->dir);
        printf("%d ", arvore->info);
    }
}


/*--------------------------------------------Fim Funções--------------------------------------------*/

/*----------------------------------------------Exercícios----------------------------------------------*/

/* Exercicio 1 */
void tipos_percurso(Arv* arvore){
    printf("\nImpressão pre ordem:\n");
    imprime_pre_ordem(arvore);
    printf("\nImpressão simetrica:\n");
    imprime_simetrica(arvore);
    printf("\nImpressão pos ordem:\n");
    imprime_pos_ordem(arvore);
    printf("\n");
}

/* Exercicio 2 */
Arv* insersao_ordenada(Arv* arvore, int elemento){
    // Achou a posição do novo nó:
    if(arv_vazia(arvore)){
        arvore=(Arv *)malloc(sizeof(Arv));
        arvore->info = elemento;
        arvore->esq = NULL;
        arvore->dir = NULL;
    // se menor que info do nó atual anda para esquerda:
    }else if(elemento < arvore->info){
        arvore->esq = insersao_ordenada(arvore->esq, elemento);
    // Se maior que info do nó atual anda para direita:
    } else if(elemento > arvore->info){
        arvore->dir = insersao_ordenada(arvore->dir, elemento);
    }
    
    return arvore;
}

/* função que preenche uma arvore com números inteiros (parte do ex 2)
* @param arvore arvore a ser preenchida
* @return arvore já preenchida
*/
Arv* preenche_arv(Arv* arvore){
    int qnt_elementos, elemento;

    printf("Quantos elementos terá a arvore? ");
    scanf("%d", &qnt_elementos);
    getchar(); // Tira o \n

    for(int i = 0; i < qnt_elementos; i++){
        printf("%d elemento: ", i+1);
        scanf("%d", &elemento);
        arvore = insersao_ordenada(arvore, elemento);
    }

    return arvore;
}

/* Exercicio 3 */
int* arv_conta(Arv* arvore, int* count){
    if((arvore->esq == NULL) && (arvore->dir == NULL)){
        count[0]++; // conta folha
    } else if((arvore->esq != NULL) && (arvore->dir != NULL)){
        count[1]++; // conta nós com 2 filhos
        count = arv_conta(arvore->esq, count);
        count = arv_conta(arvore->dir, count);
    } else if((arvore->esq != NULL) && (arvore->dir == NULL)){
        count[2]++; // conta nós com 1 filho
        count = arv_conta(arvore->esq, count);
    } else if((arvore->esq == NULL) && (arvore->dir != NULL)){
        count[2]++; // conta nós com 1 filho
        count = arv_conta(arvore->dir, count);
    }

    return count;
}

/* Função que imprime o histograma*/
void Imprime_histograma(int* count){
    int maior = count[0], i;

    for(i = 0; i < 26; i++){
        if(count[i] > maior){
            maior = count[i];
        }
    }

    for(i = maior; i > 0; i--){
        for(int j = 0; j < 26; j++){
            if(count[j] >= i){
                printf("∎\t");
            } else{
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("---------------------------------------------------------------------------------\n");
    printf("A\tB\tC\tD\tE\tF\tG\tH\tI\tJ\tK\tL\tM\tN\tO\tP\tQ\tR\tS\tT\tU\tV\tW\tX\tY\tZ\n");
}

Arv_char* insere_histograma(Arv_char* arvore, char elemento){
    // Achou a posição do novo nó:
    if(arv_char_vazia(arvore)){
        arvore=(Arv_char *)malloc(sizeof(Arv_char));
        arvore->info = elemento;
        arvore->esq = NULL;
        arvore->dir = NULL;
    // se menor que info do nó atual anda para esquerda:
    }else if(elemento <= arvore->info){
        arvore->esq = insere_histograma(arvore->esq, elemento);
    // Se maior que info do nó atual anda para direita:
    } else if(elemento > arvore->info){
        arvore->dir = insere_histograma(arvore->dir, elemento);
    }
    
    return arvore;
}

void conta_caracteres(Arv_char* arvore, int* count){
    int pos = arvore->info - 65;

    if(!arv_char_vazia(arvore)){
        printf("%d\n", pos);
        if(pos >= 0 && pos < 26){
            count[pos]++;
        }
        conta_caracteres(arvore->esq, count);
        conta_caracteres(arvore->dir, count);
    }
}

/* Exercicio 4 */
void histograma(){
    int qnt_elementos;
    Arv_char* arvore = arv_char_criavazia();
    char elemento;
    int count[26];    

    printf("Quantos elementos terá a arvore? ");
    scanf("%d", &qnt_elementos);
    getchar(); // tira o \n

    for(int i = 0; i < qnt_elementos; i++){
        printf("%d caractere: ", i+1);
        scanf("%c", &elemento);
        getchar(); // tira o \n
        elemento = toupper(elemento);

        arvore = insere_histograma(arvore, elemento);
    }
    printf("Chegou aqui\n");
    conta_caracteres(arvore,count);
    printf("Aqui tbm\n");
    Imprime_histograma(count);
    
    arv_char_libera(arvore);
}

/*--------------------------------------------Fim Exercícios--------------------------------------------*/

/* Função principal, escolha do exercício
* @return SUCESSO caso seja executado corretamente
*/
int main(){
    int nExercicio;

    do{
        Arv* arvore = arv_criavazia();

        printf("Escolha um dos exercicios:\n1.Tipos de percurso\n2.Conta filhos e nos\n3.Histograma\n0.Finalizar\n");
        scanf("%d", &nExercicio);
        getchar(); // tira o \n

        switch (nExercicio){
            case 1: // Tipos de percurso
                arvore = preenche_arv(arvore);
                tipos_percurso(arvore);
                arv_libera(arvore);
                break;
            case 2: // Conta filhos e nós
                arvore = preenche_arv(arvore);
                int* count=(int*)malloc(3 * sizeof(int));

                count[0] = count[1] = count[2] = 0;
                count = arv_conta(arvore,count);
                printf("Folhas: %d\nNos com 2 filho: %d\nNos com apenas 1 filho: %d\n", count[0], count[1], count[2]);  

                free(count);              
                arv_libera(arvore);
                break;
            case 3: // Histograma
                histograma();
                break;
            case 0: // Finaliza
                break;
            default:
                printf("Numero invalido!\n");
                break;
        }

    }while(nExercicio != 0);

    return SUCESSO;
}