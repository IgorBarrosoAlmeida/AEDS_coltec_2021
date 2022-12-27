/* Biblioteca com funções necessarias para
* identificar uma estrutura de dados
*/

/* Constantes */
#define DIRETORIO  	"./entrada.txt"
#define INSERIR 	(1)
#define RETIRAR		(2)
#define VERDADEIRO 	(1==1)
#define FALSO 		(!VERDADEIRO)
#define MENOR_INT 	(-2147483647)

/* tipos */

typedef struct lista{
	int info;
	struct lista *prox;
} Lista;

typedef struct pilha_lst{
	Lista *prim;
} Pilha_lst;

typedef struct filal{
	Lista *ini;
	Lista *fim;
} Fila;

typedef int Bool;

/* Funções pilhas */
Pilha_lst *pilha_lst_cria();
void pilha_lst_push(Pilha_lst *p, int v);
int pilha_lst_pop(Pilha_lst *p);
void pilha_lst_libera(Pilha_lst *p);

/* Funções fila */
Fila *fila_cria_l();
void fila_insere_l(Fila *f,int v);
int fila_retira_l(Fila *f);
void fila_libera_l(Fila *f);