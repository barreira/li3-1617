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

AVL initAvl();

AVL freeAvl(AVL a);

AVL insert(AVL a, void* i, void* (*f)(void*, void*, int*), int* flag);

void incrementCounters(Node n, void (*inc)(void*));

int getTotalNodes(AVL a);

void mapAVL(AVL a, void* acc, void* aux, void (*f)(void*, void*, void*));

void* findAndApply(AVL a, void* i, void* aux, void* (*f)(void*, void*));

#endif