#ifndef CONTRIBUTORS_H
#define CONTRIBUTORS_H

typedef struct contributor_set *CONTRIBUTOR_SET;
typedef struct contributor *CONTRIBUTOR;

/* API */

CONTRIBUTOR_SET initContributorSet();
CONTRIBUTOR initContributor();

CONTRIBUTOR_SET insertContributor(CONTRIBUTOR_SET cs, CONTRIBUTOR c);

CONTRIBUTOR setContributorID(CONTRIBUTOR c, char* id);
CONTRIBUTOR setUsername(CONTRIBUTOR c, char* u);
char* getContributorID(CONTRIBUTOR c);
char* getUsername(CONTRIBUTOR c);

#endif