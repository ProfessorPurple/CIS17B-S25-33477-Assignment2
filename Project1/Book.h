#ifndef BOOK_H
#define BOOK_H

// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    Book(const std::string& title, const std::string& author, const std::string& ISBN) : title(title),
        author(author),
        ISBN(ISBN),
        isAvailable(true) {}

    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    bool getAvailabilty() const;

    void setAvailabilty(bool availability);
};

#endif