// create a list of student information
#include <iostream>
#include <string.h>
#include "student.h"
using namespace std;

istream& operator >> (istream& stream, Student& s)
{ // read fields from input
	cout << "Enter name, or <cr> to end: " << flush;
	stream.getline(s.Name, 30);
	if (strlen(s.Name) == 0) return stream;
	cout << "Enter address: " << flush; stream.getline(s.Address, 30);
	cout << "Enter date: " << flush; stream.getline(s.date, 30);
	cout << "Enter DateOfFirstEnrollment: " << flush; stream.getline(s.DateOfFirstEnrollment, 15);
	cout << "Enter NumberOfCreditHourse: " << flush; stream.getline(s.NumberOfCreditHourse, 10);
	return stream;
}

Student::~Student() {
	if (Name != 0) delete Name;
	if (Address != 0) delete Address;
	if (DateOfFirstEnrollment != 0) delete DateOfFirstEnrollment;

	Identifier = 0;
	date = 0;
	NumberOfCreditHourse = 0;
	Name[0] = 0;
	Address[0] = 0;
	DateOfFirstEnrollment[0] = 0;
}

Student& Student::operator = (const Student& s) {
	if (s.Identifier < 0) {
		s.~Student();

		Student s2;
		s2.date = s.date;
		s2.Identifier = s.Identifier;
		s2.NumberOfCreditHourse = s.NumberOfCreditHourse;
		strcpy(s2.Name, s.Name);
		strcpy(s2.Address, s.Address);
		strcpy(s2.DateOfFirstEnrollment, s.DateOfFirstEnrollment);
	}
	cout << "assignment::operator=() is called" << endl;

	return *this;
}