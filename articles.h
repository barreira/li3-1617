#ifndef ARTICLES_H
#define ARTICLES_H

typedef struct article_set *ARTICLE_SET;
typedef struct article *ARTICLE;
typedef struct revision *REVISION;

/* API */

ARTICLE_SET initArticleSet();
ARTICLE initArticle();
REVISION initRevision();

ARTICLE_SET insertArticle(ARTICLE_SET as, ARTICLE a);
ARTICLE addRevision(ARTICLE a, REVISION r);

ARTICLE setArticleID(ARTICLE a, char* id);
REVISION setRevisionID(REVISION r, char* id);
REVISION setTimestamp(REVISION r, char* t);
REVISION setTitle(REVISION r, char* t);
REVISION setTextSize(REVISION r, int ts);
REVISION setWordCount(REVISION r, int wc);

#endif