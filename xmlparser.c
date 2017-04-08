#include <libxml/xmlmemory.h>

#include "xmlparser.h"
#include "avl.h"
#include "articles.h"
#include "contributors.h"

void parseContributor(CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "username"))) {
			xmlChar* username = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setUsername(c, username);
			free(username);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setContributorID(c, id);
			free(id);
		}

	}
}

void parseRevision(REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setRevisionID(r, id);
			free(id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "timestamp"))) {
			xmlChar* timestamp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setTimestamp(r, timestamp);
			free(timestamp);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "contributor"))) {
			parseContributor(a, c, doc, cur);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "text"))) {
			xmlChar* text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (te)
			// Calcular o número de palavras + setWC(), percorrer...
			// Calcular o tamanho do texto + setTextSize(), strlen(text)+1
		}
	}
}

void parsePage(TAD_istruct s, ARTICLE a, REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	ARTICLE a = initArticle();
	REVISION r = initRevision();
	CONTRIBUTOR c = initContributor();

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			xmlChar* title = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			a = setTitle(a, title);
			free(title);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setArticleID(a, id);	
			free(id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "revision"))) {
			parseRevision(r, c, doc, cur);
		}

		addRevision(ARTICLE a, REVISION r);
		s->aset = insertArticle(s->aset, a);
		s->cset = insertContributor(s->cset, c);
	}	
}

static void parseFile(TAD_istruct s, char* file) {
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file);
	
	if (!doc) {
		fprintf(stderr, "Document not parsed successfully \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);
	
	if (!cur) {
		fprintf(stderr, "Empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
		fprintf(stderr, "Document of the wrong type (root node != mediawiki)");
		xmlFreeDoc(doc);
		return;
	}

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "page"))) {
			parsePage(s, doc, cur);
		}
	}

	xmlFreeDoc(doc);
}