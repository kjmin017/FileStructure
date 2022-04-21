#pragma once
#ifndef SUPPLY
#define SUPPLY

#include <iostream>
#include "fixfld.h"
#include "length.h"
#include "iobuffer.h"
#include "delim.h"
using namespace std;

class Supply
{
public:
	// data members
	char sno[3]; char pno[3]; char jno[3]; char city[10]; char qty[3];
	// method
	Supply(); // default constructor
	static int InitBuffer(DelimFieldBuffer&);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(FixedFieldBuffer&);
	void Clear();
	char* Key() const;
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	void Print(ostream&, char* label = 0) const;
};



#endif
/*
supply.h�� ���� ���̺��� class �������Ѵ�
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key�� (sno,pno, jno)�� ������
*/