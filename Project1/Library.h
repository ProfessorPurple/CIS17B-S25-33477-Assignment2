#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Faculty.h"

class Library
{
private:
    static Library* instance;   //singleton class 
    vector<Book> books;         // vector of a class of books
    vector<Student> students;   // vector for class students
    vector<Faculty> faculty;    // vector for class faculty

    Library() {} // Private constructor for Singleton
public:
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    static Library* getInstance();

    void initializeBooks();
    void initializeUsers();

    void addBook();
    void listBooks() const;
    void listTitles() const;

    void manageUsers();
    void createNewUser();
    void listUsers();
    void editUser();

    void transactionsMenu();
    void checkoutBook();
    void returnBook();

    void libraryMenu();
};

#endif