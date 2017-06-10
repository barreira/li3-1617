package engine;

import li3.Interface;
import parser.XMLParser;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class QueryEngineImpl implements Interface {

    private WikiData wd;

    // Init, load e clean

    public void init()
    {
        wd = new WikiData();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths)
    {
        for (String s : snaps_paths) {
            XMLParser.parseFile(wd, s);
        }
    }

    public void clean()
    {
        wd = null; // para o garbage collector poder limpar
    }

    // Queries

    public long all_articles()
    {
        return wd.getAllArticles();
        /*
        long contador = 0;

        for (Article a : wd.getArtigos().values()) {
            contador += a.getOccurrences();
        }

        return contador;*/
    }

    public long unique_articles()
    {
        return wd.getUniqueArticles();
        // return wd.getArtigos().size();
    }

    public long all_revisions()
    {
        return wd.getAllRevisions();
        /*
        long contador = 0;

        for (Article a : wd.getArtigos().values()) {
            contador += a.getRevisions().size();
        }

        return contador;*/
    }

    public ArrayList<Long> top_10_contributors()
    {
        return wd.getQ4().stream()
                         .sorted(new ComparatorContributor().reversed())
                         .map(Contributor::getID)
                         .map(Long::valueOf)
                         .collect(Collectors.toCollection(ArrayList::new));
    }

    public String contributor_name(long contributor_id)
    {
        String id = Long.toString(contributor_id);

        Contributor c = wd.getContribuidores().get(id);

        if (c != null) {
            return c.getUsername();
        }
        else {
            return null;
        }
    }

    public ArrayList<Long> top_20_largest_articles()
    {
        return wd.getQ6().stream()
                         .sorted(new ComparatorLargestArticle().reversed())
                         .map(Article::getID)
                         .map(Long::valueOf)
                         .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_title(long article_id)
    {
        String id = Long.toString(article_id);

        Article a = wd.getArtigos().get(id);

        if (a != null) {
            List<Revision> revisions = a.getRevisions();

            return revisions.get(revisions.size() - 1).getTitle();
        }
        else {
            return null;
        }
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n)
    {
        return wd.getArtigos().values().stream()
                                       .sorted(new ComparatorArticleWithMoreWords().reversed())
                                       .limit(n)
                                       .map(a -> Long.parseLong(a.getID()))
                                       .collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<String> titles_with_prefix(String prefix)
    {
        return wd.getArtigos().values().stream()
                                       .map(Article::getLastRevision)
                                       .map(Revision::getTitle)
                                       .filter(title -> title.startsWith(prefix))
                                       .sorted()
                                       .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_timestamp(long article_id, long revision_id)
    {
        String articleID = Long.toString(article_id);
        String revisionID = Long.toString(revision_id);

        Article a = wd.getArtigos().get(articleID);

        if (a != null) {
            List<Revision> revisions = a.getRevisions();

            for (Revision r : revisions) {
                if (r.getID().equals(revisionID)) {
                    return r.getTimestamp();
                }
            }

            return null; // existe artigo mas não existe revisão
        }
        else {
            return null; // não existe artigo
        }
    }
}