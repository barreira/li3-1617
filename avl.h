#ifndef AVL_H
#define AVL_H

// Estruturas

typedef struct article *ARTICLE;
typedef struct revision *REVISION;
typedef struct contribution *CONTRIBUTION;
typedef struct page *PAGE;
typedef struct avl *AVL;

// Init das estruturas

ARTICLE initArticle();
REVISION initRevision();
CONTRIBUTION initContribution();
PAGE initPage();
AVL initAvl();

// Insert

AVL insertAvl(AVL, char*, char*, char*, char*, char*, char*, char*);
PAGE insertPage(PAGE, char*, char*, char*, char*, char*, char*, char*);

















/*
TAD_istruct init();
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]);
TAD_istruct clean(TAD_istruct qs);
*/

#endif