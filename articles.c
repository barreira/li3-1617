/**
 * @file articles.c
 * @brief Definição das estruturas relativas aos artigos
 * 
 * Contém a definição das estruturas que definem um artigo e um array de AVLs
 * de artigos.
 * 
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-09
 */

#include <stdlib.h>
#include <string.h>

#include "articles.h"

#define DEFAULT_REVCOUNT 5 // média de revisões por arigo (confirmar)
#define SIZE 10

/* Estruturas */

struct article_set {
	AVL articles[SET_SIZE_A]; // Array de AVLs (primeira para todos os artigos cujo id começa por "0", segunda para os que começam por "1", etc)
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

	for (i = 0; i < SET_SIZE_A; i++) {
		as->articles[i] = initAvl();
	}

	return as;
}

REVISION initRevision() {
	REVISION r = malloc(sizeof(struct revision));
	r->id = malloc(sizeof(char) * SIZE);
	r->timestamp = malloc(sizeof(char) * SIZE);
	r->title = malloc(sizeof(char) * SIZE);
	r->textsize = 0;
	r->wc = 0;
	return r;
}

ARTICLE initArticle() {
	ARTICLE a = malloc(sizeof(struct article));
	a->id = malloc(sizeof(char) * SIZE);
	a->revcount = 1;
	a->revcapacity = DEFAULT_REVCOUNT;
	a->revisions = malloc(sizeof(struct revision) * DEFAULT_REVCOUNT);
	a->occurrences = 1;
	return a;
}

/* Frees */

REVISION freeRevision(REVISION r) {
	free(r->id);
	free(r->timestamp);
	free(r->title);
	free(r);
	r = NULL;
	return r;
}

ARTICLE freeArticle(ARTICLE a) {
	int i;

	for (i = 0; i < a->revcount; i++) {
		a->revisions[i] = freeRevision(a->revisions[i]);
	}	

	free(a->id);
	free(a);
	a = NULL;
	return a;
}

ARTICLE_SET freeArticleSet(ARTICLE_SET as) {
	int i;

	for (i = 0; i < SET_SIZE_A; i++) {
		as->articles[i] = freeAvl(as->articles[i]);
	}

	free(as);
	as = NULL;
	return as;
}

/* Inserts */

void duplicateA(Node n, void* dup) {
	ARTICLE tmp = getInfo(n);
	int cap = tmp->revcapacity;
	int nr = tmp->revcount;

	if (nr == cap) {
		tmp->revisions = realloc(tmp->revisions, sizeof(struct revision) * cap * 2);
		tmp->revcapacity *= 2;
	}

	tmp->revisions[nr] = ((ARTICLE) dup)->revisions[0];
	(tmp->revcount)++;
	(tmp->occurrences)++;
	
	setInfo(n, tmp);

	dup = freeArticle(dup);
	free(tmp);
}

ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = a->id[0] - '0';
	as->articles[pos] = insert(as->articles[pos], a->id, a, duplicateA);
	return as;	
}


ARTICLE addRevision(ARTICLE a, REVISION r) {
	a->revisions[a->revcount] = r;
	(a->revcount)++;
	(a->occurrences)++;
	return a;
}

/* Teste de existência */

int existsArticle(ARTICLE_SET as, ARTICLE a) {
	int pos = a->id[0] - '0';
	int res = exists(as->articles[pos], a->id);
	return res;
}

/* Getters e Setters */

AVL getArticleSubset(ARTICLE_SET as, int pos) {
	return as->articles[pos];
}

char* getTitle(REVISION r) {
	char* ret = malloc(sizeof(r->title));
	strcpy(ret, r->title);
	return ret;
}

ARTICLE setArticleID(ARTICLE a, char* id) {
	strcpy(a->id, id);
	return a;
}

REVISION setRevisionID(REVISION r, char* id) {
	strcpy(r->id, id);
	return r;
}

REVISION setTimestamp(REVISION r, char* t) {
	strcpy(r->timestamp, t);
	return r;
}

REVISION setTitle(REVISION r, char* t) {
	strcpy(r->title, t);
	return r;
}

REVISION setTextSize(REVISION r, int ts) {
	r->textsize = ts;
	return r;
}

REVISION setWordCount(REVISION r, int wc) {
	r->wc = wc;
	return r;
}