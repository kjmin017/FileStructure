#pragma once
#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "iobuffer.h"

// class person with fixed field buffer
class Student
	// a recording with a composite key
{
public:
	Student();
	Student(char* sid, char* sname, char* dept,
		char* syear);
	char SId[5]; char SName[14]; char Dept[10];	char SYear[1];
	char* Key() const; // return key of object
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	void Print(ostream&, char* label = 0) const;
};

ostream& operator << (ostream&, Student&);
inline ostream& operator << (ostream& stream, Student& rec)
{
	rec.Print(stream); return stream;
}

#endif