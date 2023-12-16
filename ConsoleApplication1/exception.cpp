#ifndef _exception_
#define _exception_
#include  <iostream>
#include  <limits>
#include  <fstream>
#include  <cstdlib>
#include  <string>
#include  <iomanip>
#include  <conio.h>
#include  <Windows.h>
#include  <sstream>
using namespace std;
class Err
{
protected:
	string mes;                             //  Что за ошибка 
	string mes2;                           //  в каком методе произошла

public:

	//     Идентифицирующий конструктор
	Err(string mes0, string mes20) : mes(mes0), mes2(mes20) {}

	virtual void ErrOutput()
	{
		cout << "Ошибка: " << mes;
		cout << " в функции/методе " << mes2 << endl;
		_getch();
	}

};

class ErrFile : public Err
{
protected:
	string mes1;                             //  при работе с каким файлом
public:

	//     Идентифицирующий конструктор
	ErrFile(string mes0, string mes10, string mes20)
		: Err(mes0, mes20), mes1(mes10) {}

	virtual void ErrOutput()
	{
		cout << "Ошибка: " << mes << endl;
		cout << "При работе с файлом: " << mes1 << endl;
		cout << "Произошла в методе: " << mes2 << endl;
		_getch();
	}//  Вывод сообщения об ошибке
};


class ErrMem : public ErrFile
{
protected:
public:

	//    Идентифицирующий конструктор
	ErrMem(string mes0, string mes10, string mes20)
		: ErrFile(mes0, mes10, mes20) {}

	virtual void ErrOutput()
	{
		cout << "Ошибка: " << mes;
		cout << " при выделении памяти для " << mes1;
		cout << " в методе " << mes2 << endl;
		_getch();
	}
	string getMes() { return mes; }
	string getMes1() { return mes1; }
};
#endif