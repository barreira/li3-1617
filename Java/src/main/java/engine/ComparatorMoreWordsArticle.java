package engine;

import java.util.Comparator;

public class ComparatorMoreWordsArticle implements Comparator<Article> {

    public int compare(Article a1, Article a2) {
        int a1MaxWordCount = a1.getMaxWordCount();
        int a2MaxWordCount = a2.getMaxWordCount();

        if (a1MaxWordCount < a2MaxWordCount)
            return -1;
        else if (a1MaxWordCount == a2MaxWordCount) {
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
