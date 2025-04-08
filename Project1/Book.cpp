// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#include "Book.h"

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getISBN() const
{
    return ISBN;
}

bool Book::getAvailabilty() const
{
    return isAvailable;
}

void Book::setAvailabilty(bool availability)
{
    isAvailable = availability;
}


