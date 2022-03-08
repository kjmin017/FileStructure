
#include <iostream>
#include <stdlib.h>
 using namespace std;
class String {
public:
	//default constructor
	String();
	//copy constructor
	String(const String&);
	//create from C string
	String(const char*);
	//destructor
	~String();
	//assignment
	String& operator = (const String&);
	//less than
	int operator<(const String&)const;
		//greater than
	int operator>(const String&)const;
		//less than or equal to
	int operator<=(const String&)const;
		//greater than or equal to
	int operator>=(const String&)const;
		//inequality
	int operator != (const String&) const;
		//equality
	int operator == (const String&) const;
		//return a copy of string
	char* str() const;
		//conversion to char*
	operator char* ();
protected:
	char* string;
	unsigned int MaxLength;
	friend ostream& operator << (ostream& stream, String& str);
};
