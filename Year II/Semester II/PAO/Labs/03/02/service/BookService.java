package service;

import model.Book;
import java.util.ArrayList;
import java.util.List;

public class BookService implements BookServiceInterface
{
    private List<Book> books = new ArrayList<>();
    private StringBuffer sb = new StringBuffer();

    private BookService(){};

    @Override
    public void addBook(Book book)
    {
        books.add(book);
        sb.append("Added book: ").append(book).append("\n");
    }

    @Override
    public void rateABook(Book book)
    {
        book.setRating(book.getRating() + 1);
        sb.append("Rated book: ").append(book).append("\n");
    }

    @Override
    public void listBookOrderByRating()
    {
        books.sort((b1, b2) -> b1.getRating().compareTo(b2.getRating()));
        System.out.println(books);
        sb.append("Listed books by rating\n");
    }

    @Override
    public void listBookOrderByName()
    {
        books.sort((b1, b2) -> b1.getNume().compareTo(b2.getNume()));
        System.out.println(books);
        sb.append("Listed books by name\n");
    }

    @Override
    public void listAuditOperation()
    {
        System.out.println(sb);
    }

    public void setBooks(List<Book> books)
    {
        this.books = books;
    }

    private static final class SINGLETON 
    {
        private static BookService INSTANCE = new BookService();
    }

    public static BookService getInstance() 
    {
        return SINGLETON.INSTANCE;
    }

}