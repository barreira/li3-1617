#include <stdlib.h>

#include "queries.h"
#include "avl.h"

#define SET_SIZE 10

/* Estruturas (definição) */

struct wikidata {
	ContributorSet cset;
	ArticleSet aset;
};

struct contributorset {
	AVL contributors[SET_SIZE];
};

struct articleset {
	AVL articles[SET_SIZE];
};

/* Estruturas (inits) */

ArticleSet initArticleSet() {
	ArticleSet as = malloc(sizeof(struct articleset));

	for (int i = 0; i < SET_SIZE; i++) {
		as->articles[i] = initAvl();
	}

	return as;
}

ContributorSet initContributorSet() {
	ContributorSet cs = malloc(sizeof(struct contributorset));

	for (int i = 0; i < SET_SIZE; i++) {
		cs->contributors[i] = initAvl();
	}

	return cs;
}

WikiData initWikiData() {
	WikiData wd = malloc(sizeof(struct wikidata));

	wd->aset = initArticleSet();
	wd->cset = initContributorSet();

	return wd;
}

/* Estruturas (frees) */

ArticleSet freeArticleSet(ArticleSet as) {
	for (int i = 0; i < SET_SIZE; i++) {
		as->articles[i] = freeAvl(as->articles[i]);
	}

	free(as);
	as = NULL;
	return as;
}

ContributorSet freeContributorSet(ContributorSet cs) {
	for (int i = 0; i < SET_SIZE; i++) {
		cs->contributors[i] = freeAvl(cs->contributors[i]);
	}

	free(cs);
	cs = NULL;
	return cs;
}

WikiData freeWikiData(WikiData wd) {
	wd->aset = freeArticleSet(wd->aset);
	wd->cset = freeContributorSet(wd->cset);
	free(wd);
	wd = NULL;
	return wd;
}

/* Estruturas (inserts) */

WikiData insertArticle(WikiData wd, ARTICLE a, int* flag) {
	char* id = getArticleID(a);

	if (a != NULL) {
		int pos = id[0] - '0';
		wd->aset->articles[pos] = insert(wd->aset->articles[pos], id, a, duplicateA, flag);
	}

	return wd;	
}

WikiData insertContributor(WikiData wd, CONTRIBUTOR c) {
	char* id = getContributorID(c);

	if (id != NULL) { 
		int pos = id[0] - '0';
		wd->cset->contributors[pos] = insert(wd->cset->contributors[pos], id, c, duplicateC, NULL);
	}

	return wd;
}

/* Queries */

void query1_aux(void* info, void* acc) {
	(*(long*) acc) += (long) getOccurrences((ARTICLE) info);
}

long query1(WikiData wd) {
	long res = 0;

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], &res, query1_aux);
	}

	return res;	
}