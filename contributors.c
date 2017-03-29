#include <stdlib.h>

#include "contributors.h"

#define NUMSIZE 10 // Sequêcia de 0 a 9 (primeiro numero do id de contribuidor)

struct contributor_set {
	TAD_istruct cset[NUMSIZE]; // Array de AVLs (primeira para todos os contribuidores cujo id começa por "0", segunda para os que começam por "1", etc)
};

struct contributor {
	char* id;
	char* name;
	int revisions;
};

CONTRIBUTOR_SET initContributorSet() {
	int i;
	CONTRIBUTOR_SET cs = malloc(sizeof(struct contributor_set));

	for (i = 0; i < NUMSIZE; i++) {
		cs->cset[i] = init();
	}

	return cs;
}

CONTRIBUTOR initContributor() {
	CONTRIBUTOR c = malloc(sizeof(struct contributor));
	c->id = NULL;
	c->name = NULL;
	c->revisions = 0;
	return c;
}

void freeContributor(CONTRIBUTOR c) {
	free(c->id);
	free(c->name);
	free(&(c->revisions));
	free(c);
}

void freeContributorSet(CONTRIBUTOR_SET cs) {
	int i;

	if (cs) {
		for (i = 0; i < NUMSIZE; i++) {
			cs->cset[i] = clean(cs->cset[i]);
		}

		free(cs);
	}
}

CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	cs->cset[pos] = insert(cs->cset[pos], c->id, c);
	return cs;
}

int existsContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	int res = exists(cs->cset[pos], c->id);
	return res;
}

// Getters e Setters

TAD_istruct getContributorSubset(CONTRIBUTOR_SET cs, int pos) {
	return cs->cset[pos];
}