/**
 * @file avl.h
 * @brief API do módulo da AVL genérica
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-29
 */

#ifndef AVL_H
#define AVL_H

typedef struct node *Node;
typedef struct avl *AVL;

/******************************************************************************
 *                                  API                                       *
 ******************************************************************************/

/*
 * @brief Inicializa uma árvore
 * 
 * Recebe como parâmetro um apontador para a função de comparação
 * dos nós da árvore.
 *
 * @param cmp Apontador para função de comparação dos nós
 */
AVL initAvl();


/*
 * @brief Liberta o espaço ocupado por uma árvore
 * 
 * @param n Árvore a libertar
 */
AVL freeAvl(AVL a);


/*
 * @brief Efetua a inserção de um nó numa árvore
 *
 * @param a Árvore onde se efetuará a inserção
 * @param i Informação a inserir na árvore
 * @param f Apontador para a função que trata de inserções repetidas na árvore
 */
AVL insert(AVL a, void* i, void* (*f)(void*, void*, int*), int* flag);


/*
 * @brief Incrementa os contadores de um nó de uma árvore
 *
 * @param n   Nó a incrementar
 * @param inc Apontador para função de incrementação dos contadores de um nó
 */
void incrementCounters(Node n, void (*inc)(void*));


/*
 * @brief Devolve o número total de nós de uma árvore
 */
int getTotalNodes(AVL a);


/*
 * @brief Aplica uma função a todos os nós de uma árvore
 *
 * @param a   Árvore
 * @param acc Acumulador do resultado da aplicação da função a um nó
 * @param aux Variável auxiliar (opcional) à execução da função recebida
 * @param f   Apontador para a função a aplicar aos nós de uma árvore
 */
void mapAVL(AVL a, void* acc, void* aux, void (*f)(void*, void*, void*));


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
void* findAndApply(AVL a, void* i, void* aux, void* (*f)(void*, void*));

#endif