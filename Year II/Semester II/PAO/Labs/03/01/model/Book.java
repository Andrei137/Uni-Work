package model;

// constructor cu parametrii
// getters 
// totul este final
// metode de equal si hashcode
// public record Book(string autor)
// {
    
// }

// clasa imutabila
public final class Book
{
    private final String autor;

    public Book(String autor)
    {
        this.autor = autor;
    }

    public String getAuthor()
    {
        return autor;
    }
}