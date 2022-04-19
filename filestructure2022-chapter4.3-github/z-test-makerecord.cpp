//makerec.cc
#include "buffile.h"
#include "recording.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"

//file�� write �� �Ŀ� read�Ͽ� ����ϴ� ���α׷� �ۼ� �ǽ� 
// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class BufferFile
//    the file "record2.dat" is created using class RecordFile<Recording>
using namespace std;
int main(void)
{
	int recaddr;
	int result;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buffer;
	Recording::InitBuffer(Buffer);
	BufferFile IndexedFile(Buffer);

	char* myfile = "record.ind";
	result = IndexedFile.Create(myfile, ios::out);
	cout << "main()::create file " << result << endl;
	if (!result)
	{
		cout << "main()::Unable to create file " << myfile << endl;
		result = IndexedFile.Open(myfile, ios::out);
		cout << "main()::open file " << result << endl;
		if (!result)
		{
			cout << "main()::Unable to open file " << myfile << endl;
			system("pause");

			return 0;
		}
	}
	RecordFile<Recording> RecordedFile(Buffer);
	RecordedFile.Create("recording.dat", ios::out);

	Recording* R[10]; //=> 1�忡�� ���� Student record�� �����Ѵ�.
	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	for (int i = 0; i < 10; i++)
	{
		//TextIndex�� ������ index.Insert()
		recaddr = RecordedFile.Write(*R[i]);
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}
	//IndexedFile, RecordFile�� write�� ���ڵ带 �д� �ڵ带 �߰��Ѵ�
	//IndexedFile�� ������ index�� ����
	IndexedFile.Close();
	RecordedFile.Close();

	IndexedFile.Open(); //�ٽ� open
	RecordedFile.Open();//�ٽ� open
	//char *keyname = "DG18807"; ȭ�鿡�� �Է¹޾Ƽ� �ݺ� �����ϰ� ó��
	//�Էµ� key�� ���� index�� search�� �Ŀ� �ش� ���ڵ带 ����ϴ� ���α׷� - makeind-2.cpp�� �����Ͽ�
	// �� ���α׷��� �����Ͽ� �ϼ�
	system("pause");
	return 1;
}


