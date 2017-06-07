package engine;

import li3.Interface;

import java.util.ArrayList;

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
        wd = null;
        // para o garbage collector poder limpar
    }

    // Queries

    public long all_articles() {

        return 0;
    }

    public long unique_articles() {

        return 0;
    }

    public long all_revisions() {

        return 0;
    }

    public ArrayList<Long> top_10_contributors() {

        return new ArrayList<Long>();
    }

    public String contributor_name(long contributor_id) {

        return " ";
    }

    public ArrayList<Long> top_20_largest_articles() {

        return new ArrayList<Long>();
    }

    public String article_title(long article_id) {

        return " ";
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return new ArrayList<Long>();
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return new ArrayList<String>();
    }

    public String article_timestamp(long article_id, long revision_id) {

        return " ";
    }
}
