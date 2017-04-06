#include <stdlib.h>
#include <string.h>

#include "avl.h"

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

AVL initAvl() {
	AVL a = malloc(sizeof(struct avl));
	a->root = initNode();
	a->total = 0;
	return a;	
}

// Inserções nas estruturas

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
		/*
		void functionC(Node n, void* info) {
			(n->info->revisions)++;
			freeContributor(info);
		}
		
		void functionA(Node n, void* info) {
			int cap = n->info->revcapacity;
			int nr = n->info->revcount;
		
			if (nr == cap) {
				int size = getRevisionSize(); // size da struct revision
				realloc(n->info->revisions, size * cap * 2);
				n->info->capacity *= 2;
			}
		
			n->info->revisions[nr] = info->revisions[0];
			(n->info->revcount)++;
			(n->info->occurrences)++;
			
			freeArticle(info);
		}*/

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

// Testar existência de uma page numa AVL

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

int totalNodes(AVL a) {
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

AVL freeAvl(AVL a) {
	if (a) {
		freeNode(a->root);
		free(a);
	}

	return NULL;
}