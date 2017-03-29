#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "xmlparser.h"

#define SIZE_KEY 10

struct node { /* o typedef do .h provavelmente deveria estar aqui */
	char* key;
	void* info;
	int height;
	struct node *left, *right;
};

struct TCD_istruct {
	int total;
	Node root;
};

// Funções auxiliares

int greater(int x, int y) {
	return (x > y) ? x : y;
}

int getHeight(Node n) {
	return (n) ? n->height : 0;
}

Node updateHeight(Node x, Node y) {
	x->height = greater(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = greater(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

Node rotateRight(Node n) {
	Node tmp;

	tmp = n->left;
	n->left = tmp->right;
	tmp->right = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

Node rotateLeft(Node n) {
	Node tmp;

	tmp = n->right;
	n->right = tmp->left;
	tmp->left = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

// Inicialização das estruturas

Node initNode() {
	return NULL;
}

// Inserções nas estruturas

Node insertNode(Node n, char* k, void* i) {
	if (!n) {
		n = malloc(sizeof(struct node));
		n->key = malloc(sizeof(char) * SIZE_KEY);
		strcpy(n->key, k);
		n->info = i;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
	}

	else {
		int cmp = strcmp(n->key, k);

		if (cmp > 0) {
			n->left = insertNode(n->left, k, i);
		}

		else if (cmp < 0) {
			n->right = insertNode(n->right, k, i);
		}

		else {
			n->info = i;
		}
		
		if (cmp) { /* balancear */
			int hl = getHeight(n->left);
			int hr = getHeight(n->right);
			n->height = greater(hl, hr) + 1;

			int bal = hl-hr;

			if (bal > 1) { /* right bal */
				int lcmp = strcmp(k, n->left->key);

				if (lcmp < 0) {
					return rotateRight(n);
				}
				
				else if (lcmp > 0) {
					n->left = rotateLeft(n->left);
					return rotateRight(n);
				}
			}

			else if (bal < -1) { /* left bal */
				int rcmp = strcmp(k, n->right->key);

				if (rcmp > 0) {
					return rotateLeft(n);
				}

				else if (rcmp < 0) {
					n->right = rotateRight(n->right);
					return rotateLeft(n);
				}
			}
		}
	}

	return n;
}

TAD_istruct insert(TAD_istruct a, char* k, void* i) {
	if (!a) {
		a = init();
	}

	a->root = insertNode(a->root, k, i);
	(a->total)++;

	return a;
}

// Testar existência de uma page numa TAD_istruct

int existsNode(Node n, char* k) {
	int res = 0;
	int cmp = strcmp(n->key, k);

	if (cmp == 0) {
		return 1;
	}
	else if (cmp > 0 && n->left) {
		res = existsNode(n->left, k);
	}
	else if (n->right) { /* cmp < 0 */
		res = existsNode(n->right, k);
	}

	return res;
}

int exists(TAD_istruct a, char* k) {
	int res = existsNode(a->root, k);
	return res;
}

int totalNodes(TAD_istruct a) {
	return (a) ? a->total : 0;
}

void freeNode(Node n) {
	if (n) {
		freeNode(n->right);
		freeNode(n->left);
		free(n->key);
		/* free info? */
		free(n);
	}
}

// Funções originais da interface

TAD_istruct init() {
	TAD_istruct a = malloc(sizeof(struct TCD_istruct));
	a->root = initNode();
	a->total = 0;
	return a;
}

/*
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		loadFile(qs, snaps_paths[i]);
	}

	return qs;
}*/


TAD_istruct clean(TAD_istruct qs) {
	if (qs) {
		freeNode(qs->root);
		free(qs);
	}

	return NULL;
}

/*
long all_articles(TAD_istruct qs);
long unique_articles(TAD_istruct qs);
long all_revisions(TAD_istruct qs);
long* top_10_contributors(TAD_istruct qs);
char* contributor_name(long contributor_id, TAD_istruct qs);
long* top_20_largest_articles(TAD_istruct qs);
char* article_title(long article_id, TAD_istruct qs);
long* top_N_articles_with_more_words(int n, TAD_istruct qs);
char** titles_with_prefix(char* prefix, TAD_istruct qs);
char* article_timestamp(long article_id, long revison_id, TAD_istruct qs);
*/