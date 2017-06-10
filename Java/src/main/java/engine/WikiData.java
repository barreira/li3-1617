package engine;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Classe responsável pelo armazenamento dos dados extraídos das snapshots da wikipédia
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class WikiData {

    // Variáveis de instância

    private Map<String, Article> artigos;            // mapeamento entre os artigos e o seu ID
    private Map<String, Contributor> contribuidores; // mapeamento entre os contribuidores e o seu ID
    private int allArticles;                         // número total de artigos (variável auxiliar à query 1)
    private int uniqueArticles;                      // número de artigos únicos (variável auxiliar à query 2)
    private int allRevisions;                        // número total de revisões (variável auxiliar à query 3)
    private List<Contributor> q4;                    // top 10 de contribuidores com mais revisões (variável auxiliar à query 4)
    private List<Article> q6;                        // top 20 de artigos com maior tamanho (variável auxiliar à query 6)

    public static final int q4_size = 10; // tamanho do top da query 4
    public static final int q6_size = 20; // tamanho do top da query 6

    // Construtores

    /**
     * Construtor vazio
     */
    public WikiData()
    {
        artigos = new HashMap<>();
        contribuidores = new HashMap<>();
        allArticles = 0;
        uniqueArticles = 0;
        allRevisions = 0;
        q4 = new ArrayList<>(q4_size); // lista da q4 é inicilizada com tamanho q4_size
        q6 = new ArrayList<>(q6_size); // lista da q6 é inicilizada com tamanho q6_size
    }

    /**
     * Construtor por partes
     *
     * @param artigos        Map dos artigos
     * @param contribuidores Map dos contribuidores
     * @param allArticles    Número total de artigos
     * @param uniqueArticles Número total de artigos únicos
     * @param allRevisions   Número total de revisões
     * @param q4             Top de contribuidores com mais revisões
     * @param q6             Top de artigos com maior tamanho
     */
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

    /**
     * Construtor por cópia
     *
     * @param wd WikiData a copiar
     */
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

    /**
     * Devolve o map dos artigos
     */
    public Map<String, Article> getArtigos()
    {
        return artigos.values().stream()
                               .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    /**
     * Devolve o map dos contribuidores
     */
    public Map<String, Contributor> getContribuidores()
    {
        return contribuidores.values().stream()
                                      .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
    }

    /**
     * Devolve o número total de artigos
     */
    public int getAllArticles()
    {
        return allArticles;
    }

    /**
     * Devolve o número total de artigos únicos
     */
    public int getUniqueArticles()
    {
        return uniqueArticles;
    }

    /**
     * Devolve o número total de revisões
     */
    public int getAllRevisions()
    {
        return allRevisions;
    }

    /**
     * Devolve o top de contribuidores com mais revisões
     */
    public List<Contributor> getQ4()
    {
        return q4.stream()
                 .map(Contributor::clone)
                 .collect(Collectors.toList());
    }

    /**
     * Devolve o top dos artigos com maior tamanho
     */
    public List<Article> getQ6()
    {
        return q6.stream()
                 .map(Article::clone)
                 .collect(Collectors.toList());
    }

    /**
     * Altera o map dos artigos
     */
    public void setArtigos(Map<String, Article> artigos)
    {
        this.artigos = artigos.values().stream()
                                       .collect(Collectors.toMap(Article::getID, Article::clone));
    }

    /**
     * Altera o map dos contribuidores
     */
    public void setContribuidores(Map<String, Contributor> contribuidores)
    {
        this.contribuidores = contribuidores.values().stream()
                                                     .collect(Collectors.toMap(Contributor::getID, Contributor::clone));
    }

    /**
     * Altera o valor do total dos artigos
     */
    public void setAllArticles(int allArticles)
    {
        this.allArticles = allArticles;
    }

    /**
     * Altera o valor do total dos artigos únicos
     */
    public void setUniqueArticles(int uniqueArticles)
    {
        this.uniqueArticles = uniqueArticles;
    }

    /**
     * Altera o valor do total de revisões
     */
    public void setAllRevisions(int allRevisions)
    {
        this.allRevisions = allRevisions;
    }

    /**
     * Altera o top de contribuidores com mais revisões
     */
    public void setQ4(List<Contributor> q4)
    {
        this.q4 = q4.stream()
                    .map(Contributor::clone)
                    .collect(Collectors.toList());
    }

    /**
     * Devolve o top dos artigos com maior tamanho
     */
    public void setQ6(List<Article> q6)
    {
        this.q6 = q6.stream()
                    .map(Article::clone)
                    .collect(Collectors.toList());
    }

    // Outros métodos

    /**
     * Insere um artigo no map de artigos da WikiData
     *
     * @param a Artigo a inserir no map dos artigos da WikiData
     *
     * @return 1 caso se trate da inserção de uma revisão repetida
     *         0 caso contrário
     */
    public int insertArticle(Article a)
    {
        /* Tenta-se ir buscar o artigo ao map de artigos */

        Article original = artigos.get(a.getID());

        /* Se a for diferente de null, isto indica-nos que o artigo existe no map. Ao não estarmos a testar a existência
           do artigo diretamente (i.e. containsKey(a.getID())) e só depois irmos buscá-lo à arvore (com o get), estamos
           a poupar uma iteração do map dos artigos. */

        if (original != null) {

            /* Como se trata de uma nova ocorrência de um artigo que já existia no map, incrementa-se o contador das
               ocorrências do mesmo */

            original.incrementOccurrences();

            List<Revision> revisions = original.getRevisions();

            Revision r1 = revisions.get(revisions.size() - 1);
            Revision r2 = a.getRevisions().get(0); // artigo que se está a tentar inserir só tem uma revisão

            /* Caso a revisão que se está a tentar inserir não exista, insere-se-a na lista de revisões do artigo e
               insere-se o artigo na estrutura auxiliar da q6 */

            if (!r1.getID().equals(r2.getID())) {
                original.addRevision(r2.clone());
                insertArticleQ6(original.clone());
            }

            /* Caso já exista a revisão é devolvido 1 mas tem de se incrementar o contador referente ao total de artigos
               encontrados */

            else {
                allArticles++;
                return 1;
            }
        }

        /* Caso o artigo não exista no map de artigos, adiciona-se-o ao map, insere-se-o na estrutura do top da q6 e
           incrementa-se a variável referente à totalidade dos artigos únicos encontrados */

        else {
            artigos.put(a.getID(), a.clone());
            insertArticleQ6(a.clone());
            uniqueArticles++;
        }

        /* Em ambos os casos, incrementam-se as variáveis referentes à totalidade das revisões e dos artigos */

        allRevisions++;
        allArticles++;

        /* É devolvido 0 pois tratou-se, de facto, de uma nova contribuição (pois a revisão não existia previamente) */

        return 0;
    }

    /**
     * Insere um contribuidor no map de contribuidores da WikiData
     *
     * @param c Contribuidor a inserir no map dos contribuidores
     */
    public void insertContributor(Contributor c)
    {
        /* Tenta-se ir buscar o contribuidor ao map dos contribuidores */

        Contributor original = contribuidores.get(c.getID());

        /* Se c for diferente de null, isto indica-nos que o contribuidor existe no map. Ao não estarmos a testar a
           existência do contribuidor diretamente (i.e. containsKey(c.getID())) e só depois irmos buscá-lo ao map (com o
           get), estamos a poupar uma iteração do map dos contribuidores. */

        if (original != null) {

            /* Como se trata de uma nova ocorrência de um contribuidor que já existia no map, incrementa-se o contador
               das revisões do mesmo */

            original.incrementRevisions();

            /* Caso o ID do contribuidor seja diferente de "N/A" (i.e. não havia referência à tag <username>), insere-se
               o contribuidor na estrutura auxiliar à q4 */

            if (!original.getID().equals("N/A")) {
                insertContributorQ4(original.clone());
            }
        }

        /* Caso o contribuidor não exista no map dos contribuidores, adiciona-se-o ao map e insere-se-o na estrutura do
           top da q6 */

        else {
            contribuidores.put(c.getID(), c.clone());

            if (!c.getID().equals("N/A")) {
                insertContributorQ4(c.clone());
            }
        }
    }

    /**
     * Devolve a posição da lista de contribuidores recebida como parâmetro com o contribuidor com menor número de
     * revisões
     *
     * @param l Lista de contribuidores
     *
     * @return Índice da posição com o contribuidor com menor número de revisões
     */
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

    /**
     * Insere o contribuidor na estrutura auxiliar à q4 (top dos contribuidores)
     *
     * @param c Contribuidor a inserir na estrutura auxiliar à q4
     */
    public void insertContributorQ4(Contributor c)
    {
        /* Verifica-se se já existe o contribuidor no top (contribuidor com o mesmo ID) */

        if (q4.stream().map(Contributor::getID).anyMatch(id -> id.equals(c.getID()))) {
            int index = 0;

            /* Caso já exista um contribuidor com o mesmo ID no top, substitui-se-o pelo contribuidor recebido */

            for (int i = 0; i < q4.size(); i++) {
                if (q4.get(i).getID().equals(c.getID())) {
                    index = i;
                }
            }

            q4.set(index, c.clone());
        }

        /* Caso não exista um contribuidor com o mesmo ID no top */

        else {

            /* Se o número de elementos do top for inferior ao limite máixmo (i.e. q4_size), basta adicionar o
               contribuidor ao top */

            if (q4.size() < q4_size) {
                q4.add(c.clone());
            }

            /* Senão vai-se buscar o contribuidor com menor número de revisões (i.e. contribuidor na última posição do
               top e, caso o contribuidor recebido seja maior do que este, é inserido no top */

            else {
                int index = getLeastIndexQ4(q4);

                if (q4.get(index).compareByRevisions(c) == -1) {
                    q4.set(index, c.clone());
                }
            }
        }
    }

    /**
     * Devolve a posição da lista de artigos recebida como parâmetro com o artigo cuja maior revisão tem o menor tamanho
     * dos da lista
     *
     * @param l Lista de artigos
     *
     * @return Índice da posição com o artigo com o menor tamanho
     */
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

    /**
     * Insere o artigo na estrutura auxiliar à q6 (top dos artigos)
     *
     * @param a Artigo a inserir na estrutura auxiliar à q6
     */
    public void insertArticleQ6(Article a)
    {
        /* Verifica-se se já existe o artigo no top (artigo com o mesmo ID) */

        if (q6.stream().map(Article::getID).anyMatch(id -> id.equals(a.getID()))) {
            int index = 0;

            /* Caso já exista um artigo com o mesmo ID no top, substitui-se-o pelo artigo recebido */

            for (int i = 0; i < q6.size(); i++) {
                if (q6.get(i).getID().equals(a.getID())) {
                    index = i;
                }
            }

            q6.set(index, a.clone());
        }

        /* Caso não exista um artigo com o mesmo ID no top */

        else {

            /* Se o número de elementos do top for inferior ao limite máixmo (i.e. q6_size), basta adicionar o
               artigo ao top */

            if (q6.size() < q6_size) {
                q6.add(a.clone());
            }

            /* Senão vai-se buscar o artigo com menor tamanho do texto (i.e. artigo na última posição do top e, caso o
               artigo recebido seja maior do que este, é inserido no top */

            else {
                int index = getLeastIndexQ6(q6);

                if (q6.get(index).compareByTextSize(a) == -1) {
                    q6.set(index, a.clone());
                }
            }
        }
    }

    // Métodos complementares comuns

    /**
     * Compara a WikiData com um Object
     *
     * @param o Objeto a comparar
     *
     * @return true  caso sejam iguais
     *         false caso contrário
     */
    @Override
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

    /**
     * Devolve uma string com a representação textual de WikiData
     */
    @Override
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

    /**
     * Faz uma cópia de WikiData
     *
     * @return Cópia da WikiData
     */
    @Override
    public WikiData clone()
    {
        return new WikiData(this);
    }

    /**
     * Gera um código de hash para WikiData a partir das suas variáveis de instância
     */
    @Override
    public int hashCode()
    {
        int result = super.hashCode();
        result = 31 * result + artigos.hashCode();
        result = 31 * result + contribuidores.hashCode();
        return result;
    }
}