package engine;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

public class WikiData {

    // Variáveis de instância

    private Map<String, Article> artigos;
    private Map<String, Contributor> contribuidores;
    private int allArticles; // q1
    private int uniqueArticles; // q2
    private int allRevisions; // q3
    private List<Contributor> q4; // top 10 de contribuidores com mais revisões
    private List<Article> q6;     // top 20 de artigos com maior tamanho

    public static final int q4_size = 10;
    public static final int q6_size = 20;

    // Construtores

    public WikiData()
    {
        artigos = new HashMap<>();
        contribuidores = new HashMap<>();
        allArticles = 0;
        uniqueArticles = 0;
        allRevisions = 0;
        q4 = new ArrayList<>(q4_size);
        q6 = new ArrayList<>(q6_size);
    }

    public WikiData(Map<String, Article> artigos, Map<String, Contributor> contribuidores, int allArticles,
                    int uniqueArticles, int allRevisions, List<Contributor> q4, List<Article> q6)
    {
        this.setArtigos(artigos);
        this.setContribuidores(contribuidores);
        this.setAllArticles(allArticles);
        this.setUniqueArticles(uniqueArticles);
        this.setAllRevisions(allRevisions);
        this.setQ4(q4);
        this.setQ6(q6);
    }

    public WikiData(WikiData wd)
    {
        artigos = wd.getArtigos();
        contribuidores = wd.getContribuidores();
        allArticles = wd.getAllArticles();
        uniqueArticles = wd.getUniqueArticles();
        allRevisions = wd.getAllRevisions();
        q4 = wd.getQ4();
        q6 = wd.getQ6();
    }

    // Getters e Setters

    public Map<String, Article> getArtigos()
    {
        return artigos.values().stream()
                               .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    public Map<String, Contributor> getContribuidores()
    {
        return contribuidores.values().stream()
                                      .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
    }

    public int getAllArticles()
    {
        return allArticles;
    }

    public int getUniqueArticles()
    {
        return uniqueArticles;
    }

    public int getAllRevisions()
    {
        return allRevisions;
    }

    public List<Contributor> getQ4()
    {
        return q4.stream()
                 .map(Contributor::clone)
                 .collect(Collectors.toList());
    }

    public List<Article> getQ6()
    {
        return q6.stream()
                 .map(Article::clone)
                 .collect(Collectors.toList());
    }

    public void setArtigos(Map<String, Article> artigos)
    {
        this.artigos = artigos.values().stream()
                                       .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    public void setContribuidores(Map<String, Contributor> contribuidores)
    {
        this.contribuidores = contribuidores.values().stream()
                                                     .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
    }

    public void setAllArticles(int allArticles)
    {
        this.allArticles = allArticles;
    }

    public void setUniqueArticles(int uniqueArticles)
    {
        this.uniqueArticles = uniqueArticles;
    }

    public void setAllRevisions(int allRevisions)
    {
        this.allRevisions = allRevisions;
    }

    public void setQ4(List<Contributor> q4)
    {
        this.q4 = q4.stream()
                    .map(Contributor::clone)
                    .collect(Collectors.toList());
    }

    public void setQ6(List<Article> q6)
    {
        this.q6 = q6.stream()
                    .map(Article::clone)
                    .collect(Collectors.toList());
    }

    // Outros métodos

    public int insertArticle(Article a)
    {
        Article original = artigos.get(a.getID());

        if (original != null) {
            original.incrementOccurrences();

            List<Revision> revisions = original.getRevisions();

            Revision r1 = revisions.get(revisions.size() - 1);
            Revision r2 = a.getRevisions().get(0); // artigo que se está a tentar inserir só tem uma revisão

            if (!r1.getID().equals(r2.getID())) {
                original.addRevision(r2.clone());
                insertArticleQ6(original.clone());
            }
            else {
                allArticles++;
                return 1;
            }
        }
        else {
            artigos.put(a.getID(), a.clone());
            insertArticleQ6(a.clone());
            uniqueArticles++;
        }

        allRevisions++;
        allArticles++;

        return 0;
    }

    public void insertContributor(Contributor c)
    {
        Contributor original = contribuidores.get(c.getID());

        if (original != null) {
            original.incrementRevisions();

            if (!original.getID().equals("N/A")) {
                insertContributorQ4(original.clone());
            }
        }
        else {
            contribuidores.put(c.getID(), c.clone());

            if (!c.getID().equals("N/A")) {
                insertContributorQ4(c.clone());
            }
        }
    }

    public int getLeastIndexQ4(List<Contributor> l)
    {
        Contributor menor = l.get(0);
        int index = 0;

        for (int i = 1; i < l.size(); i++) {
            if (l.get(i).compareByRevisions(menor) == -1) {
                menor = l.get(i);
                index = i;
            }
        }

        return index;
    }

    public void insertContributorQ4(Contributor c)
    {
        if (q4.stream().map(Contributor::getID).anyMatch(id -> id.equals(c.getID()))) {
            int index = 0;

            for (int i = 0; i < q4.size(); i++) {
                if (q4.get(i).getID().equals(c.getID())) {
                    index = i;
                }
            }

            q4.set(index, c.clone());
        }
        else {
            if (q4.size() < q4_size) {
                q4.add(c.clone());
            }
            else {
                int index = getLeastIndexQ4(q4);

                if (q4.get(index).compareByRevisions(c) == -1) {
                    q4.set(index, c.clone());
                }
            }
        }
    }

    public int getLeastIndexQ6(List<Article> l)
    {
        Article menor = l.get(0);
        int index = 0;

        for (int i = 1; i < l.size(); i++) {
            if (l.get(i).compareByTextSize(menor) == -1) {
                menor = l.get(i);
                index = i;
            }
        }

        return index;
    }

    public void insertArticleQ6(Article a)
    {
        if (q6.stream().map(Article::getID).anyMatch(id -> id.equals(a.getID()))) {
            int index = 0;

            for (int i = 0; i < q6.size(); i++) {
                if (q6.get(i).getID().equals(a.getID())) {
                    index = i;
                }
            }

            q6.set(index, a.clone());
        }
        else {
            if (q6.size() < q6_size) {
                q6.add(a.clone());
            }
            else {
                int index = getLeastIndexQ6(q6);

                if (q6.get(index).compareByTextSize(a) == -1) {
                    q6.set(index, a.clone());
                }
            }
        }
    }

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