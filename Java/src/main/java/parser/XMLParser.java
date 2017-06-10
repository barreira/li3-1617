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

public class XMLParser {

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

    public static void parseFile(WikiData wd, String fileName)
    {
        Article article = null;
        Revision revision = null;
        Contributor contributor = null;

        boolean isRevision = false;
        boolean isContributor = false;

        int repeatedRevision;

        try {
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLEventReader eventReader = factory.createXMLEventReader(new FileInputStream(fileName));

            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();

                switch (event.getEventType()) {
                    case XMLStreamConstants.START_ELEMENT:
                        StartElement startElement = event.asStartElement();
                        String startTagName = startElement.getName().getLocalPart();

                        if (startTagName.equalsIgnoreCase("page")) {
                            article = new Article();
                            revision = new Revision();
                            contributor = new Contributor();
                        }
                        else if (startTagName.equalsIgnoreCase("title")) {
                            revision.setTitle(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("id")) {
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
                            revision.setTimestamp(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("contributor")) {
                            isContributor = true;
                        }
                        else if (startTagName.equalsIgnoreCase("username")) {
                            contributor.setUsername(eventReader.getElementText());
                        }
                        else if (startTagName.equalsIgnoreCase("text")) {
                            String text = eventReader.getElementText();
                            revision.setWordCount(countWords(text));
                            revision.setTextSize(text.getBytes().length);
                        }

                        break;

                    case XMLStreamConstants.END_ELEMENT:
                        EndElement endElement = event.asEndElement();
                        String endTagName = endElement.getName().getLocalPart();

                        if (endTagName.equalsIgnoreCase("contributor")) {
                            isContributor = false;
                        }

                        else if (endTagName.equalsIgnoreCase("revision")) {
                            isRevision = false;
                        }

                        else if (endTagName.equalsIgnoreCase("page")) {
                            article.addRevision(revision);

                            repeatedRevision = wd.insertArticle(article);

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