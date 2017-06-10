package parser;

import engine.Article;
import engine.Contributor;
import engine.Revision;
import engine.WikiData;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

/**
 * Classe responsável pelo parsing dos ficheiro XML relativos às snapshots da wikipédia
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class XMLParser {

    /**
     * Cálcula o número de palavras de uma string
     *
     * @param s String
     */
    public static int countWords(String s)
    {
        int wordCount = 0;
        boolean beginWord = true;
        char[] strChars = s.toCharArray();

        for (char c : strChars) {
            if (c > 32) { // é uma letra
                if (beginWord) {
                    wordCount++;
                    beginWord = false;
                }
            }
            else {
                beginWord = true;
            }
        }

        return wordCount;
    }

    /**
     * Faz o parsing de um ficheiro XML
     *
     * @param wd       Variável do tipo WikiData para onde serão lidos os dados
     * @param fileName Nome do ficheiro XML
     */
    public static void parseFile(WikiData wd, String fileName)
    {
        Article article = null;
        Revision revision = null;
        Contributor contributor = null;

        boolean isRevision = false;    // serve para indicar se se está a fazer parsing de uma tag <revision>
        boolean isContributor = false; // serve para indicar se se está a fazer parsing de uma tag <contributor>

        int repeatedRevision; // indica se a revisão que se tentou inserir já se encontrava no map dos artigos (i.e. se
                              // se tratou, de facto, de uma nova contribuição)

        try {
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLEventReader eventReader = factory.createXMLEventReader(new FileInputStream(fileName));

            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();

                switch (event.getEventType()) {

                    /* Tag do tipo <tag> (i.e. tag de abertura) */

                    case XMLStreamConstants.START_ELEMENT:
                        StartElement startElement = event.asStartElement();
                        String startTagName = startElement.getName().getLocalPart();

                        if (startTagName.equalsIgnoreCase("page")) {

                            /* Caso se encontre uma tag <page>, iniciam-se os objetos para guardar os dados do artigo,
                               revisão e contribuidor */

                            article = new Article();
                            revision = new Revision();
                            contributor = new Contributor();
                        }
                        else if (startTagName.equalsIgnoreCase("title")) {

                            /* Coloca-se o título lido na revisão */

                            revision.setTitle(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("id")) {

                            /* Coloca-se o ID lido no objeto correspondente (contribuidor, revisão ou artigo) */

                            if (isContributor) {
                                contributor.setID(eventReader.getElementText());
                            }
                            else if (isRevision) {
                                revision.setID(eventReader.getElementText());
                            }
                            else {
                                article.setID(eventReader.getElementText());
                            }
                        }
                        else if (startTagName.equalsIgnoreCase("revision")) {
                            isRevision = true;
                        }
                        else if (startTagName.equalsIgnoreCase("timestamp")) {

                            /* Coloca-se o timestamp lido na revisão */

                            revision.setTimestamp(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("contributor")) {
                            isContributor = true;
                        }
                        else if (startTagName.equalsIgnoreCase("username")) {

                            /* Coloca-se o username lido no contribuidor */

                            contributor.setUsername(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("text")) {
                            String text = eventReader.getElementText();

                            /* Coloca-se os valores do tamanho do texto e do número de palavras na revisão */

                            revision.setWordCount(countWords(text));
                            revision.setTextSize(text.getBytes().length);
                        }

                        break;

                    /* Tag do tipo </tag> (i.e. tag de fecho) */

                    case XMLStreamConstants.END_ELEMENT:
                        EndElement endElement = event.asEndElement();
                        String endTagName = endElement.getName().getLocalPart();

                        /* Caso encontre uma tag </contributor>, coloca o boolean isContributor a falso */

                        if (endTagName.equalsIgnoreCase("contributor")) {
                            isContributor = false;
                        }

                        /* Caso encontre uma tag </revision>, coloca o boolean isRevision a falso */

                        else if (endTagName.equalsIgnoreCase("revision")) {
                            isRevision = false;
                        }

                        else if (endTagName.equalsIgnoreCase("page")) {

                            /* Adiciona-se a revisão ao artigo lido */

                            article.addRevision(revision);

                            /* Insere-se o artigo no map de artigos */

                            repeatedRevision = wd.insertArticle(article);

                            /* Apenas é inserido o contribuidor no map caso se trate, de facto, de uma nova contribuição
                               (i.e. caso a revisão lida ainda não esteja no map dos artigos) */

                            if (repeatedRevision == 0){
                                wd.insertContributor(contributor);
                            }
                        }

                        break;
                }
            }
        }
        catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }
}