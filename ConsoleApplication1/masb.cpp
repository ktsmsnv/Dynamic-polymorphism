#include  "masb.h"
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
using namespace std;
masB::masB(masB& z)
try : masA(z) //конструктор копирования класса masB
{
	int i;
	k = z.k;
	if (z.mas == NULL) mas = NULL;
	else {
		try {
			mas = new PLATAA[k];
			throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			mas = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (mas)", "конструктор копирования masB");
		}

		if (mas == NULL) {
			cout << "Нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}
		for (i = 0; i < k; i++)
			mas[i] = z.mas[i];
	}
}
catch (ErrMem& ex) { throw ErrMem(ex.getMes(), ex.getMes1(), "masB(masB &z)"); }

masB& masB :: operator= (masA& z) //перегруженная операция виртуальная
{
	int i;
	masB  r;
	if (this == &z) return *this;
	// Вызов перегруженной операции присваивания класса masА для 
	masA :: operator=(z);  // присваивания родительской части объекта z
	r = (masB&)z;                 //  понижающее присваивание
	if (mas != NULL) delete[] mas;
	k = r.k;
	if (r.mas == NULL) mas = NULL;
	else {
		try {
			mas = new PLATAA[k];
			//throw bad_alloc();
		}
		catch (bad_alloc)
		{
			throw ErrMem("Нет памяти", "перечня (py)",
				"masB::operator=( masB &z))");
		}

		for (i = 0; i < k; i++)
			mas[i] = r.mas[i];
	}
	return *this;
}

masB& masB :: operator=(masB& z) //перегруженная операция присваивания класса masB
{
	int i;
	if (this == &z) return *this;
	// Вызов перегруженной операции присваивания класса masА для 
	masA :: operator= (z);  // присваивания родительской части объекта z
	if (mas != NULL) delete[] mas;
	k = z.k;
	if (z.mas == NULL) mas = NULL;
	else {
		try {
			mas = new PLATAA[k];
			//throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			mas = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (mas)", "перегруженная операция присваивания masB");
		}
		if (mas == NULL) {
			cout << "Нет памяти при присваивании. \n";
			system("pause"); return z;
		}
		for (i = 0; i < k; i++)
			mas[i] = z.mas[i];
	}
	return *this;
	
}

//Сортировка перечня по абонентской плате
void masB::sort1()
{
	int fl, i, kk;
	PLATAA t;

	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].plata > mas[i + 1].plata)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по абонентской плате.\n";
	system("pause");
}
//  Сортировка перечня по численности
void masB::sort3()
{
	int i, fl, kk;
	PLATAA t;
	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].count > mas[i + 1].count)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по количеству абонентов по каждому виду платежа. \n";
	system("pause");
}
//Вывод перечня в текстовый файл 
void masB::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла\n"; cin >> file;
	fout.open(file.c_str());
	//  Защита от неправильного ввода имени файла

	if (fout.fail()) throw ErrFile("не создается файл", file,
		"masВ::outputFile");
	//Генерация исключения "Файл не создается"

	fout << "______________________\n";
	fout << "| Плата  | Количество | \n";
	fout << "______________________\n";
	for (i = 0; i < k; i++)
		fout << setw(6) << mas[i].plata << " | " << setw(11) << mas[i].count << " | \n";
	fout << "_______________________\n";
	fout.close();
	cout << "Перечень сохранен в файле.\n";
	system("pause");
}
//Вывод перечня на экран 
void masB::outputMas()
{
	int i;

	// Вывод заголовка таблицы (массива структур) 
	cout << "перечень: " << endl;
	cout << "______________________\n";
	cout << "| Плата  | Количество | \n";
	cout << "______________________\n";
	cout << left;
	// Вывод строк таблицы
	for (i = 0; i < k; i++)
		cout << setw(6) << "|" << mas[i].plata << "|" << setw(11) << mas[i].count << " | \n";
	cout << "_______________________\n";
	system("pause");

}
//Определение метода makePerech (…) класса masB
void masB::makePerech()
{
	int i, j, fl;
	PLATAA* y;
	try {
		y = new PLATAA[n];
		//throw bad_alloc();
	}
	catch (bad_alloc)   //  Обработчик без передачи данных
	{
		throw ErrMem("нет памяти", "рабочего массива (перечня)", "makePerech()");
	}


	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause");
		return;
	}
	k = 0;

	if (mas != NULL) delete[] mas;
	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if (px[i].plata == y[j].plata)
			{
				fl = 1; y[j].count++;
			}
		if (fl == 0) {
			y[k].plata = px[i].plata;
			y[k].count = 1;
			k++;
		}
	}
	try {
		mas = new PLATAA[k];
		//throw bad_alloc();
	}
	catch (bad_alloc)   //  Обработчик без передачи данных
	{
		mas == NULL;
		k = 0;
		delete[] mas;
		throw ErrMem("нет памяти", " перечня(py)", "makePerech()");
	}

	for (j = 0; j < k; j++)
		mas[j] = y[j];
	delete[] y;
	cout << "Перечень сформирован.\n";
	system("pause");
}
ostream& operator<<(ostream& out, masB& z)
{
	int i;
	out << "перечень: " << endl;
	out << "______________________\n";
	out << "| Плата  | Количество | \n";
	out << "______________________\n";

	for (i = 0; i < z.k; i++)
		out << z.mas[i];
	out << "______________________\n";
	system("pause");
	return out;
}
