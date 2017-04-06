#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "articles.h"
#include "contributors.h"
//#include "xmlparser.h"

struct TCD_istruct {
	ARTICLE_SET aset;
	CONTRIBUTOR_SET cset;
};

TAD_istruct init() {
	TAD_istruct s;

	s->aset = initArticleSet();
	s->cset = initContributorSet();

	return a;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		loadFile(qs, snaps_paths[i]);
	}

	return qs;
}

/*
TAD_istruct clean(TAD_istruct qs) {
	if (qs) {
		freeNode(qs->root);
		free(qs);
	}

	return NULL;
}*/

/*
long all_articles(TAD_istruct qs);
long unique_articles(TAD_istruct qs);
long all_revisions(TAD_istruct qs);
long* top_10_contributors(TAD_istruct qs);
char* contributor_name(long contributor_id, TAD_istruct qs);
long* top_20_largest_articles(TAD_istruct qs);
char* article_title(long article_id, TAD_istruct qs);
long* top_N_articles_with_more_words(int n, TAD_istruct qs);
char** titles_with_prefix(char* prefix, TAD_istruct qs);
char* article_timestamp(long article_id, long revison_id, TAD_istruct qs);
*/