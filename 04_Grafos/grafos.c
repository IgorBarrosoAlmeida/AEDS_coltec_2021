/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

/*---------------------------Funções matriz adjacente---------------------------*/

// Função que cria um grafo usando matriz adjacente
void Grafo_cria_MA(grafo_t** grafo, int nVertices, int Tipo){
    int i, j, limiteLinha;

    // Aloca espaço para a estrutura
    *grafo = (grafo_t*)malloc(sizeof(grafo_t));

    // Aloca espaço para um sentido da matriz
    (*grafo)->dados = (int**)malloc(nVertices * sizeof(int*));

    for(i = 0; i < nVertices; i++){
        // Define a partir do tipo o tamanho da matriz
        limiteLinha = (Tipo == GRAFO_ORIENTADO ? nVertices : i+1);
        // Aloca espaço para o outro sentido da matriz
        (*grafo)->dados[i] = (int*)malloc(limiteLinha * sizeof(int));
    }

    // Inicializa a matriz sem arestas
    for(i = 0; i < nVertices; i++){
        limiteLinha = (Tipo == GRAFO_ORIENTADO ? nVertices : i + 1);

        for(j = 0; j < limiteLinha; j++){
            ((*grafo)->dados[i])[j] = SEM_ARESTA;
        }
    }

    // Adiciona informações finais na estrutura
    (*grafo)->nVertices = nVertices;
    (*grafo)->tipo = Tipo;
}

// Função que libera o espaço alocado para o grafo MA
void Grafo_libera_MA(grafo_t** grafo){
    int i;

    for(i = 0; i < (*grafo)->nVertices; i++){
        // Libera cada linha
        free(((int**)(*grafo)->dados)[i]);
    }

    // Libera o resto da matriz
    free((*grafo)->dados);

    // Libera o grafo
    free(*grafo);
}

// Função que imprime as informações de um grafo feito com matriz de adjacencia
void Grafo_imprime_MA(grafo_t** grafo){
    int i, j, limiteLinha;

    if(grafo != NULL){
        // Imprime informações básicas
        (void)printf("       IMPRESSÃO GRAFO       \n");
        (void)printf("-----------------------------\n");
        (void)printf("Tipo: ");
        if((*grafo)->tipo == GRAFO_ORIENTADO){
            (void)printf("Orientado\n");
        } else{
            (void)printf("Não orientado\n");
        }
        (void)printf("Número de vértices: %d\n", (*grafo)->nVertices);
        
        // Imprime matriz de adjacencia
        (void)printf("---------------------------\n");
        (void)printf("Matriz da adjacencia:\n");
        for(i = 0; i < (*grafo)->nVertices; i++){
            limiteLinha = ((*grafo)->tipo == GRAFO_ORIENTADO ? (*grafo)->nVertices : i + 1);
            for(j = 0; j < limiteLinha; j++){
                (void)printf("%d ", (*grafo)->dados[i][j]);
            }
            (void)printf("\n");
        }
        
        // Imprime Detalhadamente cada aresta
        (void)printf("---------------------------\n");
        (void)printf("Arestas existentes:\n");
        for(i = 0; i < (*grafo)->nVertices; i++){
            limiteLinha = ((*grafo)->tipo == GRAFO_ORIENTADO ? (*grafo)->nVertices : i + 1);

            for(j = 0; j < limiteLinha; j++){
                if((*grafo)->dados[i][j] == COM_ARESTA){
                    (void)printf("%d%c-->%d\n", i+1, (*grafo)->tipo == GRAFO_ORIENTADO ? '-' : '<', j+1);
                }
            }
        }
    }
}

// Função que adiciona uma aresta ao grafo
void Grafo_criaAresta_MA(grafo_t** grafo, int Origem, int Destino){
    int vOrigem, vDestino;

    // Para não contar com vertice 0
    Origem--;
    Destino--;

    // De acordo com o tipo muda o destino e a origem
    if((*grafo)->tipo == GRAFO_ORIENTADO){
            vOrigem = Origem;
            vDestino = Destino;
        } else{
        if(Origem < Destino){
            vOrigem = Destino;
            vDestino = Origem; 
        } else{
            vOrigem = Origem;
            vDestino = Destino;
        }
    }

    // Se a aresta não existe passa a existir
    if((*grafo)->dados[vOrigem][vDestino] == COM_ARESTA){
        (void)printf("A aresta já existe\n");
    } else{
        (*grafo)->dados[vOrigem][vDestino] = COM_ARESTA;
    }
}

// Função que calcula e imprime o grau dos vertices de um grafo
void Grafo_determinaGrau_MA(grafo_t** grafo){
    int grau, i, j;

    for(i = 0; i < (*grafo)->nVertices; i++){
        grau = 0;

        // De acordo com o tipo, calcula o grau do vertice em questão(i)
        if((*grafo)->tipo == GRAFO_ORIENTADO){
            for(j = 0; j < (*grafo)->nVertices; j++){
                if((*grafo)->dados[j][i] == COM_ARESTA){
                    grau++;
                }
            }    
        } else{
            for(j = i; j < (*grafo)->nVertices; j++){
                if((*grafo)->dados[j][i] == COM_ARESTA){
                    grau++;
                }
            }
            for(j = 0; j < i+1; j++){
                if(((*grafo)->dados[i][j] == COM_ARESTA)){
                    grau++;
                }
            }
        }

        // Imprime o grau do vertice em questão(i) para o usuario
        (void)printf("Vertice %d: Grau %d\n", i+1, grau);
    }
}

/*-------------------------Funções matriz adjacente FIM-------------------------*/

/*      Funções Lista       */

// Função que libera o espaço alocado para uma lista
void lst_libera(lista_t *l){
	lista_t *p=l;

	while(p!=NULL){
		lista_t *t=p->prox;
		free(p);
		p=t;
	}
}

/*-------------------------Funções lista de adjacencia---------------------------*/

// Função que cria um grafo com lista de adjacência
void Grafo_cria_LA(grafoLA_t** grafo, int nVertices, int tipo){
    // Aloca espaço para o grafo
    *grafo = (grafoLA_t*)malloc(sizeof(grafoLA_t));
    
    // Aloca espaço para uma lista por vertice
    (*grafo)->vertices = (lista_t**)malloc(nVertices * sizeof(lista_t*));

    // Aloca espaço para o primeiro elemento da lista, que é o vertice em questão
    for(int i = 0; i < nVertices; i++){
        (*grafo)->vertices[i] = (lista_t*)malloc(sizeof(lista_t));

        (*grafo)->vertices[i]->nArestas = 0;
        (*grafo)->vertices[i]->vertice = i+1;
        (*grafo)->vertices[i]->prox = NULL;
    }

    (*grafo)->nVertices = nVertices;
    (*grafo)->tipo = tipo;
}

// Função que libera o espaço alocado para o grafo
void Grafo_libera_LA(grafoLA_t** grafo){
    // Libera cada lista de arestas
    for(int i = 0; i < (*grafo)->nVertices; i++){
        lst_libera((*grafo)->vertices[i]);
    }

    // Libera a lista de listas
    free((*grafo)->vertices);

    // Libera o grafo
    free(*grafo);
}

// Função que imprime um grafo de lista de adjacência
void Grafo_imprime_LA(grafoLA_t** grafo){
    lista_t* aux;

    if((*grafo) != NULL){
        // Imprime informações gerais
        (void)printf("------------------------------------\n");
        (void)printf("         IMPRESSÃO DO GRAFO         \n");
        (void)printf("------------------------------------\n");
        (void)printf("Número de vertices: %d\n", (*grafo)->nVertices);
        (void)printf("Tipo: ");
        (*grafo)->tipo == GRAFO_ORIENTADO ? (void)printf("Orientado\n") : (void)printf("Não orientado\n");
        
        // Imprime as arestas
        (void)printf("------------------------------------\n");
        (void)printf("Arestas:\n");
        for(int i = 0; i < (*grafo)->nVertices; i++){
            aux = (*grafo)->vertices[i]->prox;
            for(int j = 0; j < (*grafo)->vertices[i]->nArestas; j++){
                if(aux != NULL){
                    (void)printf("%d--->%d\n", (*grafo)->vertices[i]->vertice, aux->vertice);
                    aux = aux->prox;
                }
            }
        }
    }
}

// Função que cria a aresta em si
void CriaAresta(grafoLA_t** grafo, int vOrigem, int vDestino){
    lista_t* novo;
    lista_t* aux;

    // Adicionando mais uma aresta
    (*grafo)->vertices[vOrigem-1]->nArestas++;
    aux = (*grafo)->vertices[vOrigem-1];

    // Acha o final da lista
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    // Cria o novo elemento/aresta na lista
    novo = (lista_t*)malloc(sizeof(lista_t));
    novo->vertice = vDestino;
    novo->nArestas = (*grafo)->vertices[vOrigem-1]->nArestas;
    novo->prox = NULL;

    // "Insere" na lista
    aux->prox = novo;
}

// Função que adiciona uma ou duas aresta ao grafo dependendo do tipo
void Grafo_criaAresta_LA(grafoLA_t** grafo, int vOrigem, int vDestino){
    
    if((*grafo) != NULL){
        CriaAresta(grafo, vOrigem, vDestino);

        if((*grafo)->tipo == GRAFO_NAO_ORIENTADO){
            // Em grafo não orientado adiciona aresta no outro sentido
            CriaAresta(grafo, vDestino, vOrigem);
        }
    }
}

// Função que calcula e mostra o grau das arestas de um grafo LA
void Grafo_calculaGrau_LA(grafoLA_t** grafo){
    
    if((*grafo) != NULL){
        int i, j;
        int* grau;
        grau = (int*)calloc((*grafo)->nVertices, sizeof(int));

        (void)printf("----------GRAUS DOS VERTICES----------\n");
        if((*grafo)->tipo == GRAFO_NAO_ORIENTADO){
            // Se não é orientado o grau é o mesmo que o numero de arestas
            for(i = 0; i < (*grafo)->nVertices; i++){
                (void)printf("Vertice %d: Grau %d\n", i+1, (*grafo)->vertices[i]->nArestas);
            }
        } else{
            // Se é orientado o grau é calculado
            for(i = 0; i < (*grafo)->nVertices; i++){
                if((*grafo)->vertices[i]->prox != NULL){
                    lista_t* aux = (*grafo)->vertices[i]->prox;

                    // Em cada posição de "grau" tem o grau do vertice referente
                    while(aux != NULL){
                        grau[(aux->vertice)-1]++;

                        aux = aux->prox;
                    }
                }
            }

            for(i = 0; i < (*grafo)->nVertices; i++){
                (void)printf("Vertice %d: Grau %d\n", i+1, grau[i]);
            }
        }
        
        free(grau);
    }
}

/*-----------------------Funções lista de adjacencia FIM-------------------------*/