#include "String.h"
//ostream& operator << (ostream& stream, String& str);
ostream& operator << (ostream& stream, String& str) {
	stream << str.string; return stream;
}
inline int String::operator > (const String& str) const {
	return !(*this <= str);
}
inline int String::operator >= (const String& str) const {
	return !(*this < str);
}
inline int String::operator != (const String& str) const {
	return !(*this == str);
}
String::String() {
	string = new char[20];
	MaxLength = 0;
}
// copy constructor
String::String(const String& str) {
	string = new char[strlen(str.string) + 1];
	strcpy(string, str.string);
	MaxLength = strlen(string);
	cout << endl << "copy constructor is called" << endl;
}
// create from C string
String::String(const char* str) {
	string = new char[strlen(str) + 1];
	strcpy(string, str);
	MaxLength = strlen(string);
	cout << endl << "conversion constructor is called" << endl;
}
String::~String() {
	if (string != 0) delete string;
	MaxLength = 0;
	string = 0;
}

String::operator char* () {
	cout << "operator char*():: " << string << endl;
	return string;
}

//assignment
String& String::operator = (const String& str) {
	if (strlen(str.string) >= MaxLength) {
		delete string;
		string = new char[strlen(str.string) + 1];
		strcpy(string, str.string);
		MaxLength = strlen(string);
	}
	cout << "assignment::operator=() is called" << "::string = " << string << endl;
	strcpy(string, str.string);
	return *this;
}
int String::operator < (const String& str) const {
	// less than, lexicographic
	return strcmp(string, str.string) < 0;
}
int String::operator <= (const String& str)const {
	return strcmp(string, str.string) <= 0;
}
int String::operator == (const String& str)const {
	return strcmp(string, str.string) <= 0;
}
// return a copy of the string
char* String::str() const {
	return string;
}
