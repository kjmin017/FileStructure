// recordng.h

#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include "iobuffer.h"

#include "fixfld.h"
#include "length.h"
#include "delim.h"
using namespace std;
// class person with fixed field buffer

class Recording
// a recording with a composite key
{public:
	Recording ();
	Recording (char * label, char * idNum, char * title, 
		char * composer, char * artist);
	char Identifier[9]; char Name[11]; char Address[16];
	char DateOfFirstEnrollment[10]; char NumberOfCreditHoursCompleted[2];
	char * Key () const; // return key of object
	int Unpack (IOBuffer &);
	int Pack (IOBuffer &) const;
	void Print (ostream &, char * label = 0) const;
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
};

ostream & operator << (ostream &, Recording &);
inline ostream & operator << (ostream & stream, Recording & rec)
{	rec.Print(stream); return stream;}

#endif
