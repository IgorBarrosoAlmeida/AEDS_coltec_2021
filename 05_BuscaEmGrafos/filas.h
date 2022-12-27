struct lista{
	int info;
	struct lista *prox;
};
typedef struct lista Lista;

struct filal{
	Lista *ini;
	Lista *fim;
};

typedef struct filal FilaL;

FilaL *fila_cria_l();
void fila_insere_l(FilaL *f, int v);
int fila_retira_l(FilaL *f);
int fila_vazia_l(FilaL *f);
void fila_libera_l(FilaL *f);
void fila_imprime_l(FilaL *f);
Lista* fila_busca_l(FilaL *fila, int informacao);
