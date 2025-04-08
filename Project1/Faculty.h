#pragma once
#include "User.h"
class Faculty : public User
{
private:
	string department;

public:
	Faculty(const string& name, const string& dept);
	void displayInfo() const override;
	void setDepartment(string);
};

