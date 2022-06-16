/*
22.6.16 �⸻ �ڵ� ����: ���⹰�� �� ������ ������ �ҽ��ڵ�� ���� ����� ȭ�� ĸ���� ������ �����Ѵ�.
1. data file�� �������� ���ڵ带 �����ϰ� index�μ� btree�� ����Ѵ�.
2. page 563: Programming Project : 20, 21, 22
3. an existing student record file : RecordFile<Student> StudentDataFile(Buffer);
	- data file�� ���� ����� file�� close�Ѵ�.������ data file�� �о Btree index�� �����.
	- resultIndex = bt.Create("studentbtree.dat");
	�ּ� 6�� �̻� ���ڵ� �Է�: R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel"); �̷� ����� ó���Ѵ�.
4. an existing course registration record file : RecordFile<CourseRegistration> CourseRegistrationDataFile(Buffer);
	-resultIndex = bt.Create("coursebtree.dat");
	-data file�� ���� ����� file�� close�Ѵ�.������ data file�� �о Btree index�� �����.
	- �� Sid�� ���Ͽ� ��Ī�Ǵ� ���� ������ 4�� �̻�ǵ��� �Է�
5.6. page 563: Programming Project 22�� ������ SId�� �Է¹޾� ������ ���� ����Ѵ�.(�Է¹��� SId�� ������ ����Ʈ�� ���Ͽ� ã�⸦ �ݺ��Ѵ�)
	s123 ȫ�浿  ��ǻ�� 3
		DB  3.0
		OS  4.0
	s124 ȫ���  ����   4
		File Structure 3.5
		Data Structure 4.5
*** course list�� DB, OS, File Structure, Data Structure, CPP, C Programming, Network, Web Programming, AI, Big Data
*/
#include "direct.h"
#include <conio.h>
#include "recording.h"
#include <fstream>
#include <iomanip>
#include <string>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "buffile.h"
#include "recfile.h"
#include "indbuff.h"
#include <strstream>
#include <iostream>
using namespace std;
class Student {
	char SId[5]; char SName[14]; char Dept[10];	int SYear;
public:
	Student()
	{
		SId[0] = 0;
		SName[0] = 0;
		Dept[0] = 0;
		SYear = 0;
	}
	Student(char* sid, char* sname, char* dept,
		int syear)
	{
		strcpy(SId, sid); strcpy(SName, sname);
		strcpy(Dept, dept); SYear=syear;
	}
	char* Key() const
	{// produce key as concatenation of Label and IdNum
		ostrstream key;
		key << SId << ends;
		return key.str();
	}
	int Pack(IOBuffer& Buffer) const
	{// return TRUE if all succeed, FALSE o/w
		int numBytes;
		Buffer.Clear();
		numBytes = Buffer.Pack(SId);
		if (numBytes == -1) return FALSE;
		numBytes = Buffer.Pack(SName);
		if (numBytes == -1) return FALSE;
		numBytes = Buffer.Pack(Dept);
		if (numBytes == -1) return FALSE;
		return TRUE;
	}
	int Unpack(IOBuffer& Buffer)
	{// unpack with maximum size, and add null termination to strings
		int numBytes;
		numBytes = Buffer.Unpack(SId, 5);
		if (numBytes == -1) return FALSE;
		SId[numBytes] = 0;
		numBytes = Buffer.Unpack(SName, 14);
		if (numBytes == -1) return FALSE;
		SName[numBytes] = 0;
		numBytes = Buffer.Unpack(Dept, 10);
		if (numBytes == -1) return FALSE;
		Dept[numBytes] = 0;
		return TRUE;
	}
	void Print(ostream& stream) const
	{
		stream << SId << ' ' << SName << ' ' << Dept << ' ' << SYear;
	}
};
class CourseRegistration {
	char SId[5]; char CourseName[10]; int Grade;\
public:
	CourseRegistration()
	{
		SId[0] = 0;
		CourseName[0] = 0;
		Grade = 0;
	}
	CourseRegistration(char* sid, char* coursename,
		int grade)
	{
		strcpy(SId, sid); strcpy(CourseName, coursename);
		Grade = grade;
	}
	char* Key() const
	{// produce key as concatenation of Label and IdNum
		ostrstream key;
		key << SId << ends;
		return key.str();
	}
	int Pack(IOBuffer& Buffer) const
	{// return TRUE if all succeed, FALSE o/w
		int numBytes;
		Buffer.Clear();
		numBytes = Buffer.Pack(SId);
		if (numBytes == -1) return FALSE;
		numBytes = Buffer.Pack(CourseName);
		if (numBytes == -1) return FALSE;
		return TRUE;
	}
	int Unpack(IOBuffer& Buffer)
	{// unpack with maximum size, and add null termination to strings
		int numBytes;
		numBytes = Buffer.Unpack(SId, 5);
		if (numBytes == -1) return FALSE;
		SId[numBytes] = 0;
		numBytes = Buffer.Unpack(CourseName, 10);
		if (numBytes == -1) return FALSE;
		CourseName[numBytes] = 0;
		return TRUE;
	}
	void Print(ostream& stream) const
	{
		stream << "		" << SId << ' ' << CourseName << ' ' << Grade;
	}
};

const char* keys;
const int BTreeSize = 4;//Btree node �뷮�� 4���� �Ѵ�

int main(int argc, char** argv)
{
	//���� ���� �ڵ�
	int count, select, recaddr, results, resultc;
	char removeKey[15], searchKey[15];
	
	Recording record;
	LengthFieldBuffer Buffer(10);
	BTree <char> student_bt(BTreeSize);
	BTree <char> course_bt(BTreeSize);
	RecordFile<Student> StudentDataFile(Buffer);
	RecordFile<CourseRegistration> CourseRegistrationDataFile(Buffer);

	Student* R[6];
	R[0] = new Student("s123", "ȫ�浿", "��ǻ��", 3);
	R[1] = new Student("s124", "ȫ���", "����", 4);
	R[2] = new Student("s125", "ȫ����", "��ǻ��", 4);
	R[3] = new Student("s126", "ȫ���", "����", 3);
	R[4] = new Student("s127", "ȫ���", "��ǻ��", 2);
	R[5] = new Student("s128", "ȫ����", "����", 2);
	CourseRegistration* C[30];
	C[0] = new CourseRegistration("s123", "DB", 3.0);
	C[1] = new CourseRegistration("s123", "OS", 4.0);
	C[2] = new CourseRegistration("s123", "File Structure", 2.5);
	C[3] = new CourseRegistration("s123", "Data Structure", 4.5);
	C[4] = new CourseRegistration("s124", "File Structure", 3.5);
	C[5] = new CourseRegistration("s124", "Data Structure", 4.5);
	C[6] = new CourseRegistration("s124", "CPP", 3.0);
	C[7] = new CourseRegistration("s124", "C Programming",3.5);
	C[8] = new CourseRegistration("s125", "Network", 4.0);
	C[9] = new CourseRegistration("s125", "Web Programming", 3.5);
	C[10] = new CourseRegistration("s125", "AI", 4.0);
	C[11] = new CourseRegistration("s125", "Big Data", 4.5);
	C[12] = new CourseRegistration("s126", "DB", 2.0);
	C[13] = new CourseRegistration("s126", "OS",3.0);
	C[14] = new CourseRegistration("s126", "File Structure", 4.0);
	C[15] = new CourseRegistration("s126", "Data Structure",3.5);
	C[16] = new CourseRegistration("s127", "CPP", 3.5);
	C[17] = new CourseRegistration("s127", "C Programming", 4.5);
	C[18] = new CourseRegistration("s127", "Network", 4.5);
	C[19] = new CourseRegistration("s127", "Web Programming", 4.5);
	C[20] = new CourseRegistration("s128", "AI", 4.0);
	C[21] = new CourseRegistration("s128", "DB",3.5);
	C[22] = new CourseRegistration("s128", "Big Data", 4.0);
	C[23] = new CourseRegistration("s128", "OS", 3.5);

	while (1)
	{
		cout << "\nSelect command 1: insert student record set, 2: insert course registration record set, 3. create a btree file from an student record file," <<
			"4. create a btree file from an course registration record file, 5. print the student that match the input Sid" <<
			"6. print the all course grades that match the input Sid, 7. Quit => ";
		cin >> select;

		switch (select) {
		case 1://1: insert student record set
			StudentDataFile.Create("datafiles.dat", ios::in | ios::out);
			for (int i = 0; i < 5; i++)
			{
				recaddr = StudentDataFile.Append(*R[i]);//data file�� �������� record�� ����
				cout << "Saving ";
				R[i]->Print(cout);
				cout << endl;
			}
			//R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
			//6���� record�� data file�� ����
			StudentDataFile.Close();
			break;
		case 2://2: insert course registration record set
			CourseRegistrationDataFile.Create("datafilec.dat", ios::in | ios::out);
			//R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
			//6���� record�� data file�� ����
			for (int i = 0; i < 23; i++)
			{
				recaddr = CourseRegistrationDataFile.Append(*C[i]);//data file�� �������� record�� ����
				cout << "Saving ";
				C[i]->Print(cout);
				cout << endl;
			}
			CourseRegistrationDataFile.Close();
			break;

		case 3://3. create a btree file from an student record file
			StudentDataFile.Open("datafiles.dat", ios::in | ios::out);
			student_bt.Create("studentbt.dat", ios::in | ios::out);
			for (int i = 0; i < 5; i++)
			{
				recaddr = CourseRegistrationDataFile.Write(*C[i]);
				//assign getKey(*R[i]) to *keys;//keys�� �����Ͽ� *keys�� ����
				keys = R[i]->Key();
				results = student_bt.Insert(keys[i], -1);
				student_bt.Print(cout);
			}
			StudentDataFile.Close();
			student_bt.Close();
			break;

		case 4://4. create a btree file from an course registration record file
			CourseRegistrationDataFile.Open("datafilec.dat", ios::in | ios::out);
			course_bt.Create("coursebt.dat", ios::in | ios::out);
			for (int i = 0; i < 23; i++)
			{
				keys = C[i]->Key();
				results = student_bt.Insert(keys[i], -1);
				student_bt.Print(cout);
			}
			CourseRegistrationDataFile.Close();
			course_bt.Close();

			break;
		case 5://5. print the student that match the input Sid
			StudentDataFile.Open("datafiles.dat", ios::in);
			student_bt.Open("studentbt.dat", ios::in);

			cout << "Input key what search : ";
			cin >> searchKey;
			Student* rec;
			rec = new Student;
			recaddr = student_bt.Search(*searchKey, -1);
			StudentDataFile.Read(*rec, recaddr);
			
			rec->Print(cout);
			cout << endl;
			StudentDataFile.Close();
			student_bt.Close();

			break;
		case 6://6. print the all course grades that match the input Sid
			StudentDataFile.Open("datafiles.dat", ios::in);
			student_bt.Open("studentbt.dat", ios::in);
			CourseRegistrationDataFile.Open("datafilec.dat", ios::in);
			course_bt.Open("coursebt.dat", ios::in);

			cout << "Input key what search : ";
			cin >> searchKey;
			CourseRegistration* recc;
			recc = new CourseRegistration;
			recaddr = course_bt.Search(*searchKey, -1);
			CourseRegistrationDataFile.Read(*recc, recaddr);
			recc->Print(cout);

			StudentDataFile.Close();
			student_bt.Close();
			CourseRegistrationDataFile.Close();
			course_bt.Close();
			break;

		default:
			exit(0);
			break;
		}
	}

	system("pause");
	return 1;
}