/**
 * @file interface.h
 * @brief API do módulo da interface
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct TCD_istruct *TAD_istruct; // Estrutura principal do programa, que
                                         // contém todos os dados lidos das snapshots
                                         // disponibilizadas.

/************************************************************************************
 *                                    API                                           *
 ************************************************************************************/

/*
 * @brief Inicializa a estrutura de dados principal do programa.
 *
 * Deve ser a primeira função a ser executada pois só após a chamada desta
 * função, é que a estrutura de dados estará pronta a ser carregada.
 *
 * @return Devolve a estrutura inicializada
 */
TAD_istruct init();

/*
 * @brief Carrega a estrutura de dados principal do programa
 *
 * A estrutura de dados deve primeiro ser inicializada. O carregamento é feito
 * a partir dos ficheiros das snapshots cujo caminho é passado como parâmetro.
 *
 * @param qs          Estrutura para onde se deverão carregar os dados
 * @param nsnaps      Número de snapshots que deverão ser lidas
 * @param snaps_paths Caminhos onde se encontram os ficheiros das snapshots
 *
 * @return Devolve a estrutura carregada
 */
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]);

/*
 * @brief Query 1
 *
 * Calcula o número total de artigos encontrados, incluindo artigos
 * duplicados e novas revisões de artigos já existentes. 
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long all_articles(TAD_istruct qs);

/*
 * @brief Query 2
 *
 * Calcula o número de artigos únicos encontrados (i.e. artigos com
 * identificador único). Ou seja, não inclui artigos duplicados nem
 * novas revisões de artigos já existentes.
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long unique_articles(TAD_istruct qs);

/*
 * @brief Query 3
 *
 * Calcula o número total de revisões de artigos encontradas. Inclui quer
 * a versão base de um artigo, quer as restantes revisões feitas ao mesmo
 * posteriormente.
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long all_revisions(TAD_istruct qs);

/*
 * @brief Query 4
 *
 * Devolve um array com os IDs dos 10 contribuidores que contribuíram para
 * um maior número de revisões de artigos. O resultado é ordenado de forma
 * decrescente e, caso, existam contribuidores com um número igual de
 * contribuições, estes aparecem ordenados pelo seu ID (do menor para o maior).
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com o top 10 dos contribuidores que mais contribuíram
 */
long* top_10_contributors(TAD_istruct qs);

/*
 * @brief Query 5
 *
 * Devolve o username de um contribuidor cujo ID é passado como parâmetro. Caso
 * não exista nenhum contribuidor com esse ID, é devolvido NULL.
 *
 * @param contributor_id ID do contribuidor
 * @param qs             Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Nome do contribuidor (NULL caso não exista)
 */
char* contributor_name(long contributor_id, TAD_istruct qs);

/*
 * @brief Query 6
 *
 * Devolve um array com os IDs dos 20 artigos que possuem textos com um maior
 * tamanho (em bytes). Para cada artigo, é apenas contabilizado o maior tamanho
 * de todas as revisões do mesmo. O resultado é ordenado de forma decrescente
 * e, caso, existam artigos com um tamanho igual, estes aparecem ordenados pelo
 * seu ID (do menor para o maior).
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com o top 20 dos maiores artigos
 */
long* top_20_largest_articles(TAD_istruct qs);

/*
 * @brief Query 7
 *
 * Devolve o título de um artigo cujo ID é passado como parâmetro. São apenas
 * considerados os títulos das últimas revisões dos artigos. Caso não exista
 * nenhum artigo com esse ID, é devolvido NULL.
 *
 * @param article_id ID do artigo
 * @param qs         Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Título da última revisão de um artigo (NULL caso não exista)
 */
char* article_title(long article_id, TAD_istruct qs);

/*
 * @brief Query 8
 *
 * Devolve um array com os identificadores dos N artigos que possuem textos com um
 * maior número de palavras. Para cada artigo, é apenas contabilizado o texto com o
 * maior número de palavras de todas as revisões do mesmo. O resultado é ordenado de
 * forma decrescente e, caso, existam artigos com um número de palavras igual, estes
 * aparecem ordenados pelo seu ID (do menor para o maior).
 *
 * @param n  Tamanho do array
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com os N artigos com mais palavras
 */
long* top_N_articles_with_more_words(int n, TAD_istruct qs);

/*
 * @brief Query 9
 *
 * Devolve um array com os títulos dos artigos que começam pelo prefixo passado como
 * parâmetro. É apenas considerado o título da última revisão de cada artigo.
 *
 * @param prefix Prefixo a procurar
 * @param qs     Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com os títulos dos artigos começados pelo prefixo
 */
char** titles_with_prefix(char* prefix, TAD_istruct qs);

/*
 * @brief Query 10
 *
 * Devolve o timestamp de uma revisão de um dado artigo (valores passados como
 * parâmetro).
 *
 * @param article_id  ID do artigo
 * @param revision_id ID da revisão de um artigo
 * @param qs          Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Timestamp da revisão de um artigo (NULL caso não exista o artigo/revisão)
 */
char* article_timestamp(long article_id, long revison_id, TAD_istruct qs);


/*
 * @brief Liberta a estrutura de dados principal do programa
 *
 * Liberta o apontador para estrutura passada como parâmetro, bem como todo
 * e qualquer espaço previamente ocupado pela mesma.
 *
 * @param qs Estrutura que deve ser limpa
 *
 * @return Devolve o apontador recebido a NULL
 */
TAD_istruct clean(TAD_istruct qs);

#endif