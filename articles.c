#include <stdlib.h>

#include "articles.h"
#include "avl.h"

#define NUMSIZE 10 // Sequêcia de 0 a 9 (primeiro numero do id de artigo)
#define DEFAULT_REVCOUNT 5 // média de revisões por arigo (confirmar)

struct article_set {
	AVL aset[NUMSIZE]; // Array de AVLs (primeira para todos os artigos cujo id começa por "0", segunda para os que começam por "1", etc)
};

struct revision {
	char* id;
	char* timestamp;
	char* title;
	int textsize;
	int wc;
};

struct article {
	char* id;
	int revcount;
	int revcapacity;
	REVISION* revisions;
	int occurrences;
};

ARTICLE_SET initArticleSet() {
	int i;
	ARTICLE_SET as = malloc(sizeof(struct article_set));

	for (i = 0; i < NUMSIZE; i++) {
		as->aset[i] = initAvl();
	}

	return as;
}

REVISION initRevision() {
	//REVISION r = malloc(sizeof(struct revision)); // já não é preciso
	r->id = NULL;
	r->timestamp = NULL;
	r->title = NULL;
	r->textsize = 0;
	r->wc = 0;
	return r;
}

ARTICLE initArticle() {
	ARTICLE a = malloc(sizeof(struct article));
	a->id = NULL;
	a->revcount = 0;
	a->revcapacity = DEFAULT_REVCOUNT;
	a->revisions = calloc(sizeof(struct revision) * DEFAULT_REVCOUNT); // inicializa + coloca a NULL
	// a->revisions[0] = initRevision(); // inicializa o primeiro
	a->occurrences = 0;
	return a;
}

REVISION freeRevision(REVISION r) {
	free(r->id);
	free(r->timestamp);
	free(r->title);
	free(&(r->textsize));
	free(&(r->wc));
	return NULL;
}

void freeArticle(ARTICLE a) {
	int i;
	free(a->id);

	for (i = 0; a->revisions[i] != NULL; i++) {
		a->revisions[i] = freeRevision(a->revisions[i]);
	}	

	free(&(a->occurrences));
}

void freeArticleSet(ARTICLE_SET as) {
	int i;

	if (as) {
		for (i = 0; i < NUMSIZE; i++) {
			as->aset[i] = freeAvl(as->aset[i]);
		}

		free(as);
	}
}

ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = atoi(&(a->id[0]));
	as->aset[pos] = insert(as->aset[pos], a->id, a);
	return as;	
}

int existsArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = atoi(&(a->id[0]));
	int res = exists(as->aset[pos], a->id);
	return res;
}

// Getters e Setters

AVL getArticleSubset(ARTICLE_SET as, int pos) {
	return as->aset[pos];
}

unsigned int getRevisionSize() {
	return (sizeof(struct revision));
}