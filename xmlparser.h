#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <libxml/parser.h>

#include "interface.h"

void parsePage(AVL a, xmlDocPtr doc, xmlNodePtr cur);
void loadFile(AVL a, char* file);

#endif