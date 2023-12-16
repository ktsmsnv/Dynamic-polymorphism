#pragma once
#ifndef _masc_
#define _masc_
#define NOMINMAX
#include  <iostream>
#include  <limits>
#include  <fstream>
#include  <cstdlib>
#include  <string>
#include  <iomanip>
#include  <conio.h>
#include  <Windows.h>
#include  <sstream>

#include  "masb.h"
#include  "struct.h"
#include  "exception.h"
using namespace std;

class masC : public masB
{
protected:
	abonent* pz;
	int l;
public:
	masC() :pz(NULL), l(0) {};
	masC(masC& z);
	virtual ~masC() { if (pz != NULL) delete[]pz; cout << "~masC() \n"; }
	masC& operator=(masC& z);
	virtual masC& operator=(masA& z);
	
	//Методы только masC
	void findRegion();
	//Переопределяемые методы
	void sort2();
	void sort1();
	//Виртуальные методы
	virtual void outputMas();
	virtual void outputFile();

	friend ostream& operator<<(ostream& out, masC& z);
};
#include "masc.cpp"
#endif
