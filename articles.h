/**
 * @file articles.h
 * @brief API do módulo dos artigos
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-29
 */

#ifndef ARTICLES_H
#define ARTICLES_H

#include "avl.h"

typedef struct article *ARTICLE;
typedef struct revision *REVISION;

/******************************************************************************
 *                                  API                                       *
 ******************************************************************************/

/*
 * @brief Inicializa a estrutura responsável por guardar um artigo
 *
 * Inicializa o apontador para um novo artigo (devolvendo-o no fim) e os seus
 * campos, mas não alocando, ainda, espaço para os campos do tipo char*.
 *
 * O array de revisões é inicializado alocando o espaço necessário para duas
 * revisões. Este número surge do cálculo do número médio de revisões para cada
 * artigo único (i.e. 40131 / 19867 = 2,02 ~= 2 revisões/artigo).
 *
 * @return Devolve o apontador para um novo contribuidor (inicializado)
 */
ARTICLE initArticle();


/*
 * @brief Inicializa a estrutura responsável por guardar uma revisão
 *
 * Inicializa o apontador para uma nova revisão (devolvendo-o no fim) e os seus 
 * campos, mas não alocando, ainda, espaço para os campos do tipo char*.
 *
 * @return Devolve o apontador para uma nova revisão (inicializada)
 */
REVISION initRevision();


/*
 * @brief Liberta o espaço ocupado por um artigo
 *
 * Liberta os campos que, eventualmente, tinham sido alocados manualmente na
 * memória através de malloc (os campos do tipo char*), o array de revisões (e
 * cada uma das revisões que lá estavam) e o apontador para o artigo passado
 * como parâmetro que é, posteriormente, colocado a NULL.
 *
 * @param a Artigo a libertar
 */
ARTICLE freeArticle(ARTICLE a);


/*
 * @brief Função que trata dos casos de inserção de um artigo duplicado numa
 *        árvore
 *
 * Caso já exista o artigo que se tentou inserir na árvore, tem de se verificar
 * se o que se está a inserir corresponde a uma nova revisão do artigo.
 *
 * Caso corresponda, coloca-se essa nova revisão no array de revisões do artigo
 * que já estava na árvore.
 * 
 * Caso não corresponda, apenas se aciona a flag que é recebida como parâmetro e
 * que sinalizará que não é necessário colocar o contribuidor correspondente na
 * árvore dos contribuidores (pois não houve, de facto, nenhuma nova
 * contribuição) .
 * 
 * Em ambos os casos, incrementa-se o número de ocorrências pois este campo
 * conta o número total de artigos (incluindo duplicados e novas revisões do
 * mesmo artigo).
 *
 * Um apontador para esta função é passado como parâmetro aquando da inserção de
 * um artigo numa árvore.
 *
 * @param info Nó original da árvore (artigo)
 * @param dup  Nó (duplicado) que se tentou inserir na árvore (artigo)
 * @param flag Aciona se não for necessário colocar o contribuidor
               correspondente na árvore respetiva (i.e. se houve ou não, de
			   facto, uma nova contribuição).
 *
 * @return Retorna a informação atualizada do nó original (artigo) da árvore
 */
void* duplicateArticle(void* info, void* dup, int* flag);


/*
 * @brief Adiciona a primeira revisão (previamente alocada) a um artigo
 *
 * @return Artigo com a nova revisão no seu array de revisões
 */
ARTICLE addFirstRevision(ARTICLE a, REVISION r);


/*
 * @brief Retorna o campo ID de um artigo
 *
 * Em vez de retornar o valor do ID por referência, devolve uma cópia, alocando
 * o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo ID do artigo
 */
char* getArticleID(ARTICLE a);


/*
 * @brief Retorna o campo ocurrences de um artigo
 *
 * Em vez de retornar o valor das ocorrências por referência, devolve uma cópia.
 *
 * @return Cópia do campo occurrences do artigo
 */
int getOccurrences(ARTICLE a);


/*
 * @brief Retorna o campo revcount de um artigo
 *
 * Em vez de retornar o valor das ocorrências por referência, devolve uma cópia.
 *
 * @return Cópia do campo revcount do artigo
 */
int getRevCount(ARTICLE a);


/*
 * @brief Retorna o campo title de um artigo
 *
 * Em vez de retornar o valor do título por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo title do artigo
 */
char* getTitle(REVISION r);
char* getTimestamp(REVISION r);


/*
 * @brief Altera o valor do campo ID de um artigo
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para o artigo recebido como parâmetro, com o
 *         campo referente ao ID alterado.
 */
ARTICLE setArticleID(ARTICLE a, char* id);


/*
 * @brief Altera o valor do campo ID de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao ID alterado.
 */
REVISION setRevisionID(REVISION r, char* id);


/*
 * @brief Altera o valor do campo timestamp de uma revisão
 *
 * É alocado espaço e efetuada uma cópia da timestamp recebida.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente à timestamp alterado.
 */
REVISION setTimestamp(REVISION r, char* t);


/*
 * @brief Altera o valor do campo title de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do título recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao título alterado.
 */
REVISION setTitle(REVISION r, char* t);


/*
 * @brief Altera o valor do campo textsize de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do textsize recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao textsize alterado.
 */
REVISION setTextSize(REVISION r, int ts);

/*
 * @brief Altera o valor do campo wc de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do wordcount recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao contador de palavras do texto alterado.
 */
REVISION setWordCount(REVISION r, int wc);


/*
 * @brief Retorna o tamanho da maior revisão de um artigo
 */
int getBiggestRevisionSize(ARTICLE a);


/*
 * @brief Retorna o maior wordcount das revisões de um artigo
 */
int getBiggestRevisionWC(ARTICLE a);


/*
 * @brief Retorna o título da última revisão de um artigo
 *
 * Em vez de retornar o valor do título por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do título da última revisão do artigo
 */
char* getLastRevisionTitle(ARTICLE a);


/*
 * @brief Retorna o timestamp de uma revisão de um artigo
 *
 * Em vez de retornar o valor do timestamp por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @param a           Artigo
 * @param revision_id ID da revisão da qual se pretende saber o timestamp
 *
 * @return Cópia do timestamp da última revisão do artigo (NULL caso não exista
 *         a revisão)
 */
char* getArticleRevisionTimestamp(ARTICLE a, char* revision_id);

#endif