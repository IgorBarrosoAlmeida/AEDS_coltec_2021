/*
* @file Ex1.c
* @brief implementando exercicio 1:
* @author Igor Barroso Almeida
* 3. Você foi contratado(a) para montar a nova rede do Coltec (O Fabrício cansou e fugiu).
* Você sabe que existem 10 servidores nessa rede e cada servidor está conectado a 8 máquinas.
* Os 10 servidores se comunicam entre si, mas cada um é responsável único por suas 8 máquinas.
* Usando um grafo, faça um programa para detectar quando há falha de comunicação entre
* algum dos servidores.
* @date 30-07-2022
*/

/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

/* Constantes */
#define SUCESSO             (0)
#define N_SERVIDORES        (4)
#define NAO_VISITADO        (0)
#define VISITADO            (1)

/*-----------------------------FUNÇÕES-----------------------------*/

// Função que imprime um grafo de lista de adjacência
void Servidor_imprime(grafoLA_t** grafo){
    lista_t* aux;

    if((*grafo) != NULL){
        // Imprime informações gerais
        (void)printf("----------------------------------------------\n");
        (void)printf("               DADOS DO SISTEMA               \n");
        (void)printf("----------------------------------------------\n");
        (void)printf("Número de servidores: %d\n", (*grafo)->nVertices);
        
        // Imprime as arestas
        (void)printf("\nConexões:\n");
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

// Retorna verdadeiro se tem falha e falso se não tem
bool_t Verifica_conexao(grafoLA_t** grafo, int ini, int fim, int* visitados){
    int i;
    lista_t* aux = (*grafo)->vertices[ini];
    bool_t falha = VERDADEIRO;

    // Atualiza vetor "visitados"
    visitados[aux->vertice-1] = VISITADO;
    aux = aux->prox;

    // Verifica se existe caminho entre o par de vertices
    while(aux != NULL){
        if(falha != FALSO){
            if(aux->vertice-1 == fim){
                return FALSO;
            } else if(visitados[aux->vertice-1] == NAO_VISITADO){
                falha = Verifica_conexao(grafo, aux->vertice-1, fim, visitados);
            } else{
                aux = aux->prox;
            }
        } else{
            return falha;
        }
    }


    return falha;
}

void Servidor_falhas(grafoLA_t** grafo){
    int i, j, nFalhas = 0;
    bool_t falha;
    
    (void)printf("Falhas detectadas na comunicação entre os servidores:\n");
    for(i = 0; i < (*grafo)->nVertices; i++){
        for(j = 0; j < (*grafo)->nVertices; j++){
            if(i != j){ // Não analisa autolaços
                // Aloca e inicia tudo com 0(Não visitado)
                int* visitados = (int*)calloc(N_SERVIDORES, sizeof(int));

                falha = Verifica_conexao(grafo, i, j, visitados);

                if(falha){
                    (void)printf("%d e %d\n", i+1, j+1);
                    nFalhas++;
                }
                free(visitados);
            }
        }
    }
    if(nFalhas == 0){
        (void)printf("\n* Nenhuma falha detectada *\n");
    } else{
        (void)printf("\n* Um total de %d falhas foram detectadas *\n", nFalhas);
    }
}

/*---------------------------FUNÇÕES FIM---------------------------*/

/* Função principal
* @return SUCESSO caso seja executado corretamente
*/
int main(){
    int escolha, sOrigem, sDestino;
    grafoLA_t* grafo = NULL;

    // Cria o grafo
    Grafo_cria_LA(&grafo, N_SERVIDORES, GRAFO_ORIENTADO);

    do{
        // Menu
        (void)printf("\n----------------------------------------------\n");
        (void)printf("|      SISTEMA DE SERVIDORES DO COLTEC       |\n");
        (void)printf("----------------------------------------------\n");

        (void)printf("Escolha uma das opções:\n");
        (void)printf("1.Criar conexão\n2.Ver Conexões\n3.Ver falhas(Caminhos entre vertices)\n4.Ver falhas(arestas entre vertices)\n0.Finalizar\n");
        scanf("%d", &escolha);
        getchar(); // Tira o \n

        switch (escolha)
        {
        case 1: // Criar conexões
            (void)printf("\nDigite o servidor de origem: ");
            scanf("%d", &sOrigem);
            getchar(); // Tira o \n
            (void)printf("Digite o servidor de destino: ");
            scanf("%d", &sDestino);
            getchar(); // Tira o \n

            Grafo_criaAresta_LA(&grafo, sOrigem, sDestino);

            (void)printf("Conexão criada\n");
            break;
        case 2: // Ver conexões
            Servidor_imprime(&grafo);
            break;
        case 3: // Ver falhas(Caminhos entre vertices)
            Servidor_falhas(&grafo);
            break;
        case 4: // Ver falhas(arestas entre vertices)

            (void)printf("Servidores que não estão conectados a todos os outros:\n");
            for(int i = 0; i < grafo->nVertices; i++){
                if(grafo->vertices[i]->nArestas < N_SERVIDORES-1){
                    (void)printf("Servidor %d\n", i+1);
                }
            }
            break;
        case 0:
            break;
        default:
            (void)printf("Escolha invalida\n");
            break;
        }

    }while(escolha != 0);

    Grafo_libera_LA(&grafo);

    return SUCESSO;
}