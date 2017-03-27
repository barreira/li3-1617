#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xmlparser.h"
#include "interface.h"

void parsePage(AVL a, xmlDocPtr doc, xmlNodePtr cur) {

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			xmlChar* title = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("%s\n", title);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			xmlChar* a_id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("%s\n", a_id);
		}

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "revision"))) {
			
		}

	}

	//insert(a, a_id, r_id, timestamp, title, text, c_id, name);
}

void loadFile(AVL a, char* file) {
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file);
	/*
	if (!doc) {
		return -1; // Erro na leitura do ficheiro
	}*/

	cur = xmlDocGetRootElement(doc);
	/*
	if (!cur) {
		xmlFreeDoc(doc);
		return -1; // Ficheiro vazio
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
		return -1; // Root node != mediawiki
	}*/

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "page"))) {
			parsePage(a, doc, cur);
		}
	}

	xmlFreeDoc(doc);
}