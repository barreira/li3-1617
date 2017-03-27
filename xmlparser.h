#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <libxml/parser.h>

#include "interface.h"

void parsePage(TAD_istruct a, xmlDocPtr doc, xmlNodePtr cur);
void loadFile(TAD_istruct a, char* file);

#endif