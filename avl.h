#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct node *Node;
typedef struct avl *AVL;

/* API */

AVL initAvl();
AVL insert(AVL a, char* k, void* i, void (*f)(Node n, void* i));
int exists(AVL a, char* k);
AVL freeAVL(AVL a);

#endif