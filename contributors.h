/**
 * @file contributors.h
 * @brief API do módulo dos contribuidores
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-29
 */

#ifndef CONTRIBUTORS_H
#define CONTRIBUTORS_H

#include "avl.h"

typedef struct contributor *CONTRIBUTOR;

/******************************************************************************
 *                                  API                                       *
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
CONTRIBUTOR initContributor();


/*
 * @brief Liberta o espaço ocupado por um contribuidor
 *
 * Liberta os campos que, eventualmente, tinham sido alocados manualmente na
 * memória através de malloc (os campos do tipo char*), e o apontador para o
 * contribuidor passado como parâmetro que é, posteriormente, colocado a NULL.
 *
 * @param c Contribuidor a libertar
 */
CONTRIBUTOR freeContributor(CONTRIBUTOR c);


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
 * @param info Nó original da árvore
 * @param dup  Nó (duplicado) que se tentou inserir na árvore
 * @param flag É sempre NULL pois não é utilizada neste caso (módulo dos
 *             contribuidores) mas tem de obedecer à API do módulo da AVL
 *
 * @return Retorna a informação atualiza do nó original da árvore
 */
void* duplicateC(void* info, void* dup, int *flag);


/*
 * @brief Altera o valor do campo ID de um contribuidor
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para o contribuidor recebido como parâmetro, com
 *         o campo referente ao ID alterado.
 */
CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id);


/*
 * @brief Altera o valor do campo username de um contribuidor
 *
 * É alocado espaço e efetuada uma cópia do username recebido.
 *
 * @return Devolve o apontador para o contribuidor recebido como parâmetro, com
 *         o campo referente ao username alterado. 
 */
CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u);


/*
 * @brief Retorna o campo ID de um contribuidor
 *
 * Em vez de retornar o valor do ID por referência, devolve uma cópia, alocando
 * o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo ID do contribuidor
 */
char* getContributorID(CONTRIBUTOR c);


/*
 * @brief Retorna o campo username de um contribuidor
 *
 * Em vez de retornar o valor do username por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo username do contribuidor 
 */
char* getUsername(CONTRIBUTOR c);


/*
 * @brief Retorna o campo revisions de um contribuidor
 *
 * Em vez de retornar o valor de revisions por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo revisions do contribuidor 
 */
int getRevisions(CONTRIBUTOR c);

#endif