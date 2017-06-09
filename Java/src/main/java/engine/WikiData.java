package engine;


import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

//import static java.util.stream.Collectors.toMap;

public class WikiData {

    // Variáveis de instância

    private Map<String, Article> artigos;
    private Map<String, Contributor> contribuidores;

    private List<Contributor> q4; // top 10 de contribuidores com mais revisões
    private List<Article> q6;     // top 20 de artigos com maior tamanho

    public static final int q4_size = 10;
    public static final int q6_size = 20;

    // Construtores

    public WikiData()
    {
        artigos = new HashMap<>();
        contribuidores = new HashMap<>();
        q4 = new ArrayList<Contributor>(q4_size);
        q6 = new ArrayList<Article>(q6_size);
    }

    public WikiData(Map<String, Article> artigos, Map<String, Contributor> contribuidores, List<Contributor> q4,
                    List<Article> q6)
    {
        this.setArtigos(artigos);
        this.setContribuidores(contribuidores);
        this.setQ4(q4);
        this.setQ6(q6);
    }

    public WikiData(WikiData wd)
    {
        artigos = wd.getArtigos();
        contribuidores = wd.getContribuidores();
        q4 = wd.getQ4();
        q6 = wd.getQ6();
    }

    // Getters e Setters

    public Map<String, Article> getArtigos()
    {
        return artigos.values()
                      .stream()
                      .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    public Map<String, Contributor> getContribuidores()
    {
        return contribuidores.values()
                             .stream()
                             .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
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
        this.artigos = artigos.values()
                              .stream()
                              .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    public void setContribuidores(Map<String, Contributor> contribuidores)
    {
        this.contribuidores = contribuidores.values()
                                            .stream()
                                            .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
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
        if (artigos.containsKey(a.getID())) {
            Article original = artigos.get(a.getID()); // artigo que já estava no HashMap artigos

            List<Revision> revisions = original.getRevisions();

            Revision rev1 = revisions.get(revisions.size() - 1);
            Revision rev2 = a.getRevisions().get(0); // artigo que se está a tentar inserir só tem uma revisão

            if (rev1.getID().equals(rev2.getID()) == false) {
                original.addRevision(rev2.clone());
            }
            else {
                return 1; // não foi inserido nada (i.e. não se trata de uma nova contribuição)
            }

            original.incrementOccurrences();
        }
        else {
            artigos.put(a.getID(), a.clone());
        }

        insertArticleQ6(a);

        return 0;
    }

    public void insertContributor(Contributor c)
    {
        if (contribuidores.containsKey(c.getID())) { // podemos melhorar isto
            contribuidores.get(c.getID()).incrementRevisions();
        }
        else {
            contribuidores.put(c.getID(), c.clone());
        }

        if (c.getID().compareTo("N/A") != 0) {
            insertContributorQ4(contribuidores.get(c.getID()).clone());
        }
    }

    private int getLeastIndexQ4(List<Contributor> l) {
        Contributor menor = l.get(0);
        int index = 0;

        for (int i = 1; i < l.size(); i++) {
            if (l.get(i).compare(menor) == -1) {
                menor = l.get(i);
                index = i;
            }
        }

        return index;
    }

    private int getLeastIndexQ6(List<Article> l) {
        Article menor = l.get(0);
        int index = 0;

        for (int i = 1; i < l.size(); i++) {
            if (l.get(i).compare(menor) == -1) {
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

                if (q4.get(index).compare(c) == -1) {
                    q4.set(index, c.clone());
                }
            }
        }
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

                if (q6.get(index).compare(a) == -1) {
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