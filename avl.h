#ifndef AVL_H
#define AVL_H

#include "interface.h"

// Estruturas

typedef struct contribution *CONTRIBUTION;
typedef struct revision *REVISION;
typedef struct page *PAGE;

// Funções de inicialização das estruturas

PAGE initPage();

// Funções de inserção nas estruturas

AVL insert(AVL a, char* a_id, char* r_id, char* timestamp, char* title, char* text, char* c_id, char* name);

// Outras funções

int exists(AVL a, char* a_id);
int totalPages(AVL a);

#endif