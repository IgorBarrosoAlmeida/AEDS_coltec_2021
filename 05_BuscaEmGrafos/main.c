/*
* @file main.c
* @brief implementando busca em largura e em profundidade em grafos
* @date 06-08-2022
*/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"
#include "filas.h"

/* Constantes */
#define SUCESSO         (0)

// Cores para representar o estado do vertice
#define WHITE           (0)
#define GRAY            (1)
#define BLACK           (2)

// Inicialização de Vinfo
#define SEM_ANT         (0)
#define N_CONECTA       (0)

/* Tipos */
typedef struct vertice_s{
    int dist; // Usado apenas em largura
    int temp; // Usado apenas em profundidade
    int temp_volta; // apenas profundidade
    int ant;
    int cor;
}Vinfo;

// Função que inicia os dados de uma estrutura Vinfo para Busca em largura
void Vinfo_init(Vinfo* v, int nVertices, int Vsource){
    for(int i = 0; i < nVertices; i++){
        v[i].cor = WHITE;
        v[i].ant = SEM_ANT;
        v[i].dist = N_CONECTA;
    }
    // Inicia com a fonte cinza
    v[Vsource - 1].cor = GRAY;
}

// Fução que imprime as informações de uma busca em largura
void Grafo_buscaImprime_LA(grafoLA_t** grafo, Vinfo* info){

    for(int i = 0; i < (*grafo)->nVertices; i++){

        (void)printf("---------Vertice %d---------\n", i + 1);
        switch (info[i].cor){
        case BLACK:
            (void)printf("Vertice preto\n");
            break;
        case WHITE:
            (void)printf("Vertice branco\n");
            break;
        case GRAY:
            (void)printf("Vertice cinza\n");
            break;
        default:
            break;
        }
        (void)printf("Anterior: %d\n", info[i].ant);
        (void)printf("Distancia: %d\n", info[i].dist);
    }
}

// Função de busca em largura utilizando lista de adjacencia
void Grafo_buscaLargura_LA(grafoLA_t** grafo, int Vsource, Vinfo* info){
    FilaL* fila = fila_cria_l();
    int atual = Vsource;
    lista_t* aux;

    // Inicia as informações presentes em Vinfo
    Vinfo_init(info, (*grafo)->nVertices, Vsource);
    fila_insere_l(fila, Vsource);

    do{

        if(info[atual - 1].cor == GRAY){
            aux = (*grafo)->vertices[atual - 1]->prox;
            
            while (aux != NULL){

                if(info[aux->vertice - 1].cor == WHITE){
                    fila_insere_l(fila, aux->vertice);
                    // atualiza a cor e o vertice anterior
                    info[aux->vertice - 1].cor = GRAY;
                    info[aux->vertice - 1].ant = (*grafo)->vertices[atual - 1]->vertice;
                    // A distancia do atual = distancia do anterior mais 1
                    info[aux->vertice - 1].dist = info[info[aux->vertice -1].ant -1].dist + 1;
                    
                }

                aux = aux->prox;
            }

            // Atualiza a fila de vertices
            fila_retira_l(fila);
            info[atual - 1].cor = BLACK;
        }

        if(!fila_vazia_l(fila)){
            atual = fila->ini->info;
        }
    }while(!fila_vazia_l(fila));

    

    Grafo_buscaImprime_LA(grafo, info);

    // Libera memória alocada
    fila_libera_l(fila);
}

int Grafo_buscaProfundidade_LA(grafoLA_t** grafo, int Vsource, Vinfo* info, int cTempo){

    // Atualiza as informações do vertice
    info[Vsource].cor = GRAY;
    info[Vsource].temp = cTempo;
    cTempo++;

    lista_t* aux = (*grafo)->vertices[Vsource]->prox;

    // Percorre pelas arestas
    while(aux != NULL){

        // Se a cor do adjacente for branca o anterior é o atual
        if(info[aux->vertice - 1].cor == WHITE){
            info[aux->vertice - 1].ant = (*grafo)->vertices[Vsource]->vertice;

            // Recurção, chama a função com o vertice não visitado
            cTempo = Grafo_buscaProfundidade_LA(grafo, aux->vertice - 1, info, cTempo);
        }

        aux = aux->prox;
    }

    // Visitou todos os adjacentes --> fica preto e conta o tempo de volta
    info[Vsource].cor = BLACK;
    info[Vsource].temp_volta = cTempo;
    cTempo++;
    return cTempo;
}

/* Função principal
* @return SUCESSO caso seja executado corretamente
*/
int main(){
    int escolha, vOrigem, vDestino, nVertices, tipo, Vsource;
    grafoLA_t* grafo = NULL;

    // Criando o grafo
    (void)printf("----------Criando grafo----------\n");
    (void)printf("Quantos vertices tem o grafo? ");
    scanf("%d", &nVertices);
    getchar(); // Tira o \n

    (void)printf("Qual o tipo do grafo:\n");
    (void)printf("1.Orientado\n2.Não orientado\n");
    scanf("%d", &tipo);
    getchar(); // Tira o \n

    Grafo_cria_LA(&grafo, nVertices, (tipo == 1 ? GRAFO_ORIENTADO : GRAFO_NAO_ORIENTADO));
    
    // Informações para buscas
    Vinfo* info = (Vinfo *)malloc(grafo->nVertices * sizeof(Vinfo));

    do{ 
        // Menu
        (void)printf("\nEscolha uma das opções:\n");
        (void)printf("1.Criar aresta\n2.Imprimir grafo\n3.Busca em largura\n4.Busca em profundidade\n");
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

            Grafo_criaAresta_LA(&grafo, vOrigem, vDestino);
            break;
        case 2:// Imprime grafo

            Grafo_imprime_LA(&grafo);
            break;
        case 3: // Busca em largura

            (void)printf("Qual é o vertice de fonte/source da busca?\n");
            scanf("%d", &Vsource);
            getchar(); // Tira o \n

            // Inicia a struct
            Vinfo_init(info, grafo->nVertices, Vsource);

            Grafo_buscaLargura_LA(&grafo, Vsource, info);
            break;
        case 4: // Busca em profundidade

            // Inicia a struct
            for(int i = 0; i < grafo->nVertices; i++){
                info[i].cor = WHITE;
                info[i].ant = SEM_ANT;
                info[i].temp = 0;
            }

            int cTempo = 1;

            // Aplica a busca para todos os vertices brancos
            for(int i = grafo->vertices[0]->vertice - 1; i < grafo->nVertices; i++){
                if(info[i].cor == WHITE){
                    cTempo = Grafo_buscaProfundidade_LA(&grafo, i, info, cTempo);
                }
            }

            // Imprime o retorno da busca de profundidade
            for(int i = grafo->vertices[0]->vertice - 1; i < grafo->nVertices; i++){
                (void)printf("---------Vertice %d---------\n", i + 1);
                (void)printf("Predecessor %d\n", info[i].ant);
                (void)printf("Tempo visitado %d\n", info[i].temp);
                (void)printf("Tempo de volta %d\n", info[i].temp_volta);
            }

            break;
        case 0: // Finaliza
            break;
        default:
            (void)printf("Opção invalida\n");
            break;
        }
    }while(escolha != 0);

    free(info);
    Grafo_libera_LA(&grafo);

    // Se chegou até aqui ocorreu tudo certo
    return SUCESSO;
}