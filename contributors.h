/**
 * @file contributors.h
 * @brief API do módulo dos contribuidores
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-09
 */

#ifndef CONTRIBUTORS_H
#define CONTRIBUTORS_H

#include "avl.h"

#define SET_SIZE_C 10

typedef struct contributor_set *CONTRIBUTOR_SET;
typedef struct contributor *CONTRIBUTOR;

/* API */

CONTRIBUTOR_SET initContributorSet();
CONTRIBUTOR initContributor();

CONTRIBUTOR_SET freeContributorSet(CONTRIBUTOR_SET cs);

CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c);

CONTRIBUTOR freeContributor(CONTRIBUTOR c);

AVL getContributorSubset(CONTRIBUTOR_SET cs, int pos);
CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id);
CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u);
char* getContributorID(CONTRIBUTOR c);
char* getUsername(CONTRIBUTOR c);
int getRevisions(CONTRIBUTOR c);

#endif