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
import javax.xml.stream.events.Characters;
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

        boolean isTitle = false;
        boolean isArticleID = false;
        boolean isRevision = false;
        boolean isRevisionID = false;
        boolean isTimestamp = false;
        boolean isContributor = false;
        boolean isContributorID = false;
        boolean isUsername = false;

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
                            isTitle = true;
                        }
                        else if (startTagName.equalsIgnoreCase("id")) {
                            if (isContributor) isContributorID = true;
                            else if (isRevision) isRevisionID = true;
                            else isArticleID = true;
                        }
                        else if (startTagName.equalsIgnoreCase("revision")) {
                            isRevision = true;
                        }
                        else if (startTagName.equalsIgnoreCase("timestamp")) {
                            isTimestamp = true;
                        }
                        else if (startTagName.equalsIgnoreCase("contributor")) {
                            isContributor = true;
                        }
                        else if (startTagName.equalsIgnoreCase("username")) {
                            isUsername = true;
                        }
                        else if (startTagName.equalsIgnoreCase("text")) {
                            String text = eventReader.getElementText();
                            revision.setWordCount(countWords(text));
                            revision.setTextSize(text.getBytes().length);
                        }

                        break;

                    case XMLStreamConstants.CHARACTERS:
                        Characters characters = event.asCharacters();

                        if (isTitle) {
                            revision.setTitle(characters.getData());
                            isTitle = false;
                        }
                        else if (isArticleID) {
                            article.setID(characters.getData());
                            isArticleID = false;
                        }
                        else if (isRevisionID) {
                            revision.setID(characters.getData());
                            isRevisionID = false;
                        }
                        else if (isContributorID) {
                            contributor.setID(characters.getData());
                            isContributorID = false;
                        }
                        else if (isTimestamp) {
                            revision.setTimestamp(characters.getData());
                            isTimestamp = false;
                        }
                        else if (isUsername) {
                            contributor.setUsername(characters.getData());
                            isUsername = false;
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