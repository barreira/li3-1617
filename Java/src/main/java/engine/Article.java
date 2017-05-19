package engine;

import java.util.Set;
import java.util.HashSet;
import java.util.stream.Collectors;

public class Article {

    // Variáveis de instância

    private String id;
    private int occurrences;
    private Set<Revision> revisions;

    // Construtores

    public Article() {
        id = "N/A";
        occurrences = 0;
        revisions = new HashSet<>();
    }

    public Article(String id, int occurrences, Set<Revision> revisions) {
        this.id = id;
        this.occurrences = occurrences;
        this.revisions = revisions;
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

    public Set<Revision> getRevisions() {
        return revisions.stream()
                        .map(Revision::clone)
                        .collect(Collectors.toSet());
    }

    public void setID(String id) {
        this.id = id;
    }

    public void setOccurrences(int occurrences) {
        this.occurrences = occurrences;
    }

    public void setRevisions(Set<Revision> revisions) {
        this.revisions = revisions.stream()
                                  .map(Revision::clone)
                                  .collect(Collectors.toSet());
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