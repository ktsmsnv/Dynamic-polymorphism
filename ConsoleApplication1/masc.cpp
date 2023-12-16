#include  "masc.h"
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
#include  "masa.h"
#include  "masb.h"
using namespace std;

masC::masC(masC& z)
try : masB(z)
{
	int i;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		try {
			pz = new abonent[l];
			//throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			pz = NULL; l = 0;
			throw ErrMem("Нет памяти", "исх. массива (pz)", "конструктор копирования masC");
		}
		for (i = 0; i < l; i++)
			pz[i] = z.pz[i];
	}
}
catch (ErrMem& ex) { throw ErrMem(ex.getMes(), ex.getMes1(), "masC(masC &z)"); }

masC& masC::operator=(masC& z) //перегруженная операция 
{
	int i;
	if (this == &z) return *this;
	// Вызов перегруженной операции присваивания класса masB для 
	masB :: operator=(z);  // присваивания родительской части объекта z
	if (pz != NULL) delete[] pz;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		try {
			pz = new abonent[l];
			//throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			pz = NULL; l = 0;
			throw ErrMem("Нет памяти", "исх. массива (pz)", " перегруженной операции присваивания класса masC");
		}
		for (i = 0; i < l; i++)
			pz[i] = z.pz[i];
	}
	return *this;
}
masC& masC :: operator= (masA& z)//перегруженная операция виртуальная 
{
	int i;
	masC  r;
	if (this == &z) return *this;

	// Вызов перегруженной операции присваивания класса masС для 
	masB:: operator=(z);  //  присваивания родительской части объекта z

	r = (masC&)z;               //  понижающее присваивание
	if (pz != NULL) delete[] pz;
	l = r.l;
	if (r.pz == NULL) pz = NULL;
	else {
		try {
			pz = new abonent[l];
			//throw bad_alloc();
		}
		catch (bad_alloc)
		{
			throw ErrMem("Нет памяти", "студентов группы (pz)",
				"masC::operator=( masC &z)");
		}
		for (i = 0; i < l; i++)
			pz[i] = r.pz[i];
	}
	return *this;
}

void masC::sort1()
{
	int i, fl, nn;
	abonent t;

	nn = l;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (pz[i].pers.name > pz[i + 1].pers.name)
			{
				fl = 1;  t = pz[i];
				pz[i] = pz[i + 1];
				pz[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по ФИО в алфавитном порядке\n";
	system("pause");
}
//Сортировка массива структур masC по дате заключения (сортировка по нескольким полям)
void masC::sort2() // сортировка по дате заключения
{
	int fl, i, nn;
	abonent t;

	nn = l;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (pz[i].datzakl > pz[i + 1].datzakl)
			{
				fl = 1; t = pz[i];
				pz[i] = pz[i + 1];
				pz[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по дате заключения договора\n";
	system("pause");
}
//Вывод массива структур на экран
void masC::outputMas()
{
	int i;

	// Вывод заголовка таблицы (массива структур) 
	cout << "Результаты поиска: " << endl;
	cout << "_____________________________________________________________________________________________________________________________________\n";
	cout << "|   |                | Дата заключения |                   |                    |          |                             |           |\n";
	cout << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес                       | Телефон   |\n";
	cout << "|" << "___________________________________________________________________________________________________________________________________" << " | " << "\n";
	cout << left;
	// Вывод строк таблицы
	for (i = 0; i < l; i++)
		cout << "|" << setw(3) << i + 1 << "|" << setw(16) << pz[i].number << "|" << setw(5) << pz[i].datzakl.d << "|" << setw(6) << pz[i].datzakl.m << "|" << setw(4) << pz[i].datzakl.y << "|" << setw(19) << pz[i].plata << "|" << setw(20) << pz[i].pers.name << "|" << setw(10) << pz[i].pers.region << "|" << setw(29) << pz[i].pers.adress << "|" << setw(11) << pz[i].pers.phone << "| \n";
	cout << "|" << "___________________________________________________________________________________________________________________________________" << " | \n";
	system("pause");
}
//Вывод массива структур masC в текстовый файл
void masC::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла:";   cin >> file;
	fout.open(file.c_str());
	//  Защита от неправильного ввода имени файла

	if (fout.fail()) throw ErrFile("не создается файл", file,
		"masС::outputFile");
	//Генерация исключения "Файл не создается"

	fout << "_____________________________________________________________________________________________________________________________________\n";
	fout << "|   |                | Дата заключения |                   |                    |          |                             |           |\n";
	fout << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес                       | Телефон   |\n";
	fout << "|" << "_________________________________________________________________________________________________________________________________" << " | " << "\n";

	for (i = 0; i < l; i++)
		fout << "|" << setw(3) << i + 1 << "|" << setw(16) << pz[i].number << "|" << setw(5) << pz[i].datzakl.d << "|" << setw(6) << pz[i].datzakl.m << "|" << setw(4) << pz[i].datzakl.y << "|" << setw(19) << pz[i].plata << "|" << setw(20) << pz[i].pers.name << "|" << setw(10) << pz[i].pers.region << "|" << setw(29) << pz[i].pers.adress << "|" << setw(12) << pz[i].pers.phone << "| \n";
	fout << "_________________________________________________________________________________________________________________________\n";

	fout.close();
	cout << "Массив структур сохранен в фаил\n";
	system("pause");
}
//Определение метода findRegion(…) класса masС
void masC::findRegion()
{
	int i, j;
	string region0;
	abonent* y;

	try {
		y = new abonent[n];
		//throw bad_alloc();
	}
	catch (bad_alloc)    //  Обработчик без передачи данных
	{
		throw ErrMem("нет памяти", "раб. массива (y)", "findRegion()");
	}

	cout << "Название региона : ";
	cin >> region0;
	if (cin.fail())
	{
		throw Err("при вводе", "findRegion()");
	}
	l = 0;
	for (i = 0; i < n; i++)
		if (px[i].pers.region == region0) { y[l] = px[i];  l++; }
	if (pz != NULL) delete[] pz;
	try {
		pz = new abonent[l]; //	throw bad_alloc();
	}

	catch (bad_alloc)      //  Обработчик без передачи данных
	{
		pz = NULL;
		l = 0;
		delete[]y;
		throw ErrMem("нет памяти", "массива студ. (pz)", "findRegion()");
	}

	for (j = 0; j < l; j++)
		pz[j] = y[j];
	delete[] y;
	cout << "Массив абонетов искомого района сформирован. \n";
	system("pause");
}
ostream& operator<<(ostream& out, masC& z)
{
	int i;
	out << "_____________________________________________________________________________________________________________________________________\n";
	out << "|   |                | Дата заключения |                   |                    |          |                             |           |\n";
	out << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес                       | Телефон   |\n";
	out << "|" << "___________________________________________________________________________________________________________________________________" << " | " << "\n";
	out << left;
	for (i = 0; i < z.l; i++)
		cout << "|" << setw(3) << i + 1 << "|" << setw(16) << z.pz[i].number << "|" << setw(5) << z.pz[i].datzakl.d << "|" << setw(6) << z.pz[i].datzakl.m << "|" << setw(4) << z.pz[i].datzakl.y << "|" << setw(19) << z.pz[i].plata << "|" << setw(20) << z.pz[i].pers.name << "|" << setw(10) << z.pz[i].pers.region << "|" << setw(29) << z.pz[i].pers.adress << "|" << setw(11) << z.pz[i].pers.phone << "| \n";
	out << "|" << "___________________________________________________________________________________________________________________________________" << " | \n";
	system("pause"); return out;
}