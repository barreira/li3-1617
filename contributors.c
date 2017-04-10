/**
 * @file contributors.c
 * @brief Definição das estruturas relativas aos contribuidores
 * 
 * Contém a definição das estruturas que definem um contribuidor e um array
 * de AVLs de contribuidores.
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

#include "contributors.h"
#include "avl.h"

#define NUMSIZE 10 // Sequêcia de 0 a 9 (primeiro numero do id de contribuidor)

/* Estruturas */

struct contributor_set {
	AVL cset[NUMSIZE]; // Array de AVLs (primeira para todos os contribuidores cujo id começa por "0", segunda para os que começam por "1", etc)
};

struct contributor {
	char* id;
	char* username;
	int revisions;
};

/* Inits */

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

/* Frees */

CONTRIBUTOR freeContributor(CONTRIBUTOR c) {
	free(c->id);
	free(c->username);
	free(&(c->revisions));
	free(c);
	c = NULL;
	return c;
}

CONTRIBUTOR_SET freeContributorSet(CONTRIBUTOR_SET cs) {
	int i;

	for (i = 0; i < NUMSIZE; i++) {
		cs->cset[i] = freeAvl(cs->cset[i]);
	}

	free(cs);
	cs = NULL;
	return cs;
}

/* Inserts */

void increment(void* info) {
	((CONTRIBUTOR) info)->revisions += 1;
}

void duplicateC(Node n, void* dup) {
	incrementCounters(n, increment);
	dup = freeContributor(dup);
}

CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	cs->cset[pos] = insert(cs->cset[pos], c->id, c, duplicateC);
	return cs;
}

/* Teste de existência */

int existsContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	int pos = atoi(&(c->id[0]));
	int res = exists(cs->cset[pos], c->id);
	return res;
}

/* Getters e Setters */

AVL getContributorSubset(CONTRIBUTOR_SET cs, int pos) {
	return cs->cset[pos];
}

CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id) {
	strcpy(c->id, id);
	return c;
}

CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u) {
	strcpy(c->username, u);
	return c;
}

char* getContributorID(CONTRIBUTOR c) {
	char* aux = malloc(sizeof(c->id)); // é assim?
	strcpy(aux, c->id);
	return aux;
}

char* getUsername(CONTRIBUTOR c) {
	char* aux = malloc(sizeof(c->username)); // é assim?
	strcpy(aux, c->username);
	return aux;
}
