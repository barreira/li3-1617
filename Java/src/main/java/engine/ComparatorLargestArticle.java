package engine;

import java.util.Comparator;

public class ComparatorLargestArticle implements Comparator<Article> {

    public int compare(Article a1, Article a2) {
        int a1MaxTextSize = a1.getMaxTextSize();
        int a2MaxTextSize = a2.getMaxTextSize();

        if (a1MaxTextSize < a2MaxTextSize)
            return -1;
        else if (a1MaxTextSize == a2MaxTextSize) {
            long id1 = Long.parseLong(a1.getID());
            long id2 = Long.parseLong(a2.getID());
            if (id1 < id2)
                return 1;
            else
                return -1;
        }
        else
            return 1;
    }
}