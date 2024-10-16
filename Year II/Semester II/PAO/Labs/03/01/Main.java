import java.util.ArrayList;
import java.util.List;


public class Main
{
    public static void main(String[] args)
    {
        // mostenire => is-a
        // agregare & compozitie => has-a
        // agregarea -> weak association
        // compozitia -> strong association

        // agregare
        Person p1 = new Person("Ionel");
        House house = new House(p1);

        System.out.println(house);
        p1.setNume("Georgel");
        System.out.println(house);


        // compozitie
        Room r1 = new Room();


        // Imutabilitate
        // String -> clasa imutabila

        String s1 = "test";
        s1.concat("anotherString");
        System.out.println(s1);

        StringBuilder sb = new StringBuilder("test");
        sb.append("anotherString");
        System.out.println(sb);

        StringBuffer stb = new StringBuffer("test");
        stb.append("anotherString");
        System.out.println(stb);

        // regex -> expresii regulate
        String s2 = "test";
        if (s2.matches("^[a-zA-Z0-9_]*$"))
        {
            System.out.println("Nu are caractere speciale");
        }
        else
        {
            System.out.println("Are caractere speciale");
        }

        List<String> list = new ArrayList<>();
        list.add("test");
        list.add("test2");
        System.out.println(list);

        list.forEach(e -> System.out.println(e));
    }
}

class House
{
    private Person person;

    public House(Person person)
    {
        this.person = person;
    }

    @Override
    public String toString() 
    {
        return "House{" +
                "person=" + person +
                '}';
    }
}

class Person
{
    private String nume;

    public Person(String nume) 
    {
        this.nume = nume;
    }

    public String getNume() 
    {
        return nume;
    }

    public void setNume(String nume) 
    {
        this.nume = nume;
    }

    @Override
    public String toString() 
    {
        return "Person{" +
                "nume='" + nume + '\'' +
                '}';
    }
}

class Room
{
    private String tip;

    public Room()
    {

    }

    public Room(Room room)
    {
        Room r = new Room(room);
        this.tip = r.tip;
    }

    @Override
    public String toString() 
    {
        return "Room{" +
                "tip='" + tip + '\'' +
                '}';
    }
}