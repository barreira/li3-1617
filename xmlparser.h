/**
 * @file xmlparser.h
 * @brief API do módulo do parsing XML
 *
 * @author Ana Paula Carvalho  - A61855
 * @author Joana Arantes       - A57810
 * @author João Pires Barreira - A73831 
 * @author Miguel Cunha        - A78478
 *
 * @version 2017-04-28
 */

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "queries.h"

/****************************************************************************************
 *                                       API                                            *
 ****************************************************************************************/

/*
 * @brief Faz a leitura e o parsing de um ficheiro XML
 *
 * Lê um ficheiro XML (correspondente a uma snapshot), validando-o, fazendo o seu parsing
 * e carregando a estrutura WikiData recebida.
 *
 * @param wd   Estrutura para onde irão ser lidos os dados
 * @param file Ficheiro XML
 *
 * @return Estrutura WikiData com toda a informação lida da snapshot
 */
WikiData parseFile(WikiData wd, char* file);

#endif