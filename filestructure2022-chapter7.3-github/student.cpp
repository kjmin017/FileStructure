#include "student.h"

Student::Student() { Clear(); }

void Student::Clear()
{
	// set each field to an empty string
	Identifier[0] = 0; Name[0] = 0; Address[0] = 0;
	DateOfFirstEnrollment[0] = 0; NumberOfCreditHoursCompleted[0] = 0;
}


int Student::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(Identifier);//동적 바인딩
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Name);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(DateOfFirstEnrollment);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(NumberOfCreditHoursCompleted);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Student::Unpack(IOBuffer& Buffer)
{
	Clear();
	int numBytes;
	//power of virtual functions
	numBytes = Buffer.Unpack(Identifier);//Unpack()에 대항 F12를 누르면 일치하는 3개 함수 존재 - 동적 바인딩
	if (numBytes == -1) return FALSE;
	Identifier[numBytes] = 0;
	numBytes = Buffer.Unpack(Name);
	if (numBytes == -1) return FALSE;
	Name[numBytes] = 0;
	numBytes = Buffer.Unpack(Address);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer.Unpack(DateOfFirstEnrollment);
	if (numBytes == -1) return FALSE;
	DateOfFirstEnrollment[numBytes] = 0;
	numBytes = Buffer.Unpack(NumberOfCreditHoursCompleted);
	if (numBytes == -1) return FALSE;
	NumberOfCreditHoursCompleted[numBytes] = 0;
	return TRUE;
}

int Student::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedFieldBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(9); // LastName [11];
	result = result && Buffer.AddField(11); // firstName [11];
	result = result && Buffer.AddField(16); // City [16];
	result = result && Buffer.AddField(10); // State [3];
	result = result && Buffer.AddField(2); // ZipCode [10];
	return result;
}

int Student::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimFieldBuffer to be used for Persons
{
	return TRUE;
}

int Student::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthFieldBuffer to be used for Persons
{
	return TRUE;
}

void Student::Print(ostream& stream, char* label) const
{
	if (label == 0) stream << "Person:";
	else stream << label;
	stream << "\n\t  Last Name '" << Identifier << "'\n"
		<< "\t First Name '" << Name<< "'\n"
		<< "\t    Address '" << Address << "'\n"
		<< "\t       City '" << DateOfFirstEnrollment << "'\n"
		<< "\t      State '" << NumberOfCreditHoursCompleted << "'\n" << flush;
}