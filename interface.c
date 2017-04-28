/**
 * @file interface.c
 * @brief Definição de todas as funções pertencentes à interface do programa
 * 
 * Contém as funções principais do programa: init, load, queries e clean.
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#include <stdlib.h>
#include <stdio.h>

#include "interface.h"
#include "avl.h"
#include "contributors.h"
#include "articles.h"
#include "queries.h"
#include "xmlparser.h"

/*
 * Estrutura principal do programa, que contém todos os dados lidos das
 * snapshots disponibilizadas.
 */
struct TCD_istruct {
	WikiData wikidata;
};

/**************************************************************************
 *                       INIT, LOAD E CLEAN                               *
 **************************************************************************/

/*
 * @brief Inicializa a estrutura de dados principal do programa.
 *
 * Deve ser a primeira função a ser executada pois só após a chamada desta
 * função, é que a estrutura de dados estará pronta a ser carregada.
 *
 * @return Devolve a estrutura inicializada
 */
TAD_istruct init()
{
	// Aloca-se espaço para o apontador para a estrutura

	TAD_istruct s = malloc(sizeof(struct TCD_istruct));

	// Inicializa-se a estrutura complementar do tipo WikiData

	s->wikidata = initWikiData();
	
	return s;
}


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
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[])
{
	for (int i = 0; i < nsnaps; i++) {

		// Faz-se a leitura e o parsing de cada um dos ficheiros, carregando
		// os dados para a estrutura
		
		parseFile(qs->wikidata, snaps_paths[i]);
	}

	return qs;
}


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
TAD_istruct clean(TAD_istruct qs)
{
	// Liberta-se o espaço ocupado pela estrutura

	qs->wikidata = freeWikiData(qs->wikidata);
	
	// Liberta-se o apontador, colocando-o a NULL
	
	free(qs);
	qs = NULL;

	return qs;
}


/**************************************************************************
 *                          FUNÇÕES AUXILIARES                            *
 **************************************************************************/

/*
 * Calcula o número de dígitos de um long passado como parâmetro.
 */
int getLongLength(long x)
{
	int digits = 1;

	while (x >= 10) {
	    x /= 10;
	    digits++;
	}

	return digits;
}


/**************************************************************************
 *                        QUERIES / INTERROGAÇÕES                         *
 **************************************************************************/

/*
 * @brief Query 1
 *
 * Calcula o número total de artigos encontrados, incluindo artigos
 * duplicados e novas revisões de artigos já existentes. 
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long all_articles(TAD_istruct qs)
{
	return query1(qs->wikidata);
}


/*
 * @brief Query 2
 *
 * Calcula o número de artigos únicos encontrados (i.e. artigos com
 * identificador único). Ou seja, não inclui artigos duplicados nem
 * novas revisões de artigos já existentes.
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long unique_articles(TAD_istruct qs)
{
	return query2(qs->wikidata);
}


/*
 * @brief Query 3
 *
 * Calcula o número total de revisões de artigos encontradas. Inclui quer
 * a versão base de um artigo, quer as restantes revisões feitas ao mesmo
 * posteriormente.
 *
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 */
long all_revisions(TAD_istruct qs)
{
	return query3(qs->wikidata);
}


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
long* top_10_contributors(TAD_istruct qs)
{
	return query4(qs->wikidata);
}


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
char* contributor_name(long contributor_id, TAD_istruct qs)
{
	char* id;

	// Conversão do ID do contribuidor de long para char*

	id = malloc(sizeof(char) * (getLongLength(contributor_id) + 1));
	sprintf(id, "%ld", contributor_id);

	return query5(qs->wikidata, id);
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
 * @param qs Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com o top 20 dos maiores artigos
 */
long* top_20_largest_articles(TAD_istruct qs)
{
	return query6(qs->wikidata);
}


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
char* article_title(long article_id, TAD_istruct qs)
{
	char* id;

	// Conversão do ID do artigo de long para char*

	id = malloc(sizeof(char) * (article_id));
	sprintf(id, "%ld", article_id);

	return query7(qs->wikidata, id);
}


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
long* top_N_articles_with_more_words(int n, TAD_istruct qs)
{
	return query8(qs->wikidata, n);
}

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
char** titles_with_prefix(char* prefix, TAD_istruct qs)
{
	return query9(qs->wikidata, prefix);
}


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
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs)
{
	char *a_id, *r_id;

	// Conversão do ID do artigo de long para char*

	a_id = malloc(sizeof(char) * (getLongLength(article_id) + 1));
	sprintf(a_id, "%ld", article_id);

	// Conversão do ID da revisão de long para char*

	r_id = malloc(sizeof(char) * (getLongLength(revision_id) + 1));
	sprintf(r_id, "%ld", revision_id);	

	return query10(qs->wikidata, a_id, r_id);
}