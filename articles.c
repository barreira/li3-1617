/**
 * @file articles.c
 * @brief Definição das estruturas/funções relativas aos artigos
 * 
 * Contém a definição das estruturas que definem um artigo (e revisões do mesmo)
 * e respetivas funções.
 * 
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-29
 */

#include <stdlib.h>
#include <string.h>

#include "articles.h"

#define DEFAULT_REVCOUNT 5

/* Estruturas */

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

REVISION initRevision() {
	REVISION r = malloc(sizeof(struct revision));
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

/* Inserts */

REVISION getRevisionAt(REVISION* revs, int pos) {
	REVISION r = initRevision();
	setRevisionID(r, revs[pos]->id);
	setTimestamp(r, revs[pos]->timestamp);
	setTitle(r, revs[pos]->title);
	setTextSize(r, revs[pos]->textsize);
	setWordCount(r, revs[pos]->wc);
	return r;
}

void* duplicateA(void* info, void* dup, int* flag) {
	int lr, cmp;
	
	lr = ((ARTICLE) info)->revcount - 1;
	cmp = strcmp(((ARTICLE) info)->revisions[lr]->id, ((ARTICLE) dup)->revisions[0]->id);

	if (cmp != 0) {
		int cap = ((ARTICLE) info)->revcapacity;
		int nr = ((ARTICLE) info)->revcount;

		if (nr == cap) {
			((ARTICLE) info)->revisions = realloc(((ARTICLE) info)->revisions, sizeof(struct revision) * cap * 2);
			((ARTICLE) info)->revcapacity *= 2;
		}

		((ARTICLE) info)->revisions[nr] = getRevisionAt(((ARTICLE) dup)->revisions, 0); // ((ARTICLE) dup)->revisions[0]; 
		((ARTICLE) info)->revcount += 1;
		dup = freeArticle((ARTICLE) dup);
	}
	else {
		*flag = 1;
	}

	((ARTICLE) info)->occurrences += 1;

	return info;
}
/*
ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a, int* flag) {
	if (a->id != NULL) {
		int pos = a->id[0] - '0';
		as->articles[pos] = insert(as->articles[pos], a->id, a, duplicateA, flag);
	}

	return as;	
}*/

ARTICLE addRevision(ARTICLE a, REVISION r) {
	a->revisions[a->revcount] = r;
	(a->revcount)++;
	(a->occurrences)++;
	return a;
}

/* Getters e Setters */

char* getArticleID(ARTICLE a) {
	char* ret = malloc(sizeof(char) * (strlen(a->id) + 1));
	strcpy(ret, a->id);
	return ret;	
}

char* getTitle(REVISION r) {
	char* ret = malloc(sizeof(char) * (strlen(r->title) + 1));
	strcpy(ret, r->title);
	return ret;
}

char* getTimestamp(REVISION r) {
	char* ret = malloc(sizeof(char) * (strlen(r->timestamp) + 1));
	strcpy(ret, r->timestamp);
	return ret;	
}

ARTICLE setArticleID(ARTICLE a, char* id) {
	a->id = malloc(strlen(id) + 1);
	strcpy(a->id, id);
	return a;
}

REVISION setRevisionID(REVISION r, char* id) {
	r->id = malloc(strlen(id) + 1);
	strcpy(r->id, id);
	return r;
}

REVISION setTimestamp(REVISION r, char* t) {
	r->timestamp = malloc(strlen(t) + 1);
	strcpy(r->timestamp, t);
	return r;
}

REVISION setTitle(REVISION r, char* t) {
	r->title = malloc(strlen(t) + 1);
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

/* Queries */

long getOccurrences(void* i) {
	long ret = (long) ((ARTICLE) i)->occurrences;
	return ret;
}

long getRevCount(void *i) {
	long ret = (long) ((ARTICLE) i)->revcount;
	return ret;
}

REVISION getRevision(ARTICLE a, char* revision_id) {
	int i;

	for (i = 0; i < a->revcount; i++) {
		if (strcmp(a->revisions[i]->id, revision_id) == 0) {
			return a->revisions[i];
		}
	}

	return NULL;
}

REVISION getLastRevision(ARTICLE a) {
	return a->revisions[a->revcount - 1];
}

char* getLastRevisionTitle(ARTICLE a) {
	char* ret;
	
	ret = malloc(sizeof(char) * (strlen(a->revisions[a->revcount-1]->title) + 1));
	strcpy(ret, a->revisions[a->revcount-1]->title);

	return ret;
}

char* getArticleRevisionTimestamp(ARTICLE a, char* revision_id) {
	char* ret;

	for (int i = 0; i < a->revcount; i++) {
		if (strcmp(a->revisions[i]->id, revision_id) == 0) {
			ret = malloc(sizeof(char) * strlen(a->revisions[i]->timestamp));
			strcpy(ret, a->revisions[i]->timestamp);
			return ret;
		}
	}

	return NULL;
}

int getBiggestRevisionSize(ARTICLE a) {
	int i, s = 0;

	for (i = 0; i < a->revcount; i++) {
		if (a->revisions[i]->textsize >= s) {
			s = a->revisions[i]->textsize;
		}
	}

	return s;
}

int getBiggestRevisionWC(ARTICLE a) {
	int i, s = 0;

	for (i = 0; i < a->revcount; i++) {
		if (a->revisions[i]->wc >= s) {
			s = a->revisions[i]->wc;
		}
	}

	return s;
}