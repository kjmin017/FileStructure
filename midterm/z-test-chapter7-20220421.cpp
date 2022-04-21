/*
supply.h에 다음 테이블을 class 로정의한다
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key는 (sno,pno, jno)로 구성됨
*/
#include "textind.h"
#include "delim.h"
#include "fixfld.h"
#include "buffile.h"
#include "indfile.h"
#include <iostream>
#include "length.h"
//*
//Using class Index, the index object should be stored into the RecordFile
class Supply {
private:
	char sno[3], pno[3], jno[3];
	char city[10];
	char qty[3];
public:
	Supply();
	Supply(Supply&);
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
	void Clear();
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	char* Key() const; // key는 sno+pno+jno -> 예시: s1p1j1으로 구성
	void Print(ostream&, char* label = 0) const;
	friend std::istream& operator >> (std::istream& stream, Supply& p);
	friend std::ostream& operator << (std::ostream& stream, Supply& p);
};
char* Supply::Key() const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << sno << pno << jno << ends;
	return key.str();
}
istream& operator >> (istream& stream, Supply& spj)
{ // read fields from input
	stream >> spj.sno >> spj.pno >> spj.jno >> spj.city >> spj.qty;
	return stream;
}
ostream& operator << (ostream& stream, Supply& spj)
{
	//함수 구현
	stream << spj.sno << '|' << spj.pno << '|' << spj.jno << '|'
		<< spj.city << '|' << spj.qty;
	return stream;
}
//*/
int main(void)
{
	char key[20];
	char filename[20];
	int count = 0, select, result, n, recaddr;
	Supply spj, foundSPJ;
	Supply* R[10];


	DelimFieldBuffer Buff;

	TextIndexedFile<Supply> IndFile(Buff, 12, 10);
	cout << "Testing TextIndex Buffer" << endl;

	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);

	while (1)
	{
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5. use index file for reading data file, 6. print the records of Supply in key order, 7.Quit => ";
		cin >> select;
		count = 10;
		switch (select) {
		case 1://
		{
			for (int i = 0; i < count; i++)
			{
			//R[10] 레코드를 초기화 - 기존 실습 코드를 참조하여 작성
				R[i] = new Supply();
				cin >> *R[i];
			}
			break;
		}
		case 2://입력된 레코드를 화면에 출력
		{
			// to display the array of objects into screen  
			for (int i = 0; i < count; i++)
			{
				//cout << record를 사용
				cout << *R[i] << endl;
			}
			break;
		}
		case 3: //file 생성 : data file, index file의 생성 - 단한번만 실행
		{
			// to write the array of objects into a file
			int recaddr;
			for (int i = 0; i < count; i++)
			{
				//10개의 레코드를 file에 append
				recaddr = IndFile.Append(*R[i]);
				cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
			}	
			break;
		}
		case 4://data file을 순차적 read한다.
		{
			int result = IndFile.Open(filename, ios::in);


			for (int i = 0; i < count; i++)
			{
				//순차적으로 읽은 record를 출력한다.
				R[i] = new Supply;
				IndFile.Read(*R[i]);
			}
			IndFile.Close();
			break;
		}

		case 5:
		{
			// read RecordFile by using index file.

			int result = IndFile.Open(filename, ios::in);

			char* searchKey = "";//임의 지정
			cout << endl << "Searck key::" << searchKey << endl;
			//key를 사용한 record 검색후 레코드 출력한다.
			Supply foundRecord;
			IndFile.Read(searchKey, foundRecord);
			foundRecord.Print(cout);
			
			IndFile.Close();
			break;
		}
		case 6://print the records of Supply in key order
		{
			// read RecordFile by using index file.
			int result = IndFile.Open(filename, ios::in);
			/*
			교재 285, 13번 programming and design exercises
			add two methods to class textIndex:
			   1) int FirstRecAddr(); //index table에서 smallest key에 대한  reference address를 return
			   2) int NextRecAddr(); //index table에서 next key에 대한 reference address를 return
			 2개의 함수를 사용하여 키 값 순서로 Supply 레코드들을 출력 
			*/



			IndFile.Close();
			break;
		}
		default:
			// others
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
}
