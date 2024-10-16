package model;

public class Pisica extends Animal
{
    private String culoare;

    public Pisica(String nume, String culoare) 
    {
        super(nume);
        this.culoare = culoare;
    }

    public Pisica(String nume) 
    {
        super(nume);
    }

    public String getCuloare() 
    {
        return culoare;
    }

    public void setCuloare(String culoare) 
    {
        this.culoare = culoare;
    }

    @Override
    public String toString() 
    {
        return "Pisica{" +
                "culoare='" + culoare + '\'' +
                '}';
    }
}