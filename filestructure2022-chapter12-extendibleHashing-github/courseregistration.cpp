#include "courseregistration.h"
#include <strstream>
#include <string.h>
#pragma warning(disable : 4996)

CourseRegistration::CourseRegistration()
{
	SId[0] = 0;
	CourseName[0] = 0;
	Grade[0] = 0;
}

CourseRegistration::CourseRegistration(char* sid, char* coursename, char* grade)
{
	strcpy(SId, sid); strcpy(CourseName, coursename);
	strcpy(Grade, grade);
}

char* CourseRegistration::Key() const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << SId << ends;
	return key.str();
}

int CourseRegistration::Pack(IOBuffer& Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(SId);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(CourseName);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Grade);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int CourseRegistration::Unpack(IOBuffer& Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer.Unpack(SId, 5);
	if (numBytes == -1) return FALSE;
	SId[numBytes] = 0;
	numBytes = Buffer.Unpack(CourseName, 10);
	if (numBytes == -1) return FALSE;
	CourseName[numBytes] = 0;
	numBytes = Buffer.Unpack(Grade, 1);
	if (numBytes == -1) return FALSE;
	Grade[numBytes] = 0;
	return TRUE;
}

void CourseRegistration::Print(ostream& stream, char* label) const
{	
	stream << "		" << SId << ' ' << CourseName << ' ' << Grade << endl;
}