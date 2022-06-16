/* 12장 extendible hashing 프로그래밍 과제 
1. page 563: Programming Project: 20,21,22
2. an existing student record file: RecordFile<Student> StudnetDataFile(Buffer);
  - data file을 먼저 만들고 file을 close한다. 다음에 data file을 읽어서 hashed index를 만든다.
  - 	resultIndex = Dir.Create("studenthash");
  최소 6개 이상 레코드 입력
3. an existing course registration record file: RecordFile<CourseRegistration> CourseRegistrationDataFile(Buffer);
  - 	resultIndex = Dir.Create("coursehash");
  - data file을 먼저 만들고 file을 close한다. 다음에 data file을 읽어서 hashed index를 만든다.
  - 각 Sid에 대하여 매칭되는 수강 과목이 4개 이상되도록 입력
4. 22번 문제는 SId를 입력받아 다음과 같이 출력한다.(입력받은 SId와 교과목 리스트에 대하여 찾기를 반복한다)
    s123 홍길동  컴퓨터 3
	      DB  3.0
		  OS  4.0
	s124 홍길순  전자   4
	      File Structure 3.5
		  Data Structure 4.5
5. course list는 DB, OS, File Structure, Data Structure, CPP, C Programming, Network, Web Programming, AI, Big Data
6. 수강 취소는 CourseRegistration index에서 remove key를 입력받아 사용하고 data file에서 삭제 마크 '0000'로 처리하고 
    Read()에서 삭제 마크로 표시된 레코드는 출력하지 않는다.
*/
#include "direct.h"
#include "bucket.h"
#include "hash.h"
#include <conio.h>
#include "recording.h"
#include "courseregistration.h"
#include <fstream>
#include <iomanip>
#include <string>
#include "iobuffer.h"
#include "student.h"
#include "fixfld.h"
#include "length.h"
#include "buffile.h"
#include "recfile.h"
#include "indbuff.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	/* 참고용이니 삭제할 것
	
	
	char removeKey[15], searchKey[15];
	Directory Dir(4);
	resultIndex = Dir.Create("tsthash");
	Recording record, * rec;
	FixedFieldBuffer Buffer(10);
	Buffer.InitFields(); // Add each field size of record to buffer (can change if you need)
	RecordFile<Recording> DataFile(Buffer);
	Recording* R[10];
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
	*/
	
	//
	int count, select, resultFiles, resultFilec, resultIndexs, resultIndexc;
	char removeKey[15], searchKey[15];
	Directory Dirs(4);
	Directory Dirc(4);
	resultIndexs = Dirs.Create("studenthash");
	resultIndexc = Dirc.Create("coursehash");
	Recording record;
	FixedFieldBuffer Buffer(10);
	Buffer.InitFields(); 
	RecordFile<Student> StudentDataFile(Buffer);
	RecordFile<CourseRegistration> CourseRegistrationDataFile(Buffer);


	resultFiles = StudentDataFile.Create("datafiles.dat", ios::in | ios::out);
	cout << "Create file " << resultFiles << endl;
	if (!resultFiles)
	{
		cout << "Unable to Create file : datafiles.dat" << endl;
		return 0;
	}
	resultFilec = CourseRegistrationDataFile.Create("datafilec.dat", ios::in | ios::out);
	cout << "Create file " << resultFilec << endl;
	if (!resultFilec)
	{
		cout << "Unable to Create file : datafilec.dat" << endl;
		return 0;
	}
	Student* R[10];
	R[0] = new Student("s123", "홍길동", "컴퓨터", "3");
	R[1] = new Student("s124", "홍길순", "전자", "4");
	R[2] = new Student("s125", "홍길자", "컴퓨터", "4");
	R[3] = new Student("s126", "홍길두", "전자", "3");
	R[4] = new Student("s127", "홍길례", "컴퓨터", "2");
	R[5] = new Student("s128", "홍길정", "전자", "2");
	CourseRegistration* C[30];
	C[0] = new CourseRegistration("s123", "DB",  "3.0");
	C[1] = new CourseRegistration("s123", "OS", "4.0");
	C[2] = new CourseRegistration("s123", "File Structure", "2.5");
	C[3] = new CourseRegistration("s123", "Data Structure", "4.5");
	C[4] = new CourseRegistration("s124", "File Structure", "3.5");
	C[5] = new CourseRegistration("s124", "Data Structure", "4.5");
	C[6] = new CourseRegistration("s124", "CPP", "3.0");
	C[7] = new CourseRegistration("s124", "C Programming", "3.5");
	C[8] = new CourseRegistration("s125", "Network", "4.0");
	C[9] = new CourseRegistration("s125", "Web Programming", "3.5");
	C[10] = new CourseRegistration("s125", "AI", "4.0");
	C[11] = new CourseRegistration("s125", "Big Data", "4.5");
	C[12] = new CourseRegistration("s126", "DB", "2.0");
	C[13] = new CourseRegistration("s126", "OS", "3.0");
	C[14] = new CourseRegistration("s126", "File Structure", "4.0");
	C[15] = new CourseRegistration("s126", "Data Structure", "3.5");
	C[16] = new CourseRegistration("s127", "CPP", "3.5");
	C[17] = new CourseRegistration("s127", "C Programming", "4.5");
	C[18] = new CourseRegistration("s127", "Network", "4.5");
	C[19] = new CourseRegistration("s127", "Web Programming", "4.5");
	C[20] = new CourseRegistration("s128", "AI", "4.0");
	C[21] = new CourseRegistration("s128", "DB", "3.5");
	C[22] = new CourseRegistration("s128", "Big Data", "4.0");
	C[23] = new CourseRegistration("s128", "OS", "3.5");
	int recaddr;

	while (1)
	{
		cout << "\nSelect command 1: insert student record set, 2: insert course registration record set, 3. create a hash file from an student record file,"<<
			"4. create a hash file from an course registration record file, 5. print all course grades that match the input Sid, 6. delete a course registration record with input SId and course name, "
			<<"7. print the course registration record set, 8. Quit => ";
		cin >> select;

		switch (select) {
		case 1://input data record set
			cout << "1. insert the student record set" << endl;
			for (int i = 0; i < 6; i++)
			{
				R[i]->Print(cout);
				R[i]->Pack(Buffer);
				recaddr = StudentDataFile.Write(*R[i]);
				cout << "DataFile R[" << i << "] at recaddr " << recaddr << endl;
				char* keys = R[i]->Key();
				cout << "Inserting with key = " << keys << endl;
				//1 block = 4 records
				//delete R[i];
				cout << (void*)Hash(keys);//(void*) casting은 bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				resultIndexs = Dirs.Insert(keys, recaddr);
				if (resultIndexs == 0) cout << "Insert for " << keys[i] << " failed" << endl;
				Dirs.Print(cout);
			}
			Dirs.Close();
			StudentDataFile.Close();
			break;
		case 2:
			
			cout << "1. insert the courseregistration record set" << endl;
			for (int i = 0; i < 6; i++)
			{
				C[i]->Print(cout);
				C[i]->Pack(Buffer);
				recaddr = CourseRegistrationDataFile.Write(*C[i]);
				cout << "DataFile C[" << i << "] at recaddr " << recaddr << endl;
				char* keys = C[i]->Key();
				cout << "Inserting with key = " << keys << endl;
				//1 block = 4 records
				//delete C[i];
				cout << (void*)Hash(keys);//(void*) casting은 bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				resultIndexc = Dirc.Insert(keys, recaddr);
				if (resultIndexc == 0) cout << "Insert for " << keys[i] << " failed" << endl;
				Dirc.Print(cout);
			}
			CourseRegistrationDataFile.Close();
			Dirs.Close();
			break;

		case 3:
			
			StudentDataFile.Close();
			cout << endl;
			break;

		case 4:
			
			StudentDataFile.Close();
			Dirs.Close();
			break;
		case 5:
			resultFilec = CourseRegistrationDataFile.Open("datafilec.dat", ios::in | ios::out);
			if (!resultFilec)
			{
				cout << "Unable to open data file" << endl;
				return 0;
			}
			resultIndexc = Dirc.Open("coursehash");
			if (resultIndexs == 0)
			{
				cout << "Please create coursehash.dir and coursehash.bkt" << endl;
				return 0;
			}
			cout << "Input key what search : ";
			cin >> searchKey;

			recaddr = Dirc.Search(searchKey);
			if (recaddr == -1)
				cout << endl << "Search for " << searchKey << " failed" << endl;
			else
			{
				cout << endl << endl << searchKey << "  " << (void*)MakeAddress(searchKey, 16) << endl;
				cout << "RecAddr : " << recaddr << endl;
			}
			CourseRegistration* rec;
			rec = new CourseRegistration;
			CourseRegistrationDataFile.Read(*rec, recaddr);

			cout << rec->Grade;

			CourseRegistrationDataFile.Close();
			Dirc.Close();
			break;
		case 6:
			resultFilec = CourseRegistrationDataFile.Open("datafilec.dat", ios::in | ios::out);
			if (!resultFilec)
			{
				cout << "Unable to open data file" << endl;
				return 0;
			}
			resultIndexc = Dirc.Open("coursehash");
			if (resultIndexc == 0)
			{
				cout << "Please create coursehash.dir and coursehash.bkt" << endl;
				return 0;
			}
			cout << "Input key what remove : ";
			cin >> removeKey;
			for (int i = 0; i < 4; ++i) {
				cout << endl << endl << removeKey << "  " << (void*)MakeAddress(removeKey, 16) << endl << endl;
				recaddr = Dirc.Search(removeKey);
				CourseRegistrationDataFile.Read(*rec, recaddr);
				//update *rec
				CourseRegistrationDataFile.Write(*rec, recaddr);//update mark on key field
				resultIndexc = Dirc.Remove(removeKey);
				if (resultIndexc == 0) cout << "Remove for " << removeKey << " failed" << endl;
				Dirc.Print(cout);
			}
			CourseRegistrationDataFile.Close();
			Dirc.Close();
			break;
		case 7:

			CourseRegistrationDataFile.Close();
			Dirc.Close();
			break;
		default:
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
}