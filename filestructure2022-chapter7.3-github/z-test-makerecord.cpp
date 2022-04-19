//makerec.cc
#include "buffile.h"
#include "student.h"
#include "recordng.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include "textind.h"
#include "tindbuff.h"


//file�� write �� �Ŀ� read�Ͽ� ����ϴ� ���α׷� �ۼ� �ǽ� 
// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class BufferFile
//    the file "record2.dat" is created using class RecordFile<Recording>
using namespace std;

int RetrieveRecording(Recording& recording, char* key,
	TextIndex& RecordingIndex, BufferFile& RecordingFile)
	// read and unpack the recording, return TRUE if succeeds
{
	int result;
	cout << "Retrieve " << key << " at recaddr " << RecordingIndex.Search(key) << endl;
	result = RecordingFile.Read(RecordingIndex.Search(key));
	cout << "read result: " << result << endl;
	if (result == -1) return FALSE;
	result = recording.Unpack(RecordingFile.GetBuffer());
	return result;
}

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
	R[0] = new Recording("201824448", "Kjm", "31091", "0311", "16");
	R[1] = new Recording("201820000", "asd", "12352", "0311", "16");
	R[2] = new Recording("201820001", "sdf", "11257", "0311", "16");
	R[3] = new Recording("201820002", "xcv", "34684", "0311", "16");
	R[4] = new Recording("201820003", "bvx", "89434", "0311", "16");
	R[5] = new Recording("201820004", "weh", "35467", "0311", "16");
	R[6] = new Recording("201820005", "sdf", "76977", "0311", "16");
	R[7] = new Recording("201820006", "qad", "37980", "0311", "16");
	R[8] = new Recording("201820007", "ads", "56027", "0311", "16");
	R[9] = new Recording("201820008", "hjk", "34056", "0311", "16");
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

	IndexedFile.Open(myfile, ios::out); //�ٽ� open
	RecordedFile.Open("recording.dat", ios::out);//�ٽ� open

	TextIndex RecordingIndex(10);
	Recording rec;
	int recaddr, result;
	DelimFieldBuffer Buffer; // create a buffer
	BufferFile IndexingFile(Buffer);
	result = IndexingFile.Create(myfile, ios::out);
	if (!result)
	{
		cout << "Unable to open file " << myfile << endl;
		return 0;
	}
	RecordFile<Recording> DataFile(Buffer);
	DataFile.Open("recording.dat", ios::in);
	while (1) 
	{
		recaddr = DataFile.Read(rec); 
		if (recaddr < 0) break;
		rec.Unpack(Buffer);
		RecordingIndex.Insert(rec.Key(), recaddr);
		cout << recaddr << '\t' << rec << endl;
	}
	RecordingIndex.Print(cout);
	result = RetrieveRecording(rec, "201824448", RecordingIndex, IndexingFile);
	cout << "Found record: " << rec;

	//char *keyname = "DG18807"; ȭ�鿡�� �Է¹޾Ƽ� �ݺ� �����ϰ� ó��
	//�Էµ� key�� ���� index�� search�� �Ŀ� �ش� ���ڵ带 ����ϴ� ���α׷� - makeind-2.cpp�� �����Ͽ�
	// �� ���α׷��� �����Ͽ� �ϼ�
	system("pause");
	return 1;
}


