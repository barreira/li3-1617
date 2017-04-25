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

typedef struct contributor *CONTRIBUTOR;

/* API */

CONTRIBUTOR initContributor();

void* duplicateC(void* info, void* dup, int *flag);
/*CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c);*/

CONTRIBUTOR freeContributor(CONTRIBUTOR c);

CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id);
CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u);
char* getContributorID(CONTRIBUTOR c);
char* getUsername(CONTRIBUTOR c);
int getRevisions(CONTRIBUTOR c);

#endif