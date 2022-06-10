#pragma once
#pragma once

#ifndef COURSEREGISTRATION_H
#define COURSEREGISTRATION_H

#include <iostream>
#include "iobuffer.h"

// class person with fixed field buffer
class CourseRegistration
	// a recording with a composite key
{
public:
	CourseRegistration();
	CourseRegistration(char* sid, char* coursename, char* grade);
	char SId[5]; char CourseName[10]; char Grade[1];
	char* Key() const; // return key of object
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	void Print(ostream&, char* label = 0) const;
};

ostream& operator << (ostream&, CourseRegistration&);
inline ostream& operator << (ostream& stream, CourseRegistration& rec)
{
	rec.Print(stream); return stream;
}

#endif
