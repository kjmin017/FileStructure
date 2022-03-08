#include "String.h"
int main() {
	//use string::string(const char*)
	String s1("Hello");
	String s2;
	char str[10];
	//use string::operator char *();
	cout <<endl<< "strcpy(str, s1) is called" << endl;
	strcpy(str, s1);
	cout << endl<<"s2 = s1 is called" << endl;
	s2 = s1;
	String s3 = s2;
	cout <<endl<< "s3 = str is called::" << endl;
	s3 = str;
	cout << endl;
	//using overloaded assignment}
	system("pause");
	return 1;
}
