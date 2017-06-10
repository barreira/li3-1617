package engine;

import java.util.Comparator;

public class ComparatorLargestArticle implements Comparator<Article> {

    @Override
    public int compare(Article a1, Article a2)
    {
        if (a1.getLargestRevision().getTextSize() > a2.getLargestRevision().getTextSize()) {
            return 1;
        }
        else if (a1.getLargestRevision().getTextSize() < a2.getLargestRevision().getTextSize()) {
            return -1;
        }
        else {
            return Integer.valueOf(a2.getID()).compareTo(Integer.valueOf(a1.getID()));
        }
    }
}