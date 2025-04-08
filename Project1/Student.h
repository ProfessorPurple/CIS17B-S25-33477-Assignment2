#pragma once
#include "User.h"
class Student : public User
{
private:
	string major;

public:
	Student(const string& name, const string& major);
	void displayInfo() const override;

	void setMajor(string);
};

