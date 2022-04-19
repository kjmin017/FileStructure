//testind.cc - TextindexedFile 사용 실습
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recordng.h"
#include "indfile.h"
#include <iostream>

int main (void)
{// first argument is the file name for the data file
	int result;

	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Recording> IndFile (Buffer, 12, 10);
	//TextIndexedFile<RecType>::TextIndexedFile(IOBuffer & buffer, int keySize, int maxKeys)
	result = IndFile . Create ("indfile", ios::out);
	if (!result) 
	{
		cout<<"Unable to open indfile "<<result<<endl;
		return 0;
	}	
	int recaddr;
	//write records
	Recording* R[10], foundRecord;

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
		recaddr = IndFile.Append(*R[i]);
		cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
	}

	char* searchKey = "201824448";
	IndFile.Read(searchKey, foundRecord);
	foundRecord.Print(cout);
	IndFile.Close();
	system("pause");
	return 1;
}

