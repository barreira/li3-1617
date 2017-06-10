package engine;

public class Revision {

    // Variáveis de instância

    private String id;
    private String timestamp;
    private String title;
    private int textSize;
    private int wordCount;

    // Construtores

    public Revision()
    {
        id = "N/A";
        timestamp = "N/A";
        title = "N/A";
        textSize = 0;
        wordCount = 0;
    }

    public Revision(String id, String timestamp, String title, int textSize, int wordCount)
    {
        this.id = id;
        this.timestamp = timestamp;
        this.title = title;
        this.textSize = textSize;
        this.wordCount = wordCount;
    }

    public Revision(Revision r)
    {
        id = r.getID();
        timestamp = r.getTimestamp();
        title = r.getTitle();
        textSize = r.getTextSize();
        wordCount = r.getWordCount();
    }

    // Getters e Setters

    public String getID()
    {
        return id;
    }

    public String getTimestamp()
    {
        return timestamp;
    }

    public String getTitle()
    {
        return title;
    }

    public int getTextSize()
    {
        return textSize;
    }

    public int getWordCount()
    {
        return wordCount;
    }

    public void setID(String id)
    {
        this.id = id;
    }

    public void setTimestamp(String timestamp)
    {
        this.timestamp = timestamp;
    }

    public void setTitle(String title)
    {
        this.title = title;
    }

    public void setTextSize(int textSize)
    {
        this.textSize = textSize;
    }

    public void setWordCount(int wordCount)
    {
        this.wordCount = wordCount;
    }

    // Métodos complementares comuns

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

    public Revision clone()
    {
        return new Revision(this);
    }

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