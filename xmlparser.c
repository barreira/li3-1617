#include <stdlib.h>
#include <string.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xmlparser.h"
#include "contributors.h"
#include "articles.h"

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
				int size;
				size = strlen((char*) text) + 1;
				r = setTextSize(r, size);
				
				int palavras = 0;

				for (int i = 0; text[i] != '\0'; i++) {
					if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
						palavras++;

						while (text[i+1] == ' ' || text[i+1] == '\n' || text[i+1] == '\t') {
							i++;
						}
					}
				}

				setWordCount(r, palavras);
			}

		}
	}
}

WikiData parsePage(WikiData wd, xmlDocPtr doc, xmlNodePtr cur) {
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
	
	int flag = 0;
	wd = insertArticle(wd, a, &flag);
	
	if (flag == 0) {
		wd = insertContributor(wd, c);
	}
	else {
		c = freeContributor(c);
	}

	return wd;
}

WikiData parseFile(WikiData wd, char* file) {
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
			wd = parsePage(wd, doc, cur);
		}
	}

	xmlFreeDoc(doc);
	return wd;
}