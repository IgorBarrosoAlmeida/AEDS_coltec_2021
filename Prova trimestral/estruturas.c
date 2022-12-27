/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

/*--------------------------------Funções pilha--------------------------------*/
Pilha_lst *pilha_lst_cria(){
	Pilha_lst *p=(Pilha_lst *)malloc(sizeof(Pilha_lst));
	p->prim=NULL;
	return p;
}

void pilha_lst_push(Pilha_lst *p, int v){
	Lista *l=(Lista *)malloc(sizeof(Lista));
	l->info=v;
	l->prox=p->prim;
	p->prim=l;
}

int pilha_lst_pop(Pilha_lst *p){
	Lista *l;
	int c;
	if(p->prim == NULL){
		printf("Pilha vazia\n");
		exit(1);
	}
	l=p->prim;
	c = l->info;
	p->prim = l->prox;
	free(l);
	return c;
}

void pilha_lst_libera(Pilha_lst *p){
	Lista *l=p->prim;
	while(l != NULL){
		Lista *t = l->prox;
		free(l);
		l=t;
	}
	free(p);
}
/*------------------------------Funções pilha fim-------------------------------*/

/*--------------------------------Funções fila--------------------------------*/
Fila *fila_cria_l(){
	Fila *f = (Fila *)malloc(sizeof(Fila));
	f->ini = f->fim = NULL;
	return f;
}

void fila_insere_l(Fila *f,int v){
	Lista *n = (Lista *) malloc(sizeof(Lista));
	int i;
    n->info = v;
	n->prox = NULL;
	if(f->fim != NULL) f->fim->prox = n;
	else f->ini = n;
	f->fim = n;
}

int fila_retira_l(Fila *f){
	Lista *t;
	int v;
	if(f->ini == NULL){
		printf("Fila vazia!");
		exit(1);
	}
	t = f->ini;
	v = t->info;
	f->ini = t->prox;
	if(f->ini==NULL) f->fim = NULL;
	free(t);
	return v;
}

void fila_libera_l(Fila *f){
	Lista *q = f->ini;
	while(q!=NULL){
		Lista *t = q->prox;
		free(q);
		q = t;
	}
	free(f);
}
/*------------------------------Funções fila fim-------------------------------*/