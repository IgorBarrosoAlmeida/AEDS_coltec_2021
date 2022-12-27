/*
* @file Ex1.c
* @brief implementando exercicio 1:
* 1. Usando uma matriz de adjacências, crie um grafo orientado e calcule os graus de seus vértices.
* @author Igor Barroso Almeida
* @date 27-07-2022
*/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

/* Constantes */
#define SUCESSO         (0)

/* Função principal
* @return SUCESSO caso seja executado corretamente
*/
int main(){
    int escolha, nVertices, tipo, vOrigem, vDestino;
    grafo_t* grafo = NULL;

    // Criando o grafo
    (void)printf("----------Criando grafo----------\n");
    (void)printf("Quantos vertices tem o grafo? ");
    scanf("%d", &nVertices);
    getchar(); // Tira o \n

    (void)printf("Qual o tipo do grafo:\n");
    (void)printf("1.Orientado\n2.Não orientado\n");
    scanf("%d", &tipo);
    getchar(); // Tira o \n

    Grafo_cria_MA(&grafo, nVertices, (tipo == 1 ? GRAFO_ORIENTADO : GRAFO_NAO_ORIENTADO));

    do{
        (void)printf("\nEscolha uma das opções:\n");
        (void)printf("1.Criar aresta\n2.Graus dos vertices\n3.Imprimir grafo\n");
        (void)printf("0.Finalizar\n");
        scanf("%d", &escolha);
        getchar(); // Tira o \n

        switch (escolha)
        {
        case 1: // Cria uma aresta
            (void)printf("Vertice de origem: ");
            scanf("%d", &vOrigem);
            getchar(); // Tira o \n
            (void)printf("Vertice de destino: ");
            scanf("%d", &vDestino);
            getchar(); // Tira o \n

            Grafo_criaAresta_MA(&grafo, vOrigem, vDestino);
            break;
        case 2: // Graus dos vertices
            Grafo_determinaGrau_MA(&grafo);
            break;
        case 3: // Imprime grafo
            Grafo_imprime_MA(&grafo);
            break;
        case 0: // Finaliza
            break;
        default:
            (void)printf("Opção invalida\n");
            break;
        }
    }while(escolha != 0);

    // Libera o grafo
    Grafo_libera_MA(&grafo);

    // Se chegou até aqui ocorreu tudo certo
    return SUCESSO;
}