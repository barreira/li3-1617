package engine;


import java.util.Map;
import java.util.HashMap;
import java.util.List;

import static java.util.stream.Collectors.toMap;

public class WikiData {

    // Variáveis de instância

    private Map<String, Article> artigos;
    private Map<String, Contributor> contribuidores;

    /*private Contributor[] query4; // top 10 de contribuidores com mais revisões
    private Article[] query6;     // top 20 de artigos com maior tamanho

    public static final int q4_size = 10;
    public static final int q5_size = 20;*/

    // Construtores

    public WikiData()
    {
        artigos = new HashMap<>();
        contribuidores = new HashMap<>();
        //query4 = new Contributor[q4_size];
        //query6 = new Article[q5_size];
    }

    public WikiData(Map<String, Article> artigos, Map<String, Contributor> contribuidores) //, Contributor[] query4, Article[] query6
    {
        this.setArtigos(artigos);
        this.setContribuidores(contribuidores);
        //this.setQuery4(query4);
        //this.setQuery6(query6);
    }

    public WikiData(WikiData wd)
    {
        artigos = wd.getArtigos();
        contribuidores = wd.getContribuidores();
        //query4 = wd.getQuery4();
        //query6 = wd.getQuery6();
    }

    // Getters e Setters

    public Map<String, Article> getArtigos()
    {
        return artigos.values()
                      .stream()
                      .collect(toMap(Article::getID, Article::clone));
    }

    public Map<String, Contributor> getContribuidores()
    {
        return contribuidores.values()
                             .stream()
                             .collect(toMap(Contributor::getID, Contributor::clone));
    }
/*
    public Contributor[] getQuery4()
    {
        Contributor[] res = new Contributor[q4_size];

        int i = 0;
        for (Contributor c : query4) {
            res[i] = c.clone();
            i++;
        }

        return res;
    }

    public Article[] getQuery6()
    {

    }
    */

    public void setArtigos(Map<String, Article> artigos)
    {
        this.artigos = artigos.values()
                              .stream()
                              .collect(toMap(Article::getID, Article::clone));
    }

    public void setContribuidores(Map<String, Contributor> contribuidores)
    {
        this.contribuidores = contribuidores.values()
                                            .stream()
                                            .collect(toMap(Contributor::getID, Contributor::clone));
    }

    // Outros métodos

    public boolean insertArticle(Article a) {
        boolean repeatedRevision = false;

        if (artigos.containsKey(a.getID())) {
            Article original = artigos.get(a.getID()); // artigo que já estava no HashMap artigos

            Revision rev = a.getRevisions().get(0); // artigo que se está a tentar inserir só tem uma revisão

            if (!original.containsRevision(rev)) {
                original.addRevision(rev.clone());
            }
            else
                repeatedRevision = true;

            original.incrementOccurrences();
        }
        else {
            artigos.put(a.getID(), a.clone());
        }

        return repeatedRevision;
    }

    public void insertContributor(Contributor c)
    {
        if (contribuidores.containsKey(c.getID())) {
            contribuidores.get(c.getID()).incrementRevisions();
        }
        else {
            contribuidores.put(c.getID(), c.clone());
        }
    }
/*
    public void insertContributor_q4(Contributor c)
    {

    }

    public void insertArticle_q6(Article a)
    {

    }*/

    // Equals, toString, clone e hashCode

    public boolean equals(Object o)
    {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        WikiData wd = (WikiData) o;

        return artigos.equals(wd.getArtigos()) && contribuidores.equals(wd.getContribuidores());
    }

    public String toString()
    {
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

    public WikiData clone()
    {
        return new WikiData(this);
    }

    public int hashCode()
    {
        int result = super.hashCode();
        result = 31 * result + artigos.hashCode();
        result = 31 * result + contribuidores.hashCode();
        return result;
    }
}