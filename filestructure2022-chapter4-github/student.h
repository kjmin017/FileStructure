#pragma once
#ifndef STUDENT
#define STUDENT

class Student
{
public:
	// data members
	int Identifier; char Name[11]; char Address[16];
	int DateOfFirstEnrollment; int NumberOfCreditHoursCompleted;
	// method
	Student(); // default constructor
	Student& operator = (const Student&);
};

Student::Student()
{//constructor
	Identifier = 0; Name[0] = 0; Address[0] = 0;
	DateOfFirstEnrollment = 0; NumberOfCreditHoursCompleted = 0;
}

#endif