#pragma once
#ifndef STUDENT
#define STUDENT

#include <iostream>
#include "fixfld.h"
#include "length.h"
#include "delim.h"
using namespace std;

class Student
{
public:
	// data members
	char Identifier[9]; char Name[11]; char Address[16];
	char DateOfFirstEnrollment[10]; char NumberOfCreditHoursCompleted[2];
	// method
	Student(); // default constructor
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
	void Clear();
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	void Print(ostream&, char* label = 0) const;
};


#endif
