// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#pragma once
#include "Book.h"
#include <vector>

class User
{
protected:
	vector<Book>checkedBooks;	//each student or faculty should have checked books
	string userName;
	static int nextID;
	int userID;
	bool isFaculty;
public:
	User(const string&, bool);

	string getName() const;
	int getUserID() const;
	bool getIsFaculty() const;
	vector<Book>& getCheckedBooks();

	virtual void displayInfo() const;

	void checkoutBook(Book& book);
	void listCheckedBooks() const;
	void setUsername(string&);
	void setIsFaculty(bool faculty);
};
