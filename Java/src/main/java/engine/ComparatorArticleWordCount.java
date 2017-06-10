package engine;

import java.util.Comparator;

/**
 * Classe correspondente ao comparador de Artigos por número de palavras
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class ComparatorArticleWordCount implements Comparator<Article> {

    /**
     * Efetua a comparação entre dois artigos pelo word count da revisão com maior número de palavras
     *
     * Nota: Caso a maior revisão de ambos os artigos tenha o mesmo número de palavras, faz-se uma comparação pelo valor
     *       dos seus IDs.
     *
     * @param a1 Artigo a comparar
     * @param a2 Artigo a comparar
     *
     * @return 1 caso a1 > a2
     *         0 caso a1 == a2
     *        -1 caso a1 < a2
     */
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