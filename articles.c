#include <stdlib.h>

#include "articles.h"
#include "avl.h"

#define NUMSIZE 10 // Sequêcia de 0 a 9 (primeiro numero do id de artigo)
#define DEFAULT_REVCOUNT 5 // média de revisões por arigo (confirmar)

/* Estruturas */

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

/* Inits */

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
	a->revisions = malloc(sizeof(struct revision) * DEFAULT_REVCOUNT);
	a->occurrences = 0;
	return a;
}

/* Frees */

REVISION freeRevision(REVISION r) {
	free(r->id);
	free(r->timestamp);
	free(r->title);
	free(&(r->textsize));
	free(&(r->wc));
	free(r);
	r = NULL;
	return r;
}

ARTICLE freeArticle(ARTICLE a) {
	int i;

	for (i = 0; i < a->revcount; i++) {
		a->revisions[i] = free(a->revisions[i]);
	}	

	free(a->id);
	free(&(a->revcount));
	free(&(a->revcapacity));
	free(&(a->occurrences));
	free(a);
	a = NULL;
	return a;
}

ARTICLE_SET freeArticleSet(ARTICLE_SET as) {
	int i;

	for (i = 0; i < NUMSIZE; i++) {
		as->aset[i] = freeAvl(as->aset[i]);
	}

	free(as);
	as = NULL;
	return as;
}

/* Inserts */

void duplicateArticle(Node n, void* info) {
			int cap = n->info->revcapacity;
			int nr = n->info->revcount;
		
			if (nr == cap) {
				int size = getRevisionSize(); // size da struct revision
				realloc(n->info->revisions, size * cap * 2);
				n->info->capacity *= 2;
			}
		
			n->info->revisions[nr] = info->revisions[0];
			(n->info->revcount)++;
			(n->info->occurrences)++;
			
			info = freeArticle(info);
}

ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = atoi(&(a->id[0]));
	as->aset[pos] = insert(as->aset[pos], a->id, a, duplicateArticle);
	return as;	
}

ARTICLE insertRevision(ARTICLE a, REVISION r) {

}

/* Teste de existência */

int existsArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = atoi(&(a->id[0]));
	int res = exists(as->aset[pos], a->id);
	return res;
}

/* Getters e Setters */

AVL getArticleSubset(ARTICLE_SET as, int pos) {
	return as->aset[pos];
}

unsigned int getRevisionSize() {
	return (sizeof(struct revision));
}

void setArticleID(ARTICLE a, char* id) {
	strcpy(a->id, id);
}

void setRevisionID(REVISION r, char* id) {
	strcpy(r->id, id);
}

void setTimestamp(REVISION r, char* t) {
	strcpy(r->timestamp, t);
}

void setTitle(REVISION r, char* t) {
	strcpy(r->title, t);
}

void setTextSize(REVISION r, int ts) {
	r->textsize = ts;
}

void setWordCount(REVISION r, int wc) {
	r->wc = wc;
}