#include <stdlib.h>
#include <string.h>

#include "queries.h"
#include "avl.h"

#define SET_SIZE 10

/* Estruturas (definição) */

typedef struct contributorset {
	AVL contributors[SET_SIZE];
} *ContributorSet;

typedef struct articleset {
	AVL articles[SET_SIZE];
} *ArticleSet;

struct wikidata {
	ContributorSet cset;
	ArticleSet aset;
};

/* Estruturas (inits) */

int strcmpA(const void* a, const void* b) {
	char* id_a = getArticleID((ARTICLE) a);
	char* id_b = getArticleID((ARTICLE) b);
	return strcmp(id_a, id_b);
}

int strcmpC(const void* a, const void* b) {
	char* id_a = getContributorID((CONTRIBUTOR) a);
	char* id_b = getContributorID((CONTRIBUTOR) b);
	return strcmp(id_a, id_b);
}


ArticleSet initArticleSet() {
	ArticleSet as = malloc(sizeof(struct articleset));

	for (int i = 0; i < SET_SIZE; i++) {
		as->articles[i] = initAvl(strcmpA);
	}

	return as;
}

ContributorSet initContributorSet() {
	ContributorSet cs = malloc(sizeof(struct contributorset));

	for (int i = 0; i < SET_SIZE; i++) {
		cs->contributors[i] = initAvl(strcmpC);
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
		wd->aset->articles[pos] = insert(wd->aset->articles[pos], a, duplicateA, flag);
	}

	return wd;	
}

WikiData insertContributor(WikiData wd, CONTRIBUTOR c) {
	char* id = getContributorID(c);

	if (id != NULL) { 
		int pos = id[0] - '0';
		wd->cset->contributors[pos] = insert(wd->cset->contributors[pos], c, duplicateC, NULL);
	}

	return wd;
}


/* Queries */

typedef struct sq468 {
	long* ids;
	long* values; // revs, sizes, words
} *SQ468;

typedef struct sq9 {
	char** titles;
	int size;
} *SQ9;

SQ468 initStructQ468(int size) {
	SQ468 s = malloc(sizeof(struct sq468));
	
	s->ids = calloc(size, sizeof(long));
	s->values = calloc(size, sizeof(long));

	return s;
}

SQ9 initStructQ9() {
	SQ9 s = malloc(sizeof(struct sq9));
	
	s->titles = NULL;
	s->size = 0;

	return s;
}

// 1

void query1_aux(void* info, void* acc, void* aux) {
	(*(long*) acc) += getOccurrences((ARTICLE) info);
}

long query1(WikiData wd) {
	long articles = 0;

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], &articles, NULL, query1_aux);
	}

	return articles;	
}

// 2

long query2(WikiData wd) {
	long articles = 0;

	for (int i = 0; i < SET_SIZE; i++) {
		articles += (long) getTotalNodes(wd->aset->articles[i]);
	}

	return articles;
}

void query3_aux(void* info, void* acc, void* aux) {
	(*(long*) acc) += getRevCount((ARTICLE) info);
}

// 3

long query3(WikiData wd) {
	long revisions = 0;

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], &revisions, NULL, query3_aux);
	}

	return revisions;	
}

// 4

void query4_aux(void* info, void* acc, void* aux) {
	int i, index;
	long id, revs;

	id = atol(getContributorID((CONTRIBUTOR) info));
	revs = (long) getRevisions((CONTRIBUTOR) info);

	for (i = 0; i < 10 && ((SQ468) acc)->values[i] > revs; i++);
	
	while (i < 10 && ((SQ468) acc)->values[i] == revs && ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	index = i;

	for (i = 10; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	((SQ468) acc)->values[i] = revs;
	((SQ468) acc)->ids[i] = id;
}

long* query4(WikiData wd) {
	SQ468 s;

	s = initStructQ468(10);

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->cset->contributors[i], s, NULL, query4_aux);
	}

	return s->ids;
}

// 5

void* query5_aux(void* info, void* aux) {
	return getUsername((CONTRIBUTOR) info);
}

char* query5(WikiData wd, char* contributor_id) {
	char* username;
	int pos;
	
	pos = contributor_id[0] - '0';

	CONTRIBUTOR tmp = initContributor();
	setContributorID(tmp, contributor_id);

	username = findAndApply(wd->cset->contributors[pos], tmp, NULL, query5_aux);

	free(tmp);

	return username;
}

// 6

void query6_aux(void* info, void* acc, void* aux) {
	int i, index;
	long id, size;

	id = atol(getArticleID((ARTICLE) info));
	size = getBiggestRevisionSize((ARTICLE) info);

	for (i = 0; i < 20 && ((SQ468) acc)->values[i] > size; i++);
	
	while (i < 20 && ((SQ468) acc)->values[i] == size && ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	index = i;

	for (i = 20; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	((SQ468) acc)->values[i] = size;
	((SQ468) acc)->ids[i] = id;
}

long* query6(WikiData wd) {
	SQ468 s;

	s = initStructQ468(20);

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, NULL, query6_aux);
	}

	return s->ids;
}

// 7

void* query7_aux(void* info, void* aux) {
	return getLastRevisionTitle((ARTICLE) info);
}

char* query7(WikiData wd, char* article_id) {
	char* title;
	int pos;
	
	pos = article_id[0] - '0';

	ARTICLE tmp = initArticle();
	setArticleID(tmp, article_id);

	title = findAndApply(wd->aset->articles[pos], tmp, NULL, query7_aux);

	free(tmp);

	return title;
}

// 8

void query8_aux(void* info, void* acc, void* aux) {
	int i, index, n;
	long id, wc;

	n = (*(int*) aux);

	id = atol(getArticleID((ARTICLE) info));
	wc = getBiggestRevisionWC((ARTICLE) info);

	for (i = 0; i < n && ((SQ468) acc)->values[i] > wc; i++);
	
	while (i < n && ((SQ468) acc)->values[i] == wc && ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	index = i;

	for (i = n; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	((SQ468) acc)->values[i] = wc;
	((SQ468) acc)->ids[i] = id;
}

long* query8(WikiData wd, int n) {
	SQ468 s;

	s = initStructQ468(n);

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, &n, query8_aux);
	}

	return s->ids;
}

// 9

int my_strcmp(const void* a, const void* b) { 
	char const *char_a = *(char const **)a;
	char const *char_b = *(char const **)b;

	return strcmp(char_a, char_b);
}

int isPrefix(char* s, char* p) {
	int i;

	for (i = 0; s[i] == p[i] && s[i] != '\0' && p[i] != '\0'; i++);

	if (i == strlen(p)) {
		return 1;
	}

	return 0;
}

void query9_aux(void* info, void* acc, void* aux) {
	char* t;
	int tam;

	t = getLastRevisionTitle((ARTICLE) info);
	tam = ((SQ9) acc)->size;

	if (isPrefix(t, (char*) aux)) {
		((SQ9) acc)->titles = realloc(((SQ9) acc)->titles, sizeof(char*) * (tam + 1));
		((SQ9) acc)->titles[tam] = t;
		((SQ9) acc)->size += 1;
	}
}

char** query9(WikiData wd, char* prefix) {
	SQ9 s;

	s = initStructQ9();

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, prefix, query9_aux);
	}

	qsort(s->titles, s->size, sizeof(char*), my_strcmp);

	if (s->titles != NULL) {
		s->titles[s->size] = NULL;
	}

	return s->titles;
}

// 10

void* query10_aux(void* info, void* aux) {
	return getArticleRevisionTimestamp((ARTICLE) info, (char*) aux);
}

char* query10(WikiData wd, char* article_id, char* revision_id) {
	char* timestamp;
	int pos;
	
	pos = article_id[0] - '0';

	ARTICLE tmp = initArticle();
	setArticleID(tmp, article_id);

	timestamp = findAndApply(wd->aset->articles[pos], tmp, revision_id, query10_aux);

	free(tmp);

	return timestamp;
}