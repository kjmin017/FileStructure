//Recording.cpp
#include "recordng.h"
#include <strstream>
#include <string.h>
/*
supply.h에 다음 테이블을 class 로정의한다
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key는 (sno,pno, jno)로 구성됨
*/
Recording::Recording ()
{
	sno[0] = 0; pno[0] = 0; jno[0] = 0;
	city[0] = 0; qty[0] = 0;
}

Recording::Recording (char * label, char * idNum, char * title, 
		char * composer, char * artist)
{
	strcpy(sno, label); strcpy(pno, idNum);
	strcpy(jno, title); strcpy(city, composer);
	strcpy(qty, artist);
}

char * Recording::Key () const
{// produce key as concatenation of Label and IdNum
	ostrstream key;
	key << sno << pno << jno << ends;
	return key.str();	
}

int Recording::Pack (IOBuffer & Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer . Clear ();
	numBytes = Buffer . Pack (sno);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (pno);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (jno);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (city);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (qty);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Recording::Unpack (IOBuffer & Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer . Unpack (sno, 9);
	if (numBytes == -1) return FALSE;
	sno[numBytes] = 0;
	numBytes = Buffer . Unpack (pno, 11);
	if (numBytes == -1) return FALSE;
	pno[numBytes] = 0;
	numBytes = Buffer . Unpack (jno, 16);
	if (numBytes == -1) return FALSE;
	jno[numBytes] = 0;
	numBytes = Buffer . Unpack (city, 10);
	if (numBytes == -1) return FALSE;
	city[numBytes] = 0;
	numBytes = Buffer . Unpack (qty, 2);
	if (numBytes == -1) return FALSE;
	qty[numBytes] = 0;
	return TRUE;
}

void Recording::Print (ostream & stream, char * label) const
{
	stream << sno <<'|'<<pno <<'|' << jno <<'|'
		<< city <<'|'<< qty ;
}
int Recording::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedFieldBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(3); // IdNum[7]
	result = result && Buffer.AddField(3); // Title[30]
	result = result && Buffer.AddField(3); // Composer[30]
	result = result && Buffer.AddField(10); // Artist[30]
	result = result && Buffer.AddField(3); // Label[7]
	return result;
}
//char IdNum[7]; char Title[30]; char Composer[30];char Artist[30]; char Label[7];
int Recording::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimFieldBuffer to be used for Persons
{
	return TRUE;
}

int Recording::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthFieldBuffer to be used for Persons
{
	return TRUE;
}
