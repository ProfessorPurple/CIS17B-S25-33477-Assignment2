// RICARDO RAMIREZ
// CIS -17B
// JOHN O'CONNOR
// LESSON 2 ASSIGNMENT
// LIBRARY MANAGEMENT SYSTEM ASSIGNMENT
#include "Library.h"
#include <iostream>

using namespace std;
Library* Library::instance = nullptr;

Library* Library::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Library();
        instance->initializeBooks();
        instance->initializeUsers();
    }
    return instance;
}

//FILL THE LIBRARY WITH SOME CLASSIC TITLES AT FIRST
void Library::initializeBooks() 
{
        books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565"));
        books.push_back(Book("1984", "George Orwell", "9780451524935"));
        books.push_back(Book("To Kill a Mockingbird", "Harper Lee", "9780060935467"));
        books.push_back(Book("Pride and Prejudice", "Jane Austen", "9781503290563"));
        books.push_back(Book("Moby-Dick", "Herman Melville", "9781503280786"));
}

//some template users to be in the system from the start of the program.
void Library::initializeUsers()
{
    faculty.push_back(Faculty("Mickey Mouse", "Dean"));
    faculty.push_back(Faculty("Donald Duck", "Instructor of Quackery"));

    students.push_back(Student("John Muir", "Forestry"));
    students.push_back(Student("Ricky Ramirez", "Computer Programming"));
    students.push_back(Student("Big Bad John", "Tom-foolery"));

}

//Get all information for a book, then add it to the vector of books
void Library::addBook()
{
    string title, author, isbn;
    cin.ignore();
    cout << "Enter the book title: ";
    getline(cin, title);

    cout << "Enter the Author's name: ";
    getline(cin, author);

    cout << "Enter the book ISBN: ";
    getline(cin, isbn);

    books.emplace_back(title, author, isbn);
}

//print out all books in the system and displays them 
void Library::listBooks() const
{

    cout << "~~\n~~\n~~\n";

    cout << "Library's current stock:\n";
    for (const auto& book : books)
    {
        cout << "Title:    " << book.getTitle() 
             << "\nAuthor: " << book.getAuthor() 
             << "\nISBN:   " << book.getISBN() 
             << "\nStock:  " << (book.getAvailabilty() ? "Available" : "Checked-out") << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
}

//prints out only the titles of the books that are in stock... used for the checkout process
void Library::listTitles() const
{
    int index = 1;
    cout << "Library's current stock:\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    for (const auto& book : books)
    {
        if (book.getAvailabilty()) {
            cout <<index << ". " << book.getTitle() << endl;
            ++index;
        }
    }

}

// Switch menu to manage users... create, list existing, edit...
void Library::manageUsers()
{
    int choice;

    do
    {
        cout << "1. Create New User\n"
            << "2. List Existing Users\n"
            << "3. Edit Existing User\n"
            << "4. Back To Main Menu\n"
            << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewUser();
            break;
        case 2:
            listUsers();
            break;
        case 3:
            editUser();
            break;
        }

    } while (choice != 4);

}

//---------------------------------------------------------------------
//-Allows the creation of a new user and puts it the end of the vector-
//---------------------------------------------------------------------
void Library::createNewUser()
{
    string name;    // create a variable to hold the user input name
    cin.ignore();   // clears a blank line to ensure the getline is allowed to go through

    cout << "Enter User's name: ";
    getline(cin, name); // gets user input

    // Prompt for faculty status
    char facultyChoice;

    do {
        // get a check if the new user is a faculty member
        cout << "Is the user a faculty member? (y/n): ";
        cin >> facultyChoice;
        facultyChoice = toupper(facultyChoice);
       
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Discard invalid input

        // Check for valid input
        if(facultyChoice != 'Y' && facultyChoice != 'N') {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }
    } while (facultyChoice != 'Y' && facultyChoice != 'N');

    // Determine faculty status
    bool isFaculty = (facultyChoice == 'Y');

    if (isFaculty) {    // if they are faculty...
        string department;

        //get their department...
        cout << "What department does " << name << " Work in: ";
        getline(cin, department);
        Faculty newFaculty(name, department);
        faculty.push_back(newFaculty);
    }
    else {      // if they are a student...
        string major;

        cout << "What is " << name << " majoring in: ";
        getline(cin, major);
        Student newStudent(name, major);
        students.push_back(newStudent);
    }
}

//-------------------------------------------------------------
//-Will print out all currently saved users in the user vector-
//-------------------------------------------------------------
void Library::listUsers()
{
    cout << "--->Students in the database<---\n";
    for ( const auto& student : students)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        student.displayInfo();
        student.listCheckedBooks();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "--->Faculty in the database<---\n";
    for (const auto& fac : faculty)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        fac.displayInfo();
        fac.listCheckedBooks();
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
//-----------------------------------------------------------------------------------------
//This function will allow the editing of a certain user on file, or the deletion of that user.
//-----------------------------------------------------------------------------------------
void Library::editUser()
{
    int idChoice;   // user input to get the user to edit
    int choice;     // general user input for menu options
    bool isValid = false;   // keeps user in loop 

    //do this only once to keep screen from overflowing / not in the while loop
    listUsers();    // lists the users currently in the program

    while (!isValid)
    {
        //get user input for the user id you'd like to alter
        cout << "Enter the userID # of the user you'd like to edit/remove: ";
        cin >> idChoice;

        if (cin.fail() || idChoice < 1) { // If input is not numeric or less than 1
            cout << "Invalid userID. Please enter a valid ID #: \n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        bool found = false; // flag to indicate if user is found

        for (auto iterator = students.begin(); iterator != students.end(); iterator++){
            if (iterator->getUserID() == idChoice) {
                found = true;

                cout << "\n\nWould you like to edit or remove " << iterator->getName() << "?\nEnter 1 to edit, or 2 to remove: ";
                cin >> choice;

                // ensures a correct option of 1 or 2 are selected
                if (cin.fail() || (choice != 1 && choice != 2))
                {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "\nPlease enter a valid option\nEnter 1 to edit, or 2 to remove: ";
                    cin >> choice;
                }
                //edit the user information
                if (choice == 1) {
                    string newName;
                    string newMajor;
                    cout << "\n\nEnter a new name for this user: ";
                    cin.ignore();
                    getline(cin, newName);

                    cout << "\nEnter a new Major for " << iterator->getName() << ": ";
                    cin.ignore();
                    getline(cin, newMajor);

                    iterator->setUsername(newName);
                    iterator->setMajor(newMajor);
                    isValid = true;
                }
                else if (choice == 2) {
                    //remove the user from the vector
                    cout << "Removing user " << iterator->getName() << " from database.\n";
                    students.erase(iterator);  
                    isValid = true;
                    break;  // breaks out of the loop since the iterator is no longer existant
                }
            }
        }

        //loop for faculty if not found in student loop
        if (!found) {
            for (auto iterator = faculty.begin(); iterator != faculty.end(); iterator++) {
                if (iterator->getUserID() == idChoice) {
                    found = true;
                    cout << "\n\nWould you like to edit or remove " << iterator->getName() << "?\nEnter 1 to edit, or 2 to remove: ";
                    cin >> choice;

                    // ensures a correct option of 1 or 2 are selected
                    if (cin.fail() || (choice != 1 && choice != 2))
                    {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "\nPlease enter a valid option\nEnter 1 to edit, or 2 to remove: ";
                        cin >> choice;
                    }
                    //edit the user information
                    if (choice == 1) {
                        string newName;
                        string newDept;

                        cout << "\n\nEnter a new name for this user: ";
                        cin.ignore();
                        getline(cin, newName);

                        cout << "\nEnter a new dept for " << iterator->getName() << ": ";
                        cin.ignore();
                        getline(cin, newDept);

                        iterator->setUsername(newName);
                        iterator->setDepartment(newDept);
                        isValid = true;
                    }
                    else if (choice == 2) {
                        //remove the user from the vector
                        cout << "Removing user " << iterator->getName() << " from database.\n";
                        faculty.erase(iterator);
                        isValid = true;
                        break;  // breaks out of the loop since the iterator is no longer existant
                    }
                }
            }
        }

        if (!isValid) {
            cout << "Invalid userID. Please enter a valid ID #: \n";
        }
    }
}

// Menu to handled the checking and returning of books, as well as a list of the current books in the system.
void Library::transactionsMenu()
{

    int choice;

    do
    {
        cout << "Manage Transactions:\n"
             << "1. Check Out a Book\n"
             << "2. Return a Book\n"
             << "3. List All Books\n"
             << "4. Back to Main Menu\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            checkoutBook();
            break;
        case 2:
            returnBook();
            break;
        case 3:
            listBooks();
            break;
        }
    } while (choice != 4);


}

//Great Big checkout book method, tons of error checking
void Library::checkoutBook()
{
    int bookChoiceIndex;            // variable used for the user to get the according book that is in the availableBooks vector
    vector<Book*> availableBooks;   // vector to hold all the books that are actually available for check out.
    int idChoice;
    bool isValid = false;
    User* selectedUser = nullptr;   //pointer to hold user info who is attempting to check out a book

    listUsers();    // list the users who are in system
    //get a user instance to check out and validate the input
    while (!isValid)
    {
        cout << "Enter the userID # of the user who is checking out: ";
        cin >> idChoice;

        if (cin.fail() || idChoice < 1) { // If input is not numeric or less than 1
            cout << "Invalid userID. Please enter a valid ID #: \n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cin >> idChoice;
        }

        bool found = false;

        //loop for the students
        for (auto iterator = students.begin(); iterator != students.end(); iterator++) 
        {
            if (iterator->getUserID() == idChoice) {
                selectedUser = &(*iterator);    //assigns the selected user to the variable to be used later outside of this while loop
                cout << "Welcome " << selectedUser->getName() << "!\n\n"; // greeting
                isValid = true; // if the id entered matches an id, is true
                found = true;   // tells compiler to skip the loop for the faculty loop below
            }
        }

        //seperate loop for the faculty, if not found in students
        if (!found)
        {
            for (auto iterator = faculty.begin(); iterator != faculty.end(); iterator++)
            {
                if (iterator->getUserID() == idChoice) {
                    selectedUser = &(*iterator);    //assigns the selected user to the variable to be used later outside of this while loop

                    cout << "Welcome " << selectedUser->getName() << "!\n\n";
                    isValid = true; // if the id entered matches an id, is true
                    found = true;
                }
            }
        }
        if (!isValid) {
            cout << "Invalid userID. Please enter a valid ID #: \n\n";
        }
    }

    // create a new vector of the available books only
    for (auto& book : books) {
        if (book.getAvailabilty()) {
            availableBooks.push_back(&book);
        }
    }    

    listTitles(); //display all of the titles ONLY

    // listTitles() will list a numbered index starting at 1 and the book titles
    // The user is prompted to enter a number that matches that index
    cout << "\nEnter the number corresponding to the book you'd like to check out: ";
    cin >> bookChoiceIndex;

    // error check input
    if (cin.fail() || bookChoiceIndex < 1 || bookChoiceIndex > availableBooks.size()) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid choice. Please enter a number between 1 and " << availableBooks.size() << "." << endl;
    }
    else {
        // Get the book using the index (adjusting for zero-based indexing)
        Book* selectedBook = availableBooks[bookChoiceIndex - 1];
        // Perform the checkout
        selectedUser->checkoutBook(*selectedBook); // Pass the matched Book object
    }
}

// returns a book, similar structure to that of CheckoutBook
void Library::returnBook()
{
    int idChoice;
    int returnChoice;
    bool isValid = false;
    User* selectedUser = nullptr;

    listUsers();
    //get a user instance to check out and validate the input
    while (!isValid)
    {
        cout << "Enter the userID # of the user who is returning books: ";
        cin >> idChoice;

        if (cin.fail() || idChoice < 1) { // If input is not numeric or less than 1
            cout << "Invalid userID. Please enter a valid ID #: \n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cin >> idChoice;
        }

        bool found = false;

        for (auto& student : students) 
        { 
            if (student.getUserID() == idChoice) 
            {
                selectedUser = &student;
                if (selectedUser->getCheckedBooks().empty()) {
                    cout << "\nSorry, " << selectedUser->getName() << " has no checked books.\n";
                    return; // Exit the `checkoutBook` method and return to the main menu
                }
                isValid = true;
                found = true;
                break;
            }
        }

        //seperate loop for faculty
        if (!found)
        {
            for (auto& fac : faculty)
            {
                if (fac.getUserID() == idChoice)
                {
                    selectedUser = &fac;
                    if (selectedUser->getCheckedBooks().empty()) {
                        cout << "\nSorry, " << selectedUser->getName() << " has no checked books.\n";
                        return; // Exit the `checkoutBook` method and return to the main menu
                    }
                    isValid = true;
                    found = true;
                    break;
                }
            }
        }

        if (!isValid) {
            cout << "Invalid userID. Please enter a valid ID #: \n\n";
        }
    }


    do {
        selectedUser->listCheckedBooks();
        cout << "\nEnter the number corresponding to the book you'd like to return: ";
        cin >> returnChoice;

        // error check input
        if (cin.fail() || returnChoice < 1 || returnChoice > selectedUser->getCheckedBooks().size()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice." << endl;
        }
        else {
            break;
        }
    } while (true);
    // Get the book to return
    Book& bookToReturn = selectedUser->getCheckedBooks()[returnChoice - 1];
    //variable created so title can still be accessed after erasure of user CheckedBook data cause the reference to be lost in the BookToReturn variable above.
    string bookTitle = bookToReturn.getTitle();
    // Update book availability in the library's books vector
    for (auto& book : books) { // Assuming 'books' is the Library's master book list
        if (book.getTitle() == bookToReturn.getTitle()) {
            book.setAvailabilty(true);
            cout << "Library stock updated: \"" << bookTitle << "\" is now available." << endl;
            break;
        }
    }

    // Remove the book from the user's checkedBooks
    selectedUser->getCheckedBooks().erase(selectedUser->getCheckedBooks().begin() + (returnChoice - 1));
    cout << selectedUser->getName() << " has returned the book: \"" << bookTitle << "\"" << endl;

    //for (int i = 0; i < checkedBooks.size(); ++i)
    //{
    //    if (checkedBooks[i].getTitle() == book.getTitle()) {
    //        Library.updateBookAvailability(book.getTitle(), true); // Update the book as available
    //        checkedBooks.erase(checkedBooks.begin() + i);
    //        cout << userName << " has returned the book : " << book.getTitle() << endl;
    //        break;
    //    }

    //}
}

// The big main menu of the program. everything stems from here
void Library::libraryMenu()
{
    Library* library = Library::getInstance(); // Access the Singleton instance
    int choice;

    do
    {
    cout << "Welcome to Ricky's Library!\n"
        << "1. Add Books\n"
        << "2. List Books\n"
        << "3. Manage Users\n"
        << "4. Manage Transactions\n"
        << "5. Exit Program\n";

    cin >> choice;

   
        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            listBooks();
            break;
        case 3: 
            manageUsers();
            break;
        case 4:
            transactionsMenu();
            break;
        }
    } while (choice != 5);
}
