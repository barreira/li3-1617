package li3;

import java.util.ArrayList;

public interface Interface {

    void init();

    void load(int nsnaps, ArrayList<String> snaps_paths);

    long all_articles(); // travessia total. *a_id*, a_ocurrences

    long unique_articles(); // travessia total. artigos (size)

    long all_revisions(); // travessia total. *a_id*, revisions (size)

    ArrayList<Long> top_10_contributors(); // travessia total. c_id, *c_revisions*

    String contributor_name(long contributor_id); // um só. c_id, c_username

    ArrayList<Long> top_20_largest_articles(); // travessia total. a_id, r_id, *r_textsize*

    String article_title(long article_id); // um só. a_id, r_id, r_title

    ArrayList<Long> top_N_articles_with_more_words(int n); // travessia total. a_id, r_id, *r_wordcount*

    ArrayList<String> titles_with_prefix(String prefix); // travessia total. a_id, r_id, *r_title*

    String article_timestamp(long article_id, long revision_id); // um só. a_id, r_id, r_timestamp

    void clean();
}