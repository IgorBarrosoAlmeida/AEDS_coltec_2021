//ARVORE BINARIA INT
struct arv{
	int info;
	struct arv *esq;
	struct arv *dir;
};

// ARVORE PARA HISTOGRAMA
struct arv_char{
	char info;
	struct arv_char *esq;
	struct arv_char *dir;
};

typedef struct arv Arv;
typedef struct arv_char Arv_char;


Arv* arv_criavazia(void);
int arv_vazia(Arv* a);
Arv* arv_libera(Arv* a);

Arv_char* arv_char_criavazia(void);
int arv_char_vazia(Arv_char* a);
Arv_char* arv_char_libera(Arv_char* a);