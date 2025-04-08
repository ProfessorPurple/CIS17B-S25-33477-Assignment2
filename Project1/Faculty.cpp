#include "Faculty.h"

Faculty::Faculty(const string& name, const string& dept)
    : User(name, true), department(dept) {
}

void Faculty::displayInfo() const
{
    {
        cout << "Name:   " << this->getName() << endl;
        cout << "UserId: " << this->getUserID() << endl;
        cout << "Role:   " << (this->getIsFaculty() ? "Faculty" : "Student") << endl;
    }
}

void Faculty::setDepartment(string dept)
{
    department = dept;
}
