#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct node *Node;
typedef struct avl *AVL;

/* API */

AVL initAvl();
AVL freeAvl(AVL a);
AVL insert(AVL a, char* k, void* i, void (*f)(Node n, void* i));
void incrementCounters(Node n, void (*inc)(void* info));
int exists(AVL a, char* k);
void* getInfo(Node n);

#endif