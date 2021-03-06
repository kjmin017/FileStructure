//testind.cc
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recordng.h"
#include "indfile.h"
#include <iostream>

// make an indexed file from a recording file
int ReadIndexRecordingFile (char * myfile, 
	TextIndexedFile<Recording> & indexFile)
{
	Recording fileRec; 
	Recording indRec;
	int recaddr, result;
	DelimFieldBuffer Buffer; // create a buffer
	BufferFile RecFile(Buffer); 
	result = RecFile . Open (myfile,ios::in);
	if (!result)
	{
		cout << "Unable to open file "<<myfile<<endl;
		return 0;
	}
	while (1) // loop until the read fails
	{
		recaddr = RecFile . Read (); // read next record
		if (recaddr < 0) break;
		fileRec. Unpack (Buffer);
		cout <<"\nLooking for record with key:"
			<<fileRec.Key()<<endl;
		result=indexFile . Read(fileRec.Key(),indRec);
		if (result<0) cout <<"record not found";//need to make code for making index file
		else indRec.Print(cout);
	}
}


int main (void)
{// first argument is the file name for the data file
	int result;
	char* fname = "recindex.dat";//indexed file
	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Recording> IndFile (Buffer, 12, 10);
	result = IndFile . Open ("indfile");
	if (!result) 
	{
		cout<<"Unable to open indfile "<<result<<endl;
		return 0;
	}	
	ReadIndexRecordingFile (fname, IndFile);
	IndFile.Close();
	system("pause");
	return 1;
}

