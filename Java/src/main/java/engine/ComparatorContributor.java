package engine;

import java.util.Comparator;

public class ComparatorContributor implements Comparator<Contributor> {

    public int compare(Contributor c1, Contributor c2) {
        if (c1.getRevisions() < c2.getRevisions())
            return -1;
        else if (c1.getRevisions() == c2.getRevisions()) {
            long id1 = Long.parseLong(c1.getID());
            long id2 = Long.parseLong(c2.getID());
            if (id1 < id2)
                return 1;
            else
                return -1;
        }
        else
            return 1;
    }
}