package engine;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

/**
 * @brief Classe responsável por codificar a estrutura de um artigo da wikipédia
 *
 * @author Ana Paula Carvalho
 * @author Joana Arantes
 * @author João Pires Barreira
 * @author Miguel Cunha
 *
 * @version 2017-06-10
 */
public class Article {

    // Variáveis de instância

    private String id;                // ID do artigo
    private int occurrences;          // número de ocorrências do artigo nas snapshots
    private List<Revision> revisions; // lista das revisões do artigo

    // Construtores

    /**
     * @brief Construtor vazio
     */
    public Article()
    {
        id = "N/A";
        occurrences = 1;
        revisions = new ArrayList<>();
    }

    /**
     * @brief Construtor por partes
     *
     * @param id          ID do artigo
     * @param occurrences Número de ocorrências do artigo nas snapshots
     * @param revisions   Lista das revisões do artigo
     */
    public Article(String id, int occurrences, List<Revision> revisions)
    {
        setID(id);
        setOccurrences(occurrences);
        setRevisions(revisions);
    }

    /**
     * @brief Construtor por cópia
     *
     * @param a Artigo a copiar
     */
    public Article(Article a)
    {
        id = a.getID();
        occurrences = a.getOccurrences();
        revisions = a.getRevisions();
    }

    // Getters e Setters

    /**
     * @brief Devolve o ID do artigo
     */
    public String getID()
    {
        return id;
    }

    /**
     * @brief Devolve o número de ocorrências do artigo nas snapshots
     */
    public int getOccurrences()
    {
        return occurrences;
    }

    /**
     * @brief Devolve a lista das revisões do artigo
     *
     */
    public List<Revision> getRevisions()
    {
        return revisions.stream()
                        .map(Revision::clone)
                        .collect(Collectors.toList());
    }

    /**
     * @brief Altera o ID do artigo
     */
    public void setID(String id)
    {
        this.id = id;
    }

    /**
     * @brief Altera o valor do número de ocorrências do artigo nas snapshots
     */
    public void setOccurrences(int occurrences)
    {
        this.occurrences = occurrences;
    }

    /**
     * @brief Altera a lista das revisões do artigo
     */
    public void setRevisions(List<Revision> revisions)
    {
        this.revisions = revisions.stream()
                                  .map(Revision::clone)
                                  .collect(Collectors.toList());
    }

    // Outros métodos

    /**
     * @brief Adiciona uma revisão à lista das revisões de um Artigo
     *
     * @param r Revisão a ser adicionada à lista
     */
    public void addRevision(Revision r)
    {
        revisions.add(r.clone());
    }

    /**
     * @brief Incrementa o número de ocorrências do artigo nas snapshots
     */
    public void incrementOccurrences()
    {
        occurrences += 1;
    }

    /**
     * @brief Devolve a última revisão de um artigo
     */
    public Revision getLastRevision()
    {
        return revisions.get(revisions.size() - 1);
    }

    /**
     * @brief Devolve a revisão com mais palavras de um artigo
     */
    public Revision getRevisionWithMoreWords()
    {
        Revision largest = revisions.get(0);

        for (Revision r : revisions) {
            if (r.getWordCount() > largest.getWordCount()) {
                largest = r.clone();
            }
        }

        return largest;
    }

    /**
     * @brief Devolve a revisão com um maior texto de um artigo
     */
    public Revision getLargestRevision()
    {
        Revision largest = revisions.get(0);

        for (Revision r : revisions) {
            if (r.getTextSize() > largest.getTextSize()) {
                largest = r.clone();
            }
        }

        return largest;
    }

    /**
     * @brief Efetua a comparação com outro artigo pelo tamanho do texto da sua maior revisão
     *
     * Caso a maior revisão de ambos os artigos tenha o mesmo tamanho, faz-se uma comparação pelo valor dos seus IDs.
     *
     * @param a Artigo a comparar
     *
     * @return 1 caso this > a
     *         0 caso this == a
     *        -1 caso this < a
     */
    public int compareByTextSize(Article a)
    {
        if (this.getLargestRevision().getTextSize() > a.getLargestRevision().getTextSize()) {
            return 1;
        }
        else if (this.getLargestRevision().getTextSize() < a.getLargestRevision().getTextSize()) {
            return -1;
        }
        else {
            return Integer.valueOf(a.getID()).compareTo(Integer.valueOf(this.getID()));
        }
    }

    // Métodos complementares comuns

    /**
     * @brief Compara o artigo com um Object
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

        Article a = (Article) o;

        return id.equals(a.getID()) && occurrences == a.getOccurrences() && revisions.equals(a.getRevisions());
    }

    /**
     * @brief Devolve uma string com a representação textual de um artigo
     */
    @Override
    public String toString()
    {
        int counter = 1;
        StringBuilder sb = new StringBuilder("Article: { ");

        sb.append(id);
        sb.append(", ");
        sb.append(occurrences);
        sb.append(", ");
        sb.append("{ ");

        for (Revision r : revisions) {
            sb.append(r.toString());

            if (counter < revisions.size()) {
                sb.append(", ");
            }

            counter++;
        }

        sb.append(" } }");

        return sb.toString();
    }

    /**
     * @brief Faz uma cópia de um artigo
     *
     * @return Cópia do artigo
     */
    @Override
    public Article clone()
    {
        return new Article(this);
    }

    /**
     * @brief Gera um código de hash para um artigo a partir das suas variáveis de instância
     */
    @Override
    public int hashCode()
    {
        int result = super.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + occurrences;
        result = 31 * result + revisions.hashCode();
        return result;
    }
}