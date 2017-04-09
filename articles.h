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

typedef struct article_set *ARTICLE_SET;
typedef struct article *ARTICLE;
typedef struct revision *REVISION;

/* API */

ARTICLE_SET initArticleSet();
ARTICLE initArticle();
REVISION initRevision();

ARTICLE_SET freeArticleSet(ARTICLE_SET as);

ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a);
ARTICLE addRevision(ARTICLE a, REVISION r);

ARTICLE setArticleID(ARTICLE a, char* id);
REVISION setRevisionID(REVISION r, char* id);
REVISION setTimestamp(REVISION r, char* t);
REVISION setTitle(REVISION r, char* t);
REVISION setTextSize(REVISION r, int ts);
REVISION setWordCount(REVISION r, int wc);

#endif