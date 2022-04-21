// recordng.h

#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include "iobuffer.h"

#include "fixfld.h"
#include "length.h"
#include "delim.h"
using namespace std;
// class person with fixed field buffer
/*
supply.h에 다음 테이블을 class 로정의한다
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key는 (sno,pno, jno)로 구성됨
*/
class Recording
// a recording with a composite key
{public:
	Recording ();
	Recording (char * sno, char * pno, char * jno, 
		char * city, char * qty);
	char sno[3]; char pno[3]; char jno[3];
	char city[10]; char qty[3];
	char * Key () const; // return key of object
	int Unpack (IOBuffer &);
	int Pack (IOBuffer &) const;
	void Print (ostream &, char * label = 0) const;
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
};

ostream & operator << (ostream &, Recording &);
inline ostream & operator << (ostream & stream, Recording & rec)
{	rec.Print(stream); return stream;}

#endif
