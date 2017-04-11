#include "menu.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

TAD_istruct s = NULL;

int menu()
{
    char opcao[1], op[1];
    int sair=0, flag=0;
    
    printf("\n******************************************************************************************\n");
    printf("*                                          MENU                                          *\n");
    printf("******************************************************************************************\n");
    printf("* i) Init                                                                                *\n");
    printf("* l) Load                                                                                *\n");
    printf("* c) Clean                                                                               *\n");
    printf("* 1) all_articles                                                                        *\n");
    printf("* 2) unique_articles                                                                     *\n");
    printf("* 3) Quantas revisões foram efetuadas naqueles backups.                                  *\n");
    printf("* 4) 10 autores que contribuíram para um maior número de versões de artigos.             *\n");
    printf("* 5) Nome do autor com um determinado identificador.                                     *\n");
    printf("* 6) 20 artigos que possuem textos com um maior tamanho.                                 *\n");
    printf("* 7) Título do artigo com um determinado identificador.                                  *\n");
    printf("* 8) Identificadores dos N artigos que possuem textos com um maior número de palavras.   *\n");
    printf("* 9) Lista de títulos de artigos que começam com um determinado prefixo.                 *\n");
    printf("* 10) Timestamp para uma certa revisão de um artigo.                                     *\n");
    printf("* 0) Sair                                                                                *\n");
    printf("******************************************************************************************\n\n");
    printf("Selecione a opção que pretende realizar: ");

    scanf("%s", opcao);
    printf("\n");

    while(sair!=1)
    {   
        if (strcmp(opcao, "i") == 0)
        {
            s = init();
            flag=1;
            sair=1;
            fflush(stdin);
            menu();
        }

        else if (strcmp(opcao, "l") == 0)
        {
            char* snaps[3];
            snaps[0] = "snapshot_dec16";
            snaps[1] = "snapshot_jan17";
            snaps[2] = "snapshot_fev17";
            s = load(s, 3, snaps);

            flag=1;
            sair=1;
            fflush(stdin);
            menu();            
        }

        else if (strcmp(opcao, "1")==0)
        {
            printf("Q1: %ld\n", all_articles(s));
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Q1: %ld\n", all_articles(s));
                    printf("\nDeseja executar esta query novamente?(S/N): ");
                    scanf("%s", op);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "2")==0)
        {
            //query2();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Qual a letra inicial do produto a escolher? (A, B, ..., Z) ");
                    //scanf("%s",l);
                    //query2(l);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if(strcmp(opcao, "3")==0)
        {
            //query3();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", (char *) op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {

                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "4")==0)
        {
            //query4();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query4();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "5")==0)
        {
            //query5();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query5();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "6")==0)
        {
            //query6();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {

                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "7")==0)
        {
            //query7();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query7();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "8")==0)
        {
            //query8();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {

                    //query8(p, f);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if (strcmp(opcao, "9")==0)
        {
            //query9();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {

                    //query9(c,m);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        else if(strcmp(opcao, "10")==0)
        {
            //query10();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query10();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }

        
        else if (strcmp(opcao, "0")==0)
            sair=1;

        else
        {
            printf("Opção inexistente! Deverá seleccionar um valor entre 0 e 12.\n");
            printf("Seleccione a opção que pretende realizar: ");
            scanf("%s", opcao);
            printf("\n");
        }
    }
    return 0;
}
