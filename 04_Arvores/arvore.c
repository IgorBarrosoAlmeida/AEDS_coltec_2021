#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>

Arv* arv_criavazia(){return NULL;}

int arv_vazia(Arv* a){
	return (a == NULL);	
}

Arv* arv_libera(Arv* a){
	if(!arv_vazia(a)){
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
	return NULL;
}

Arv_char* arv_char_criavazia(){return NULL;}

int arv_char_vazia(Arv_char* a){
	return (a == NULL);	
}

Arv_char* arv_char_libera(Arv_char* a){
	if(!arv_char_vazia(a)){
		arv_char_libera(a->esq);
		arv_char_libera(a->dir);
		free(a);
	}
	return NULL;
}