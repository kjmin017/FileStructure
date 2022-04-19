//Recording.cpp
#include "recordng.h"
#include <strstream>
#include <string.h>

Recording::Recording ()
{
	Identifier[0] = 0; Name[0] = 0; Address[0] = 0;
	DateOfFirstEnrollment[0] = 0; NumberOfCreditHoursCompleted[0] = 0;
}

Recording::Recording (char * label, char * idNum, char * title, 
		char * composer, char * artist)
{
	strcpy(Identifier, label); strcpy(Name, idNum);
	strcpy(Address, title); strcpy(DateOfFirstEnrollment, composer);
	strcpy(NumberOfCreditHoursCompleted, artist);
}

char * Recording::Key () const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << Name << Identifier << ends;
	return key.str();	
}

int Recording::Pack (IOBuffer & Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer . Clear ();
	numBytes = Buffer . Pack (Identifier);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (Name);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (DateOfFirstEnrollment);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (NumberOfCreditHoursCompleted);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Recording::Unpack (IOBuffer & Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer . Unpack (Identifier, 9);
	if (numBytes == -1) return FALSE;
	Identifier[numBytes] = 0;
	numBytes = Buffer . Unpack (Name, 11);
	if (numBytes == -1) return FALSE;
	Name[numBytes] = 0;
	numBytes = Buffer . Unpack (Address, 16);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer . Unpack (DateOfFirstEnrollment, 10);
	if (numBytes == -1) return FALSE;
	DateOfFirstEnrollment[numBytes] = 0;
	numBytes = Buffer . Unpack (NumberOfCreditHoursCompleted, 2);
	if (numBytes == -1) return FALSE;
	NumberOfCreditHoursCompleted[numBytes] = 0;
	return TRUE;
}

void Recording::Print (ostream & stream, char * label) const
{
	stream << Identifier <<'|'<<Name <<'|' << Address <<'|'
		<< DateOfFirstEnrollment <<'|'<< NumberOfCreditHoursCompleted ;
}
int Recording::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedFieldBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(9); // IdNum[7]
	result = result && Buffer.AddField(11); // Title[30]
	result = result && Buffer.AddField(16); // Composer[30]
	result = result && Buffer.AddField(10); // Artist[30]
	result = result && Buffer.AddField(2); // Label[7]
	return result;
}
//char IdNum[7]; char Title[30]; char Composer[30];char Artist[30]; char Label[7];
int Recording::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimFieldBuffer to be used for Persons
{
	return TRUE;
}

int Recording::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthFieldBuffer to be used for Persons
{
	return TRUE;
}
