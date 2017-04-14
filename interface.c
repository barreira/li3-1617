/**
 * @file interface.c
 * @brief Definição de todas as funções pertencentes à interface do projeto
 * 
 * Contém as funções responsáveis pelo parsing dos ficheiros XML, pela definição,
 * carregamento e limpeza das estruturas e pelas queries. 
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * TODO: corrigir contagem de palavras na função parseRevision
 *
 * @version 2017-04-09
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "interface.h"
#include "avl.h"
#include "contributors.h"
#include "articles.h"

struct TCD_istruct {
	ARTICLE_SET aset;
	CONTRIBUTOR_SET cset;
};

/* XML PARSING */

CONTRIBUTOR parseContributor(CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "username"))) {
			xmlChar* username = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			c = setUsername(c, (char*) username);
			free(username);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			c = setContributorID(c, (char*) id);
			free(id);
		}
	}

	return c;
}

void parseRevision(REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id;
			id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			r = setRevisionID(r, (char*) id);
			free(id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "timestamp"))) {
			xmlChar* timestamp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			r = setTimestamp(r, (char*) timestamp);
			free(timestamp);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "contributor"))) {
			c = parseContributor(c, doc, cur);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "text"))) {
			xmlChar* text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			
			if (text != NULL) {
				unsigned int size;
				size = strlen((char*) text) + 1;
				r = setTextSize(r, size);
				
				/*int palavras = 0;

				while (*text != '\0') {

					while (*text == ' ' || *text == '\n' || *text == '\t') {
						text++;
					}

					palavras++;

					while (*text != ' ' || *text != '\n' || *text != '\t') {
						text++;
					}
				}

				setWordCount(r, palavras);*/			
			}

		}
	}
}

TAD_istruct parsePage(TAD_istruct s, xmlDocPtr doc, xmlNodePtr cur) {

	ARTICLE a = initArticle();
	REVISION r = initRevision();
	CONTRIBUTOR c = initContributor();

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			xmlChar* title = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			r = setTitle(r, (char*) title);
			free(title);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			a = setArticleID(a, (char*) id);
			free(id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "revision"))) {
			parseRevision(r, c, doc, cur);
		}
	}

	a = addRevision(a, r);
	s->aset = insertArticle(s->aset, a);
	s->cset = insertContributor(s->cset, c);	

	return s;
}

TAD_istruct parseFile(TAD_istruct s, char* file) {
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file);
	
	if (!doc) {
		fprintf(stderr, "Document not parsed successfully \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);
	
	if (!cur) {
		fprintf(stderr, "Empty document\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
		fprintf(stderr, "Document of the wrong type (root node != mediawiki)");
		xmlFreeDoc(doc);
		return NULL;
	}

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "page"))) {
			s = parsePage(s, doc, cur);
		}
	}

	xmlFreeDoc(doc);
	return s;
}

/* INIT, LOAD E CLEAN */

TAD_istruct init() {
	TAD_istruct s = malloc(sizeof(struct TCD_istruct));

	s->aset = initArticleSet();
	s->cset = initContributorSet();

	return s;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]) {
	int i;

	for (i = 0; i < nsnaps; i++) {
		parseFile(qs, snaps_paths[i]);
	}

	return qs;
}


TAD_istruct clean(TAD_istruct qs) {
	qs->aset = freeArticleSet(qs->aset);
	qs->cset = freeContributorSet(qs->cset);
	free(qs);
	qs = NULL;
	return qs;
}

/* QUERIES */

// 1
long all_articles(TAD_istruct qs) {
	long res = 0;
	int i;
	AVL tmp;

	for (i = 0; i < SET_SIZE_A; i++) {
		tmp = getArticleSubset(qs->aset, i);
		res += query1(tmp);
	}

	return res;
}

// 2
long unique_articles(TAD_istruct qs) {
	long res = 0;
	int i;
	AVL tmp;

	for (i = 0; i < SET_SIZE_A; i++) {
		tmp = getArticleSubset(qs->aset, i);
		res += (long) getTotalNodes(tmp);
	}

	return res;
}

// 3
long all_revisions(TAD_istruct qs) {
	long res = 0;
	int i;
	AVL tmp;

	for (i = 0; i < SET_SIZE_A; i++) {
		tmp = getArticleSubset(qs->aset, i);
		res += query3(tmp);
	}

	return res;	
}

// 4
long* top_10_contributors(TAD_istruct qs) {
	long* ret = 0;
	return ret;
}

// 5
char* contributor_name(long contributor_id, TAD_istruct qs) {
	char* id = malloc(sizeof(contributor_id));
	sprintf(id, "%ld", contributor_id);

	int pos = id[0] - '0';
	AVL tmp = getContributorSubset(qs->cset, pos);

	return query5(tmp, id);
}

// 6
long* top_20_largest_articles(TAD_istruct qs) {
	long* ret = 0;
	return ret;
}

// 7
char* article_title(long article_id, TAD_istruct qs) {
	char* id = malloc(sizeof(article_id));
	sprintf(id, "%ld", article_id);

	int pos = id[0] - '0';
	AVL tmp = getArticleSubset(qs->aset, pos);

	return query7(tmp, id);
}

// 8
long* top_N_articles_with_more_words(int n, TAD_istruct qs) {
	long* ret = 0;
	return ret;	
}


int prefix(char* s, char* p) {
	int i;

	for (i = 0; s[i] == p[i] && s[i] != '\0' && p[i] != '\0'; i++);

	if (i == strlen(p)) {
		return 1;
	}

	return 0;
}

// 9
int my_strcmp(const void* a, const void* b) { 
	char const *char_a = *(char const **)a;
	char const *char_b = *(char const **)b;

	return strcmp(char_a, char_b);
}

char** titles_with_prefix(char* prefix, TAD_istruct qs) {
	int i, size = 0;
	char*** ret = malloc(sizeof(char**));
	*ret = NULL;

	for (i = 0; i < SET_SIZE_A; i++) {
		AVL tmp = getArticleSubset(qs->aset, i);
		query9(tmp, prefix, ret, &size);
	}

	qsort(*ret, size, sizeof(char*), my_strcmp);

	if (*ret != NULL) {
		(*ret)[size] = NULL;
	}

	return *ret;
}

// 10
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs) {
	char* a_id = malloc(sizeof(article_id));
	sprintf(a_id, "%ld", article_id);

	char* r_id = malloc(sizeof(revision_id));
	sprintf(r_id, "%ld", revision_id);	

	int pos = a_id[0] - '0';
	AVL tmp = getArticleSubset(qs->aset, pos);

	return query10(tmp, a_id, r_id);
}