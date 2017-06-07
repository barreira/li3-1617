package engine;

import java.util.Map;
import java.util.TreeMap;
import java.util.List;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.toMap;

public class WikiData {

    // Variáveis de instância

    private Map<String, Article> artigos;
    private Map<String, Contributor> contribuidores;
    // private Map<Contributor> contributorMap; // para q5
    // private Map<Article> articleMap // para q7 e q10

    // Construtores

    public WikiData() {
        artigos = new TreeMap<String, Article>();
        contribuidores = new TreeMap<String, Contributor>();
    }

    public WikiData(Map<String, Article> artigos, Map<String, Contributor> contribuidores) {
        setArtigos(artigos);
        setContribuidores(contribuidores);
    }

    public WikiData(WikiData wd) {
        artigos = wd.getArtigos();
        contribuidores = wd.getContribuidores();
    }

    // Getters e Setters

    public Map<String, Article> getArtigos() {
        return artigos.values()
                      .stream()
                      .collect(toMap(Article::getID, Article::clone));
    }

    public Map<String, Contributor> getContribuidores() {
        return contribuidores.values()
                             .stream()
                             .collect(toMap(Contributor::getID, Contributor::clone));
    }

    public void setArtigos(Map<String, Article> artigos) {
        this.artigos = artigos.values()
                              .stream()
                              .collect(toMap(Article::getID, Article::clone));
    }

    public void setContribuidores(Map<String, Contributor> contribuidores) {
        this.contribuidores = contribuidores.values()
                                            .stream()
                                            .collect(toMap(Contributor::getID, Contributor::clone));
    }

    // Outros métodos

    public void insertArticle(Article a) {
        if (artigos.containsKey(a.getID())) {
            Artigo original = artigos.get(a.getID()); // artigo que já estava no TreeMap artigos

            List<Revision> revisions = original.getRevisions();

            Revision rev1 = revisions.get(revisions.size() - 1);
            Revision rev2 = a.getRevisions().get(0); // artigo que se está a tentar inserir só tem uma revisão

            if (rev1.getID().equals(rev2.getID()) == false) {
                revisions.add(rev2.clone());
            }
        }
        else {
            artigos.put(a.getID(), a.clone());
        }
    }

    public void insertContributor(Contributor c) {
        if (contribuidores.containsKey(c.getID())) {

            // continuar isto

        }
        else {
            contribuidores.put(c.getID(), c.clone());
        }
    }

    // Equals, toString, clone e hashCode

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        WikiData wd = (WikiData) o;

        return artigos.equals(wd.getArtigos()) && contribuidores.equals(wd.getContribuidores());
    }

    public String toString() {
        int counter1 = 1, counter2 = 1;
        StringBuilder sb = new StringBuilder("WikiData: { ");

        sb.append(" { ");

        for (Article a : artigos.values()) {
            sb.append(a.toString());

            if (counter1 < artigos.values().size()) {
                sb.append(", ");
            }

            counter1++;
        }

        sb.append(" }, { ");

        for (Contributor c : contribuidores.values()) {
            sb.append(c.toString());

            if (counter2 < contribuidores.values().size()) {
                sb.append(", ");
            }

            counter2++;
        }

        sb.append(" } }");

        return sb.toString();
    }

    public WikiData clone() {
        return new WikiData(this);
    }

    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + artigos.hashCode();
        result = 31 * result + contribuidores.hashCode();
        return result;
    }
}