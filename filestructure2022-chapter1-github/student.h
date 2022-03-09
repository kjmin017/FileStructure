#pragma once
#ifndef STUDENT
#define STUDENT

class Student
{
public:
	// data members
	int Identifier; char Name[11]; char Address[16];
	int date; char DateOfFirstEnrollment[16]; int NumberOfCreditHourse;
	// method
	Student(); // default constructor
	~Student();
	Student& operator = (const Student&);
};

Student::Student()
{//constructor
	Identifier = 0; Name[0] = 0; Address[0] = 0;
	date = 0; DateOfFirstEnrollment[0] = 0; NumberOfCreditHourse = 0;
}

#endif
