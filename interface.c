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
#include <stdio.h>
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

/* FUNÇÕES AUXILIARES */

int getLongLength(long x) {
	int digits = 1;

	while (x >= 10) {
	    x /= 10;
	    digits++;
	}

	return digits;
}

/* QUERIES */

// 1
long all_articles(TAD_istruct qs) {
	return query1(qs->wikidata);
}

// 2
long unique_articles(TAD_istruct qs) {
	return query2(qs->wikidata);
}

// 3
long all_revisions(TAD_istruct qs) {
	return query3(qs->wikidata);
}


// 4
long* top_10_contributors(TAD_istruct qs) {
	return query4(qs->wikidata);
}

// 5
char* contributor_name(long contributor_id, TAD_istruct qs) {
	char* id;

	id = malloc(sizeof(char) * getLongLength(contributor_id));
	sprintf(id, "%ld", contributor_id);

	return query5(qs->wikidata, id);
}

// 6
long* top_20_largest_articles(TAD_istruct qs) {
	return query6(qs->wikidata);
}

// 7
char* article_title(long article_id, TAD_istruct qs) {
	char* id;

	id = malloc(sizeof(char) * getLongLength(article_id));
	sprintf(id, "%ld", article_id);

	return query7(qs->wikidata, id);
}

// 8
long* top_N_articles_with_more_words(int n, TAD_istruct qs) {
	return query8(qs->wikidata, n);
}

// 9

char** titles_with_prefix(char* prefix, TAD_istruct qs) {
	return query9(qs->wikidata, prefix);
}

// 10
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs) {
	char *a_id, *r_id;

	a_id = malloc(sizeof(char) * getLongLength(article_id));
	sprintf(a_id, "%ld", article_id);

	r_id = malloc(sizeof(char) * getLongLength(revision_id));
	sprintf(r_id, "%ld", revision_id);	

	return query10(qs->wikidata, a_id, r_id);
}