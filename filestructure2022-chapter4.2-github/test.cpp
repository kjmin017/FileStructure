// test.cc// Copyright 1997, Gregory A. Riccardi
// 4장 과제2: while(1) { } 문을 완성한다.
#include <fstream>
#include <string.h>
#include <iomanip>
#include <string.h>
#include <string>
#include "fixtext.h"
#include "lentext.h"
#include "deltext.h"
#include "student.h"
using namespace std;
//*
void testFixText()
{
	Student s;
	FixedTextBuffer Buff(6);
	Student::InitBuffer(Buff);
	strcpy(s.Name, "Ames");
	strcpy(s.Address, "123 Maple");
	s.DateOfFirstEnrollment = 0;
	s.Identifier = 202212345;
	s.NumberOfCreditHoursCompleted = 0;
	s.Print(cout);
	s.Pack(Buff);
	Buff.Print(cout);
	ofstream TestOut("fixtext.dat", ios::out | ios::binary);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("fixtext.dat", ios::in | ios::binary);
	FixedTextBuffer InBuff(6);
	Student::InitBuffer(InBuff);
	Buff.Read(TestIn);
	s.Unpack(Buff);
	s.Print(cout);
	Student person;
	Student* stable[10];
	FixedTextBuffer Buff(6);
	Student::InitBuffer(Buff);
	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);
	//*
	string name[5];
	string address[5];
	int DFE[5];
	int identifier[5];
	int NCHC[5];
	while (1)
	{
		int count;
		int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Student object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (int i = 0; i < count; i++)
			{
				cin >> name[i]; cin.ignore();
				cin >> address[i]; cin.ignore();
				cin >> DFE[i];
				cin >> identifier[i];
				cin >> NCHC[i];
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{
				cout << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return ;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fostream << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			fostream.close();
			break;
		}
		case 4:
		{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return ;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fistream >> name[i] >> "//" >> address[i] >> "//" >> DFE[i] >> "//" >> identifier[i] >> "//" >> NCHC[i];
			}
			fistream.close();
			break;
		}
		default:
			// others
			exit(0);
			break;
		}
	}
}
//*/
//*
int testLenText()
{
	char filename[20];
	cout << "\nTesting LengthTextBuffer" << endl;
	Student s;
	LengthTextBuffer Buff;
	Student::InitBuffer(Buff);
	strcpy(s.Name, "Ames");
	strcpy(s.Address, "123 Maple");
	s.DateOfFirstEnrollment = 0;
	s.Identifier = 202212345;
	s.NumberOfCreditHoursCompleted = 0;
	s.Print(cout);
	Buff.Print(cout);
	cout << "pack student " << s.Pack(Buff) << endl;
	Buff.Print(cout);
	ofstream TestOut("lentext.dat", ios::out | ios::binary);
	Buff.Write(TestOut);
	Buff.Write(TestOut);
	strcpy(s.Name, "Dave");
	s.Print(cout);
	s.Pack(Buff);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("lentext.dat", ios::in | ios::binary);
	LengthTextBuffer InBuff;
	Student::InitBuffer(InBuff);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	//*
	string name[5];
	string address[5];
	int DFE[5];
	int identifier[5];
	int NCHC[5];
	while (1)
	{
		int count;
		int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Student object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (int i = 0; i < count; i++)
			{
				cin >> name[i]; cin.ignore();
				cin >> address[i]; cin.ignore();
				cin >> DFE[i];
				cin >> identifier[i];
				cin >> NCHC[i];
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{
				cout << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			break;
		case 3:
			{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fostream << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			fostream.close();
			break;
			}
		case 4:
			{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fistream >> name[i] >> "//" >> address[i] >> "//" >> DFE[i] >> "//" >> identifier[i] >> "//" >> NCHC[i];
			}
			fistream.close();
			break;
			}
		default:
			// others
			exit(0);
			break;
		}
	}
	return 1;
}
//*/
int testDelText()
{
	char filename[20];
	cout << "\nTesting DelimTextBuffer" << endl;
	Student s;
	strcpy(s.Name, "Ames");
	strcpy(s.Address, "123 Maple");
	s.DateOfFirstEnrollment = 0;
	s.Identifier = 202212345;
	s.NumberOfCreditHoursCompleted = 0;
	s.Print(cout);
	DelimTextBuffer Buff;
	Student::InitBuffer(Buff);
	Buff.Print(cout);
	cout << "pack student " << s.Pack(Buff) << endl;
	Buff.Print(cout);
	ofstream TestOut("deltextstudent.txt", ios::out | ios::binary | ios::trunc);
	Buff.Write(TestOut);
	Buff.Write(TestOut);
	strcpy(s.Name, "Dave");
	s.Print(cout);
	s.Pack(Buff);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("deltextperson.txt", ios::in | ios::binary);
	DelimTextBuffer InBuff;	Student::InitBuffer(InBuff);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << s.Unpack(Buff) << endl;
	s.Print(cout);
	//*
	string name[5];
	string address[5];
	int DFE[5];
	int identifier[5];
	int NCHC[5];
	while (1)
	{
		int count; int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Student object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			for (int i = 0; i < count; i++)
			{
				cin >> name[i]; cin.ignore();
				cin >> address[i]; cin.ignore();
				cin >> DFE[i]; 
				cin >> identifier[i];
				cin >> NCHC[i];
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{
				cout << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fostream << name[i] << "//" << address[i] << "//" << DFE[i] << "//" << identifier[i] << "//" << NCHC[i] << endl;
			}
			fostream.close();
			break;
		}
		case 4:
		{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Student::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{
				fistream >> name[i] >> "//" >> address[i] >> "//" >> DFE[i] >> "//" >> identifier[i] >> "//" >> NCHC[i];
			}
			fistream.close();
			break;
		}
		default:
			// others
			exit(0);
			break;
		}
	}
		//*/
	return 1;
}


int main(void)
{
	testFixText();
	testLenText();
	testDelText();
	system("pause");
	return 1;
}
