package engine;

/**
 * Classe responsável por codificar a estrutura de um revisão da wikipédia
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class Revision {

    // Variáveis de instância

    private String id;        // ID da revisão
    private String timestamp; // Marca temporal da submissão da revisão
    private String title;     // Título do artigo nesta revisão
    private int textSize;     // Tamanho do texto da revisão
    private int wordCount;    // Número de palavras do texto da revisão

    // Construtores

    /**
     * Construtor vazio
     */
    public Revision()
    {
        id = "N/A";
        timestamp = "N/A";
        title = "N/A";
        textSize = 0;
        wordCount = 0;
    }

    /**
     * Construtor por partes
     *
     * @param id        ID da revisão
     * @param timestamp Marca temporal da submissão da revisão
     * @param title     Título do artigo nesta revisão
     * @param textSize  Tamanho do texto da revisão
     * @param wordCount Número de palavras do texto da revisão
     */
    public Revision(String id, String timestamp, String title, int textSize, int wordCount)
    {
        this.id = id;
        this.timestamp = timestamp;
        this.title = title;
        this.textSize = textSize;
        this.wordCount = wordCount;
    }

    /**
     * Construtor por cópia
     *
     * @param r Revisão a copiar
     */
    public Revision(Revision r)
    {
        id = r.getID();
        timestamp = r.getTimestamp();
        title = r.getTitle();
        textSize = r.getTextSize();
        wordCount = r.getWordCount();
    }

    // Getters e Setters

    /**
     * Devolve o ID da revisão
     */
    public String getID()
    {
        return id;
    }

    /**
     * Devolve o timestamp do artigo
     */
    public String getTimestamp()
    {
        return timestamp;
    }

    /**
     * Devolve o título da revisão
     */
    public String getTitle()
    {
        return title;
    }

    /**
     * Devolve o tamanho do texto da revisão
     */
    public int getTextSize()
    {
        return textSize;
    }

    /**
     * Devolve o número de palavras do texto
     */
    public int getWordCount()
    {
        return wordCount;
    }

    /**
     * Altera o ID da revisão
     */
    public void setID(String id)
    {
        this.id = id;
    }

    /**
     * Altera o timestamp da revisão
     */
    public void setTimestamp(String timestamp)
    {
        this.timestamp = timestamp;
    }

    /**
     * Altera o título da revisão
     */
    public void setTitle(String title)
    {
        this.title = title;
    }

    /**
     * Altera o tamanho do texto da revisão
     */
    public void setTextSize(int textSize)
    {
        this.textSize = textSize;
    }

    /**
     * Altera o número de palavras do texto da revisão
     */
    public void setWordCount(int wordCount)
    {
        this.wordCount = wordCount;
    }

    // Métodos complementares comuns

    /**
     * Compara uma revisão com um Object
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

        Revision r = (Revision) o;

        return id.equals(r.getID()) && timestamp.equals(r.getTimestamp()) && title.equals(r.getTitle()) &&
                textSize == r.getTextSize() && wordCount == r.getWordCount();
    }

    /**
     * Devolve uma string com a representação textual de uma revisão
     */
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder("Revision: { ");

        sb.append(id);
        sb.append(", ");
        sb.append(timestamp);
        sb.append(", ");
        sb.append(title);
        sb.append(", ");
        sb.append(textSize);
        sb.append(", ");
        sb.append(wordCount);
        sb.append(" }");

        return sb.toString();
    }

    /**
     * Faz uma cópia de uma revisão
     *
     * @return Cópia da revisão
     */
    @Override
    public Revision clone()
    {
        return new Revision(this);
    }

    /**
     * Gera um código de hash para uma revisão a partir das suas variáveis de instância
     */
    @Override
    public int hashCode()
    {
        int result = super.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + timestamp.hashCode();
        result = 31 * result + title.hashCode();
        result = 31 * result + textSize;
        result = 31 * result + wordCount;
        return result;
    }
}