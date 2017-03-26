#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

int parsePage(xmlDocPtr doc, xmlNodePtr cur) {
	int res = 0;

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			res++;
		}
	}
	
	return res;
}

int parseDoc(char *docname, char *tag) {
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	if (doc == NULL) {
		fprintf(stderr, "Não foi possível ler o ficheiro.\n");
		return -1;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr, "Ficheiro vazio.\n");
		xmlFreeDoc(doc);
		return -1;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
		fprintf(stderr, "Root node != mediawiki.\n");
		return -1;
	}

	int contador = 0;

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (!(xmlStrcmp(cur->name, (const xmlChar *) tag))) {
			contador += parsePage(doc, cur);
		}
	}

	xmlFreeDoc(doc);
	return contador;
}


int main(int argc, char **argv) {
	
	if (argc < 2) {
		printf("Utilização: %s nome_do_documento1 [nome_do_documento2, ...]\n", argv[0]);
		return -1;
	}

	int i, num, res = 0;

	for (i = 1; i < argc; i++) {
		num = parseDoc(argv[i], "page");

		if (num == -1)
			return -1;

		res += num;
	}

	printf("Title #: %d\n", res);

	return 0;
}