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
 * @version 2017-04-28
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

/*
 * @brief Inicializa a estrutura responsável por guardar um contribuidor
 */
CONTRIBUTOR initContributor() {
	CONTRIBUTOR c = malloc(sizeof(struct contributor));
	c->id = NULL;
	c->username = NULL;
	c->revisions = 1;
	return c;
}

/* Frees */

/*
 * @brief Liberta o espaço ocupado por um contribuidor
 *
 * @param c Nó a libertar
 */
CONTRIBUTOR freeContributor(CONTRIBUTOR c) {
	free(c->id);
	free(c->username);
	free(c);
	c = NULL;
	return c;
}

/* Inserts */

/*
 * @brief Função que trata dos casos de inserção de um contribuidor duplicado numa árvore
 *
 * Caso já exista o contribuidor que se tentou inserir na árvore, apenas se incrementa o
 * número de revisões do contribuidor original da árvore. Além disso, o nó que se estava
 * a tentar inserir é libertado pois não é necessário.
 *
 * Um apontador para esta função é passado como parâmetro aquando da inserção de um
 * contribuidor numa árvore. Assim sendo, tem de obedecer à API do módulo da AVL e, por
 * isso, tem de receber a flag como parâmetro, mesmo não precisando dela.
 *
 * @param info Nó original da árvore
 * @param dup  Nó (duplicado) que se tentou inserir na árvore
 * @param flag 
 *
 * @return Retorna a informação atualiza do nó original da árvore
 */
void* duplicateC(void* info, void* dup, int* flag) {
	((CONTRIBUTOR) info)->revisions += 1;
	dup = freeContributor((CONTRIBUTOR) dup);
	return info;
}

/* Getters e Setters */

/*
 * @brief Altera o valor do campo ID de um contribuidor
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 */
CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id)
{
	c->id = malloc(strlen(id) + 1);
	strcpy(c->id, id);
	return c;
}

/*
 * @brief Altera o valor do campo username de um contribuidor
 *
 * É alocado espaço e efetuada uma cópia do username recebido.
 */
CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u)
{
	c->username = malloc(strlen(u) + 1);
	strcpy(c->username, u);
	return c;
}

/*
 * @brief Retorna o campo ID de um contribuidor
 *
 * Em vez de retornar o valor do ID por referência, devolve 
 *
 *
 */
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