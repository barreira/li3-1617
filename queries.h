#ifndef QUERIES_H
#define QUERIES_H

#include "contributors.h"
#include "articles.h"

typedef struct wikidata *WikiData; // Estrutura que guarda toda a informação
                                   // (artigos e contribuidores) lida das
                                   // snapshots

/******************************************************************************
 *                                  API                                       *
 ******************************************************************************/

/*
 * @brief Inicializa a estrutura da wikidata
 *
 * Inicializa o apontador para uma nova estrutura wikidata, inicializando também
 * os arrays dos contribuidores e dos artigos.
 *
 * @return Devolve o apontador para uma nova estrutura wikidata (inicializada)
 */
WikiData initWikiData();


/*
 * @brief Liberta o espaço ocupado por uma estrutura wikidata
 *
 * Liberta o apontador para a estrutura wikidata, libertando também os arrays
 * dos contribuidores e dos artigos.
 *
 * @param wd Estrutura do tipo wikidata a ser libertada
 *
 * @return Devolve o apontador recebido (colocado a NULL)
 */
WikiData freeWikiData(WikiData wd);


/*
 * @brief Insere um contribuidor na estrutura WikiData (no seu array de
          contribuidores)
 *
 * @param wd Estrutura wikidata
 * @param c  Contribuidor a inserir
 *
 * @return Estrutura wikidata com o novo contribuidor lá colocado
 */
WikiData insertContributor(WikiData wd, CONTRIBUTOR c);


/*
 * @brief Insere um artigo na estrutura WikiData (no seu array de artigos)
 *
 * @param wd   Estrutura wikidata
 * @param a    Artigo a inserir
 * @param flag Flag que aciona caso não seja necessário colocar o contribuidor
 *             correspondente deste artigo na árvore respetiva. Isto é, se houve
 *             ou não, de facto, uma nova contribuição. Ou seja, se se trata da
 *             inserção de um artigo repetido (e sem nova revisão).
 *
 * @return Estrutura wikidata com o novo artigo lá colocado (caso não seja
 *         duplicado)
 */
WikiData insertArticle(WikiData wd, ARTICLE a, int* flag);


/*
 * @brief Query 1
 *
 * Calcula o número total de artigos encontrados, incluindo artigos duplicados
 * e novas revisões de artigos já existentes.
 */
long query1(WikiData wd);


/*
 * @brief Query 2
 *
 * Calcula o número de artigos únicos encontrados (i.e. artigos com
 * identificador único). Ou seja, não inclui artigos duplicados nem novas
 * revisões de artigos já existentes.
 */
long query2(WikiData wd);


/*
 * @brief Query 3
 *
 * Calcula o número total de revisões de artigos encontradas. Inclui quer a
 * versão base de um artigo, quer as restantes revisões feitas ao mesmo
 * posteriormente.
 */
long query3(WikiData wd);


/*
 * @brief Query 4
 *
 * Devolve um array com os IDs dos 10 contribuidores que contribuíram para um
 * maior número de revisões de artigos. O resultado é ordenado de forma
 * decrescente e, caso, existam contribuidores com um número igual de
 * contribuições, estes aparecem ordenados pelo seu ID (do menor para o maior).
 *
 * @return Array ordenado com o top 10 dos contribuidores que mais contribuíram
 */
long* query4(WikiData wd);


/*
 * @brief Query 5
 *
 * Devolve o username de um contribuidor cujo ID é passado como parâmetro. Caso
 * não exista nenhum contribuidor com esse ID, é devolvido NULL.
 *
 * @param contributor_id ID do contribuidor
 * @param wd             Estrutura de dados (previamente carregada e
 *                       inicializada)
 *
 * @return Nome do contribuidor (NULL caso não exista)
 */
char* query5(WikiData wd, char* contributor_id);


/*
 * @brief Query 6
 *
 * Devolve um array com os IDs dos 20 artigos que possuem textos com um maior
 * tamanho (em bytes). Para cada artigo, é apenas contabilizado o maior tamanho
 * de todas as revisões do mesmo. O resultado é ordenado de forma decrescente
 * e, caso, existam artigos com um tamanho igual, estes aparecem ordenados pelo
 * seu ID (do menor para o maior).
 *
 * @return Array ordenado com o top 20 dos maiores artigos
 */
long* query6(WikiData wd);


/*
 * @brief Query 7
 *
 * Devolve o título de um artigo cujo ID é passado como parâmetro. São apenas
 * considerados os títulos das últimas revisões dos artigos. Caso não exista
 * nenhum artigo com esse ID, é devolvido NULL.
 *
 * @param article_id ID do artigo
 * @param wd         Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Título da última revisão de um artigo (NULL caso não exista)
 */
char* query7(WikiData wd, char* article_id);


/*
 * @brief Query 8
 *
 * Devolve um array com os identificadores dos N artigos que possuem textos com
 * um maior número de palavras. Para cada artigo, é apenas contabilizado o texto
 * com o maior número de palavras de todas as revisões do mesmo. O resultado é
 * ordenado de forma decrescente e, caso, existam artigos com um número de
 * palavras igual, estes aparecem ordenados pelo seu ID (do menor para o maior).
 *
 * @param n  Tamanho do array
 * @param wd Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com os N artigos com mais palavras
 */
long* query8(WikiData wd, int n);


/*
 * @brief Query 9
 *
 * Devolve um array com os títulos dos artigos que começam pelo prefixo passado
 * como parâmetro. É apenas considerado o título da última revisão de cada
 * artigo.
 *
 * @param prefix Prefixo a procurar
 * @param wd     Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com os títulos dos artigos começados pelo prefixo
 */
char** query9(WikiData wd, char* prefix);


/*
 * @brief Query 10
 *
 * Devolve o timestamp de uma revisão de um dado artigo (valores passados como
 * parâmetro).
 *
 * @param article_id  ID do artigo
 * @param revision_id ID da revisão de um artigo
 * @param wd          Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Timestamp da revisão de um artigo (NULL caso não exista o artigo ou a
           revisão)
 */
char* query10(WikiData wd, char* article_id, char* revision_id);

#endif
