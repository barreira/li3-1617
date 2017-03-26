#ifndef AVL_H
#define AVL_H

// Estruturas

typedef struct contribution *CONTRIBUTION;
typedef struct revision *REVISION;
typedef struct page *PAGE;

// Funções de inicialização das estruturas

PAGE initPage();

// Funções de inserção nas estruturas

AVL insert(AVL, char*, char*, char*, char*, char*, char*, char*);

// Outras funções

int exists(AVL, char*);
int totalPages(AVL);

#endif