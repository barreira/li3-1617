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
AVL insert(AVL a, char* k, void* i, void* (*f)(void* info, void* dup, int* flag), int* flag);
void incrementCounters(Node n, void (*inc)(void* info));
int exists(AVL a, char* k);
void* getInfo(Node n);
Node setInfo(Node n, void* info);
int getTotalNodes(AVL a);

void mapAVL(AVL a, void* acc, void (*f)(void* info, void* acc));

/* Queries */
/*
long query1(AVL a);
long query3(AVL a);
long* query4(AVL a, long** ids, long** revs, int size);
char* query5(AVL a, char* contributor_id);
long* query6(AVL a, long** ids, long** sizes, int size);
char* query7(AVL a, char* article_id);
long* query8(AVL a, long** ids, long** words, int size);
char** query9(AVL a, char* prefix, char*** res, int* size);
char* query10(AVL a, char* article_id, char* revision_id);

int getContributorRevsByID(AVL a, char* id);*/

#endif