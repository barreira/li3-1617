package engine;

import java.util.Comparator;

public class ComparatorArticle implements Comparator<Article> {

    public int compare(Article a1, Article a2) {
        return a1.getID().compareTo(a2.getID());
    }
}