/*  Igor Barroso Almeida / 203a 
*   05/05/2022   
*   Aula 02 - Pilhas
*/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

/* Constantes */
#define SUCESSO (0)
#define TRUE    (1 == 1)
#define FALSE   (!TRUE)

/* Tipos */
typedef int bool; // Tipo booleano

/* Main, determina se uma sequencia de parenteses está ou não bem formada
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro 
*/
int main(int argc, char** argv){
    char caractere;
    Pilha_lst* Parenteses = pilha_lst_cria();
    bool bem_formado = TRUE;

    printf("Digite a expressão:\n");
    do{
        scanf("%c", &caractere);
        if(caractere == '('){
            pilha_lst_push(Parenteses, '('); // coloca abre parentese na pilha
        } else if(caractere == ')'){
            if(pilha_lst_vazia(Parenteses)){
                bem_formado = FALSE; // tentando fechar parentese que não existe, expressão mal formada
                break;
            } else{
                (void)pilha_lst_pop(Parenteses); // tira um abre parentese da pilha
            }
        }
    }while(caractere != '\n'); // Enquanto o usuario não apertar enter continua lendo...

    if(!pilha_lst_vazia(Parenteses)){
        bem_formado = FALSE; // Se depois de fechar todos os parenteses ainda tiver parenteses, expressão mal formada
    }

    if(bem_formado){
        printf("Expressão bem formada\n");
    } else{
        printf("Expressão mal formada\n");
    }

    pilha_lst_libera(Parenteses);
    return SUCESSO;
}