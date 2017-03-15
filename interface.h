#ifndef INTERFACE_H
#define INTERFACE_H

AVL load(AVL qs, int nsnaps, char* snaps_paths[]);
AVL clean(AVL qs);

long all_articles(AVL qs);
long unique_articles(AVL qs);
long all_revisions(AVL qs);

#endif