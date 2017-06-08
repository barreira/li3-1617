package engine;

import li3.Interface;

import static parser.XMLParser.parseFile;

import java.util.Collections;
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
        List<Contributor> top = wd.getQ4();

        //Collections.sort(top, new ComparatorContributor());

        ArrayList<Long> res = new ArrayList<>();

        int i = 0;
        for (Contributor c : top) {
            //System.out.println(c.getRevisions());
            res.add(Long.valueOf(c.getID()));
            System.out.println(i + " - " + c.getID() + " - " + c.getRevisions());
            i++;
        }

        return res;
/*
        return top.stream().map(Contributor::getID)
                           .map(Long::valueOf)
                           .collect(Collectors.toCollection(ArrayList::new));*/
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
        /*
        Map<Integer, Article> mapeamento = new TreeMap<Integer, Article>(new ComparatorQuery6());

        for (Article a : wd.getArtigos().values()) {
            int revSize = a.getRevisions().size();
            int tamanho = a.getRevisions().get(revSize - 1).getTextSize();

            mapeamento.put(tamanho, a);
        }

        return new ArrayList<Long>();*/
        return new ArrayList<Long>();
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

        return new ArrayList<Long>();
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return new ArrayList<String>();
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
