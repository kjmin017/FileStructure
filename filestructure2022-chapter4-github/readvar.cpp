// D.6 readvar.cpp
// write a stream of persons, using fstream.h 
#include <fstream>
#include <strstream>
#include <string.h>
#include "student.h"
using namespace std;
istream & operator >> (istream & stream, Person & p)
{ // read fields from stream
	char delim;
	stream.getline(p.LastName, 30,'|');
	if (strlen(p.LastName)==0) return stream; 
	stream.getline(p.FirstName,30,'|');
	stream.getline(p.Address,30,'|');
	stream.getline(p.City, 30,'|');
	stream.getline(p.State,15,'|');
	stream.getline(p.ZipCode,10,'|');
	return stream;
}

//Fig 4.9 - read a variable-sized Person record
int ReadVariablePerson (istream & stream, Person & p)
{ // read a variable sized record from stream and store it in p
  // if read fails, set p.LastName to empty string and return 0
	short length;
	//istream& read(const char*, streamsize);
	stream . read ((char*)&length, sizeof(length)); //stream.read(&length, sizeof(length)) => 오류
	cout << "length = " << length << endl;
	if (stream . fail()){p.LastName[0]=0; return 0;}
	char * buffer = new char[length+1];
	stream . read (buffer, length);
	buffer [length] = 0; // terminate buffer with null
	istrstream strbuff (buffer);
	strbuff >> p;
	return 1;
}
ostream& operator << (ostream& stream, Person& p)
{ // insert fields into file
	cout << "Person 객체를 출력한다" << endl;
	stream << p.LastName << '|' << p.FirstName << '|'
		<< p.Address << '|' << p.City << '|'
		<< p.State << '|' << p.ZipCode << '|';
	cout << endl;
	return stream;
}
int main (void){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ifstream stream (filename, ios::in);
	if (stream.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		ReadVariablePerson (stream, p);
		if (strlen(p.LastName)==0) break;
		// write person to file
		cout << p;
	}
	system("pause");
	return 1;
}
