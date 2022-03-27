// D.7 writestr.cpp - 가변길이 레코드 + 가변길이 필드
// write a stream of persons, using fstream.h 
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "student.h"
using namespace std;

//Fig 4.7 write a variable-length, delimited buffer to a file
const int MaxBufferSize = 200;
int WriteStudent (ostream & stream, Student & p)
{	char buffer [MaxBufferSize];
	strcpy(buffer, to_string(p.Identifier).c_str()); strcat(buffer,"|");
	strcat(buffer, p.Name); strcat(buffer,"|");
	strcat(buffer, p.Address);  strcat(buffer,"|");
	strcat(buffer, to_string(p.DateOfFirstEnrollment).c_str());  strcat(buffer,"|");
	strcat(buffer, to_string(p.NumberOfCreditHoursCompleted).c_str());  strcat(buffer,"|");
	short length=strlen(buffer); 
	stream.write ((char *)&length, sizeof(length)); // write length
	stream.write (&buffer[0], length);
	return 1;
}
istream& operator >> (istream& stream, Student& p)
{ // read fields from input
	cout << "Enter Identifier, or <cr> to end: " << flush; stream >> p.Identifier;
	if (strlen(to_string(p.Identifier).c_str()) == 0) return stream;
	cout << "Enter Name: " << flush; stream.getline(p.Name, 30);
	cout << "Enter Address: " << flush; stream.getline(p.Address, 30);
	cout << "Enter Dateofenrollment: " << flush; stream >> p.DateOfFirstEnrollment;
	cout << "Enter credithours: " << flush; stream >> p.NumberOfCreditHoursCompleted;
	return stream;
}
int main (){
	char filename [20];
	Student p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ofstream stream (filename, ios::out);
	if (stream.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		cin >> p;
		if (strlen(p.Name)==0) break;
		// write person to output stream
		WriteStudent(stream,p);
	}
	system("pause");
	return 1;
}

