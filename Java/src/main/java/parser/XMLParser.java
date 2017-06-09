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

    /*public static int countWords(String s) {
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
    }*/

    public static int countWords(String s) {
        int wordCount = 0;

        boolean beginWord = true;

        char[] strChars = s.toCharArray();

        for (char c : strChars){
            if (c > 32){    // é uma letra
                if (beginWord){
                    wordCount++;
                    beginWord = false;
                }
            }
            else
                beginWord = true;
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
        boolean repeatedRevision;
        int debug = 0;

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
                        if (isArticleID) {
                            debug++;
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

                        if (endTagName.equalsIgnoreCase("page")) {
                            //debug++;
                            /*if (debug > 19800) {
                                System.out.println(debug + " - " + article.getID() + " - " + fileName);
                            }*/
                            article.addRevision(revision);
                            //System.out.println("ARTICLE (id): " + article.getID());
                            //System.out.println("ARTICLE (title): " + article.getRevisions().get(0).getTitle());
                            repeatedRevision = wd.insertArticle(article);

                            if (!contributor.getID().equals("N/A") && !repeatedRevision){
                                wd.insertContributor(contributor);
                            }

                            /*int size = wd.getArtigos().size();
                            if (size > 18400) {
                                System.out.println(size + " - " + fileName);
                            }*/

                            article = null;
                            revision = null;
                            contributor = null;
                        }
                        break;
                }
            }
            System.out.println(debug + " - " + fileName);
            /*int size = wd.getArtigos().size();
            System.out.println(size + " - " + fileName);*/
        }
        catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }
}