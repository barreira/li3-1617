/**
 * @file avl.h
 * @brief API do módulo da AVL genérica
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-09
 */

#ifndef AVL_H
#define AVL_H

typedef struct node *Node;
typedef struct avl *AVL;

/* API */

AVL initAvl();
AVL freeAvl(AVL a);
AVL insert(AVL a, char* k, void* i, void (*f)(Node n, void* i));
void incrementCounters(Node n, void (*inc)(void* info));
int exists(AVL a, char* k);
void* getInfo(Node n);
Node setInfo(Node n, void* info);
int getTotalNodes(AVL a);

#endif