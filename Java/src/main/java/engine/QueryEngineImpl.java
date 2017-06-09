package engine;

import li3.Interface;

import static parser.XMLParser.parseFile;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class QueryEngineImpl implements Interface {

    private WikiData wd;

    // Init, load e clean

    public void init() {
        wd = new WikiData();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        for (String s : snaps_paths) {
            parseFile(wd, s);
        }
    }

    public void clean() {
        wd = null; // para o garbage collector poder limpar
    }

    // Queries

    public long all_articles() {
        long contador = 0;

        for (Article a : wd.getArtigos().values()) {
            contador += a.getOccurrences();
        }

        return contador;
    }

    public long unique_articles() {
        return wd.getArtigos().size();
    }

    public long all_revisions() {
        long contador = 0;

        for (Article a : wd.getArtigos().values()) {
            contador += a.getRevisions().size();
        }

        return contador;
    }

    public ArrayList<Long> top_10_contributors() {
        return wd.getContribuidores().values()
                .stream()
                .sorted(new ComparatorContributor().reversed())
                .limit(10)
                .map(cont -> Long.parseLong(cont.getID()))
                .collect(Collectors.toCollection(ArrayList::new));
    }

    public String contributor_name(long contributor_id) {
        String id = Long.toString(contributor_id);

        if (wd.getContribuidores().containsKey(id)) {
            return wd.getContribuidores().get(id).getUsername();
        }
        else {
            return null;
        }
    }

    public ArrayList<Long> top_20_largest_articles() {

        return wd.getArtigos().values()
                .stream()
                .sorted(new ComparatorLargestArticle().reversed())  // ordena do maior para o menor
                .limit(20)
                .map(art -> Long.parseLong(art.getID()))    // converte o id para Long
                .collect(Collectors.toCollection(ArrayList::new));

        /*
        Map<Integer, Article> mapeamento = new TreeMap<Integer, Article>(new ComparatorQuery6());

        for (Article a : wd.getArtigos().values()) {
            int revSize = a.getRevisions().size();
            int tamanho = a.getRevisions().get(revSize - 1).getTextSize();

            mapeamento.put(tamanho, a);
        }

        return new ArrayList<Long>();*/
        //return null;
    }

    public String article_title(long article_id) {
        String id = Long.toString(article_id);

        if (wd.getArtigos().containsKey(id)) {
            List<Revision> revisions = wd.getArtigos().get(id).getRevisions();

            return revisions.get(revisions.size() - 1).getTitle();
        }
        else {
            return null;
        }
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return wd.getArtigos().values()
                .stream()
                .sorted(new ComparatorMoreWordsArticle().reversed())
                .limit(n)
                .map(art -> Long.parseLong(art.getID()))
                .collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return wd.getArtigos().values()
                .stream()
                .map(Article::getLatestTitle)
                .filter(title -> title.startsWith(prefix))
                .sorted()
                .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_timestamp(long article_id, long revision_id) {
        String articleID = Long.toString(article_id);
        String revisionID = Long.toString(revision_id);

        if (wd.getArtigos().containsKey(articleID)) {
            List<Revision> revisions = wd.getArtigos().get(articleID).getRevisions();

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
