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
	void* info;
	int height;
	struct node *left, *right;
};

struct avl {
	int total;
	Node root;
	int (*cmp)(const void*, const void*);	
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
	return NULL;
}

AVL initAvl(int (*cmp)(const void*, const void*)) {
	AVL a = malloc(sizeof(struct avl));
	a->root = initNode();
	a->total = 0;
	a->cmp = cmp;
	return a;	
}

/* Teste de existência */
/*
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
	else if (n->right) { // cmp < 0
		res = existsNode(n->right, k);
	}

	return res;
}

int exists(AVL a, char* k) {
	int res = existsNode(a->root, k);
	return res;
}*/

/* Inserts */

Node insertNode(AVL a, Node n, void* i, void* (*f)(void* info, void* dup, int* flag), int* total, int* flag) {
	if (!n) {
		n = malloc(sizeof(struct node));
		n->info = i;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
		*total += 1;
	}

	else {
		int cmp = a->cmp(n->info, i);

		if (cmp > 0) {
			n->left = insertNode(a, n->left, i, f, total, flag);
		}

		else if (cmp < 0) {
			n->right = insertNode(a, n->right, i, f, total, flag);
		}

		else { /* A função f, passada como parâmetro, trata dos casos em que já haja um nodo com o id na árvore */
			n->info = f(n->info, i, flag);
		}
		
		if (cmp) { /* balancear */
			int hl = getHeight(n->left);
			int hr = getHeight(n->right);
			n->height = greater(hl, hr) + 1;

			int bal = hl-hr;

			if (bal > 1) { /* right bal */
				int lcmp = a->cmp(i, n->left->info);

				if (lcmp < 0) {
					return rotateRight(n);
				}
				
				else if (lcmp > 0) {
					n->left = rotateLeft(n->left);
					return rotateRight(n);
				}
			}

			else if (bal < -1) { /* left bal */
				int rcmp = a->cmp(i, n->right->info);

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

AVL insert(AVL a, void* i, void* (*f)(void* info, void* dup, int* flag), int* flag) {
	a->root = insertNode(a, a->root, i, f, &(a->total), flag);

	return a;
}

/* Frees */

Node freeNode(Node n) {
	if (n != NULL) {
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

/* Map */

void mapAVL_aux(Node n, void* acc, void* aux, void (*f)(void* info, void* acc, void* aux)) {
	if (n != NULL) {
		mapAVL_aux(n->left, acc, aux, f);
		f(n->info, acc, aux);
		mapAVL_aux(n->right, acc, aux, f);
	}
}

void mapAVL(AVL a, void* acc, void* aux, void (*f)(void* info, void* acc, void* aux)) {
	if (a != NULL) {
		mapAVL_aux(a->root, acc, aux, f);
	}
}

/* Finds */

void* findAndApply_aux(AVL a, Node n, void* i, void* aux, void* (*f)(void* info, void* aux)) {
	if (n == NULL) {
		return NULL;
	}
 
	int cmp = a->cmp(n->info, i);

	if (cmp == 0) {
		return f(n->info, aux);
	}
	else if (cmp > 0 && n->left != NULL) {
		return findAndApply_aux(a, n->left, i, aux, f);
	}
	else if (n->right != NULL) { /* cmp < 0 */
		return findAndApply_aux(a, n->right, i, aux, f);
	}

	return NULL;
}

void* findAndApply(AVL a, void* i, void* aux, void* (*f)(void* info, void* aux)) {
	if (a != NULL) {
		return findAndApply_aux(a, a->root, i, aux, f);
	}

	return NULL;
}