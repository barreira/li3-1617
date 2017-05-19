package engine;

import java.util.Set;
import java.util.HashSet;
import java.util.stream.Collectors;

public class WikiData {

    // Variáveis de instância

    private Set<Article> artigos;
    private Set<Contributor> contribuidores;
    // private Map<Contributor> contributorMap; // para q5
    // private Map<Article> articleMap // para q7 e q10
    //

    // Construtores

    public WikiData() {
        artigos = new HashSet<>();
        contribuidores = new HashSet<>();
    }

    public WikiData(Set<Article> artigos, Set<Contributor> contribuidores) {
        this.artigos = artigos;
        this.contribuidores = contribuidores;
    }

    public WikiData(WikiData wd) {
        artigos = wd.getArtigos();
        contribuidores = wd.getContribuidores();
    }

    // Getters e Setters

    public Set<Article> getArtigos() {
        return artigos.stream()
                      .map(Article::clone)
                      .collect(Collectors.toSet());
    }

    public Set<Contributor> getContribuidores() {
        return contribuidores.stream()
                             .map(Contributor::clone)
                             .collect(Collectors.toSet());
    }

    public void setArtigos(Set<Article> artigos) {
        this.artigos = artigos.stream()
                              .map(Article::clone)
                              .collect(Collectors.toSet());;
    }

    public void setContribuidores(Set<Contributor> contribuidores) {
        this.contribuidores = contribuidores.stream()
                                            .map(Contributor::clone)
                                            .collect(Collectors.toSet());;
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

        for (Article a : artigos) {
            sb.append(a.toString());

            if (counter1 < artigos.size()) {
                sb.append(", ");
            }

            counter1++;
        }

        sb.append(" }, { ");

        for (Contributor c : contribuidores) {
            sb.append(c.toString());

            if (counter2 < contribuidores.size()) {
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