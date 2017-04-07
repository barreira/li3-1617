#include <stdlib.h>

#include "contributors.h"
#include "avl.h"

#define NUMSIZE 10 // Sequêcia de 0 a 9 (primeiro numero do id de contribuidor)

struct contributor_set {
	AVL cset[NUMSIZE]; // Array de AVLs (primeira para todos os contribuidores cujo id começa por "0", segunda para os que começam por "1", etc)
};

struct contributor {
	char* id; //
	char* username; //
	int revisions; //
};

CONTRIBUTOR_SET initContributorSet() {
	int i;
	CONTRIBUTOR_SET cs = malloc(sizeof(struct contributor_set));

	for (i = 0; i < NUMSIZE; i++) {
		cs->cset[i] = initAvl();
	}

	return cs;
}

CONTRIBUTOR initContributor() {
	CONTRIBUTOR c = malloc(sizeof(struct contributor));
	c->id = NULL;
	c->username = NULL;
	c->revisions = 0;
	return c;
}

void freeContributor(CONTRIBUTOR c) {
	free(c->id);
	free(c->username);
	free(&(c->revisions));
	free(c);
}

void freeContributorSet(CONTRIBUTOR_SET cs) {
	int i;

	if (cs) {
		for (i = 0; i < NUMSIZE; i++) {
			cs->cset[i] = freeAvl(cs->cset[i]);
		}

		free(cs);
	}
}

void duplicateContributor(Node n, void* info) {
	(n->info->revisions)++;
	freeContributor(info);
}

CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	cs->cset[pos] = insert(cs->cset[pos], c->id, c, duplicateContributor);
	return cs;
}

int existsContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	int res = exists(cs->cset[pos], c->id);
	return res;
}

// Getters e Setters

AVL getContributorSubset(CONTRIBUTOR_SET cs, int pos) {
	return cs->cset[pos];
}

void setContributorID(CONTRIBUTOR c, char* id) {
	strcpy(c->id, id);
}

void setUsername(CONTRIBUTOR c, char* u) {
	strcpy(c->username, u);
}

char *getContributorID(CONTRIBUTOR c) {
	return c->id;
}

char *getUsername(CONTRIBUTOR c) {
	return c->username;
}
