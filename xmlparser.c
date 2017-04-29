/**
 * @file xmlparser.c
 * @brief Definição do módulo encarregue pelo parsing XML
 * 
 * Contém as funções de leitura e parsing dos ficheiros XML (snapshots).
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#include <stdlib.h>
#include <string.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "xmlparser.h"
#include "contributors.h"
#include "articles.h"

/*
 * @brief Faz a leitura e o parsing de uma tag "revision" de uma snapshot
 *
 * Lê as tags hierarquicamente inferiores a "revision", retirando a informação
 * necessária e colocando-a nas estruturas previamente criadas.
 *
 * @param r    Estrutura para onde irão ser lidos os dados da revisão
 * @param c    Estrutura para onde irão ser lidos os dados do contribuidor
 * @param doc  Ficheiro XML
 * @param cur  Apontador para a tag atual do ficheiro XML
 */
void parseContributor(CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur)
{
	// Percorrem-se todas as tags "filhas" da tag "contributor"

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {

		// Caso se encontre uma tag cujo nome é "username"		

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "username"))) {

			// Retira-se o username do contribuidor

			xmlChar* username = xmlNodeListGetString(doc,
			                                         cur->xmlChildrenNode,
													 1);

			// Coloca-se uma cópia do username lido na estrutura que guarda o
			// contribuidor e liberta-se o espaço ocupado pela informação lida			

			c = setUsername(c, (char*) username);
			free(username);
		}

		// Caso se encontre uma tag cujo nome é "id"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {

			// Retira-se o ID do contribuidor

			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			// Coloca-se uma cópia do ID lido na estrutura que guarda o
			// contribuidor e liberta-se o espaço ocupado pela informação lida			

			c = setContributorID(c, (char*) id);
			free(id);
		}
	}
}


/*
 * @brief Faz a leitura e o parsing de uma tag "revision" de uma snapshot
 *
 * Lê as tags hierarquicamente inferiores a "revision", retirando a informação
 * necessária e colocando-a nas estruturas previamente criadas.
 *
 * @param r    Estrutura para onde irão ser lidos os dados da revisão
 * @param c    Estrutura para onde irão ser lidos os dados do contribuidor
 * @param doc  Ficheiro XML
 * @param cur  Apontador para a tag atual do ficheiro XML
 */
void parseRevision(REVISION r, CONTRIBUTOR c, xmlDocPtr doc, xmlNodePtr cur)
{
	// Percorrem-se todas as tags "filhas" da tag "revision"

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {

		// Caso se encontre uma tag cujo nome é "id"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {

			// Retira-se o ID do revisão

			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			// Coloca-se uma cópia do ID lido na estrutura que guarda a revisão
			// e liberta-se o espaço ocupado pela informação lida

			r = setRevisionID(r, (char*) id);
			free(id);
		}

		// Caso se encontre uma tag cujo nome é "timestamp"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "timestamp"))) {

			// Retira-se o timestamp

			xmlChar* timestamp = xmlNodeListGetString(doc,
			                                          cur->xmlChildrenNode,
													  1);

			// Coloca-se uma cópia do timestamp lido na estrutura que guarda a
			// revisão e liberta-se o espaço ocupado pela informação lida

			r = setTimestamp(r, (char*) timestamp);
			free(timestamp);
		}

		// Caso se encontre uma tag cujo nome é "contributor"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "contributor"))) {

			// Faz-se a leitura e o parsing da tag "contributor"

			parseContributor(c, doc, cur);
		}

		// Caso se encontre uma tag cujo nome é "text"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "text"))) {
			xmlChar* text = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			
			// Verifica-se se a tag é a que, realmente, possui o texto da
			// revisão do artigo

			if (text != NULL) {
				
				// Calcula-se o tamanho do texto da revisão

				int size = strlen((char*) text) + 1;

				// Coloca-se o tamanho do texto da revisão na estrutura que
				// guarda a revisão

				r = setTextSize(r, size);
				
				int palavras = 0;

				// Percorre-se todos os carateres do texto

				for (int i = 0; text[i] != '\0'; i++) {

					// Caso se encontre um espaço, um \n ou um \t, incrementa-se
					// o contador das palavras

					if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
						palavras++;

						// Continua-se a percorrer o texto até encontrar o
						// carater inicial da próxima palavra (ou o fim)

						while (text[i+1] == ' ' || text[i+1] == '\n' ||
							   text[i+1] == '\t') {
							i++;
						}
					}
				}

				// Coloca-se o número de palavras do texto da revisão na
				// estrutura que guarda a revisão

				setWordCount(r, palavras);
			}

		}
	}
}


/*
 * @brief Faz a leitura e o parsing de uma tag "page" de uma snapshot
 *
 * Lê as tags hierarquicamente inferiores a "page", retirando a informação
 * necessária, criando as estruturas necessárias e inserindo-as na estrutura de
 * dados recebida.
 *
 * @param wd   Estrutura para onde irão ser lidos os dados
 * @param doc  Ficheiro XML
 * @param cur  Apontador para a tag atual do ficheiro XML 
 *
 * @return Estrutura WikiData com toda a informação lida da snapshot
 */
WikiData parsePage(WikiData wd, xmlDocPtr doc, xmlNodePtr cur)
{
	// As estruturas necessárias para receber os dados lidos são criadas

	ARTICLE a = initArticle();
	REVISION r = initRevision();
	CONTRIBUTOR c = initContributor();

	// Percorrem-se todas as tags "filhas" da tag "page"

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {

		// Caso se encontre uma tag cujo nome é "title"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "title"))) {

			// Retira-se o título do artigo

			xmlChar* title = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			// Coloca-se uma cópia do título lido na estrutura que guarda o
			// artigo e liberta-se o espaço ocupado pela informação lida

			r = setTitle(r, (char*) title);
			free(title);
		}

		// Caso se encontre uma tag cujo nome é "id"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "id"))) {

			// Retira-se o ID do artigo

			xmlChar* id = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			// Coloca-se uma cópia do ID lido na estrutura que guarda o artigo e
			// liberta-se o espaço ocupado pela informação lida

			a = setArticleID(a, (char*) id);
			free(id);
		}

		// Caso se encontre uma tag cujo nome é "revision"

		if (!(xmlStrcmp(cur->name, (const xmlChar *) "revision"))) {

			// Faz-se a leitura e o parsing da tag "revision"

			parseRevision(r, c, doc, cur);
		}
	}

	// Adiciona-se a revisão ao artigo

	a = addRevision(a, r);

	int flag = 0; // Flag que indicará, após a inserção do artigo na estrutura,
	              // se já existia a revisão do artigo lido do ficheiro

	// Faz-se a inserção do artigo lido na estrutura

	wd = insertArticle(wd, a, &flag); 

	// Se a flag estiver a 1, indica-nos que a revisão do artigo que tentámos
	// inserir já existia na árvore, logo não é necessário colocar o
	// contribuidor na estrutura pois ele já existe e não se trata de uma nova
	// contribuição
	
	if (flag == 0) {

		// Caso a flag esteja a 0, pode-se inserir o contribuidor na estrutura
		// pois trata-se, de facto, de uma nova contribuição (ou de um
		// contribuidor novo)

		wd = insertContributor(wd, c);
	}
	else {

		// Caso a flag esteja a 1, pode-se libertar a estrutura do contribuidor

		c = freeContributor(c);
	}

	return wd;
}


/*
 * @brief Faz a leitura e o parsing de um ficheiro XML
 *
 * Lê um ficheiro XML (correspondente a uma snapshot), validando-o, fazendo o
 * seu parsing e carregando a estrutura WikiData recebida.
 *
 * @param wd   Estrutura para onde irão ser lidos os dados
 * @param file Ficheiro XML
 *
 * @return Estrutura WikiData com toda a informação lida da snapshot
 */
WikiData parseFile(WikiData wd, char* file)
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	// Abre-se o ficheiro

	doc = xmlParseFile(file);
	
	// Caso ocorra erro na leitura do ficheiro, devolve-se um stderr

	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);
	
	// Caso o ficheiro seja vazio, devolve-se um erro para o stderr

	if (cur == NULL) {
		fprintf(stderr, "Empty document\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	// Caso o ficheiro não seja do tipo esperado, devolve-se um erro para o
	// stderr

	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki") != 0) {
		fprintf(stderr, "Document of the wrong type (root node != mediawiki)");
		xmlFreeDoc(doc);
		return NULL;
	}

	// Lê-se, tag a tag, até encontrar uma "page".

	for (cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "page") == 0) {

			// Faz-se a leitura e o parsing da tag "page"

			wd = parsePage(wd, doc, cur);
		}
	}

	// Liberta-se o espaço alocado pelo ficheiro previamente aberto para leitura

	xmlFreeDoc(doc);

	return wd;
}