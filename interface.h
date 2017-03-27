#ifndef INTERFACE_H
#define INTERFACE_H

// TCD_istruct = avl; TAD_istruct = AVL
// typedef struct TCD_istruct *TAD_istruct;

typedef struct node *NODE;
typedef struct avl *AVL;

AVL init();
AVL load(AVL qs, int nsnaps, char* snaps_paths[]);

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

AVL clean(AVL qs);

#endif