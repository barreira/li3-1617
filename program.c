/**
 * @file program.c
 * @brief Módulo principal do projeto
 * 
 * Módulo responsável pelo chamamento da interface gráfica do menu ou, em
 * alternativa, por correr o programa sequencialmente (init -> load -> queries
 * -> clean). 
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#include <stdio.h>

#include "interface.h"
#include "menu.h"

int main()
{
	
	// Invocação do menu

	//menu();

	
	// Init

	TAD_istruct qs;

	qs = init(qs);


	// Load

    char* snaps[3];
    //snaps[0] = "../snapshot";
    snaps[0] = "../snapshot_dec16";
    snaps[1] = "../snapshot_jan17";
    snaps[2] = "../snapshot_fev17";	
	qs = load(qs, 3, snaps);


	// Queries

	printf("Q1: \t%ld\n\n", all_articles(qs));
	
	printf("Q2: \t%ld\n\n", unique_articles(qs));
	
	printf("Q3: \t%ld\n\n", all_revisions(qs));

	printf("Q4:");
    long* res4 = top_10_contributors(qs);
	for (int i = 0; i < 10; i++) { 
		if (i+1 >= 10)
			printf("\t%d - %ld\n", i+1, res4[i]);
		else
			printf("\t%d  - %ld\n", i+1, res4[i]);
	}

	printf("\nQ5: \t%s\n", contributor_name(28903366, qs));
	printf("Q5: \t%s\n", contributor_name(194203, qs));
	printf("Q5: \t%s\n\n", contributor_name(1000, qs));

	printf("Q6:");
    long* res6 = top_20_largest_articles(qs);
	for (int i = 0; i < 20; i++) { 
		if (i+1 >= 10)
			printf("\t%d - %ld\n", i+1, res6[i]);
		else
			printf("\t%d  - %ld\n", i+1, res6[i]);
	}

	printf("\nQ7: \t%s\n", article_title(15910, qs));
	printf("Q7: \t%s\n", article_title(25507, qs));
	printf("Q7: \t%s\n\n", article_title(1111, qs));
	
	printf("Q8:");
	long* res8 = top_N_articles_with_more_words(30, qs);
	for (int i = 0; i < 30; i++) {
		if (i+1 >= 10)
			printf("\t%d - %ld\n", i+1, res8[i]);
		else
			printf("\t%d  - %ld\n", i+1, res8[i]);
	} 
	
    printf("\nQ9:");
    char **res9 = titles_with_prefix("Anax", qs);
    for (int i = 0; res9[i] != NULL; i++) printf("\t%s\n", res9[i]);

	printf("\nQ10: \t%s\n", article_timestamp(12, 763082287, qs));
	printf("Q10: \t%s\n", article_timestamp(12, 755779730, qs));
	printf("Q10: \t%s\n", article_timestamp(12, 4479730, qs));

	// Clean

	qs = clean(qs);

	return 0;
}