package engine;

import java.util.Comparator;

public class ComparatorArticle implements Comparator<Article> {

    @Override
    public int compare(Article a1, Article a2) {
        int last1 = a1.getRevisions().size() - 1;
        int last2 = a2.getRevisions().size() - 1;

        if (a1.getRevisions().get(last1).getTextSize() > a2.getRevisions().get(last2).getTextSize()) {
            return 1;
        }
        else if (a1.getRevisions().get(last1).getTextSize() < a2.getRevisions().get(last2).getTextSize()) {
            return -1;
        }
        else {
            return Integer.valueOf(a1.getID()).compareTo(Integer.valueOf(a2.getID()));
        }
    }
}