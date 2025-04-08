#include "Student.h"

Student::Student(const string& name, const string& major)
    : User(name, false), major(major) {
}

void Student::displayInfo() const
{
    cout << "Name:   " << this->getName() << endl;
    cout << "UserId: " << this->getUserID() << endl;
    cout << "Role:   " << (this->getIsFaculty() ? "Faculty" : "Student") << endl;
}

void Student::setMajor(string mj)
{
    major = mj;
}
