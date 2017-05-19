#include <stdlib.h>
#include <string.h>

#include "queries.h"
#include "avl.h"

#define SET_SIZE 10


/******************************************************************************
 *                           ESTRUTURAS DE DADOS                              *
 ******************************************************************************/

/* Estrutura que guarda todos os contribuintes lidos das snapshots */

typedef struct contributorset {
	AVL contributors[SET_SIZE]; // Array de 10 árvores para guardar todos os
	                            // contribuidores lidos (em contribuidores[0]
								// estão todos os artigos cujo ID começa por
								// '0', em contribuidores[1] todos os que
								// começam por '1', etc.)
} *ContributorSet;

/* Estrutura que guarda todos os artigos lidos das snapshots */

typedef struct articleset {
	AVL articles[SET_SIZE]; // Array de 10 árvores para guardar todos os
	                        // artigos lidos (em articles[0] estão todos os
							// artigos cujo ID começa por '0', em articles[1]
							// todos os que começam por '1', etc.)
} *ArticleSet;

/* Estrutura que guarda toda a informação (artigos e contribuidores) lida das
   snapshots */

struct wikidata {
	ContributorSet cset; // Apontador para o array dos contribuidores
	ArticleSet aset;     // Apontador para o array dos artigos
};


/******************************************************************************
 *                                 INITS                                      *
 ******************************************************************************/


/*
 * @brief Inicializa a estrutura do conjunto de artigos (array)
 *
 * Inicializa o apontador para um novo conjunto de artigos e para cada uma das
 * 10 posições do array.
 *
 * @return Devolve o apontador para um novo conjunto de artigos (inicializado)
 */
ArticleSet initArticleSet()
{
	ArticleSet as = malloc(sizeof(struct articleset));

	for (int i = 0; i < SET_SIZE; i++) {
		as->articles[i] = initAvl(cmpArticle, deleteArticle);
	}

	return as;
}


/*
 * @brief Inicializa a estrutura do conjunto de contribuidores (array)
 *
 * Inicializa o apontador para um novo conjunto de contribuidores e para cada
 * uma das 10 posições do array.
 *
 * @return Devolve o apontador para um novo conjunto de contribuidores
 *         (inicializado)
 */
ContributorSet initContributorSet()
{
	ContributorSet cs = malloc(sizeof(struct contributorset));

	for (int i = 0; i < SET_SIZE; i++) {
		cs->contributors[i] = initAvl(cmpContributor, deleteContributor);
	}

	return cs;
}


/*
 * @brief Inicializa a estrutura da wikidata
 *
 * Inicializa o apontador para uma nova estrutura wikidata, inicializando também
 * os arrays dos contribuidores e dos artigos.
 *
 * @return Devolve o apontador para uma nova estrutura wikidata (inicializada)
 */
WikiData initWikiData()
{
	WikiData wd = malloc(sizeof(struct wikidata));

	wd->aset = initArticleSet();
	wd->cset = initContributorSet();

	return wd;
}


/******************************************************************************
 *                                 FREES                                      *
 ******************************************************************************/


/*
 * @brief Liberta o espaço ocupado por um conjunto de artigos (array)
 *
 * Liberta o apontador para o conjunto dos artigos, libertando também cada uma
 * das 10 posições do array.
 *
 * @param as Conjunto dos artigos a ser libertado
 */
ArticleSet freeArticleSet(ArticleSet as)
{
	for (int i = 0; i < SET_SIZE; i++) {
		as->articles[i] = freeAvl(as->articles[i]);
	}

	free(as);
	as = NULL;

	return as;
}


/*
 * @brief Liberta o espaço ocupado por um conjunto de contribuidores (array)
 *
 * Liberta o apontador para o conjunto dos contribuidores, libertando também
 * cada uma das 10 posições do array.
 *
 * @param cs Conjunto dos contribuidores a ser libertado
 *
 * @return Devolve o apontador recebido (colocado a NULL)
 */
ContributorSet freeContributorSet(ContributorSet cs)
{
	for (int i = 0; i < SET_SIZE; i++) {
		cs->contributors[i] = freeAvl(cs->contributors[i]);
	}

	free(cs);
	cs = NULL;

	return cs;
}


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
WikiData freeWikiData(WikiData wd)
{
	wd->aset = freeArticleSet(wd->aset);
	wd->cset = freeContributorSet(wd->cset);
	free(wd);
	wd = NULL;
	return wd;
}


/******************************************************************************
 *                                  INSERTS                                   *
 ******************************************************************************/

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
WikiData insertArticle(WikiData wd, ARTICLE a, int* flag)
{
	char* id = getArticleID(a);

	if (a != NULL) {
		int pos = id[0] - '0';
		wd->aset->articles[pos] = insert(wd->aset->articles[pos],
		                                 a,
										 duplicateArticle,
										 flag);
	}

	return wd;	
}


/*
 * @brief Insere um contribuidor na estrutura WikiData (no seu array de
          contribuidores)
 *
 * @param wd Estrutura wikidata
 * @param c  Contribuidor a inserir
 *
 * @return Estrutura wikidata com o novo contribuidor lá colocado
 */
WikiData insertContributor(WikiData wd, CONTRIBUTOR c)
{
	char* id = getContributorID(c);

	if (id != NULL) { 
		int pos = id[0] - '0';
		wd->cset->contributors[pos] = insert(wd->cset->contributors[pos],
		                                     c,
											 duplicateContributor,
											 NULL);
	}

	return wd;
}


/******************************************************************************
 *                   ESTRUTURAS AUXILIARES ÀS QUERIES                         *
 ******************************************************************************/

/* Estrutura auxiliar às queries 4, 6 e 8 */

typedef struct sq468 {
	long* ids;    // Array com os IDs dos artigos/contribuidores correspondentes
	              // aos valores abaixo

	long* values; // Array que guarda os valores correspondentes aos IDs dos
	              // artigos/contribuidores acima e que correspondem, ao número
				  // de revisões (q4), aos tamanhos (q6) e número de palavras
				  // (q8) dos textos dos artigos
} *SQ468;


/* Estrutura auxiliar à query 9 */

typedef struct sq9 {
	char** titles; // Array dinâmico que guarda os títulos dos artigos começados
	               // pelo prefixo

	int size;      // Tamanho do array dinâmico dos títulos dos artigos 
} *SQ9;


/*
 * @brief Inicializa a estrutura auxiliar às queries 4, 6 e 8
 */
SQ468 initStructQ468(int size)
{
	SQ468 s = malloc(sizeof(struct sq468));
	
	s->ids = calloc(size, sizeof(long));
	s->values = calloc(size, sizeof(long));

	return s;
}


/*
 * @brief Inicializa a estrutura auxiliar à query 9
 */
SQ9 initStructQ9()
{
	SQ9 s = malloc(sizeof(struct sq9));
	
	s->titles = NULL;
	s->size = 0;

	return s;
}


/******************************************************************************
 *                              QUERIES                                       *
 ******************************************************************************/

/*
 * @brief Função auxiliar à query 1 que soma o número de ocorrências de um
 *        artigo e soma-o a um acumulador (ambos recebidos como parâmetro)
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 1 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos artigos ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso é tido como um acumulador de
               longs)
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 */
void query1_aux(void* info, void* acc, void* aux)
{

    // Faz o typecast do contador (void*) para um long* e incrementa o valor do
    // do long por ele apontado com o número de ocorrências do artigo recebido

	(*(long*) acc) += (long) getOccurrences((ARTICLE) info);
}


/*
 * @brief Query 1
 *
 * Calcula o número total de artigos encontrados, incluindo artigos duplicados
 * e novas revisões de artigos já existentes.
 */
long query1(WikiData wd)
{
	long articles = 0;

	// Para todos os nós de cada uma das 10 árvores de artigos, efetua um map
	// que, por sua vez, aplica a cada um deles, a função auxiliar desta query
	// que apenas soma os campos 'occurrences' de cada artigo

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], &articles, NULL, query1_aux);
	}

	return articles;	
}


/*
 * @brief Query 2
 *
 * Calcula o número de artigos únicos encontrados (i.e. artigos com
 * identificador único). Ou seja, não inclui artigos duplicados nem novas
 * revisões de artigos já existentes.
 */
long query2(WikiData wd)
{
	long articles = 0;

	// Soma o total de nodos para cada uma das 10 árvores do array de artigos
	// correspondente ao número de artigos únicos de cada uma delas 

	for (int i = 0; i < SET_SIZE; i++) {
		articles += (long) getTotalNodes(wd->aset->articles[i]);
	}

	return articles;
}


/*
 * @brief Função auxiliar à query 3 que soma o número de revisões de um artigo
 *        e soma-o a um acumulador (ambos recebidos como parâmetro)
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 3 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos artigos ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso é tido como um acumulador de
               longs)
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 */
void query3_aux(void* info, void* acc, void* aux)
{

    // Faz o typecast do contador (void*) para um long* e incrementa o valor do
    // do long por ele apontado com o número de ocorrências do artigo recebido

	(*(long*) acc) += (long) getRevCount((ARTICLE) info);
}


/*
 * @brief Query 3
 *
 * Calcula o número total de revisões de artigos encontradas. Inclui quer a
 * versão base de um artigo, quer as restantes revisões feitas ao mesmo
 * posteriormente.
 */
long query3(WikiData wd)
{
	long revisions = 0;

	// Para todos os nós de cada uma das 10 árvores de artigos, efetua um map
	// que, por sua vez, aplica a cada um deles, a função auxiliar desta query
	// que apenas soma os campos 'revCount' de cada artigo

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], &revisions, NULL, query3_aux);
	}

	return revisions;	
}


/*
 * @brief Função auxiliar à query 4 que utiliza a estrutura auxiliar desta query
 *        como acumulador e vai buscar o número de revisões de cada
 *        contribuidor, construindo, iteração a iteração, o top 10 pedido
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 4 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos contribuidores ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso corresponde à estrutura auxiliar
 *             desta query e que tem o array referente ao top pedido
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 */
void query4_aux(void* info, void* acc, void* aux)
{
	int i, index;
	long id, revs;

	// Vai-se buscar o ID contribuidor e seu número total de contribuições

	id = atol(getContributorID((CONTRIBUTOR) info));
	revs = (long) getRevisions((CONTRIBUTOR) info);

	// Percorre-se o array de valores do acumulador (que possui o top 10 atual
	// de contribuições) até encontrar um contribuidor com menor ou igual
	// número de contribuições do que o atual

	for (i = 0; i < 10 && ((SQ468) acc)->values[i] > revs; i++);
	
	// Caso haja valores de contribuições iguais no array de valores do
	// acumulador, avança-se o i de acordo com a ordenação alfabética dos IDs

	while (i < 10 && ((SQ468) acc)->values[i] == revs && ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	// Index marca a posição onde será inserido o novo valor

	index = i;

	// Desloca-se todos os índices com números de revisões inferiores para trás
	// no array

	for (i = 10; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	// Coloca-se o valor atual na posição certa do array

	((SQ468) acc)->values[i] = revs;
	((SQ468) acc)->ids[i] = id;
}


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
long* query4(WikiData wd)
{
	SQ468 s;

	s = initStructQ468(10);

	// Para todos os nós de cada uma das 10 árvores de contribuidores, efetua um
	// map que, por sua vez, aplica a cada um deles, a função auxiliar desta
	// query, indo buscar o número de revisões de cada contribuidor e
	// construindo, iteração a iteração, o top 10 pedido

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->cset->contributors[i], s, NULL, query4_aux);
	}

	return s->ids;
}


/*
 * @brief Função auxiliar à query 5 que apenas retorna o username do nodo
 *        encontrado
 *
 * @param info Nodo da árvore dos contribuidores ao qual aplicar esta função
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 *
 * @return Username no nodo recebido como parâmetro
 */
void* query5_aux(void* info, void* aux)
{
	return getUsername((CONTRIBUTOR) info);
}


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
char* query5(WikiData wd, char* contributor_id)
{
	char* username;
	int pos;
	
	// A posição da AVL onde se encontra o contribuidor recebido como parâmetro
	// é dada pela subtração do código ASCII do seu primeiro caratere, pelo
	// valor ASCII do '0'

	pos = contributor_id[0] - '0';

	CONTRIBUTOR tmp = initContributor();
	setContributorID(tmp, contributor_id);

	// Chama-se a função findAndApply que procura o contribuidor na respetiva
	// árvore, aplica-lhe a função auxiliar a esta query, devolvendo o valor que
	// esta retorna

	username = findAndApply(wd->cset->contributors[pos], tmp, NULL, query5_aux);

	// Faz-se free do contribuidor que já não é necessário

	freeContributor(tmp);

	return username;
}


/*
 * @brief Função auxiliar à query 6 que utiliza a estrutura auxiliar desta query
 *        como acumulador e vai buscar o tamanho do texto de cada artigo,
 *        construindo, iteração a iteração, o top 20 pedido
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 6 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos artigos ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso corresponde à estrutura auxiliar
 *             desta query e que tem o array referente ao top pedido
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 */
void query6_aux(void* info, void* acc, void* aux)
{
	int i, index;
	long id, size;

	// Vai-se buscar o ID artigo e o tamanho da maior revisão do artigo

	id = atol(getArticleID((ARTICLE) info));
	size = getBiggestRevisionSize((ARTICLE) info);

	// Percorre-se o array de valores do acumulador (que possui o top 20 atual
	// de maiores tamanho) até encontrar um artigo com menor ou igual tamanho do
	// texto do que o atual

	for (i = 0; i < 20 && ((SQ468) acc)->values[i] > size; i++);
	
	// Caso haja tamanhos iguais no array de valores do acumulador, avança-se o
	// i de acordo com a ordenação alfabética dos IDs dos respetivos artigos

	while (i < 20 && ((SQ468) acc)->values[i] == size &&
	       ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	// Index marca a posição onde será inserido o novo valor no array

	index = i;

	// Desloca-se todos os índices com tamanhos inferiores para trás no array

	for (i = 20; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	// Coloca-se o valor atual na posição certa do array	

	((SQ468) acc)->values[i] = size;
	((SQ468) acc)->ids[i] = id;
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
 * @return Array ordenado com o top 20 dos maiores artigos
 */
long* query6(WikiData wd)
{
	SQ468 s;

	s = initStructQ468(20);

	// Para todos os nós de cada uma das 10 árvores de artigos, efetua um map
	// que, por sua vez, aplica a cada um deles, a função auxiliar desta query,
	// indo buscar o tamanho do texto de cada artigo e construindo, iteração a
	// iteração, o top 20 pedido

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, NULL, query6_aux);
	}

	return s->ids;
}


/*
 * @brief Função auxiliar à query 5 que apenas retorna o username do nodo
 *        encontrado
 *
 * @param info Nodo da árvore dos contribuidores ao qual aplicar esta função
 * @param aux  Não é usado por esta função (por isso é recebido sempre um NULL).
 *             Tem, no entanto, de obedecer ao cabeçalho presente no módulo da
 *             AVL genérica.
 *
 * @return Username no nodo recebido como parâmetro
 */
void* query7_aux(void* info, void* aux)
{
	return getLastRevisionTitle((ARTICLE) info);
}


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
char* query7(WikiData wd, char* article_id)
{
	char* title;
	int pos;
	
	// A posição da AVL onde se encontra o contribuidor recebido como parâmetro
	// é dada pela subtração do código ASCII do seu primeiro caratere, pelo
	// valor ASCII do '0'

	pos = article_id[0] - '0';

	ARTICLE tmp = initArticle();
	setArticleID(tmp, article_id);

	// Chama-se a função findAndApply que procura o artigo na respetiva árvore,
	// e lhe aplica a função auxiliar a esta query, devolvendo o valor que esta
	// retorna

	title = findAndApply(wd->aset->articles[pos], tmp, NULL, query7_aux);

	// Faz-se free do artigo que já não é necessário

	freeArticle(tmp);

	return title;
}


/*
 * @brief Função auxiliar à query 8 que utiliza a estrutura auxiliar desta query
 *        como acumulador e vai buscar o contador de palavras de cada artigo,
 *        construindo, iteração a iteração, o top N pedido
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 8 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos artigos ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso corresponde à estrutura auxiliar
 *             desta query e que tem o array referente ao top pedido
 * @param aux  É usado para receber o tamanho do top pedido
 */
void query8_aux(void* info, void* acc, void* aux)
{
	int i, index, n;
	long id, wc;

	// Conversão do void* recebido em int (tamanho do top)

	n = (*(int*) aux);

	// Vai-se buscar o ID artigo e o maior contador de palavras do artigo

	id = atol(getArticleID((ARTICLE) info));
	wc = getBiggestRevisionWC((ARTICLE) info);

	// Percorre-se o array de valores do acumulador (que possui o top N atual
	// de maiores contadores de palavra) até encontrar um artigo com menor ou
	// igual valor do contador do que o atual

	for (i = 0; i < n && ((SQ468) acc)->values[i] > wc; i++);
	
	// Caso haja tamanhos iguais no array de valores do acumulador, avança-se o
	// i de acordo com a ordenação alfabética dos IDs dos respetivos artigos

	while (i < n && ((SQ468) acc)->values[i] == wc && ((SQ468) acc)->ids[i] < id) {
		i++;
	}

	// Index marca a posição onde será inserido o novo valor no array

	index = i;

	// Desloca-se todos os índices com contadores de palavras inferiores para
	// trás no array

	for (i = n; i > index; i--) {
		((SQ468) acc)->values[i] = ((SQ468) acc)->values[i-1];
		((SQ468) acc)->ids[i] = ((SQ468) acc)->ids[i-1];
	}

	// Coloca-se o valor atual na posição certa do array

	((SQ468) acc)->values[i] = wc;
	((SQ468) acc)->ids[i] = id;
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
 * @param n  Tamanho do array
 * @param wd Estrutura de dados (previamente carregada e inicializada)
 *
 * @return Array ordenado com os N artigos com mais palavras
 */
long* query8(WikiData wd, int n)
{
	SQ468 s;

	s = initStructQ468(n);

	// Para todos os nós de cada uma das 10 árvores de artigos, efetua um map
	// que, por sua vez, aplica a cada um deles, a função auxiliar desta query,
	// indo buscar o contador de palavras de cada artigo e construindo, iteração
	// a iteração, o top N pedido

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, &n, query8_aux);
	}

	return s->ids;
}


/*
 * @brief Função auxiliar à query9 que compara duas strings recebidas como void*
 */
int my_strcmp(const void* a, const void* b)
{ 
	char const *char_a = *(char const **)a;
	char const *char_b = *(char const **)b;

	return strcmp(char_a, char_b);
}


/*
 * @brief Função auxiliar à query 10 e que verifica se a string 1 é prefixo da
 *        string 2
 */
int isPrefix(char* s, char* p)
{
	int i;

	for (i = 0; s[i] == p[i] && s[i] != '\0' && p[i] != '\0'; i++);

	if (i == strlen(p)) {
		return 1;
	}

	return 0;
}


/*
 * @brief Função auxiliar à query 9 que utiliza a estrutura auxiliar desta query
 *        como acumulador e vai buscar o título de cada artigo, construindo,
 *        iteração a iteração, a listagem pedida
 *
 * Esta função é passada ao módulo da AVL genérica aquando da aplicação do map
 * referente à query 9 e é aplicada a todos os nós de uma árvore.
 *
 * @param info Nodo da árvore dos artigos ao qual aplicar esta função
 * @param acc  Acumulador genérico (neste caso corresponde à estrutura auxiliar
 *             desta query e que tem o array referente ao top pedido
 * @param aux  É usado para receber o prefixo a procurar
 */
void query9_aux(void* info, void* acc, void* aux)
{
	char* t;
	int tam;

	// Vai-se buscar o título mais recente de cada artigo

	t = getLastRevisionTitle((ARTICLE) info);
	tam = ((SQ9) acc)->size;

	// Caso o título tenha o prefixo recebido, coloca-se no array das strings da
	// estrutura desta query, realocando a mesma de forma a haver espaço para
	// guardar o novo título

	if (isPrefix(t, (char*) aux)) {
		((SQ9) acc)->titles = realloc(((SQ9) acc)->titles,
		                              sizeof(char*) * (tam + 1));
		((SQ9) acc)->titles[tam] = t;
		((SQ9) acc)->size += 1;
	}
}


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
char** query9(WikiData wd, char* prefix)
{
	SQ9 s;

	s = initStructQ9();

	// Para todos os nós de cada uma das 10 árvores de artigos, efetua um map
	// que, por sua vez, aplica a cada um deles, a função auxiliar desta query,
	// indo buscar o título de cada artigo e construindo, iteração a iteração,
	// a listagem pedida

	for (int i = 0; i < SET_SIZE; i++) {
		mapAVL(wd->aset->articles[i], s, prefix, query9_aux);
	}

	// Ordena-se alfabeticamente o array resultante

	qsort(s->titles, s->size, sizeof(char*), my_strcmp);

	// Coloca-se a última posição a NULL (para evitar erros nos testes)

	if (s->titles != NULL) {
		s->titles[s->size] = NULL;
	}

	return s->titles;
}


/*
 * @brief Função auxiliar à query 10 que apenas retorna o timestamp da revisão
 *        do artigo encontrado (ambos passados como parâmetro)
 *
 * @param info Nodo da árvore dos artigo ao qual aplicar esta função
 * @param aux  É usado para receber qual o ID da revisão a procurar
 *
 * @return Timestamp do artigo/revisão recebidos como parâmetro (NULL caso não
 *         existam um ou outro)
 */
void* query10_aux(void* info, void* aux)
{
	return getArticleRevisionTimestamp((ARTICLE) info, (char*) aux);
}


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
char* query10(WikiData wd, char* article_id, char* revision_id)
{
	char* timestamp;
	int pos;
	
	// A posição da AVL onde se encontra o contribuidor recebido como parâmetro
	// é dada pela subtração do código ASCII do seu primeiro caratere, pelo
	// valor ASCII do '0'

	pos = article_id[0] - '0';

	ARTICLE tmp = initArticle();
	setArticleID(tmp, article_id);

	// Chama-se a função findAndApply que procura o artigo na respetiva árvore,
	// e lhe aplica a função auxiliar a esta query, devolvendo o valor que esta
	// retorna

	timestamp = findAndApply(wd->aset->articles[pos], tmp, revision_id,
	                         query10_aux);

	// Faz-se free do artigo que já não é necessário							 

	freeArticle(tmp);

	return timestamp;
}