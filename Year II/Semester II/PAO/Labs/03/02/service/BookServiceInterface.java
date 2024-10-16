package service;

import model.Book;

public interface BookServiceInterface
{
    void addBook(Book book);
    void rateABook(Book book);

    void listBookOrderByRating();

    void listBookOrderByName();

    void listAuditOperation();
}