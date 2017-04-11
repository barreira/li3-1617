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

/* Inserts */

Node insertNode(Node n, char* k, void* i, void (*f)(Node n, void* i)) {
	if (!n) {
		n = malloc(sizeof(struct node));
		n->key = k;
		n->info = i;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
	}

	else {
		int cmp = strcmp(n->key, k);

		if (cmp > 0) {
			n->left = insertNode(n->left, k, i, f);
		}

		else if (cmp < 0) {
			n->right = insertNode(n->right, k, i, f);
		}

		else { /* A função f, passada como parâmetro, trata dos casos em que já haja um nodo com o id na árvore */
			f(n, i);
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

AVL insert(AVL a, char* k, void* i, void (*f)(Node n, void* i)) {
	if (!a) {
		a = initAvl();
	}

	a->root = insertNode(a->root, k, i, f);
	(a->total)++;

	return a;
}

/* Teste de existência */

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

int exists(AVL a, char* k) {
	int res = existsNode(a->root, k);
	return res;
}

/* Frees */

Node freeNode(Node n) {
	n->right = freeNode(n->right);
	n->left = freeNode(n->left);
	free(n->key);
	// free info?
	free(n);
	n = NULL;
	return n;
}

AVL freeAvl(AVL a) {
	a->root = freeNode(a->root);
	free(&(a->total));
	free(a);
	a = NULL;
	return a;
}

/* Outras funções */

int getTotalNodes(AVL a) {
	return (a) ? a->total : 0;
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