package model;

public class Book
{
    private String nume; 
    private String autor;
    private double pret;
    private Integer rating = 0;

    public Book(String nume, String autor, double pret, int rating)
    {
        this.nume = nume;
        this.autor = autor;
        this.pret = pret;
        this.rating = rating;
    }
    public String getNume()
    {
        return nume;
    }

    public void setNume(String nume)
    {
        this.nume = nume;
    }

    public String getAutor()
    {
        return autor;
    }

    public void setAutor(String autor)
    {
        this.autor = autor;
    }

    public Integer getRating()
    {
        return rating;
    }

    public void setRating(int rating)
    {
        this.rating = rating;
    }

    public double getPret()
    {
        return pret;
    }

    public void setPret(float pret)
    {
        this.pret = pret;
    }

    @Override
    public String toString()
    {
        return "Book{" + "nume=" + nume + ", autor=" + autor + ", pret=" + pret + ", rating=" + rating + '}';
    }
}