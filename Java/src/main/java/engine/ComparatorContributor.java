package engine;

import java.util.Comparator;

/**
 * Classe correspondente ao comparador de Contribuidores (pelo número de revisões)
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class ComparatorContributor implements Comparator<Contributor> {

    /**
     * Efetua a comparação entre dois contribuidores pelo seu número de revisões
     *
     * Nota: Caso os contribuidores tenham o mesmo número de revisões, faz-se uma comparação pelo valor dos seus IDs.
     *
     * @param c1 Contribuidor a comparar
     * @param c2 Contribuidor a comparar
     *
     * @return 1 caso c1 > c2
     *         0 caso c1 == c2
     *        -1 caso c1 < c2
     */
    @Override
    public int compare(Contributor c1, Contributor c2)
    {
        if (c1.getRevisions() > c2.getRevisions()) {
            return 1;
        }
        else if (c1.getRevisions() < c2.getRevisions()) {
            return -1;
        }
        else {
            return Integer.valueOf(c2.getID()).compareTo(Integer.valueOf(c1.getID()));
        }
    }
}