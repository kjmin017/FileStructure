// tsthash.cpp
/*
Page 563: Programming project
1. create a hashed index of the student record file
2. The student record file is the entry-sequenced file
3. For insertion of new appended records, insert key on hashed index
4. Using hashed index, search the corresponding record with the key
*/
#include "direct.h"
#include "bucket.h"
#include "hash.h"
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
#include <iostream>
using namespace std;
/*
template��  **.h�� **.cpp�� �и����� �ʰ� **.h�� ���ľ� link error�� �ذ�
buffile.cpp�� open(0, create()�� mode ���� ����
coding exam: data file�� entry-sequenced file�μ� append, Key(record)�� ���Ͽ�b-tree�� insert�ϴ� ���α׷� ����
	Student student;
	FixedFieldBuffer Buff(6);
	Student::InitBuffer(Buff);
	Recorde<Student> rFile(Buffer, 12, 10);
	int result = rFile.Create(filename, ios::out);
	cout << "Create file " << result << endl;
	if (!result)
	{
		cout << "Unable to Create file " << filename << endl;
		return -1;
	}
	rFile.Append(*stable[i]);
	rFile.Close();

*/

int main(int argc, char ** argv)
{
	int count, select, resultFile, resultIndex;
	char removeKey[15], searchKey[15];
	Directory Dir(4);
	resultIndex = Dir.Create("tsthash");
	Recording record;
	FixedFieldBuffer Buffer(10);
	Buffer.InitFields(); // Add each field size of record to buffer (can change if you need)
	RecordFile<Recording> DataFile(Buffer);

	resultFile = DataFile.Create("datafile.dat", ios::in | ios::out);
	cout << "Create file " << resultFile << endl;
	if (!resultFile)
	{
		cout << "Unable to Create file : datafile.dat" << endl;
		return 0;
	}

	Recording * R[10];
	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("BOL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("EG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	int recaddr;
	while (1)
	{
		cout << "\nSelect command 1: insert record set, 2. delete a record, 3. print the record set, 4. search the record with key, 5. Quit => ";
		cin >> select;

		switch (select) {
		case 1://input data record set
			cout << "1. insert the record set" << endl;
			for (int i = 0; i < 10; i++)
			{
				R[i]->Print(cout);
				R[i]->Pack(Buffer);
				recaddr = DataFile.Write(*R[i]);
				cout << "DataFile R[" << i << "] at recaddr " << recaddr << endl;
				char *keys = R[i]->Key();
				cout << "Inserting with key = " << k << endl;
				//1 block = 4 records
				delete R[i];
				cout << (void *)Hash(keys);//(void*) casting�� bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				resultIndex = Dir.Insert(keys, recaddr);
				if (resultIndex == 0) cout << "Insert for " << keys[i] << " failed" << endl;
				Dir.Print(cout);
			}
			Dir.Close();
			DataFile.Close();
			break;
		case 2://2. delete a record
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);
			if (!resultFile)
			{
				cout << "Unable to open data file" << endl;
				return 0;
			}
			resultIndex = Dir.Open("tsthash");
			if (resultIndex == 0)
			{
				cout << "Please create tsthash.dir and tsthash.bkt" << endl;
				return 0;
			}
			cout << "Input key what remove : ";
			cin >> removeKey;

			cout << endl << endl << removeKey << "  " << (void*)MakeAddress(removeKey, 16) << endl << endl;
			recaddr = Dir.Search(removeKey);
			DataFile.Read(*rec, recaddr);
			//update *rec
			DataFile.Write(*rec, recaddr);//update mark on key field
			resultIndex = Dir.Remove(removeKey);
			if (resultIndex == 0) cout << "Remove for " << removeKey << " failed" << endl;
			Dir.Print(cout);
			DataFile.Close();
			Dir.Close();
			break;
		case 3://3. print the record set
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);
			if (!resultFile)
			{
				cout << "Unable to open data file" << endl;
				return 0;
			}
			Recording *rec;
			for (int i = 0; i < 10; i++)
			{
				rec = new Recording;
				DataFile.Read(*rec, recaddr);
				rec->Print(cout);
			}
			DataFile.Close();
		case 4://4. print the record with key
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);
			if (!resultFile)
			{
				cout << "Unable to open data file" << endl;
				return 0;
			}
			resultIndex = Dir.Open("tsthash");
			if (resultIndex == 0)
			{
				cout << "Please create tsthash.dir and tsthash.bkt" << endl;
				return 0;
			}
			cout << "Input key what search : ";
			cin >> searchKey;

			recaddr = Dir.Search(searchKey);
			if (recaddr == -1)
				cout << endl << "Search for " << searchKey << " failed" << endl;
			else
			{
				cout << endl << endl << searchKey << "  " << (void*)MakeAddress(searchKey, 16) << endl;
				cout << "RecAddr : " << recaddr << endl;
			}

			DataFile.Read(*rec, recaddr);
			cout << rec;
			DataFile.Close();
			Dir.Close();
		default:
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
}