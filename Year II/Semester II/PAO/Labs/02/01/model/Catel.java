package model;

public class Catel extends Animal
{
    private String culoare;

    public Catel(String nume, String culoare) 
    {
        super(nume);
        this.culoare = culoare;
    }

    public Catel(String nume) 
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
        return "Catel{" +
                "culoare='" + culoare + '\'' +
                '}';
    }
}