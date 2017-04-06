#include <libxml/xmlmemory.h>

#include "xmlparser.h"
#include "avl.h"
#include "articles.h"
#include "contributors.h"

void parseContributor(TAD_istruct s, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "username"))) {
			xmlChar* username = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setUsername(c, username);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setContributorID(c, id);
		}

	}
}

void parseRevision(TAD_istruct s, REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setRevisionID(r, id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "timestamp"))) {
			xmlChar* timestamp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setTimestamp(r, timestamp);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "contributor"))) {
			parseContributor(a, c, doc, cur);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "text xml:space=\"preserve\""))) {
			// Calcular o número de palavras + setWC()
			// Calcular o tamanho do texto + setTextSize()
		}
	}
}

void parsePage(TAD_istruct s, ARTICLE a, REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur) {
	// article a

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			xmlChar* title = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setTitle(a, title);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			setArticleID(a, id);	
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "revision"))) {
			parseRevision(a,doc, cur);
		}

		insert 
	}
}

static void loadFile(TAD_istruct s, char* file) {
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

	// Declarar estruturas (contributor, article e revision)

	ARTICLE a = initArticle();
	REVISION r = initRevision();
	CONTRIBUTOR c = initContributor();

	// Fazer o parsing, passando as estruturas

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "page"))) {
			parsePage(a, r, c, doc, cur);
		}
	}

	// Fazer o insert na estrutura de dados da interface


	xmlFreeDoc(doc);
}