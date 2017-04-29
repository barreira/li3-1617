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
 * @version 2017-04-29
 */

#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "articles.h"
#include "contributors.h"

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

/*
 * @brief Devolve o maior de dois inteiros
 *
 */
int greater(int x, int y)
{
	return (x > y) ? x : y;
}

/*
 * @brief Devolve a altura de um nó numa árvore
 *
 * @param n Nó de uma árvore
 */
int getHeight(Node n)
{
	return (n) ? n->height : 0;
}

/*
 * @brief Atualiza a altura de dois nós de uma árvore
 *
 * @param x Nó de uma árvore
 * @param y Nó de uma árvore 
 */
Node updateHeight(Node x, Node y)
{
	x->height = greater(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = greater(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

/* Rotações */

/*
 * @brief Efetua uma rotação à esquerda de uma árvore
 *
 * @param n Raiz da árvore
 */
Node rotateRight(Node n)
{
	Node tmp;

	tmp = n->left;
	n->left = tmp->right;
	tmp->right = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

/*
 * @brief Efetua uma rotação à esquerda de uma árvore
 *
 * @param n Raíz da árvore
 */
Node rotateLeft(Node n)
{
	Node tmp;

	tmp = n->right;
	n->right = tmp->left;
	tmp->left = n;
	tmp = updateHeight(n, tmp);

	return tmp;
}

/* Inits */

/*
 * @brief Inicializa um nó de uma árvore
 *
 * @param x Nó de uma árvore
 */
Node initNode()
{
	return NULL;
}

/*
 * @brief Inicializa uma árvore
 * 
 * Recebe como parâmetro um apontador para a função de comparação
 * dos nós da árvore.
 *
 * @param cmp Apontador para função de comparação dos nós
 */
AVL initAvl(int (*cmp)(const void*, const void*))
{
	AVL a = malloc(sizeof(struct avl));
	a->root = initNode();
	a->total = 0;
	a->cmp = cmp;
	return a;	
}

/* Inserts */

/*
 * @brief Efetua a inserção de um nó numa árvore
 *
 * @param a    Árvore onde se efetuará a inserção
 * @param n    Nodo atual da árvore (onde se tenta inserir)
 * @param i    Informação a inserir na árvore
 * @param f    Apontador para a função que trata de inserções repetidas na
               árvore
 * @param flag 
 */
Node insertNode(AVL a, Node n, void* i,
                void* (*f)(void* info, void* dup, int* flag), int* flag)
{
	if (!n) {
		n = malloc(sizeof(struct node));
		n->info = i;
		n->height = 0;
		n->left = NULL;
		n->right = NULL;
		(a->total)++;
	}

	else {
		int cmp = a->cmp(n->info, i);

		if (cmp > 0) {
			n->left = insertNode(a, n->left, i, f, flag);
		}

		else if (cmp < 0) {
			n->right = insertNode(a, n->right, i, f, flag);
		}

		else {

			// A função f, passada como parâmetro, trata dos casos em que já
			// haja um nodo com o id na árvore
			
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

/*
 * @brief Efetua a inserção de um nó numa árvore
 *
 * @param a Árvore onde se efetuará a inserção
 * @param i Informação a inserir na árvore
 * @param f Apontador para a função que trata de inserções repetidas na árvore
 */
AVL insert(AVL a, void* i, void* (*f)(void* info, void* dup, int* flag),
           int* flag)
{
	a->root = insertNode(a, a->root, i, f, flag);

	return a;
}

/* Frees */

/*
 * @brief Liberta o espaço ocupado por um nó de uma árvore
 * 
 * @param n Nó a libertar
 */
Node freeNode(Node n)
{
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

/*
 * @brief Liberta o espaço ocupado por uma árvore
 * 
 * @param n Árvore a libertar
 */
AVL freeAvl(AVL a)
{
	a->root = freeNode(a->root);
	free(a);
	a = NULL;
	return a;
}

/* Outras funções */

/*
 * @brief Devolve o número total de nós de uma árvore
 */
int getTotalNodes(AVL a)
{
	if (a == NULL) {
		return 0;
	}

	return a->total;
}

/*
 * @brief Incrementa os contadores de um nó de uma árvore
 *
 * @param n   Nó a incrementar
 * @param inc Apontador para função de incrementação dos contadores de um nó
 */
void incrementCounters(Node n, void (*inc)(void* info))
{
	inc(n->info);
}

/* Map */

/*
 * @brief Aplica uma função a um nó e às suas subárvores esquerda e direita
 *
 * @param n   Nó de uma árvore
 * @param acc Acumulador do resultado da aplicação da função a um nó
 * @param aux Variável auxiliar (opcional) à execução da função recebida
 * @param f   Apontador para a função a aplicar aos nós de uma árvore
 */
void mapAVL_aux(Node n, void* acc, void* aux, void (*f)(void* info, void* acc,
                void* aux))
{
	if (n != NULL) {
		mapAVL_aux(n->left, acc, aux, f);
		f(n->info, acc, aux);
		mapAVL_aux(n->right, acc, aux, f);
	}
}

/*
 * @brief Aplica uma função a todos os nós de uma árvore
 *
 * @param a   Árvore
 * @param acc Acumulador do resultado da aplicação da função a um nó
 * @param aux Variável auxiliar (opcional) à execução da função recebida
 * @param f   Apontador para a função a aplicar aos nós de uma árvore
 */
void mapAVL(AVL a, void* acc, void* aux, void (*f)(void* info, void* acc,
            void* aux))
{
	if (a != NULL) {
		mapAVL_aux(a->root, acc, aux, f);
	}
}

/* Finds */

/*
 * @brief Aplica uma função a um nó específico de uma árvore
 *
 * Primeiro procura, na árvore, o nó recebido como parâmetro e, de seguida,
 * aplica-lhe a função recebida como parâmetro.
 *
 * @param a   Árvore
 * @param i   Nó a procurar na árvore
 * @param aux Variável auxiliar (opcional) à execução da função recebida
 * @param f   Apontador para a função a aplicar ao nó
 */
void* findAndApply_aux(AVL a, Node n, void* i, void* aux,
                       void* (*f)(void* info, void* aux))
{
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

/*
 * @brief Aplica uma função a um nó específico de uma árvore
 *
 * Primeiro procura, na árvore, o nó recebido como parâmetro e, de seguida,
 * aplica-lhe a função recebida como parâmetro.
 *
 * @param a   Árvore
 * @param i   Nó a procurar na árvore
 * @param aux Variável auxiliar (opcional) à execução da função recebida
 * @param f   Apontador para a função a aplicar ao nó
 */
void* findAndApply(AVL a, void* i, void* aux, void* (*f)(void* info, void* aux))
{
	if (a != NULL) {
		return findAndApply_aux(a, a->root, i, aux, f);
	}

	return NULL;
}