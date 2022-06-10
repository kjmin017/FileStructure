//data file에 가변길이 레코드를 저장하고 index로서 btree를 사용한다.
#include <iostream>
#include <string>
#include "btree.h"
#include "recording.h"
#include "length.h"
using namespace std;

const char* keys;

const int BTreeSize = 4;
int main(int argc, char* argv) {
	int result, i;
	LengthFieldBuffer Buffer;
	BTree <char> bt(BTreeSize);
	RecordFile<Recording> dataFile(Buffer);
	result = dataFile.Create("btreedata.dat", ios::out);
	if (result == -1) {
		//
	}
	result = bt.Create("btree.dat", ios::out);
	if (!result) {
		cout << "Please delete testbt.dat" << endl;
		system("pause");
		return 0;

	}
	
	int recaddr;
	//write records
	Recording* R[20], foundRecord;
	RecordFile<Recording> IndFile(Buffer);
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
	R[10] = new Recording("1LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[11] = new Recording("1RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[12] = new Recording("1WAR", "23699", "Touchstone", "Corea", "Corea");
	R[13] = new Recording("1ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[14] = new Recording("1COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[15] = new Recording("1DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[16] = new Recording("1MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[17] = new Recording("1COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[18] = new Recording("1DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[19] = new Recording("1FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	for (int i = 0; i < 10; i++)
	{
		recaddr = IndFile.Append(*R[i]);
		cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
	}
	IndFile.Close();

	IndFile.Open("indfile", ios::in);
	for (int i = 0; i < 10; i++)
	{
		//stable[i] = new Recording;
		result = IndFile.Read(foundRecord);
		cout << endl << "IndFile.Read()::result =  " << result << "--> ";
		foundRecord.Print(cout);
	}

	char* searchKey = "DG139201";
	cout << endl << "Searck key::" << searchKey << endl;
	result = IndFile.Read(searchKey, foundRecord);
	cout << endl << "IndFile.Read(searchKey, foundRecord)::result =  " << result << "--> ";
	foundRecord.Print(cout);
	cout << endl;
	IndFile.Close();
	
	for (i = 0; i < 20; i++)
	{
		recaddr = dataFile.Append(*R[i]);//data file에 가변길이 record를 저장
		//assign getKey(*R[i]) to *keys;//keys를 추출하여 *keys에 저장
		result = bt.Insert(keys[i], recaddr);
		bt.Print(cout);
	}
	recaddr = bt.Search(*searchKey, -1);
	dataFile.Read(recaddr);//data file을 read하여 해당 레코드를 출력한다.
	bt.InorderTraversal(); //구현하여 data file의 record를 sorted 결과로 출력
	bt.Remove('L');//구현 - redistribute와 merge를 구현한다.
	bt.InorderTraversal(); //구현하여 data file의 record를 sorted 결과로 출력
	system("pause");
	return 1;
}