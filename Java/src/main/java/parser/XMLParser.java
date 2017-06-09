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

    public static int countWords(String s) {
        int wordCount = 0;

        boolean word = false;
        int endOfLine = s.length() - 1;

        for (int i = 0; i < s.length(); i++) {

            if (Character.isLetter(s.charAt(i)) && i != endOfLine) {
                word = true;
            }
            else if (!Character.isLetter(s.charAt(i)) && word) {
                wordCount++;
                word = false;
            }
            else if (Character.isLetter(s.charAt(i)) && i == endOfLine) {
                wordCount++;
            }
        }

        return wordCount;
    }

    public static void parseFile(WikiData wd, String fileName) {
        Article article = null;
        Revision revision = null;
        Contributor contributor = null;

        boolean isPage = false;
        boolean isTitle = false;
        boolean isArticleID = false;
        boolean isRevision = false;
        boolean isRevisionID = false;
        boolean isTimestamp = false;
        boolean isContributor = false;
        boolean isContributorID = false;
        boolean isUsername = false;
        boolean isText = false;
        int tamanho = 0;

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
                            isPage = true;
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
                            tamanho = 0;
                            isText = true;
                        }
                        break;
                    case XMLStreamConstants.CHARACTERS:
                        Characters characters = event.asCharacters();

                        if (isTitle) {
                            revision.setTitle(characters.getData());
                            isTitle = false;
                        }
                        if (isArticleID) {
                            article.setID(characters.getData());
                            isArticleID = false;
                        }
                        if (isRevisionID) {
                            revision.setID(characters.getData());
                            isRevisionID = false;
                        }
                        if (isContributorID) {
                            contributor.setID(characters.getData());
                            isContributorID = false;
                        }
                        if (isTimestamp) {
                            revision.setTimestamp(characters.getData());
                            isTimestamp = false;
                        }
                        if (isUsername) {
                            contributor.setUsername(characters.getData());
                            isUsername = false;
                        }
                        if (isText) {
                            /*if (debug < 3) {
                                System.out.println("!!!" + debug + "!!!");
                                debug++;
                                System.out.println(characters.getData());
                            }*/

                            tamanho += characters.getData().length();

                            //revision.setWordCount(countWords(characters.getData()));
                            //revision.setTextSize(characters.getData().length());
                        }
                        break;
                    case XMLStreamConstants.END_ELEMENT:
                        EndElement endElement = event.asEndElement();
                        String endTagName = endElement.getName().getLocalPart();

                        if (endTagName.equalsIgnoreCase("contributor")) {
                            isContributor = false;
                        }

                        if (endTagName.equalsIgnoreCase("revision")) {
                            isRevision = false;
                        }

                        if (endTagName.equalsIgnoreCase("text")) {
                            revision.setTextSize(tamanho);
                            isText = false;
                        }

                        if (endTagName.equalsIgnoreCase("page")) {
                            article.addRevision(revision);

                            int ret = wd.insertArticle(article);

                            if (ret == 0) {
                                wd.insertContributor(contributor);
                            }

                            article = null;
                            revision = null;
                            contributor = null;
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