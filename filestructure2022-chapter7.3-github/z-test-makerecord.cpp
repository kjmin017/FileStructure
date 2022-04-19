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


//file에 write 한 후에 read하여 출력하는 프로그램 작성 실습 
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

	Recording* R[10]; //=> 1장에서 만든 Student record로 변경한다.
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
		//TextIndex에 없으면 index.Insert()
		recaddr = RecordedFile.Write(*R[i]);
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		delete R[i];
	}
	//IndexedFile, RecordFile에 write한 레코드를 읽는 코드를 추가한다
	//IndexedFile에 생성된 index를 저장
	IndexedFile.Close();
	RecordedFile.Close();

	IndexedFile.Open(myfile, ios::out); //다시 open
	RecordedFile.Open("recording.dat", ios::out);//다시 open

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

	//char *keyname = "DG18807"; 화면에서 입력받아서 반복 실행하게 처리
	//입력된 key에 대한 index를 search한 후에 해당 레코드를 출력하는 프로그램 - makeind-2.cpp를 참조하여
	// 본 프로그램을 수정하여 완성
	system("pause");
	return 1;
}


