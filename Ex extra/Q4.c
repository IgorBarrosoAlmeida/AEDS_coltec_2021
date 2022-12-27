/****************************************************************************************** 
* Igor Barroso Almeida
* 06/06/2022
* 4. Faça um programa para determinar se a sequência de parênteses
* e colchetes está bem formada (ou seja, parênteses e colchetes são
* fechados na ordem inversa àquela em que foram abertos).
******************************************************************************************/

/* Tipos */

typedef struct lista{
    int info;
    struct lista* prox;
} Lista;

typedef struct pilha_lst{
	Lista *prim;
} Pilha_lst;

typedef int bool;

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>

/* Definições */
#define SUCESSO (0)
#define TRUE    (1 == 1)
#define FALSE   (!TRUE)

/* -------------------------------------Funções------------------------------------ */

Pilha_lst *pilha_lst_cria(){
	Pilha_lst *p=(Pilha_lst *)malloc(sizeof(Pilha_lst));
	p->prim=NULL;
	return p;
}

int pilha_lst_vazia(Pilha_lst *p){
	return (p->prim==NULL);
}

void pilha_lst_push(Pilha_lst *p, char v){
	Lista *l=(Lista *)malloc(sizeof(Lista));
	l->info=v;
	l->prox=p->prim;
	p->prim=l;
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

char pilha_lst_pop(Pilha_lst *p){
	Lista *l;
	char c;
	if(pilha_lst_vazia(p)){
		printf("Pilha vazia\n");
		exit(1);
	}
	l=p->prim;
	c = l->info;
	p->prim = l->prox;
	free(l);
	return c;
}

/* -----------------------------------Fim Funções---------------------------------- */

/* -----------------------------------Exercicio------------------------------------ */

// Função que verifica se uma expressão está bem formada
void Verifica_expressao(){
    char caractere;
    Pilha_lst* Expressao;
    bool bem_formado = TRUE;    
    
    printf("Digite a expressão:\n");
    do{
        scanf("%c", &caractere);
        if(caractere == '('){
            pilha_lst_push(Expressao, '('); // coloca abre parentese na pilha
        } else if(caractere == ')'){
            if(caractere == Expressao->prim->info){
                (void)pilha_lst_pop(Expressao); // tira um parentese da pilha
            } else if(pilha_lst_vazia(Expressao)){// tentando fechar mas pilha vazia
                bem_formado = FALSE;
                break; 
            } else{// tentando fechar errado
                bem_formado = FALSE;
                break;
            }
        } else if(caractere == '['){
            pilha_lst_push(Expressao, '['); // coloca abre parentese na pilha            
        } else if(caractere == ']'){
            if(caractere == Expressao->prim->info){
                (void)pilha_lst_pop(Expressao); // tira um parentese da pilha
            } else if(pilha_lst_vazia(Expressao)){// tentando fechar mas pilha vazia
                bem_formado = FALSE;
                break; 
            } else{// tentando fechar errado
                bem_formado = FALSE;
                break;
            }
        }
    }while(caractere != '\n'); // Enquanto o usuario não apertar enter continua lendo...

    if(!pilha_lst_vazia(Expressao)){
        bem_formado = FALSE; // Se depois de fechar todos os parenteses ainda tiver parenteses, expressão mal formada
    }

    if(bem_formado){
        printf("Expressão bem formada\n");
    } else{
        printf("Expressão mal formada\n");
    }
    pilha_lst_libera(Expressao);
}
/* -----------------------------------Fim Exercicio-------------------------------- */

/* Main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro s
*/
int main(int argc, char** argv){
    Verifica_expressao();

    return SUCESSO;
}