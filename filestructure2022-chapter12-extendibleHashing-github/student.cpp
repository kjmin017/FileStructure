#include "student.h"
#include <strstream>
#include <string.h>
#pragma warning(disable : 4996)

Student::Student()
{
	SId[0] = 0; 
	SName[0] = 0; 
	Dept[0] = 0;
	SYear[0] = 0;
}

Student::Student(char* sid, char* sname, char* dept,
	char* syear)
{
	strcpy(SId, sid); strcpy(SName, sname);
	strcpy(Dept, dept); strcpy(SYear, syear);
}

char* Student::Key() const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << SId << ends;
	return key.str();
}

int Student::Pack(IOBuffer& Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(SId);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(SName);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Dept);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(SYear);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Student::Unpack(IOBuffer& Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer.Unpack(SId, 5);
	if (numBytes == -1) return FALSE;
	SId[numBytes] = 0;
	numBytes = Buffer.Unpack(SName, 14);
	if (numBytes == -1) return FALSE;
	SName[numBytes] = 0;
	numBytes = Buffer.Unpack(Dept, 10);
	if (numBytes == -1) return FALSE;
	Dept[numBytes] = 0;
	numBytes = Buffer.Unpack(SYear, 1);
	if (numBytes == -1) return FALSE;
	SYear[numBytes] = 0;
	return TRUE;
}

void Student::Print(ostream& stream, char* label) const
{
	stream << SId << ' ' << SName << ' ' << Dept << ' '	<< SYear << endl;
}