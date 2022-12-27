#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filas.h"

static int incr(int i){
	return (i+1)%N;
}

Fila *fila_cria_vet(){
	Fila *f = (Fila *) malloc(sizeof(Fila));
	f->n = 0;
	f->ini = 0;
	return f;
}

void fila_insere_vet(Fila *f, float v){
	int fim;
	if(f->n == N){
		printf("Capacidade da fila estourou\n");
		exit(1);
	}
	fim = (f->ini + f->n)%N;
	f->vet[fim] = v;
	f->n++;
}

float fila_retira_vet(Fila *f){
	float v;
	if(fila_vazia_vet(f)){
		printf("Fila vazia!\n");
		exit(1);
	}
	v=f->vet[f->ini];
	f->ini = (f->ini + 1) % N;
	f->n--;
	return v;
}

int fila_vazia_vet(Fila *f){
	return (f->n == 0);
}

void fila_libera_vet(Fila *f){
	free(f);
}


// Lista encadeada
FilaL *fila_cria_l(){
	FilaL *f = (FilaL *) malloc(sizeof(FilaL));
	f->ini = f->fim = NULL;
	return f;
}

void fila_insere_l(FilaL *f,char *v){
	Lista *n = (Lista *) malloc(sizeof(Lista));
	int i;
	for(i=0;i<TAMANHO_CERTO_PLACA;i++) n->placa[i]=v[i];
	n->prox = NULL;
	if(f->fim != NULL) f->fim->prox = n;
	else f->ini = n;
	f->fim = n;
}

char *fila_retira_l(FilaL *f){
	Lista *t;
	char *v;
	if(fila_vazia_l(f)){
		printf("Fila vazia!");
		exit(1);
	}
	t = f->ini;
	v = t->placa;
	f->ini = t->prox;
	if(f->ini==NULL) f->fim = NULL;
	free(t);
	return v;
}

int fila_vazia_l(FilaL *f){
	return (f->ini == NULL);
}

void fila_libera_l(FilaL *f){
	Lista *q = f->ini;
	while(q!=NULL){
		Lista *t = q->prox;
		free(q);
		q = t;
	}
	free(f);
}

Lista* fila_busca_anterior_l(FilaL *fila, char informacao[]){
	Lista* q = fila->ini;
	Lista* ant = q;
	// Se busca o primeiro elemento o anterior é o ultimo elemento
	if (strcmp(informacao, fila->ini->placa) == 0){
		ant = fila->fim;
		return ant;
	}

	while(q != NULL){
		if(strcmp(informacao, q->placa)==0){
			return ant; // retorna o elemento anterior ao buscado
		} else{
			ant=q;
		}
		q=q->prox;
	}
	return NULL;
}

Lista* fila_busca_l(FilaL *fila, char informacao[]){
	Lista *q;
	for(q=fila->ini; q!=NULL; q=q->prox){
		if(strcmp(informacao, q->placa)==0){
			return q;
		}
	}
	return NULL;
}

// Funções de impressão

void fila_imprime_vet(Fila *f){
	int i;
	for(i=0;i<f->n; i++) printf("%f \n", f->vet[(f->ini+i)%N]);
}

void fila_imprime_l(FilaL *f){
	Lista *q;
	if(fila_vazia_l(f)){
		printf("Estacionamento vazio\n");
		return;
	}
	printf("*Saida   *\n");
	for(q=f->ini; q!= NULL; q=q->prox) printf("|%s|\n",q->placa);
	printf("*Entrada *\n");
}