/**
 * @file articles.h
 * @brief API do módulo dos artigos
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-09
 */

#ifndef ARTICLES_H
#define ARTICLES_H

#include "avl.h"

typedef struct article *ARTICLE;
typedef struct revision *REVISION;

/* API */

ARTICLE initArticle();
REVISION initRevision();

void* duplicateA(void* info, void* dup, int* flag);
/*ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a, int* flag);*/
ARTICLE addRevision(ARTICLE a, REVISION r);

REVISION getRevision(ARTICLE a, char* revision_id);
REVISION getLastRevision(ARTICLE a);
char* getArticleID(ARTICLE a);
char* getTitle(REVISION r);
char* getTimestamp(REVISION r);

ARTICLE setArticleID(ARTICLE a, char* id);
REVISION setRevisionID(REVISION r, char* id);
REVISION setTimestamp(REVISION r, char* t);
REVISION setTitle(REVISION r, char* t);
REVISION setTextSize(REVISION r, int ts);
REVISION setWordCount(REVISION r, int wc);

/* Queries */

long getOccurrences(void* i);
long getRevCount(void *i);
int getBiggestRevisionSize(ARTICLE a);
int getBiggestRevisionWC(ARTICLE a);
char* getLastRevisionTitle(ARTICLE a);
char* getArticleRevisionTimestamp(ARTICLE a, char* revision_id);

#endif