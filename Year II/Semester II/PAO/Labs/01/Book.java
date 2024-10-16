public class Book {
    private String name;
    private String author;

    {
        System.out.println("A");
    }

    static
    {
        System.out.println("B");
    }
    public Book(String name, String author) {
        System.out.println("C");
        this.name = name;
        this.author = author;
    }

    public String getName() {
        return name;
    }

    public String getAuthor() {
        return author;
    }



    @Override
    public String toString() {
        return "Book{" +
                "name='" + name + '\'' +
                ", author='" + author + '\'' +
                '}';
    }
}
