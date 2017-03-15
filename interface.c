#include <stdlib.h>

#include "interface.h"
#include "avl.h"

AVL load(AVL qs, int nsnaps, char* snaps_paths[]);
AVL clean(AVL qs);

long all_articles(AVL qs);
long unique_articles(AVL qs);
long all_revisions(AVL qs);