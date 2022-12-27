/****************************************************************************************** 
* Igor Barroso Almeida
* 07/06/2022
* Prova trimestral - Qual é essa estrutura de dados?
* Programa que de acordo com uma serie de comandos de insersão e retirada
* de elementos em uma estrutura de dados, identifica qual é esta estrutura.
******************************************************************************************/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

/* Constantes */
#define SUCESSO     (0)
#define ERRO        (1)

/* -------------------------------------Funções------------------------------------ */

/* Função que conta a quantidade de retiradas */
int conta_retira(int*vet, int qnt){
    int contador = 0;
    for(int i = 0; i < qnt; i++){
        if(vet[i] == RETIRAR){
            contador++;
        }
    }
    return contador;
}

int procura_maior_inseridos(int* operacao, int* elemento,int qnt_operacoes){
    int pos_maior, maior = MENOR_INT;
    for(int i = 0; i < qnt_operacoes; i++){
        if(operacao[i] == INSERIR){
            if(elemento[i] > maior){
                pos_maior = i;
                maior = elemento[i];
            }
        }
    }
    elemento[pos_maior] -= elemento[pos_maior];

    return maior;
}

/* Função que determina, a partir de um vetor de 
* comandos(1 para inserir e 2 para retirar)
* e um de elementos, se é ou não uma pilha
*/
Bool Identifica_pilha(int* operacao, int* elemento,int qnt_operacoes){
    Pilha_lst* pilha = pilha_lst_cria();
    int i, count_r = 0, retiras = conta_retira(operacao, qnt_operacoes);

    for(i = 0; (i < qnt_operacoes) && (count_r < retiras); i++){
        if(operacao[i] == INSERIR){
            pilha_lst_push(pilha, elemento[i]); // Insere elemento
        } else{
            if(pilha->prim != NULL){
                if(pilha->prim->info == elemento[i]){
                    pilha_lst_pop(pilha); 
                    count_r++; // conta a qnt de elementos já retirados
                } else{ // prim da pilha != elemento, não é pilha
                    pilha_lst_libera(pilha);
                    return FALSO;
                }
            } else{ // tentando retirar sem colocar
                pilha_lst_libera(pilha);
                return FALSO;
            }
        }
    }

    pilha_lst_libera(pilha);
    return VERDADEIRO;
}

/* Função que determina, a partir de um vetor de 
* comandos(1 para inserir e 2 para retirar)
* e um de elementos, se é ou não uma fila
*/
Bool Identifica_fila(int* operacao, int* elemento,int qnt_operacoes){
    Fila* fila = fila_cria_l();
    int i, count_r = 0, retiras = conta_retira(operacao, qnt_operacoes);

    for(i = 0; (i < qnt_operacoes) && (count_r < retiras); i++){
        if(operacao[i] == INSERIR){ 
            fila_insere_l(fila, elemento[i]); // Retira elemento
        }else{
            if(fila->ini != NULL){ 
                if(fila->ini->info == elemento[i]){
                    fila_retira_l(fila); // Retira se elemento == prim da fila
                    count_r++; // Conta elementos já retirados
                } else{ 
                    fila_libera_l(fila);
                    return FALSO;
                }
            } else{ // retirando elemento da fila vazia
                fila_libera_l(fila);
                return FALSO;
            }
        }
    }
    fila_libera_l(fila);
    return VERDADEIRO;
}

/* Função que determina, a partir de um vetor de 
* comandos(1 para inserir e 2 para retirar)
* e um de elementos, se é ou não uma fila de prioridade
*/
Bool Identifica_fila_prioridade(int* operacao, int* elemento,int qnt_operacoes){
    int i, j = 0;
    int* retiradas;

    retiradas =(int*)malloc((conta_retira(operacao,qnt_operacoes)) * sizeof(int));
    // Passa os elementos retirados para o vetor "retiradas"
    for(i = 0; i < qnt_operacoes; i++){
        if(operacao[i] == RETIRAR){
            retiradas[j] = elemento[i];
            j++;
        }
    }

    for(i = 0; i < conta_retira(operacao, qnt_operacoes); i++){
        int atual = retiradas[i];
        int maior = procura_maior_inseridos(operacao, elemento, qnt_operacoes);  

        if(atual != maior){
            free(retiradas);
            return FALSO;
        }
    }

    free(retiradas);
    return VERDADEIRO;
}

/* -----------------------------------Fim Funções---------------------------------- */

/* Main
*   return          - Codigo de erro
*/
int main(){
    FILE* entrada;
    int qnt_operacoes, i;
    int *operacao;
    int *elemento;
    Bool eh_pilha, eh_fila, eh_fila_p;

    entrada = fopen(DIRETORIO, "r"); // Abre arquivo de entrada

    if(entrada != NULL){ // Arquivo aberto corretamente
        while(!feof(entrada)){
            fscanf(entrada, "%d", &qnt_operacoes);
            // Aloca a memoria
            operacao = (int*)malloc(qnt_operacoes * sizeof(int));
            elemento = (int*)malloc(qnt_operacoes * sizeof(int));
            
            // Lê do arquivo
            for(i = 0; i < qnt_operacoes; i++){
                fscanf(entrada, "%d %d", &operacao[i], &elemento[i]);
            }

            eh_pilha = Identifica_pilha(operacao, elemento, qnt_operacoes);
            eh_fila = Identifica_fila(operacao, elemento, qnt_operacoes);
            eh_fila_p = Identifica_fila_prioridade(operacao, elemento, qnt_operacoes);
            
            // Testa de acordo com os resultados, qual é a estrutura de dados
            if(eh_pilha){
                if((eh_fila) || (eh_fila_p)){ 
                    printf("not sure\n");
                } else{
                    printf("stack\n");
                }
            } else if(eh_fila){
                if(eh_fila_p){
                    printf("not sure\n");
                } else{
                    printf("queue\n");
                }
            } else if(eh_fila_p){
                printf("priority queue\n");
            } else{
                printf("impossible\n");
            }
            // Libera memoria alocada
            free(operacao);
            free(elemento);
        }
    } else{
        printf("Não foi possivel abrir o arquivo\n");
        return ERRO;
    }
    fclose(entrada);
    
    return SUCESSO;
}