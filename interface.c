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

#include <string.h>

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
}

void parseRevision(REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
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

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "text xml:space=\"preserve\""))) {
			xmlChar* text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			
			if (text != NULL) {
				unsigned int size;
				size = strlen((char*) text) + 1;
				r = setTextSize(r, size);
			}

			unsigned int i, palavras = 0;

			for (i = 0; ((char*) text)[i] != '\0' ; i++); {
				if (((char*) text)[i] == " " || ((char*) text)[i] == '\n' || ((char*) text)[i] == '\t') {
					palavras++;
				}
			}

			setWordCount(r, palavras);
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

		addRevision(a, r);
		s->aset = insertArticle(s->aset, a);
		s->cset = insertContributor(s->cset, c);
	}

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

/*
long all_articles(TAD_istruct qs);
long unique_articles(TAD_istruct qs);
long all_revisions(TAD_istruct qs);
long* top_10_contributors(TAD_istruct qs);
char* contributor_name(long contributor_id, TAD_istruct qs);
long* top_20_largest_articles(TAD_istruct qs);
char* article_title(long article_id, TAD_istruct qs);
long* top_N_articles_with_more_words(int n, TAD_istruct qs);
char** titles_with_prefix(char* prefix, TAD_istruct qs);
char* article_timestamp(long article_id, long revison_id, TAD_istruct qs);
*/