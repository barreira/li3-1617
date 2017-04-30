/**
 * @file articles.c
 * @brief Definição das estruturas/funções relativas aos artigos
 * 
 * Contém a definição das estruturas que definem um artigo (e revisões do mesmo)
 * e respetivas funções.
 * 
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-29
 */

#include <stdlib.h>
#include <string.h>

#include "articles.h"

#define DEFAULT_REVCOUNT 2 // Número médio de revisões por cada artigo único
                           // (i.e. 40131 / 19867 = 2,02 ~= 2 revisões/artigo).
						   // É utilizado para o tamanho do array de revisões de
						   // um artigo.

/******************************************************************************
 *                               ESTRUTURAS                                   *
 ******************************************************************************/

/* Estrutura responsável por guardar a informação relativa a uma revisão */

struct revision {
	char* id;        // Identificador de uma revisão

	char* timestamp; // Timestamp de uma revisão (marca temporal da sua 
	                 // submissão)

	char* title;     // Título de um artigo numa determinada revisão

	int textsize;    // Tamanha do texto de uma revisão

	int wc;          // Número de palavras do texto de uma revisão
};

/* Estrutura responsável por guardar a informação relativa a um artigo */

struct article {
	char* id;            // Identificador de um artigo

	int revcount;        // Número de revisões de um artigo (i.e. posições
	                     // ocupadas do seu array de revisões)

	int revcapacity;     // Capacidade atual (i.e. tamanho) do array de revisões
	                     // de um artigo

	REVISION* revisions; // Array (dinâmico) das revisões de um artigo

	int occurrences;     // Número total de ocorrências de um artigo (inclui
	                     // duplicados e novas revisões do mesmo artigo)
};

/******************************************************************************
 *                                 INITS                                      *
 ******************************************************************************/

/*
 * @brief Inicializa a estrutura responsável por guardar uma revisão
 *
 * Inicializa o apontador para uma nova revisão (devolvendo-o no fim) e os seus 
 * campos, mas não alocando, ainda, espaço para os campos do tipo char*.
 *
 * @return Devolve o apontador para uma nova revisão (inicializada)
 */
REVISION initRevision()
{
	REVISION r = malloc(sizeof(struct revision));

	r->id = NULL;
	r->timestamp = NULL;
	r->title = NULL;
	r->textsize = 0;
	r->wc = 0;
	
	return r;
}


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
ARTICLE initArticle()
{
	ARTICLE a = malloc(sizeof(struct article));

	a->id = NULL;
	a->revcount = 0;
	a->revcapacity = DEFAULT_REVCOUNT;
	a->revisions = malloc(sizeof(struct revision) * DEFAULT_REVCOUNT);
	a->occurrences = 0;

	return a;
}


/******************************************************************************
 *                                FREES                                       *
 ******************************************************************************/

/*
 * @brief Liberta o espaço ocupado por uma revisão
 *
 * Liberta os campos que, eventualmente, tinham sido alocados manualmente na
 * memória através de malloc (os campos do tipo char*), e o apontador para a
 * revisão passado como parâmetro que é, posteriormente, colocado a NULL.
 *
 * @param r Revisão a libertar
 */
REVISION freeRevision(REVISION r)
{
	free(r->id);
	free(r->timestamp);
	free(r->title);

	free(r);
	r = NULL;

	return r;
}


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
ARTICLE freeArticle(ARTICLE a)
{
	for (int i = 0; i < a->revcount; i++) {
		a->revisions[i] = freeRevision(a->revisions[i]);
	}
    free(a->revisions);
	free(a->id);

	free(a);
	a = NULL;

	return a;
}

/******************************************************************************
 *                                INSERTS                                     *
 ******************************************************************************/

/*
 * @brief Retorna uma cópia da revisão de um artigo situada na posição recebida
 *        como parâmetro do seu array de revisões
 *
 * @param a   Artigo onde se encontra a revisão pedida
 * @param pos Posição em que se encontra a revisão pedida no array de revisões
 *            do artigo
 *
 * @return Cópia da revisão pedida
 */
REVISION getRevisionAt(ARTICLE a, int pos)
{
	REVISION r = initRevision();

	setRevisionID(r, a->revisions[pos]->id);
	setTimestamp(r, a->revisions[pos]->timestamp);
	setTitle(r, a->revisions[pos]->title);
	setTextSize(r, a->revisions[pos]->textsize);
	setWordCount(r, a->revisions[pos]->wc);
	
	return r;
}


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
void* duplicateArticle(void* info, void* dup, int* flag)
{
	int lr, cmp;

	// lr guarda o índice da última posição preenchida do array de revisões

	lr = ((ARTICLE) info)->revcount - 1;

	// Compara-se o ID da última revisão do artigo com o ID da revisão que se
	// está a tentar inserir

	cmp = strcmp(((ARTICLE) info)->revisions[lr]->id,
	             ((ARTICLE) dup)->revisions[0]->id);

	// Se forem diferentes então trata-se de uma nova revisão

	if (cmp != 0) {
		int cap = ((ARTICLE) info)->revcapacity;
		int nr = ((ARTICLE) info)->revcount;

		// Caso o número de revisões seja igual à capacidade do array (i.e. o 
		// array encontra-se totalmente cheio)

		if (nr == cap) {

			// Aumenta-se a capacidade do array para o dobro

			((ARTICLE) info)->revisions = realloc(((ARTICLE) info)->revisions,
			                                      sizeof(struct revision) * cap * 2);
			((ARTICLE) info)->revcapacity *= 2;
		}

		// Coloca-se uma cópia da nova revisão na última posição do array de
		// revisões do artigo original, incrementa-se o contador de revisões e
		// liberta-se o artigo duplicado que já não é necessário

		((ARTICLE) info)->revisions[nr] = getRevisionAt(((ARTICLE) dup), 0);
		((ARTICLE) info)->revcount += 1;
		dup = freeArticle((ARTICLE) dup);
	}

	// Se forem iguais então concluímos que não há nova revisão do artigo e, por
	// isso, aciona-se a flag

	else {
		*flag = 1;
	}

	// Em ambos os casos, incrementa-se o número de ocorrências do artigo

	((ARTICLE) info)->occurrences += 1;

	return info;
}


/*
 * @brief Adiciona a primeira revisão (previamente alocada) a um artigo
 *
 * @return Artigo com a nova revisão no seu array de revisões
 */
ARTICLE addFirstRevision(ARTICLE a, REVISION r)
{
	a->revisions[a->revcount] = r;

	(a->revcount)++;
	(a->occurrences)++;
	
	return a;
}


/******************************************************************************
 *                            GETTERS E SETTERS                               *
 ******************************************************************************/

/*
 * @brief Altera o valor do campo ID de um artigo
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para o artigo recebido como parâmetro, com o
 *         campo referente ao ID alterado.
 */
ARTICLE setArticleID(ARTICLE a, char* id)
{
	a->id = malloc(strlen(id) + 1);
	strcpy(a->id, id);
	return a;
}

/*
 * @brief Altera o valor do campo ID de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do ID recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao ID alterado.
 */
REVISION setRevisionID(REVISION r, char* id)
{
	r->id = malloc(strlen(id) + 1);
	strcpy(r->id, id);
	return r;
}


/*
 * @brief Altera o valor do campo timestamp de uma revisão
 *
 * É alocado espaço e efetuada uma cópia da timestamp recebida.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente à timestamp alterado.
 */
REVISION setTimestamp(REVISION r, char* t)
{
	r->timestamp = malloc(strlen(t) + 1);
	strcpy(r->timestamp, t);
	return r;
}


/*
 * @brief Altera o valor do campo title de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do título recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao título alterado.
 */
REVISION setTitle(REVISION r, char* t)
{
	r->title = malloc(strlen(t) + 1);
	strcpy(r->title, t);
	return r;
}


/*
 * @brief Altera o valor do campo textsize de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do textsize recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao textsize alterado.
 */
REVISION setTextSize(REVISION r, int ts)
{
	r->textsize = ts;
	return r;
}


/*
 * @brief Altera o valor do campo wc de uma revisão
 *
 * É alocado espaço e efetuada uma cópia do wordcount recebido.
 *
 * @return Devolve o apontador para a revisão recebida como parâmetro, com o
 *         campo referente ao contador de palavras do texto alterado.
 */
REVISION setWordCount(REVISION r, int wc)
{
	r->wc = wc;
	return r;
}


/*
 * @brief Retorna o campo ID de um artigo
 *
 * Em vez de retornar o valor do ID por referência, devolve uma cópia, alocando
 * o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo ID do artigo
 */
char* getArticleID(ARTICLE a)
{
	char* ret = malloc(sizeof(char) * (strlen(a->id) + 1));
	strcpy(ret, a->id);
	return ret;	
}


/*
 * @brief Retorna o campo ocurrences de um artigo
 *
 * Em vez de retornar o valor das ocorrências por referência, devolve uma cópia.
 *
 * @return Cópia do campo occurrences do artigo
 */
int getOccurrences(ARTICLE a)
{
	int ret = a->occurrences;
	return ret;
}


/*
 * @brief Retorna o campo revcount de um artigo
 *
 * Em vez de retornar o valor das ocorrências por referência, devolve uma cópia.
 *
 * @return Cópia do campo revcount do artigo
 */
int getRevCount(ARTICLE a)
{
	int ret = a->revcount;
	return ret;
}


/*
 * @brief Retorna o campo title de um artigo
 *
 * Em vez de retornar o valor do título por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo title do artigo
 */
char* getTitle(REVISION r) {
	char* ret = malloc(sizeof(char) * (strlen(r->title) + 1));
	strcpy(ret, r->title);
	return ret;
}


/*
 * @brief Retorna o campo timestamp de um artigo
 *
 * Em vez de retornar o valor do timestamp por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do campo timestamp do artigo
 */
char* getTimestamp(REVISION r) {
	char* ret = malloc(sizeof(char) * (strlen(r->timestamp) + 1));
	strcpy(ret, r->timestamp);
	return ret;	
}


/******************************************************************************
 *             FUNÇÕES AUXILIARES PARA O MÓDULO DA AVL GENÉRICA               *
 ******************************************************************************/

/*
 * @brief Função genérica de comparação de dois nós de uma árvore de artigos
 *
* É passado um apontador para esta função aquando da criação de uma AVL
 * genérica. Esta função é utilizada pela AVL genérica para a comparação dos
 * seus nós, por exemplo, durante a inserção de um novo nó na árvore ou em
 * qualquer outra travessia pela árvore.
 *
 * @param a Informação (void* correspondente a um artigo) da AVL genérica
 * @param b Informação (void* correspondente a um artigo) da AVL genérica
 * 
 */
int cmpArticle(const void* a, const void* b)
{
	return strcmp(getArticleID((ARTICLE) a), getArticleID((ARTICLE) b));
}


/*
 * @brief Função genérica de free de um nó de uma árvore de artigos
 *
 * É passado um apontador para esta função aquando da criação de uma AVL
 * genérica. Esta função é utilizada pela AVL genérica para a remoção dos seus
 * nós.
 *
 * @param a Informação (void* correspondente a um artigo) a ser libertada
 */
void deleteArticle(void* a)
{
	freeArticle((ARTICLE) a);
}


/******************************************************************************
 *                      FUNÇÕES AUXILIARES ÀS QUERIES                         *
 ******************************************************************************/

/*
 * @brief Retorna o título da última revisão de um artigo
 *
 * Em vez de retornar o valor do título por referência, devolve uma cópia,
 * alocando o espaço necessário (que depois deverá ser libertado).
 *
 * @return Cópia do título da última revisão do artigo
 */
char* getLastRevisionTitle(ARTICLE a) {
	char* ret;
	
	ret = malloc(sizeof(char) * (strlen(a->revisions[a->revcount-1]->title) + 1));
	strcpy(ret, a->revisions[a->revcount-1]->title);

	return ret;
}


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
char* getArticleRevisionTimestamp(ARTICLE a, char* revision_id)
{
	char* ret;

	for (int i = 0; i < a->revcount; i++) {
		if (strcmp(a->revisions[i]->id, revision_id) == 0) {
			ret = malloc(sizeof(char) * strlen(a->revisions[i]->timestamp));
			strcpy(ret, a->revisions[i]->timestamp);
			return ret;
		}
	}

	return NULL;
}


/*
 * @brief Retorna o tamanho da maior revisão de um artigo
 */
int getBiggestRevisionSize(ARTICLE a) {
	int s = 0;

	for (int i = 0; i < a->revcount; i++) {
		if (a->revisions[i]->textsize >= s) {
			s = a->revisions[i]->textsize;
		}
	}

	return s;
}


/*
 * @brief Retorna o maior wordcount das revisões de um artigo
 */
int getBiggestRevisionWC(ARTICLE a) {
	int s = 0;

	for (int i = 0; i < a->revcount; i++) {
		if (a->revisions[i]->wc >= s) {
			s = a->revisions[i]->wc;
		}
	}

	return s;
}