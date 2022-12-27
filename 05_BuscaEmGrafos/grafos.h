/* Inclusões */
#include <stdint.h>

/* Constantes */
#define GRAFO_ORIENTADO         (0)
#define GRAFO_NAO_ORIENTADO     (1)
#define SEM_ARESTA              (0)
#define COM_ARESTA              (1)
#define VERDADEIRO              (1==1)
#define FALSO                   (!VERDADEIRO)

/* Tipos */
typedef	struct grafo_s{
    int** dados;
    int nVertices;
    int tipo;
} grafo_t;

typedef uint16_t bool_t;

typedef struct lista_s{
	int vertice;
    int nArestas;
	struct lista_s *prox;
} lista_t;

typedef struct grafoLA_s{
    int nVertices;
    int tipo;
    lista_t** vertices;
} grafoLA_t;

// Funções referentes a matriz de adjacencia
void Grafo_cria_MA(grafo_t** grafo, int nVertices, int Tipo);
void Grafo_libera_MA(grafo_t** grafo);
void Grafo_imprime_MA(grafo_t** grafo);
void Grafo_criaAresta_MA(grafo_t** grafo, int vOrigem, int vDestino);

// Funções lista
void lst_libera(lista_t *l);

// Funções referentes a lista de adjacencia
void Grafo_cria_LA(grafoLA_t** grafo, int nVertices, int tipo);
void Grafo_libera_LA(grafoLA_t** grafo);
void Grafo_imprime_LA(grafoLA_t** grafo);
void CriaAresta(grafoLA_t** grafo, int vOrigem, int vDestino);
void Grafo_criaAresta_LA(grafoLA_t** grafo, int vOrigem, int vDestino);