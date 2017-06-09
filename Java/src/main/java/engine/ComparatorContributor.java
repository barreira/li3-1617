package engine;

import java.util.Comparator;

public class ComparatorContributor implements Comparator<Contributor> {

    @Override
    public int compare(Contributor c1, Contributor c2) {
        if (c1.getRevisions() > c2.getRevisions()) {
            return -1;
        }
        else if (c1.getRevisions() < c2.getRevisions()) {
            return 1;
        }
        else {
            return Integer.valueOf(c2.getID()).compareTo(Integer.valueOf(c1.getID()));
        }
    }
}