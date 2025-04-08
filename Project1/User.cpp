// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#include "User.h"
#include "Library.h"
//static int variable set to begin at 1 so all users are assigned a +1 ID value
int User::nextID = 1;

//constructor that gets a name and boolean value for the parameters that set name and faculty status
User::User(const string& name, bool facultyStatus)
{
	userName = name;
	userID = nextID;
	nextID++;
	isFaculty = facultyStatus;
}

//basic getters for the user private fields
string User::getName() const
{
	return userName;
}

int User::getUserID() const
{
	return userID;
}

bool User::getIsFaculty() const
{
	return isFaculty;
}

vector<Book>& User::getCheckedBooks() 
{
	return checkedBooks;
}

void User::displayInfo() const
{
	cout << "Name: " << userName << "\n ID: " << userID << endl;
}

void User::checkoutBook(Book& book)
{
	int maxCheckedBooks = 3;	// max books any user can have out 

	if (checkedBooks.size() < maxCheckedBooks)	// if the vector of checkedBooks is less than 3
	{
		if (book.getAvailabilty()) {	// if the book is available and not checked out
			book.setAvailabilty(false);	// check it out
			checkedBooks.push_back(book);	//add to vector in user instance
			cout << userName << " has checked out the book: " << book.getTitle() << " by the Author " << book.getAuthor() << endl;
		}
		else {	//else the book is not available
			cout << "Sorry, the book " << book.getTitle() << " is currently checked out.\n";
		}
	}
	else {	//else the user has 3books out already
		cout << "You currently have the maximum number of books checked out\n"
			"Please return a checked out book to check out a new one!\n";
	}
}

void User::listCheckedBooks() const
{
	int index = 1;	// index to start at 1 and list all the checked books a user has out
	if (checkedBooks.empty()) {
		cout << this->userName << " has no checked books\n";
	}
	else {
		cout << this->userName << " has these books checked out:\n";
		for (const auto& book : checkedBooks)
		{
			cout << index << ". " << book.getTitle() << " by " << book.getAuthor() << endl;
			++index;
		}
	}
}

// basic setters to set a name... used within the EditUser method
// no setUserID as those are set up with user creation and are not able to be changed
void User::setUsername(string& name)
{
	userName = name;
}

void User::setIsFaculty(bool faculty)
{
	isFaculty = faculty;
}
