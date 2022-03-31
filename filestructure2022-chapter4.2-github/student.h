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

	void Clear();
	static int InitBuffer(FixedTextBuffer&);
	int Unpack(FixedTextBuffer&);
	int Pack(FixedTextBuffer&) const;
	static int InitBuffer(LengthTextBuffer&);
	int Unpack(LengthTextBuffer&);
	int Pack(LengthTextBuffer&) const;
	static int InitBuffer(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);
	int Pack(DelimTextBuffer&) const;
	void Print(std::ostream&);
	Student(); // default constructor
	Student& operator = (const Student&);
};

Student::Student()
{//constructor
	Identifier = 0; Name[0] = 0; Address[0] = 0;
	DateOfFirstEnrollment = 0; NumberOfCreditHoursCompleted = 0;
}

#endif