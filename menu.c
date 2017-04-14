#include "menu.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

TAD_istruct s = NULL;

int menu()
{
    char opcao[1];
    int sair=0;
    
    printf("\n******************************************************************************************\n");
    printf("*                                          MENU                                          *\n");
    printf("******************************************************************************************\n");
    printf("* i) Init                                                                                *\n");
    printf("* l) Load                                                                                *\n");
    printf("* c) Clean                                                                               *\n");
    printf("* 1) all_articles                                                                        *\n");
    printf("* 2) unique_articles                                                                     *\n");
    printf("* 3) all_revisions                                                                       *\n");
    printf("* 4) top_10_contributors                                                                 *\n");
    printf("* 5) contributor_name                                                                    *\n");
    printf("* 6) top_20_largest_articles                                                             *\n");
    printf("* 7) article_title                                                                       *\n");
    printf("* 8) top_N_articles_with_more_words                                                      *\n");
    printf("* 9) titles_with_prefix                                                                  *\n");
    printf("* 10) article_timestamp                                                                  *\n");
    printf("* 0) Sair                                                                                *\n");
    printf("******************************************************************************************\n\n");
    printf("Selecione a opção que pretende realizar: ");

    scanf("%s", opcao);
    printf("\n");

    while(sair!=1)
    {   
        if (strcmp(opcao, "i") == 0)
        {
            start = clock();

            s = init();

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "l") == 0)
        {
            start = clock();

            char* snaps[3];
            //snaps[0] = "../snapshot";
            snaps[0] = "../snapshot_dec16";
            snaps[1] = "../snapshot_jan17";
            snaps[2] = "../snapshot_fev17";
            s = load(s, 3, snaps);

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            sair=1;
            fflush(stdin);
            menu();            
        }

        else if (strcmp(opcao, "c") == 0)
        {
            start = clock();

            //fazer clean
            s = clean(s);

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            sair=1;
            fflush(stdin);
            menu();            
        }

        else if (strcmp(opcao, "1")==0)
        {
        	start = clock();
            
            //Query 1
            printf("Q1: %ld\n", all_articles(s));

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;            
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "2")==0)
        {
        	start = clock();

            //Query 2
            printf("Q2: %ld\n", unique_articles(s));

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "3")==0)
        {
        	start = clock();

            //Query 3
            printf("Q3: %ld\n", all_revisions(s));
            
            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "4")==0)
        {
        	start = clock();

            //Query 4
            int i;
            long* res = top_10_contributors(s);

            printf("Q4: Top 10 dos contribuidores com maior número de revisões:\n");

        	for (i = 0; i < 10; i++) {
        		printf("%d - %ld\n", i+1, res[i]);
        	}

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "5")==0)
        {
        	start = clock();
            
            //Query 5
            char id[100];
            printf("Insira um id de um contribuidor: ");
            scanf("%s", id);
            char* res = contributor_name(atol(id), s);
            if (res != NULL) {
                printf("Q5: O username do contribuidor %s é %s.\n", id, res);
            }
            else {
                printf("Q5: O contribuidor %s não existe.\n", id);
            }
            
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "6")==0)
        {
        	start = clock();

            //Query 6
        	int i;
            long* res = top_20_largest_articles(s);

            printf("Q9: Top 20 dos artigos com maior texto:\n");

        	for (i = 0; i < 20; i++) {
        		printf("%d - %ld\n", i+1, res[i]);
        	}


            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "7")==0)
        {
            start = clock();
            
            //Query 7
            char id[100];
            printf("Insira um id de um artigo: ");
            scanf("%s", id);
            
            char* res = article_title(atol(id), s);
            if (res != NULL) {
                printf("Q7: O título do artigo %s é %s.\n", id, res);
            }
            else {
                printf("Q7: O artigo %s não existe.\n", id);
            }

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "8")==0)
        {
        	start = clock();
            
            //Query 8

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "9")==0)
        {
        	start = clock();

            //Query 9
            char prefix[100];
            printf("Insira um prefixo: ");
            scanf("%s", prefix);

            char **res = titles_with_prefix(prefix, s);

            if (res != NULL) {
                int i;

                printf("Q9: Artigos cujo título começa por %s:\n", prefix);

                for (i = 0; res[i] != NULL; i++) {
                    printf("%s\n", res[i]);
                }
                
            }
            else {
                printf("Q9: Não existem artigos cujo título tenha %s como prefixo.\n", prefix);
            }

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "10")==0)
        {
        	start = clock();

            //Query 10
            char a_id[100];
            printf("Insira um id de um artigo: \n");
            scanf("%s", a_id);

            char r_id[100];
            printf("Insira um id de uma revisão: \n");
            scanf("%s", r_id);            
            
            char* res = article_timestamp(atol(a_id), atol(r_id), s);

            if (res != NULL) {
                printf("Q10: A revisão %s do artigo %s tem o timestamp %s.\n", a_id, r_id, res);
            }
            else {
                printf("Q10: O artigo %s ou a revisão %s não existem.\n", a_id, r_id);
            }

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }       

        else if (strcmp(opcao, "0")==0)
            sair=1;

        else
        {
            printf("Opção inexistente! Deverá selecionar um valor entre 0 e 10 ou os caracteres i, l ou c.\n");
            printf("Selecione a opção que pretende realizar: ");
            scanf("%s", opcao);
            printf("\n");
        }
    }

    return 0;
}