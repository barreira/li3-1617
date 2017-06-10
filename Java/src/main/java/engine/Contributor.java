package engine;

/**
 * Classe responsável por codificar a estrutura de um contribuidor da wikipédia
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class Contributor {

    // Variáveis de instância

    private String id;       // ID
    private String username; // username
    private int revisions;   // número de revisões feitas

    // Construtores

    /**
     * Construtor vazio
     */
    public Contributor()
    {
        id = "N/A";
        username = "N/A";
        revisions = 1;
    }

    /**
     * Construtor por partes
     *
     * @param id        ID do contribuidor
     * @param username  Username do contribuidor
     * @param revisions Número de revisões feitas pelo contribuidor
     */
    public Contributor(String id, String username, int revisions)
    {
        this.id = id;
        this.username = username;
        this.revisions = revisions;
    }

    /**
     * Construtor por cópia
     *
     * @param c Contribuidor a copiar
     */
    public Contributor(Contributor c)
    {
        id = c.getID();
        username = c.getUsername();
        revisions = c.getRevisions();
    }

    // Getters e Setters

    /**
     * Devolve o ID do contribuidor
     */
    public String getID()
    {
        return id;
    }

    /**
     * Devolve o username do contribuidor
     */
    public String getUsername()
    {
        return username;
    }

    /**
     * Devolve o número de revisões feitas pelo contribuidor
     */
    public int getRevisions()
    {
        return revisions;
    }

    /**
     * Altera o ID do contribuidor
     */
    public void setID(String id)
    {
        this.id = id;
    }

    /**
     * Altera o username do contribuidor
     */
    public void setUsername(String username)
    {
        this.username = username;
    }

    /**
     * Altera o número de revisões feitas pelo contribuidor
     */
    public void setRevisions(int revisions)
    {
        this.revisions = revisions;
    }

    // Outros métodos

    /**
     * Incrementa o número de revisões feitas pelo contribuidor
     */
    public void incrementRevisions()
    {
        revisions += 1;
    }

    /**
     * Efetua a comparação com outro contribuidor pelo número de revisões efetuadas
     *
     * Nota: Caso os contribuidores tenham o mesmo número de revisões, faz-se uma comparação pelo valor dos seus IDs.
     *
     * @param c Contribuidor a comparar
     *
     * @return 1 caso this > c
     *         0 caso this == c
     *        -1 caso this < c
     */
    public int compareByRevisions(Contributor c)
    {
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

    // Métodos complementares comuns

    /**
     * Compara o contribuidor com um Object
     *
     * @param o Objeto a comparar
     *
     * @return true  caso sejam iguais
     *         false caso contrário
     */
    @Override
    public boolean equals(Object o)
    {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        Contributor c = (Contributor) o;

        return id.equals(c.getID()) && username.equals(c.getUsername()) && revisions == c.getRevisions();
    }

    /**
     * Devolve uma string com a representação textual de um contribuidor
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder("Contributor: { ");

        sb.append(id);
        sb.append(", ");
        sb.append(username);
        sb.append(", ");
        sb.append(revisions);
        sb.append(" }");

        return sb.toString();
    }

    /**
     * Faz uma cópia de um contribuidor
     *
     * @return Cópia do contribuidor
     */
    @Override
    public Contributor clone()
    {
        return new Contributor(this);
    }

    /**
     * Gera um código de hash para um contribuidor a partir das suas variáveis de instância
     */
    @Override
    public int hashCode()
    {
        int result = super.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + username.hashCode();
        result = 31 * result + revisions;
        return result;
    }
}