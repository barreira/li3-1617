#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "xmlparser.h"
#include "avl.h"

struct avl {
	int total;
	PAGE page;
};

AVL init() {
	AVL a = malloc(sizeof(struct avl)); /* é necessária esta linha? */
	a->page = initPage();
	a->total = 0;
	return a;
}


AVL load(AVL qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		loadFile(qs, snaps_paths[i]);
	}

	return qs;
}

/*
AVL clean(AVL qs) {

}

long all_articles(AVL qs);
long unique_articles(AVL qs);
long all_revisions(AVL qs);
long* top_10_contributors(AVL qs);
char* contributor_name(long contributor_id, AVL qs);
long* top_20_largest_articles(AVL qs);
char* article_title(long article_id, AVL qs);
long* top_N_articles_with_more_words(int n, AVL qs);
char** titles_with_prefix(char* prefix, AVL qs);
char* article_timestamp(long article_id, long revison_id, AVL qs);
*/