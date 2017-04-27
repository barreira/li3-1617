#ifndef QUERIES_H
#define QUERIES_H

#include "contributors.h"
#include "articles.h"

typedef struct wikidata *WikiData;
//typedef struct contributorset *ContributorSet;
//typedef struct articleset *ArticleSet;

/* API */

WikiData initWikiData();

WikiData freeWikiData(WikiData wd);

WikiData insertContributor(WikiData wd, CONTRIBUTOR c);
WikiData insertArticle(WikiData wd, ARTICLE a, int* flag);

long query1(WikiData wd);
long query2(WikiData wd);
long query3(WikiData wd);
long* query4(WikiData wd);
char* query5(WikiData wd, char* contributor_id);
long* query6(WikiData wd);
char* query7(WikiData wd, char* article_id);
long* query8(WikiData wd, int n);
char** query9(WikiData wd, char* prefix);
char* query10(WikiData wd, char* article_id, char* revision_id);

#endif
