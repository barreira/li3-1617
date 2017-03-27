#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "xmlparser.h"

#define SIZE_KEY 10

struct node {
	char* key;
	void* info;
	int height;
	struct node *left, *right;
};

struct avl {
	int total;
	NODE root;
};

// Funções auxiliares

int greater(int x, int y) {
	return (x > y) ? x : y;
}

int getHeight(NODE n) {
	return (n) ? n->height : 0;
}

NODE updateHeight(NODE x, NODE y) {
	x->height = greater(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = greater(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

NODE rotateRight(NODE n) {
	NODE tmp;

	tmp = n->left;
	n->left = tmp->right;
	tmp->right = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

NODE rotateLeft(NODE n) {
	NODE tmp;

	tmp = n->right;
	n->right = tmp->left;
	tmp->left = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

// Inicialização das estruturas

NODE initNode() {
	return NULL;
}

// Inserções nas estruturas

NODE insertNode(NODE n, char* k, void* i) {
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
		
		if (cmp) {
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

AVL insert(AVL a, char* k, void* i) {
	if (!a) {
		a = init();
	}

	a->root = insertNode(a->root, k, i);
	(a->total)++;

	return a;
}

// Testar existência de uma page numa AVL

int existsNode(NODE n, char* k) {
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

int exists(AVL a, char* k) {
	int res = existsNode(a->root, k);
	return res;
}

// Total de pages numa AVL

int totalNodes(AVL a) {
	return (a) ? a->total : 0;
}


// Funções originais da interface

AVL init() {
	AVL a = malloc(sizeof(struct avl));
	a->root = initNode();
	a->total = 0;
	return a;
}

/*
AVL load(AVL qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		loadFile(qs, snaps_paths[i]);
	}

	return qs;
}*/

/*
AVL clean(AVL qs) {

}

long all_articles(AVL qs);
long unique_articles(AVL qs);
long all_revisions(AVL qs);
long* top_10_contributors(AVL qs);
char* contributor_name(long contributor_id, AVL qs);
long* top_20_largest_articles(AVL qs);
char* article_title(long article_id, AVL qs);
long* top_N_articles_with_more_words(int n, AVL qs);
char** titles_with_prefix(char* prefix, AVL qs);
char* article_timestamp(long article_id, long revison_id, AVL qs);
*/