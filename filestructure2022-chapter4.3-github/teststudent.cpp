//Student.cc
#include "person.h"

Student::Student() { Clear(); }

void Student::Clear()
{
	// set each field to an empty string
//�ϼ��ؾ� ��
}

int Student::Pack(IOBuffer & Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
// �ϼ��ؾ� ��

	return TRUE;
}

int Student::Unpack(IOBuffer & Buffer)
{
	Clear();
	int numBytes;
	//�ϼ��ؾ� ��
	return TRUE;
}


void Student::Print(ostream & stream, char * label = 0) const
{
	//���� �ʿ�
	if (label == 0) stream << "Student:";
	else stream << label;
	stream << "\n\t SID '" << SID << "'\n";

}

istream& operator>>(istream &, Student &)
{
	// ���� �ʿ�
}
ostream& operator<<(ostream &, Student &)
{
	// ���� �ʿ�
}