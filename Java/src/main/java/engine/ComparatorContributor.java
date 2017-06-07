package engine;

import java.util.Comparator;

public class ComparatorContributor implements Comparator<Contributor> {

    public int compare(Contributor c1, Contributor c2) {
        return c1.getID().compareTo(c2.getID());
    }
}