#pragma once
#ifndef STUDENT
#define STUDENT

class Student
{
public:
	// data members
	int Identifier; char Name[11]; char Address[16];
	date DateOfFirstEnrollment[16]; int NumberOfCreditHourse;
	// method
	Student(); // default constructor
};

Student::Student()
{//constructor
	LastName[0] = 0; FirstName[0] = 0; Address[0] = 0;
	City[0] = 0; State[0] = 0; ZipCode[0] = 0;
}

#endif