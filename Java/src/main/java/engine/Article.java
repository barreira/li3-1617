package engine;

import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class Article {

    // Variáveis de instância

    private String id;
    private int occurrences;
    private List<Revision> revisions;

    // Construtores

    public Article() {
        id = "N/A";
        occurrences = 1;
        revisions = new ArrayList<>();
    }

    public Article(String id, int occurrences, List<Revision> revisions) {
        setID(id);
        setOccurrences(occurrences);
        setRevisions(revisions);
    }

    public Article(Article a) {
        id = a.getID();
        occurrences = a.getOccurrences();
        revisions = a.getRevisions();
    }

    // Getters e Setters

    public String getID() {
        return id;
    }

    public int getOccurrences() {
        return occurrences;
    }

    public List<Revision> getRevisions() {
        return revisions.stream()
                        .map(Revision::clone)
                        .collect(Collectors.toList());
    }

    public void setID(String id) {
        this.id = id;
    }

    public void setOccurrences(int occurrences) {
        this.occurrences = occurrences;
    }

    public void setRevisions(List<Revision> revisions) {
        this.revisions = revisions.stream()
                                  .map(Revision::clone)
                                  .collect(Collectors.toList());
    }

    // Outros métodos

    public void addRevision(Revision r) {
        revisions.add(r.clone());
    }

    public void incrementOccurrences() {
        occurrences += 1;
    }

    public int getMaxTextSize() {
        int maxTextSize = 0;

        for (Revision rev : this.revisions) {
            if (rev.getTextSize() > maxTextSize)
                maxTextSize = rev.getTextSize();
        }

        return maxTextSize;
    }

    public int getMaxWordCount() {
        int maxWordCount = 0;

        for (Revision rev : this.revisions) {
            if (rev.getWordCount() > maxWordCount)
                maxWordCount = rev.getWordCount();
        }

        return maxWordCount;
    }

    public String getLatestTitle() {
        String latestTitle = "";
        long id = 0;

        for (Revision rev : this.revisions) {
            if (Long.parseLong(rev.getID()) > id)   // se o id for maior, é mais recente
                latestTitle = rev.getTitle();
        }

        return latestTitle;
    }

    public boolean containsRevision(Revision revision) {
        Iterator<Revision> it = revisions.iterator();
        boolean found = false;
        String revID = revision.getID();

        while(!found && it.hasNext()){
            Revision rev = it.next();
            if (rev.getID().equals(revID))
                found = true;
        }

        return found;
    }

    // Equals, toString, clone e hashCode

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        Article a = (Article) o;

        return id.equals(a.getID()) && occurrences == a.getOccurrences() && revisions.equals(a.getRevisions());
    }

    public String toString() {
        int counter = 1;
        StringBuilder sb = new StringBuilder("Article: { ");

        sb.append(id);
        sb.append(", ");
        sb.append(occurrences);
        sb.append(", ");
        sb.append("{ ");

        for (Revision r : revisions) {
            sb.append(r.toString());

            if (counter < revisions.size()) {
                sb.append(", ");
            }

            counter++;
        }

        sb.append(" } }");

        return sb.toString();
    }

    public Article clone() {
        return new Article(this);
    }

    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + occurrences;
        result = 31 * result + revisions.hashCode();
        return result;
    }
}