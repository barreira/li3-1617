/**
 * @file menu.c
 * @brief Módulo responsável pela interface gráfica do programa, permitindo assim a sua facilidade no teste e excução.
 * 
 * Está feito e pensado para que, quando se quiser executar uma querie, apenas com o número da querie,
 * o menu chame a querie.
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#include "menu.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

/*
 * Variáveis que calculam o tempo que determinada querie demorou a executar (em segundos).
 */

clock_t start, end;
double cpu_time_used;

/*
 * @brief Inicialização da estrutura, para que o apontador seja conhecido (neste caso é vazio).
 *
 * @return Apontador NULL
 */

TAD_istruct s = NULL;

/******************************************************************************
 *                                        MENU                                *
 ******************************************************************************/

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

        /*
         * @brief Inicializa a estrutura de dados principal do programa.
         *
         * Deve ser a primeira função a ser executada pois só após a chamada desta
         * função, é que a estrutura de dados estará pronta a ser carregada.
         *
         */

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

         /*
         * @brief Carrega a estrutura de dados principal do programa
         *
         * A estrutura de dados deve primeiro ser inicializada. O carregamento é feito
         * a partir dos ficheiros das snapshots cujo caminho é passado como parâmetro.
         *
         */

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

        /*
         * @brief Liberta a estrutura de dados principal do programa
         *
         * Liberta o apontador para estrutura passada como parâmetro, bem como todo e
         * qualquer espaço previamente ocupado pela mesma.
         *
         */

        else if (strcmp(opcao, "c") == 0)
        {
            start = clock();

            s = clean(s);

            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            sair=1;
            fflush(stdin);
            menu();            
        }

        /*
         * @brief Query 1
         *
         * Calcula o número total de artigos encontrados, incluindo artigos duplicados
         * e novas revisões de artigos já existentes. 
         *
         */

        else if (strcmp(opcao, "1")==0)
        {
        	start = clock();
            
            printf("Q1: %ld\n", all_articles(s));

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;            
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);

            sair=1;
            fflush(stdin);
            menu();
        }

        /*
         * @brief Query 2
         *
         * Calcula o número de artigos únicos encontrados (i.e. artigos com
         * identificador único). Ou seja, não inclui artigos duplicados nem novas
         * revisões de artigos já existentes.
         *
         */

        else if (strcmp(opcao, "2")==0)
        {
        	start = clock();

            printf("Q2: %ld\n", unique_articles(s));

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        /*
         * @brief Query 3
         *
         * Calcula o número total de revisões de artigos encontradas. Inclui quer a
         * versão base de um artigo, quer as restantes revisões feitas ao mesmo
         * posteriormente.
         *
         */

        else if (strcmp(opcao, "3")==0)
        {
        	start = clock();

            printf("Q3: %ld\n", all_revisions(s));
            
            end = clock();
 			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("Opção executada com sucesso em %f segundos!\n", cpu_time_used);
            
            sair=1;
            fflush(stdin);
            menu();
        }

        /*
         * @brief Query 4
         *
         * Devolve um array com os IDs dos 10 contribuidores que contribuíram para um
         * maior número de revisões de artigos. O resultado é ordenado de forma
         * decrescente e, caso, existam contribuidores com um número igual de
         * contribuições, estes aparecem ordenados pelo seu ID (do menor para o maior).
         *
         */

        else if (strcmp(opcao, "4")==0)
        {
        	start = clock();

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

        /*
         * @brief Query 5
         *
         * Devolve o username de um contribuidor cujo ID é passado como parâmetro. Caso
         * não exista nenhum contribuidor com esse ID, é devolvido NULL.
         *
         */

        else if (strcmp(opcao, "5")==0)
        {
        	start = clock();
            
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

        /*
         * @brief Query 6
         *
         * Devolve um array com os IDs dos 20 artigos que possuem textos com um maior
         * tamanho (em bytes). Para cada artigo, é apenas contabilizado o maior tamanho
         * de todas as revisões do mesmo. O resultado é ordenado de forma decrescente
         * e, caso, existam artigos com um tamanho igual, estes aparecem ordenados pelo
         * seu ID (do menor para o maior).
         *
         */

        else if (strcmp(opcao, "6")==0)
        {
        	start = clock();

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

        /*
         * @brief Query 7
         *
         * Devolve o título de um artigo cujo ID é passado como parâmetro. São apenas
         * considerados os títulos das últimas revisões dos artigos. Caso não exista
         * nenhum artigo com esse ID, é devolvido NULL.
         *
         */

        else if (strcmp(opcao, "7")==0)
        {
            start = clock();
            
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

        /*
         * @brief Query 8
         *
         * Devolve um array com os identificadores dos N artigos que possuem textos com
         * um maior número de palavras. Para cada artigo, é apenas contabilizado o texto
         * com o maior número de palavras de todas as revisões do mesmo. O resultado é
         * ordenado de forma decrescente e, caso, existam artigos com um número de
         * palavras igual, estes aparecem ordenados pelo seu ID (do menor para o maior).
         *
         */

        else if (strcmp(opcao, "8")==0)
        {
        	start = clock();
            
            int tam;
            printf("Insira um tamanho: ");
            scanf("%d", &tam);
            
            long* res = top_N_articles_with_more_words(tam, s);
            for (int i = 0; i < tam; i++) {
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

        /*
         * @brief Query 9
         *
         * Devolve um array com os títulos dos artigos que começam pelo prefixo passado
         * como parâmetro. É apenas considerado o título da última revisão de cada
         * artigo.
         *
         */

        else if (strcmp(opcao, "9")==0)
        {
        	start = clock();

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

        /*
         * @brief Query 10
         *
         * Devolve o timestamp de uma revisão de um dado artigo (valores passados como
         * parâmetro).
         *
         */

        else if (strcmp(opcao, "10")==0)
        {
        	start = clock();

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

        /*
         * @brief Termina a execução do programa.
         *
         */      

        else if (strcmp(opcao, "0")==0)
            sair=1;

        /*
         * @brief Opção inserida não é válida.
         *
         * Tem de se introduzir um valor entre 0 e 10 ou os caracteres i, l ou c para que
         * a opção do menu seja executada.
         * 
         */

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