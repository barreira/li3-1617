#ifndef QUERIES_H
#define QUERIES_H

#include "contributors.h"
#include "articles.h"

typedef struct wikidata *WikiData;
typedef struct contributorset *ContributorSet;
typedef struct articleset *ArticleSet;

/* API */

WikiData initWikiData();

WikiData freeWikiData(WikiData wd);

WikiData insertContributor(WikiData wd, CONTRIBUTOR c);
WikiData insertArticle(WikiData wd, ARTICLE a, int* flag);

long query1(WikiData wd);

#endif
