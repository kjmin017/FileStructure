/*
supply.h�� ���� ���̺��� class �������Ѵ�
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key�� (sno,pno, jno)�� ������
*/
#include "textind.h"
#include "delim.h"
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
	char* Key() const; // key�� sno+pno+jno -> ����: s1p1j1���� ����
	void Print(ostream&, char* label = 0) const;
	friend std::istream& operator >> (std::istream& stream, Supply& p);
	friend std::ostream& operator << (std::ostream& stream, Supply& p);
};
istream& operator >> (istream& stream, Supply& spj)
{ // read fields from input

	return stream;
}
ostream& operator << (ostream& stream, Supply& spj)
{
	//�Լ� ����
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
			//R[10] ���ڵ带 �ʱ�ȭ - ���� �ǽ� �ڵ带 �����Ͽ� �ۼ�
			}
			break;
		}
		case 2://�Էµ� ���ڵ带 ȭ�鿡 ���
		{
			// to display the array of objects into screen  
			for (int i = 0; i < count; i++)
			{
				//cout << record�� ���
			}
			break;
		}
		case 3: //file ���� : data file, index file�� ���� - ���ѹ��� ����
		{
			// to write the array of objects into a file

			for (int i = 0; i < count; i++)
			{
				//10���� ���ڵ带 file�� append
			}	
			break;
		}
		case 4://data file�� ������ read�Ѵ�.
		{
			int result = IndFile.Open(filename, ios::in);


			for (int i = 0; i < count; i++)
			{
				//���������� ���� record�� ����Ѵ�.
			}
			IndFile.Close();
			break;
		}

		case 5:
		{
			// read RecordFile by using index file.

			int result = IndFile.Open(filename, ios::in);

			char* searchKey = "";//���� ����
			cout << endl << "Searck key::" << searchKey << endl;
			//key�� ����� record �˻��� ���ڵ� ����Ѵ�.
			IndFile.Close();
			break;
		}
		case 6://print the records of Supply in key order
		{
			// read RecordFile by using index file.
			int result = IndFile.Open(filename, ios::in);
			/*
			���� 285, 13�� programming and design exercises
			add two methods to class textIndex:
			   1) int FirstRecAddr(); //index table���� smallest key�� ����  reference address�� return
			   2) int NextRecAddr(); //index table���� next key�� ���� reference address�� return
			 2���� �Լ��� ����Ͽ� Ű �� ������ Supply ���ڵ���� ��� 
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
