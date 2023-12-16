#pragma once
#ifndef _masa_
#define _masa_
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

#include  "struct.h"
#include  "exception.h"
using namespace std;
int operator>(dat v, dat w) //Определение перегруженной операции сравнения для структур типа data
{
	if (v.y > w.y) return 1;
	if ((v.y == w.y) && (v.m > w.m)) return 1;
	if ((v.y == w.y) && (v.m == w.m) && (v.d > w.d)) return 1;
	return 0;
}
int operator>(abonent v, abonent w) //Определение перегруженной операции сравнения для структур
{
	if (v.plata > w.plata) return 1;
	if ((v.plata > w.plata) && (v.pers.name > w.pers.name)) return 1;
	return 0;
}

 ostream& operator<<(ostream& out, abonent& px) //Определение перегруженной операции вывода на экран структуры 
{
	out << "|" << setw(16) << px.number << "|" << setw(5) << px.datzakl.d << "|" << setw(6) << px.datzakl.m << "|" << setw(4) << px.datzakl.y << "|" << setw(19) << px.plata << "|" << setw(20) << px.pers.name << "|" << setw(10) << px.pers.region << "|" << setw(16) << px.pers.adress << "|" << setw(11) << px.pers.phone << "|\n";
	return out;
}

class masA
{
protected:
	abonent* px;
	int n;
public:
	masA() :px(NULL), n(0) {};
	masA(masA& z);
	virtual ~masA() { if (px != NULL) delete[]px; cout << "~masA()\n"; }
	virtual masA& operator=(masA& z);

	//Методы только в masA
	void inputFile();
	void addAbonent();
	void deleteAbonent();
	//Переопределяемые методы
	void sort1();
	void sort2();
	//Виртуальные методы
	virtual void outputMas();
	virtual void outputFile();
	virtual void sort3();

	//Определение перегруженной операции вывода на экран объекта класса masA
	friend ostream& operator<<(ostream& out, masA& z);
};//Определение методов класса masA
#include "masa.cpp"
#endif