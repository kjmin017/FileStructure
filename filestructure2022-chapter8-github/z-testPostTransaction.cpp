/*
교재: 367, 20번 programming project
Ledger 대신에 Student, Journal 대신에 course registration class를 정의한다.
*/

#include "recfile.h"
#include "stdlib.h"
#include <fstream>
#include <string.h>
#include "length.h"
class TranscriptProcess : public MasterTransactionProcess<int>
	// Transcript processing of a Transcript file and a journal file
	// the item type is int to represent an account number
{
public:
	TranscriptProcess(int monthNumber); // constructor

	// Basic list processing methods
	int InitializeList(int ListNumber, char* List1Name);
	int InitializeOutput(char* OutputListName);
	int NextItemInList(int ListNumber); //get next item from this list
	int Item(int ListNumber); // return current item from this list
	int ProcessItem(int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing

	// master/transaction methods
	virtual int ProcessNewMaster();//  when new master read
	virtual int ProcessCurrentMaster();// each transaction for a master
	virtual int ProcessEndMaster();// after all transactions for a master
	virtual int ProcessTransactionError();// no master for transaction

protected:
	// members
	int MonthNumber; // number of month to be processed
	LengthFieldBuffer Lbuffer, Jbuffer; // buffers for files
	RecordFile<Transcript> TranscriptFile; // list 1
	RecordFile<Journal> JournalFile;// list 2
	int AccountNumber[3]; // current item in each list
	Transcript Transcript; // current Transcript object
	Journal journal; // current journal object
	ofstream OutputList; // text output file for post method
	static int LowAcct;// lower than the lowest account number
	static int HighAcct;// higher than the highest account number

	int NextItemInTranscript();
	int NextItemInJournal();
};
int main(void)
{
	Student L1(101, "Checking Account #1", 1032.57, 1032.57, 1032.57);
	...


	CourseRegistration J1(101, 1271, "02/02/86", "Auto expense", -78.70);
	...
	LengthFieldBuffer Lbuffer;
	RecordFile<Transcript> TranscriptFile(Lbuffer);
	int result = TranscriptFile.Create("Transcript.dat", ios::out);
	cout << "Create file " << result << endl;
	if (!result)
	{
		cout << "Unable to Create file " << "Transcript.dat" << endl;
		return 0;
	}
	TranscriptFile.Write(L1);
	...
	TranscriptFile.Close();

	LengthFieldBuffer Jbuffer;
	RecordFile<Journal> journalFile(Jbuffer);
	int flag = journalFile.Create("journal.dat", ios::out);
	cout << "Create file " << flag << endl;
	if (!flag)
	{
		cout << "Unable to Create file " << "journal.dat" << endl;
		return 0;
	}
	journalFile.Write(J1);
    ....
	journalFile.Close();

	int res;
	RecordFile<Transcript> lFile(Lbuffer);
	lFile.Open("Transcript.dat", ios::in);
	Transcript Transcript;
	while (1)
	{
		res = lFile.Read(Transcript);
		if (res <= 0) break;
		cout << "Transcript" << endl;
		Transcript.Print(cout);
	}
	RecordFile<Journal> jFile(Jbuffer);
	jFile.Open("journal.dat", ios::in);
	Journal journal;
	while (1)
	{
		res = jFile.Read(journal);
		if (res <= 0) break;
		journal.PrintLine(cout);
	}
	cout << "Posting " << endl;
	TranscriptProcess Posting(Month);
	/*
	Modify method TranscriptProcess::ProcessEndMaster so it updates the Transcript file 
	with the new account balances for month
	*/

	Posting.PostTransactions("Student.dat", "CourseRegistration.dat", "Transcript.txt");
	//Modify to show the file Transcript.txt
	char ch;
	fstream TranscriptJournal;
	TranscriptJournal.open("Transcript.txt", ios::in);
	while (1) {
		TranscriptJournal >> ch;
		if (TranscriptJournal.fail()) break;
		cout << ch;
	}
	//Modify to show Transcript.Print();
	cout << "Showing the new account balances for the month" << endl;
	lFile.Open("Transcript.dat", ios::in);
	//*
	while (1)
	{
		res = lFile.Read(Transcript);
		if (res <= 0) break;
		cout << "Transcript" << endl;
		Transcript.Print(cout);
	}
	
	system("pause");
	return 1;
}