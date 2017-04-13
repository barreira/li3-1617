/**
 * @file avl.c
 * @brief Definição de uma AVL genérica
 * 
 * Contém a definição da AVL genérica e respetivas funções.
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

#include "avl.h"
#include "articles.h"
#include "contributors.h"

#define SIZE 10

struct node {
	char* key;
	void* info;
	int height;
	struct node *left, *right;
};

struct avl {
	int total;
	Node root;	
};

/* Funções auxiliares */

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

/* Rotações */

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

/* Inits */

Node initNode() {
	/*
	Node n = malloc(sizeof(struct node));
	n->key = malloc(sizeof(char) * SIZE);
	n->info = NULL;
	n->height = 0;
	n->left = NULL;
	n->right = NULL;
	return n;*/
	return NULL;
}

AVL initAvl() {
	AVL a = malloc(sizeof(struct avl));
	a->root = initNode();
	a->total = 0;
	return a;	
}

/* Teste de existência */

int existsNode(Node n, char* k) {
	int res = 0;

	if (n == NULL) {
		return res;
	}
 
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

/* Inserts */

Node insertNode(Node n, char* k, void* i, void* (*f)(void* info, void* dup), int *total) {
	if (!n) {
		n = malloc(sizeof(struct node));
		n->key = k;
		n->info = i;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
		*total += 1;
	}

	else {
		int cmp = strcmp(n->key, k);

		if (cmp > 0) {
			n->left = insertNode(n->left, k, i, f, total);
		}

		else if (cmp < 0) {
			n->right = insertNode(n->right, k, i, f, total);
		}

		else { /* A função f, passada como parâmetro, trata dos casos em que já haja um nodo com o id na árvore */
			n->info = f(n->info, i);
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

AVL insert(AVL a, char* k, void* i, void* (*f)(void* info, void* dup)) {
	if (!a) {
		a = initAvl();
	}

	/*
	if (exists(a, k)) {
		(a->total)++;
	}*/

	a->root = insertNode(a->root, k, i, f, &(a->total));

	return a;
}

/* Frees */

Node freeNode(Node n) {
	if (n != NULL) {
		free(n->key);

		if (n->right != NULL) {
			n->right = freeNode(n->right);
		}

		if (n->left != NULL) {
			n->left = freeNode(n->left);
		}		

		free(n);
		n = NULL;	
	}
	// free info?
	return n;
}

AVL freeAvl(AVL a) {
	a->root = freeNode(a->root);
	free(a);
	a = NULL;
	return a;
}

/* Outras funções */

int getTotalNodes(AVL a) {
	if (a == NULL) {
		return 0;
	}

	return a->total;
}

void incrementCounters(Node n, void (*inc)(void* info)) {
	inc(n->info);
}

void* getInfo(Node n) {
	return n->info;
}

Node setInfo(Node n, void* info) {
	n->info = info;
	return n;
}

/* Queries */

long query1_aux(Node n, int acc) {
	if (n == NULL) {
		return 0;
	}

	acc += getOccurrences(n->info) + query1_aux(n->left, acc) + query1_aux(n->right, acc);

	return acc;
}

long query1(AVL a) {
	return query1_aux(a->root, 0);
}

long query3_aux(Node n, int acc) {
	if (n == NULL) {
		return 0;
	}

	acc += getRevCount(n->info) + query3_aux(n->left, acc) + query3_aux(n->right, acc);

	return acc;
}

long query3(AVL a) {
	return query3_aux(a->root, 0);
}

char* query5_aux(Node n, char* contributor_id) {
	if (n == NULL) {
		return NULL;
	}
 
	int cmp = strcmp(n->key, contributor_id);

	if (cmp == 0) {
		return getUsername((CONTRIBUTOR) n->info);
	}
	else if (cmp > 0 && n->left != NULL) {
		return query5_aux(n->left, contributor_id);
	}
	else if (n->right != NULL) { /* cmp < 0 */
		return query5_aux(n->right, contributor_id);
	}

	return NULL;
}

char* query5(AVL a, char* contributor_id) {
	return query5_aux(a->root, contributor_id);
}

char* query7_aux(Node n, char* article_id) {
	if (n == NULL) {
		return NULL;
	}
 
	int cmp = strcmp(n->key, article_id);

	if (cmp == 0) {
		REVISION r = getLastRevision((ARTICLE) n->info);
		return getTitle(r);
	}
	else if (cmp > 0 && n->left != NULL) {
		return query7_aux(n->left, article_id);
	}
	else if (n->right != NULL) { /* cmp < 0 */
		return query7_aux(n->right, article_id);
	}

	return NULL;
}

char* query7(AVL a, char* article_id) {
	return query7_aux(a->root, article_id);
}

int isPrefix(char* s, char* p) {
	int i;

	for (i = 0; s[i] == p[i] && s[i] != '\0' && p[i] != '\0'; i++);

	if (i == strlen(p)) {
		return 1;
	}

	return 0;
}

char** query9_aux(Node n, char* prefix, char** res) {
	if (n == NULL) {
		return res;
	}

	REVISION r = getLastRevision((ARTICLE) n->info);
	char* t = getTitle(r);

	if (isPrefix(t, prefix)) {
		int i;
		for (i = 0; res[i] != NULL; i++);
		res[i] = t;
	}

	query9_aux(n->left, prefix, res);
	query9_aux(n->right, prefix, res);

	return res;	
}

char** query9(AVL a, char* prefix, char** res) {
	return query9_aux(a->root, prefix, res);
}


char* query10_aux(Node n, char* article_id, char* revision_id) {
	if (n == NULL) {
		return NULL;
	}
 
	int cmp = strcmp(n->key, article_id);

	if (cmp == 0) {
		REVISION r = getRevision((ARTICLE) n->info, revision_id);
		if (r != NULL) {
			return getTimestamp(r);
		}
	}
	else if (cmp > 0 && n->left != NULL) {
		return query10_aux(n->left, article_id, revision_id);
	}
	else if (n->right != NULL) { /* cmp < 0 */
		return query10_aux(n->right, article_id, revision_id);
	}

	return NULL;
}

char* query10(AVL a, char* article_id, char* revision_id) {
	return query10_aux(a->root, article_id, revision_id);
}