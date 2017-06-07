package engine;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Iterator;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class XMLParser {

    public void parseFile(WikiData wd, String fileName)
    {
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
                            else if (isPage) isArticleID = true;
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
                            // contar numero de palavras + revision.setWC()
                            // calcular tamanho do texto + revision.setTextSize()
                            isText = false;
                        }
                        break;
                    case XMLStreamConstants.END_ELEMENT:
                        EndElement endElement = event.asEndElement();
                        String endTagName = endElement.getName().getLocalPart();

                        if (endTagName.equalsIgnoreCase("page")) {
                            article.addRevision(revision);
                            wd.insertArticle(article);
                            wd.insertContributor(contributor);
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