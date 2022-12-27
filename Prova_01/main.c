/* Inclusões */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhas.h"

/* Definições */
#define SUCESSO      (0)
#define TAM_MAX_VET  (26 + 1)
#define TRUE         (0)

/*  Função que diz a ordem de inserção e retirada dos vagões da estação 
*   e diz se é possivel ou não com os vagões passados no parametro formar 
*   a palavra tambem passada de parametro
*   Param1(desorganizada): os vagões na ordem que vem do trilho A
*   Param2(Palavra_formada): A palavra que os vagões devem formar no final
*/
void Problema_dos_trilhos(char desorganizada[TAM_MAX_VET], char Palavra_formada[TAM_MAX_VET], int n_Letras){
    int i, j = 0;
    char Insere_Retira[TAM_MAX_VET];
    //Criação de uma pilha por trilho: A = P_Entrada, B = P_saida, Estação = P_aux
    Pilha_lst* P_Entrada = pilha_lst_cria();
    Pilha_lst* P_aux = pilha_lst_cria();
    Pilha_lst* P_saida = pilha_lst_cria();

    for(i = n_Letras - 1; i>=0; i--){
        pilha_lst_push(P_Entrada,desorganizada[i]); // Passa a palavra desorganizada para uma pilha na "ordem contraria"
    }

    for(i = 0; i < n_Letras; i++){
        while(!TRUE){
            if(!pilha_lst_vazia(P_Entrada)){ // Se a pilha de entrada do usuario não estiver vazia...
                if(Palavra_formada[i] != P_Entrada->prim->info){ // Se a cabeça da pilha e a letra analizada são diferentes, passa pra estação ou "aux", e tira da entrada
                    pilha_lst_push(P_aux,P_Entrada->prim->info);
                    pilha_lst_pop(P_Entrada);

                    Insere_Retira[j] = 'I';
                    j++;
                } else{ // Se a cabeça é igual a letra procurada
                    // Vai do lado A para a estação
                    pilha_lst_push(P_aux,P_Entrada->prim->info);
                    pilha_lst_pop(P_Entrada);

                    Insere_Retira[j] = 'I';
                    j++;
                    // Vai da estação para o lado B
                    pilha_lst_push(P_saida,P_aux->prim->info);
                    pilha_lst_pop(P_aux);

                    Insere_Retira[j] = 'R';
                    j++;
                    break; // Achou, vai pra proxima letra
                }
            }else{ // Se a pilha de entrada estiver vazia passa a analizar a pilha "aux"
                if(Palavra_formada[i] == P_aux->prim->info){
                    // Vai da estação para o lado B
                    pilha_lst_push(P_saida, P_aux->prim->info);
                    pilha_lst_pop(P_aux);
                    Insere_Retira[j] = 'R';
                    j++;
                    break; // Se achou, vai pra proxima letra
                }else{ // Se ainda na aux estiver na ordem errada é porque não é possivel
                    Insere_Retira[j] = '\0'; // ponto final da string na posição j pois seria a proxima a ser preenchida
                    printf("%s impossible\n", Insere_Retira);
                    return;
                }
            }
            if(pilha_lst_vazia(P_Entrada) && pilha_lst_vazia(P_aux)){
                Insere_Retira[j] = '\0'; // ponto final da string na posição j pois seria a proxima a ser preenchida
                printf("%s impossible\n", Insere_Retira);
                return;
            }
        }  
    }
    
    // Caso tenha dado certo a saida é mostrada ao usuario
    Insere_Retira[j] = '\0';
    printf("%s", Insere_Retira);
    printf("\n");

    // Libera as pilhas usadas
    pilha_lst_libera(P_Entrada);
    pilha_lst_libera(P_aux);
    pilha_lst_libera(P_saida);
}

/* Main
*   param1(argc)    - Numero de argumentos
*   param2(argv)    - Valores dos argumentos
*   return          - Codigo de erro 
*/
int main (int argc, char** argv){
    char desorganizada[TAM_MAX_VET], Palavra_formada[TAM_MAX_VET];
    int n_Letras;

    do{
        do{
            printf("Digite o número de vagões (max 26):\n");
            scanf("%d", &n_Letras);
            getchar();

            if(n_Letras > TAM_MAX_VET || n_Letras < 0){
                printf("Número invalido, você deve digitar um número menor que 26\n");
            }
        }while(n_Letras > TAM_MAX_VET || n_Letras < 0); // Repete enquanto o número de letras é invalido
        if(n_Letras == 0){
            break; // Usuario digitou 0 para finalizar
        }

        // Pega as letras que vão entrar e a palavra que deve ser formada:
        do{
            printf("Digite as letras na ordem dos vagões:\n");
            fgets(desorganizada, TAM_MAX_VET, stdin);
            desorganizada[n_Letras] = '\0'; // Substitui o \n da string por \0

            printf("Digite a palavra que sera formada:\n");
            fgets(Palavra_formada, TAM_MAX_VET, stdin);
            Palavra_formada[n_Letras] = '\0';   // Substitui o \n da string por \0

            if(strlen(desorganizada) != n_Letras || strlen(Palavra_formada) != n_Letras){
                printf("Voce digitou uma quantidade maior ou menor do que a quantidade de vagões digitada anteriormente\nTente novamente:\n");
            }
        } while(strlen(desorganizada) != n_Letras || strlen(Palavra_formada) != n_Letras); // Repete enquanto o tamanho da palavra não for condizente com n_Letras 

        Problema_dos_trilhos(desorganizada,Palavra_formada,n_Letras);
    }while(!TRUE); // Loop infinito, para quando o usuario digita 0

    return SUCESSO;
}