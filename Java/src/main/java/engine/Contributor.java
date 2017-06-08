package engine;

public class Contributor {

    // Variáveis de instância

    private String id;
    private String username;
    private int revisions;

    // Construtores

    public Contributor() {
        id = "N/A";
        username = "N/A";
        revisions = 1;
    }

    public Contributor(String id, String username, int revisions) {
        this.id = id;
        this.username = username;
        this.revisions = revisions;
    }

    public Contributor(Contributor c) {
        id = c.getID();
        username = c.getUsername();
        revisions = c.getRevisions();
    }

    // Getters e Setters

    public String getID() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public int getRevisions() {
        return revisions;
    }

    public void setID(String id) {
        this.id = id;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setRevisions(int revisions) {
        this.revisions = revisions;
    }

    // Outros métodos

    public void incrementRevisions() {
        revisions += 1;
    }

    public int compare(Contributor c) {
        if (this.getRevisions() > c.getRevisions()) {
            return 1;
        }
        else if (this.getRevisions() < c.getRevisions()) {
            return -1;
        }
        else {
            return Integer.valueOf(c.getID()).compareTo(Integer.valueOf(this.getID()));
        }
    }

    // Equals, toString, clone e hashCode

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        Contributor c = (Contributor) o;

        return id.equals(c.getID()) && username.equals(c.getUsername()) && revisions == c.getRevisions();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder("Contributor: { ");

        sb.append(id);
        sb.append(", ");
        sb.append(username);
        sb.append(", ");
        sb.append(revisions);
        sb.append(" }");

        return sb.toString();
    }

    public Contributor clone() {
        return new Contributor(this);
    }

    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + username.hashCode();
        result = 31 * result + revisions;
        return result;
    }
}