package engine;

import li3.Interface;
import parser.XMLParser;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

/**
 * Interface com a resolução das queries
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class QueryEngineImpl implements Interface {

    private WikiData wd; // WikiData com a informação lida das snapshots da wikipédia

    // Init, load e clean

    /**
     * Inicializa a WikiData
     */
    public void init()
    {
        wd = new WikiData();
    }

    /**
     * Lê os ficheiros das snapshots da wikipédia recebidos e carrega a WikiData com os dados lidos
     *
     * @param nsnaps      Número de snapshots da wikipédia a serem lidas
     * @param snaps_paths Lista de strings com o caminho para as snapshots da wikipédia
     */
    public void load(int nsnaps, ArrayList<String> snaps_paths)
    {
        for (String s : snaps_paths) {
            XMLParser.parseFile(wd, s);
        }
    }

    /**
     * Limpa a WikiData
     */
    public void clean()
    {
        wd = null; // variável de instância colocada a null para o garbage collector poder limpar
    }

    // Queries

    /**
     * Query 1
     *
     * Devolve o número total de artigos encontrados nas snapshots da wikipédia, incluindo artigos duplicados e novas
     * revisões de artigos já existentes.
     *
     * @return long Total de artigos
     */
    public long all_articles()
    {
        return wd.getAllArticles();
    }

    /**
     * Query 2
     *
     * Devolve o número de artigos únicos (i.e. artigos com identificador único) encontrados nas snapshots da wikipédia.
     * Ou seja, não inclui artigos duplicados nem novas revisões de artigos já existentes.
     *
     * @return Total de artigos únicos
     */
    public long unique_articles()
    {
        return wd.getUniqueArticles();
    }

    /**
     * Query 3
     *
     * Devolve o número total de revisões de artigos encontrados nas snapshots da wikipédia. Inclui quer a versão base
     * de um artigo, quer as restantes revisões feitas ao mesmo posteriormente.
     *
     * @return Total de revisões
     */
    public long all_revisions()
    {
        return wd.getAllRevisions();
    }

    /**
     * Query 4
     *
     * Devolve uma lista com os IDs dos 10 contribuidores que contribuíram para um maior número de revisões de
     * artigos. O resultado é ordenado de forma decrescente e, caso, existam contribuidores com um número igual de
     * contribuições, estes aparecem ordenados pelo seu ID (do menor para o maior).
     *
     * @return ArrayList com o top 10 dos IDs do contribuidores com mais contribuições
     */
    public ArrayList<Long> top_10_contributors()
    {
        return wd.getQ4().stream()
                         .sorted(new ComparatorContributor().reversed())
                         .map(Contributor::getID)
                         .map(Long::valueOf)
                         .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Query 5
     *
     * Devolve o username de um contribuidor cujo ID é passado como parâmetro. Caso não exista nenhum contribuidor com
     * esse ID, é devolvido null.
     *
     * @param contributor_id ID do contribuidor
     *
     * @return Nome do contribuidor (ou null caso não exista)
     */
    public String contributor_name(long contributor_id)
    {
        String id = Long.toString(contributor_id); // conversão do ID (de long para String)

        /* Tenta-se ir buscar o contribuidor ao map dos contribuidores */

        Contributor c = wd.getContribuidores().get(id);

        /* Se c for diferente de null, isto indica-nos que o contribuidor existe no map. Ao não estarmos a testar a
           existência do contribuidor diretamente (i.e. containsKey(c.getID())) e só depois irmos buscá-lo ao map (com o
           get), estamos a poupar uma iteração do map dos contribuidores. */

        if (c != null) {
            return c.getUsername();
        }

        /* Caso não exista o contribuidor é devolvido null */

        else {
            return null;
        }
    }

    /**
     * Query 6
     *
     * Devolve uma lista com os IDs dos 20 artigos que possuem textos com um maior tamanho (em bytes). Para cada artigo,
     * é apenas contabilizado o maior tamanho de todas as revisões do mesmo. O resultado é ordenado de forma decrescente
     * e, caso, existam artigos com um tamanho igual, estes aparecem ordenados pelo seu ID (do menor para o maior).
     *
     * @return ArrayList com o top 20 dos IDs dos artigos que possuem textos com um maior tamanho
     */
    public ArrayList<Long> top_20_largest_articles()
    {
        return wd.getQ6().stream()
                         .sorted(new ComparatorArticleTextSize().reversed())
                         .map(Article::getID)
                         .map(Long::valueOf)
                         .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Query 7
     *
     * Devolve o título de um artigo cujo ID é passado como parâmetro. São apenas considerados os títulos das últimas
     * revisões dos artigos. Caso não exista nenhum artigo com esse ID, é devolvido null.
     *
     * @param article_id ID do artigo
     *
     * @return Título da última revisão do artigo (ou null caso artigo não exista)
     */
    public String article_title(long article_id)
    {
        String id = Long.toString(article_id); // conversão do ID (de long para String)

        /* Tenta-se ir buscar o artigo ao map de artigos */

        Article a = wd.getArtigos().get(id);

        /* Se a for diferente de null, isto indica-nos que o artigo existe no map. Ao não estarmos a testar a existência
           do artigo diretamente (i.e. containsKey(a.getID())) e só depois irmos buscá-lo à arvore (com o get), estamos
           a poupar uma iteração do map dos artigos. */

        if (a != null) {
            List<Revision> revisions = a.getRevisions();

            return revisions.get(revisions.size() - 1).getTitle(); // é aplicado o getTitle à última revisão
        }

        /* Caso não exista o artigo é devolvido null */

        else {
            return null;
        }
    }

    /**
     * Query 8
     *
     * Devolve uma lista com os identificadores dos N artigos que possuem textos com um maior número de palavras. Para
     * cada artigo, é apenas contabilizado o texto com o maior número de palavras de todas as revisões do mesmo. O
     * resultado é ordenado de forma decrescente e, caso, existam artigos com um número de palavras igual, estes
     * aparecem ordenados pelo seu ID (do menor para o maior).
     *
     * @param n Tamanho do top
     *
     * @return Lista com o top dos IDs dos N artigos com mais palavras
     */
    public ArrayList<Long> top_N_articles_with_more_words(int n)
    {
        return wd.getArtigos().values().stream()
                                       .sorted(new ComparatorArticleWordCount().reversed())
                                       .limit(n)
                                       .map(a -> Long.parseLong(a.getID()))
                                       .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Query 9
     *
     * Devolve uma lista com os títulos dos artigos que começam pelo prefixo passado como parâmetro. É apenas
     * considerado o título da última revisão de cada artigo.
     *
     * @param prefix Prefixo a procurar
     *
     * @return Lista com os títulos dos artigos que começam pelo prefixo recebido
     */
    public ArrayList<String> titles_with_prefix(String prefix)
    {
        return wd.getArtigos().values().stream()
                                       .map(Article::getLastRevision)
                                       .map(Revision::getTitle)
                                       .filter(title -> title.startsWith(prefix))
                                       .sorted()
                                       .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Query 10
     *
     * Devolve o timestamp de uma revisão de um dado artigo (valores passados como parâmetro).
     *
     * @param article_id  ID do artigo
     * @param revision_id ID da revisão do artigo
     *
     * @return Timestamp da revisão de um artigo (null caso não exista o artigo ou a revisão)
     */
    public String article_timestamp(long article_id, long revision_id)
    {
        String articleID = Long.toString(article_id);
        String revisionID = Long.toString(revision_id);

        /* Tenta-se ir buscar o artigo ao map dos artigos */

        Article a = wd.getArtigos().get(articleID);

        /* Se a for diferente de null, isto indica-nos que o artigo existe no map. Ao não estarmos a testar a existência
           do artigo diretamente (i.e. containsKey(a.getID())) e só depois irmos buscá-lo à arvore (com o get), estamos
           a poupar uma iteração do map dos artigos. */

        if (a != null) {
            List<Revision> revisions = a.getRevisions();

            for (Revision r : revisions) {
                if (r.getID().equals(revisionID)) {
                    return r.getTimestamp();
                }
            }

            /* Caso exista o artigo mas não exista a revisão é devolvido null */

            return null;
        }

        /* Caso não exista o artigo é devolvido null */

        else {
            return null;
        }
    }
}