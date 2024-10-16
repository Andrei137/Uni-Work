import model.Book;
import service.BookService;

import java.util.ArrayList;
import java.util.List;

public class Main
{
    public static void main(String[] args)
    {
        BookService bookService = BookService.getInstance();
        Book book1 = new Book("Book1", "Author1", 10.0, 0);
        Book book2 = new Book("Book2", "Author2", 20.0, 0);
        Book book3 = new Book("Book3", "Author3", 30.0, 7);

        List<Book> books = new ArrayList<>();

        books.add(book1);
        books.add(book2);
        books.add(book3);

        bookService.setBooks(books);

        bookService.rateABook(book1);

        bookService.listBookOrderByRating();
        bookService.listBookOrderByName();

        bookService.addBook(new Book("Book4", "Author4", 40.0, 19));
        bookService.listBookOrderByRating();

        bookService.listAuditOperation();
    }
}