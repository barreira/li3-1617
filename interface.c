/**
 * @file interface.c
 * @brief Definição de todas as funções pertencentes à interface do projeto
 * 
 * Contém as funções responsáveis pelo parsing dos ficheiros XML, pela definição,
 * carregamento e limpeza das estruturas e pelas queries. 
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * TODO: corrigir contagem de palavras na função parseRevision
 *
 * @version 2017-04-09
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "interface.h"
#include "avl.h"
#include "contributors.h"
#include "articles.h"
#include "queries.h"
#include "xmlparser.h"

struct TCD_istruct {
	WikiData wikidata;
};

/* INIT, LOAD E CLEAN */

TAD_istruct init() {
	TAD_istruct s = malloc(sizeof(struct TCD_istruct));

	s->wikidata = initWikiData();
	
	return s;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		parseFile(qs->wikidata, snaps_paths[i]);
	}

	return qs;
}

TAD_istruct clean(TAD_istruct qs) {
	qs->wikidata = freeWikiData(qs->wikidata);
	free(qs);
	qs = NULL;
	return qs;
}

/* QUERIES */

// 1
long all_articles(TAD_istruct qs) {
	return query1(qs->wikidata);
}
/*
// 2
long unique_articles(TAD_istruct qs) {
	long res = 0;
	int i;
	AVL tmp;

	for (i = 0; i < SET_SIZE_A; i++) {
		tmp = getArticleSubset(qs->aset, i);
		res += (long) getTotalNodes(tmp);
	}

	return res;
}

// 3
long all_revisions(TAD_istruct qs) {
	long res = 0;
	int i;
	AVL tmp;

	for (i = 0; i < SET_SIZE_A; i++) {
		tmp = getArticleSubset(qs->aset, i);
		res += query3(tmp);
	}

	return res;	
}

// 4
long* top_10_contributors(TAD_istruct qs) {
	long* revs = calloc(10, sizeof(long));
	long* ids = calloc(10, sizeof(long));
	int i;

	for (i = 0; i < SET_SIZE_C; i++) {
		AVL tmp = getContributorSubset(qs->cset, i);
		query4(tmp, &ids, &revs, 10);
	}

	return ids;
}

// 5
char* contributor_name(long contributor_id, TAD_istruct qs) {
	char* id = malloc(sizeof(contributor_id));
	sprintf(id, "%ld", contributor_id);

	int pos = id[0] - '0';
	AVL tmp = getContributorSubset(qs->cset, pos);

	return query5(tmp, id);
}

// 6
long* top_20_largest_articles(TAD_istruct qs) {
	long* sizes = calloc(20, sizeof(long));
	long* ids = calloc(20, sizeof(long));
	int i;

	for (i = 0; i < SET_SIZE_A; i++) {
		AVL tmp = getArticleSubset(qs->aset, i);
		query6(tmp, &ids, &sizes, 20);
	}

	return ids;
}

// 7
char* article_title(long article_id, TAD_istruct qs) {
	char* id = malloc(sizeof(article_id));
	sprintf(id, "%ld", article_id);

	int pos = id[0] - '0';
	AVL tmp = getArticleSubset(qs->aset, pos);

	return query7(tmp, id);
}

// 8
long* top_N_articles_with_more_words(int n, TAD_istruct qs) {
	long* words = calloc(n, sizeof(long));
	long* ids = calloc(n, sizeof(long));
	int i;

	for (i = 0; i < SET_SIZE_A; i++) {
		AVL tmp = getArticleSubset(qs->aset, i);
		query8(tmp, &ids, &words, n);
	}

	return ids;
}

// 9
int my_strcmp(const void* a, const void* b) { 
	char const *char_a = *(char const **)a;
	char const *char_b = *(char const **)b;

	return strcmp(char_a, char_b);
}

char** titles_with_prefix(char* prefix, TAD_istruct qs) {
	int i, size = 0;
	char*** ret = malloc(sizeof(char**));
	*ret = NULL;

	for (i = 0; i < SET_SIZE_A; i++) {
		AVL tmp = getArticleSubset(qs->aset, i);
		query9(tmp, prefix, ret, &size);
	}

	qsort(*ret, size, sizeof(char*), my_strcmp);

	if (*ret != NULL) {
		(*ret)[size] = NULL;
	}

	return *ret;
}

// 10
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs) {
	char* a_id = malloc(sizeof(article_id));
	sprintf(a_id, "%ld", article_id);

	char* r_id = malloc(sizeof(revision_id));
	sprintf(r_id, "%ld", revision_id);	

	int pos = a_id[0] - '0';
	AVL tmp = getArticleSubset(qs->aset, pos);

	return query10(tmp, a_id, r_id);
}*/