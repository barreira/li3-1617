/**
 * @file contributors.c
 * @brief Definição das estruturas/funções relativas aos contribuidores
 * 
 * Contém a definição das estruturas que definem um contribuidor e respetivas
 * funções.
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
#include <stdio.h>

#include "contributors.h"

/******************************************************************************
 *                               ESTRUTURAS                                   *
 ******************************************************************************/

/* Estrutura responsável por guardar a informação relativa a um contribuidor */

struct contributor {
	char* id;       // Identificador de um contribuidor
	char* username; // Username de um contribuidor
	int revisions;  // Número de revisões (únicas) feitas por um contribuidor
};


/******************************************************************************
 *                                 INITS                                      *
 ******************************************************************************/

/*
 * @brief Inicializa a estrutura responsável por guardar um contribuidor
 *
 * Inicializa o apontador para o novo contribuidor (devolvendo-o no fim) e os
 * campos do novo contribuidor, colocando o número de revisões a 1 (pois se é
 * necessário inicializar um contribuidor é porque este apareceu numa snapshot
 * e, por isso, contribuiu para algum artigo) mas não alocando, ainda, espaço
 * para os campos do tipo char*.
 *
 * @return Devolve o apontador para um novo contribuidor (inicializado)
 */
CONTRIBUTOR initContributor()
{
	CONTRIBUTOR c = malloc(sizeof(struct contributor));

	c->id = NULL;
	c->username = NULL;
	c->revisions = 1;

	return c;
}


/******************************************************************************
 *                                FREES                                       *
 ******************************************************************************/

/*
 * @brief Liberta o espaço ocupado por um contribuidor
 *
 * Liberta os campos que, eventualmente, tinham sido alocados manualmente na
 * memória através de malloc (os campos do tipo char*), e o apontador para o
 * contribuidor passado como parâmetro que é, posteriormente, colocado a NULL.
 *
 * @param c Contribuidor a libertar
 */
CONTRIBUTOR freeContributor(CONTRIBUTOR c)
{
	free(c->id);
	free(c->username);

	free(c);
	c = NULL;

	return c;
}


/******************************************************************************
 *                                INSERTS                                     *
 ******************************************************************************/

/*
 * @brief Função que trata dos casos de inserção de um contribuidor duplicado
 * numa árvore
 *
 * Caso já exista o contribuidor que se tentou inserir na árvore, apenas se 
 * incrementa o número de revisões do contribuidor original da árvore. Além
 * disso, o nó que se estava a tentar inserir é libertado pois não é necessário.
 *
 * Um apontador para esta função é passado como parâmetro aquando da inserção de
 * um contribuidor numa árvore. Assim sendo, tem de obedecer à API do módulo da
 * AVL e, por isso, tem de receber a flag como parâmetro, mesmo não precisando
 * dela.
 *
 * @param info Nó original da árvore (contribuidor)
 * @param dup  Nó (duplicado) que se tentou inserir na árvore (contribuidor)
 * @param flag É sempre NULL pois não é utilizada neste caso (módulo dos
 *             contribuidores) mas tem de obedecer à API do módulo da AVL
 *
 * @return Retorna a informação atualiza do nó original da árvore
 */
void* duplicateContributor(void* info, void* dup, int* flag)
{
	((CONTRIBUTOR) info)->revisions += 1;
	dup = freeContributor((CONTRIBUTOR) dup);
	return info;
}


/******************************************************************************
 *                            GETTERS E SETTERS                               *
 ******************************************************************************/

/*
 * @brief Altera o valor do campo ID de um contribuidor
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para o contribuidor recebido como parâmetro, com
 *         o campo referente ao ID alterado.
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
 *
 * @return Devolve o apontador para o contribuidor recebido como parâmetro, com
 *         o campo referente ao username alterado. 
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
 * Em vez de retornar o valor do ID por referência, devolve uma cópia, alocando
 * o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo ID do contribuidor
 */
char* getContributorID(CONTRIBUTOR c)
{
	char* aux = NULL;

	if (c->id != NULL) {
		aux = malloc(strlen(c->id) + 1);
		strcpy(aux, c->id);
	}

	return aux;
}


/*
 * @brief Retorna o campo username de um contribuidor
 *
 * Em vez de retornar o valor do username por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo username do contribuidor 
 */
char* getUsername(CONTRIBUTOR c)
{
	char* aux = malloc(strlen(c->username) + 1);
	strcpy(aux, c->username);
	return aux;
}


/*
 * @brief Retorna o campo revisions de um contribuidor
 *
 * Em vez de retornar o valor de revisions por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo revisions do contribuidor 
 */
int getRevisions(CONTRIBUTOR c)
{
	int aux = c->revisions;
	return aux;
}