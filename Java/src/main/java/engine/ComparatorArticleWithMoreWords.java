package engine;

import java.util.Comparator;

public class ComparatorArticleWithMoreWords implements Comparator<Article> {

    @Override
    public int compare(Article a1, Article a2)
    {
        if (a1.getRevisionWithMoreWords().getWordCount() > a2.getRevisionWithMoreWords().getWordCount()) {
            return 1;
        }
        else if (a1.getRevisionWithMoreWords().getWordCount() < a2.getRevisionWithMoreWords().getWordCount()) {
            return -1;
        }
        else {
            return Integer.valueOf(a2.getID()).compareTo(Integer.valueOf(a1.getID()));
        }
    }
}