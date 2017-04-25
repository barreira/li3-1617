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
#include <stdio.h>

#include "contributors.h"

/* Estruturas */

struct contributor {
	char* id;
	char* username;
	int revisions;
};

/* Inits */

CONTRIBUTOR initContributor() {
	CONTRIBUTOR c = malloc(sizeof(struct contributor));
	c->id = NULL;
	c->username = NULL;
	c->revisions = 1;
	return c;
}

/* Frees */

CONTRIBUTOR freeContributor(CONTRIBUTOR c) {
	free(c->id);
	free(c->username);
	free(c);
	c = NULL;
	return c;
}

/* Inserts */

void* duplicateC(void* info, void* dup, int *flag) {
	((CONTRIBUTOR) info)->revisions += 1;
	dup = freeContributor((CONTRIBUTOR) dup);
	return info;
}

/*
CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c) {
	if (c->id != NULL) { 
		int pos = c->id[0] - '0';
		cs->contributors[pos] = insert(cs->contributors[pos], c->id, c, duplicateC, NULL);
	}

	return cs;
}*/

/* Getters e Setters */

CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id) {
	c->id = malloc(strlen(id) + 1);
	strcpy(c->id, id);
	return c;
}

CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u) {
	c->username = malloc(strlen(u) + 1);
	strcpy(c->username, u);
	return c;
}

char* getContributorID(CONTRIBUTOR c) {
	char* aux = NULL;

	if (c->id != NULL) {
		aux = malloc(strlen(c->id) + 1);
		strcpy(aux, c->id);
	}

	return aux;
}

char* getUsername(CONTRIBUTOR c) {
	char* aux = malloc(strlen(c->username) + 1);
	strcpy(aux, c->username);
	return aux;
}

int getRevisions(CONTRIBUTOR c) {
	int aux = c->revisions;
	return aux;
}