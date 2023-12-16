#include  "masa.h"
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
masA::masA(masA& z) //Конструктор копирования класса masA
{
	int i;
	n = z.n;
	if (n == 0) px = NULL;
	else {
		try {
			px = new abonent[n];
			//throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			px = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (px)", "masA(masA &z)");
		}
		if (px == NULL) {
			cout << "нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
} // конец конструктора копирования
masA& masA :: operator=(masA& z) //Определение перегруженной операции присваивания класса masA
{
	int i;
	if (this == &z) return *this;
	if (px != NULL) delete[]px;
	n = z.n;
	if (z.px == NULL) px = NULL;
	else {
		try {
			px = new abonent[n];
			//throw bad_alloc();
		}
		catch (bad_alloc)                     //   Обработчик без передачи данных
		{
			px = NULL; n = 0;
			throw ErrMem("Нет памяти", "исх. массива (px)", "masA::operator=(masA &z)");
		}
		if (px == NULL) {
			cout << "нет памяти.\n";
			cout << "операция присваивания.\n";
			system("pause"); return z;
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
	return *this;
}

//ввод исходного массива структур из файла
void masA::inputFile()
{
	ifstream fin;
	string file;
	string iniz;
	abonent t;
	cout << "Имя входного файла:";
	cin >> file;
	fin.open(file.c_str());
	//Защита от неправильного ввода имени файла
	if (fin.fail()) throw ErrFile("не открывается", file, "inputFile()"); //Генерация исключения "файл не откр-ся"

	n = 0;
	if (px != NULL) { delete[] px; px = NULL; }  // очистка массива

	while (1)
	{
		fin >> t.number >> t.datzakl.d >> t.datzakl.m >> t.datzakl.y >> t.plata >> t.pers.name >> iniz >> t.pers.region >> t.pers.adress >> t.pers.phone;
		if (fin.fail()) break;	n++;
	}

	//  Вместо повторного открытия файла
	fin.clear();
	fin.seekg(0, ios::beg);   //  перемещение курсора в начало файла

	try {
		px = new abonent[n];
		//throw bad_alloc();
	}
	catch (bad_alloc)      //   Обработчик без передачи данных
	{
		px = NULL; n = 0;
		throw ErrMem("Нет памяти", "исх. массива (px)", "inputFile()");
	}

	if (px == NULL) {
		cout << "Нет памяти.\n"; fin.close();
		cout << "Ввести фаил не удается.\n";
		system("pause"); n = 0; return;
	}
	for (int i = 0; i < n; i++)
	{
		fin >> px[i].number >> px[i].datzakl.d >> px[i].datzakl.m >> px[i].datzakl.y >> px[i].plata >> px[i].pers.name >> iniz >> px[i].pers.region >> px[i].pers.adress >> px[i].pers.phone;
		px[i].pers.name = px[i].pers.name + " " + iniz;
		if (fin.fail())   throw Err("при вводе", "inputFile()");
	}

	fin.close();
	cout << "Файл введен " << endl;
	system("pause");
}
//Добавление записи в динамический массив структур
void masA::addAbonent()
{
	int i;
	abonent t, * p;
	string iniz;

	try {      //   начало   try - блока
		p = new abonent[n + 1];  // выделение памяти для нового массива
		//throw bad_alloc();
	}
	catch (bad_alloc)     //   Обработчик без передачи данных
	{
		p = NULL; n = 0;
		throw ErrMem("Нет памяти", "исх. массива (p)", "adddan()");
	}
	if (p == NULL) {
		cout << "нет памяти.\n";
		cout << "Добавить не удается.\n";
		system("pause"); return;
	}
	try
	{
		cout << "Номер договора:"; cin >> t.number;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Дата заключения.\n";
		cout << "День:";   cin >> t.datzakl.d;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Месяц:"; cin >> t.datzakl.m;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Год:";      cin >> t.datzakl.y;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Абонентская плата:"; cin >> t.plata;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Ф.И.О.:"; cin >> t.pers.name >> iniz;
		t.pers.name = t.pers.name + " " + iniz;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Регион:"; cin >> t.pers.region;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Адрес:"; cin >> t.pers.adress;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}
		cout << "Телефон:"; cin >> t.pers.phone;
		if (cin.fail())
		{
			throw Err("при вводе", "adddan()");
		}

		for (i = 0; i < n; i++)
			p[i] = px[i];   // копирования старого массива в новый
		p[n] = t; // добавление новой записи в массив структур
		n++;   // увеличение счетчика количества записей

		if (px != NULL) delete[] px; // удаление старого массива
		px = p;    // адрес нового массива заносится в px

		cout << "Запись добавлена.\n";
		system("pause");
	}       //   конец   try - блока

	catch (bad_alloc)     //   Обработчик без передачи данных
	{
		throw ErrMem("Нет памяти", "исх массива", "addStudent()");
	}

}
//Удаление записи из динамического массива структур
void masA::deleteAbonent()
{
	int j, i;
	abonent* p = NULL;
	string iniz;
	char ch;

	masA::outputMas(); //  вызов на экран массива структур

	//  Защита от неправильного ввода номера строки
	cout << "Номер удаленой стороки:";
	try
	{
		cin >> j;
		if (cin.fail())
		{
			throw Err("Это не номер строки", "deleteStudent()");
		}
	}
	catch (char ex[])
	{
		throw Err("Это не номер строки", "deletedan()");
	}


	if (j<1 || j>n)  throw Err("Нет такой строки", "deleteStudent()");//Генерация исключения "нет такой строки"

	j--; //  переход от номера удаленной строки к ее индексу
	cout << j + 1 << "-я строка:\n";
	cout << px[j].number << " " << px[j].datzakl.d << "." << px[j].datzakl.m << "." << px[j].datzakl.y << " " << px[j].plata << " " << px[j].pers.name << " " << iniz << " " << px[j].pers.region << " " << px[j].pers.adress << " " << px[j].pers.phone << endl;

	cout << "Удалить?(y/n):"; cin >> ch;
	if (char(cin.peek()) != '\n')
	{
		cin.ignore();
		cin.clear();
		cin.ignore(32767, '\n');
	}
	if (ch == 'n')
	{
		throw Err("Это не та строка", "deleteStudent()");
	}
	if (ch != 'y')
	{
		throw Err("Ответ ни да ни нет ", "deleteStudent()");
	}

	//  Выполнение удаления строки     
	if (n == 1) { delete[] px; px = NULL; n = 0; }
	else
	{
		try {
			p = new abonent[n - 1];
			//throw bad_alloc();
		}
		catch (bad_alloc)    //  Обработчик без передачи данных
		{
			throw ErrMem("Нет памяти", "исх. массива (px)", "deleteStudent()");
		}

		if (p == NULL)
		{
			cout << "Нет памяти.\n ";
			cout << "Удалить не удается.\n";
			system("pause"); return;
		}
		for (i = 0; i < j; i++)
			p[i] = px[i];
		for (i = j + 1; i < n; i++)
			p[i - 1] = px[i];
		delete[] px; // удаление старого массива
		px = p;    // адрес нового массива заносится в поле px
		n--;//  уменьшение счетчика количества записей
	}
	cout << "Запись удалена.\n";
	system("pause");
}
//Сортировка массива структур по ФИО (сортировка по строковому полю в алф-ом порядке)
void masA::sort1()
{
	int i, fl, nn;
	abonent t;
	nn = n;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].pers.name > px[i + 1].pers.name)
			{
				fl = 1;  t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по ФИО в алфавитном порядке\n";
	system("pause");
}
//Сортировка массива структур по дате заключения(сортировка по нескольким полям)
void masA::sort2() // сортировка по дате заключения
{
	int fl, i, nn;
	abonent t;

	nn = n;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].datzakl > px[i + 1].datzakl) // это перегруженная операция  “>”, вызывается операторная ф-ия
			{
				fl = 1; t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по дате заключения договора\n";
	system("pause");
}
//Сортировка массива структур по числовому полю
void masA::sort3()  //по номеру договора
{
	int i, fl, nn;
	abonent t;
	nn = n;  // вводим копию размера массива
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].number > px[i + 1].number)
			{
				fl = 1;  t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по номеру договора\n";
	system("pause");
}
//Вывод массива структур на экран
void masA::outputMas()
{
	int i;

	// Вывод заголовка таблицы (массива структур) 
	cout << "_____________________________________________________________________________________________________________________________________\n";
	cout << "|   |                | Дата заключения |                   |                    |          |                             |           |\n";
	cout << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес                       | Телефон   |\n";
	cout << "|" << "___________________________________________________________________________________________________________________________________" << " | " << "\n";
	cout << left;
	// Вывод строк таблицы
	for (i = 0; i < n; i++)
		cout << "|" << setw(3) << i + 1 << "|" << setw(16) << px[i].number << "|" << setw(5) << px[i].datzakl.d << "|" << setw(6) << px[i].datzakl.m << "|" << setw(4) << px[i].datzakl.y << "|" << setw(19) << px[i].plata << "|" << setw(20) << px[i].pers.name << "|" << setw(10) << px[i].pers.region << "|" << setw(29) << px[i].pers.adress << "|" << setw(11) << px[i].pers.phone << "| \n";
	cout << "|" << "___________________________________________________________________________________________________________________________________" << " | \n";
	system("pause");

}
//Вывод массива структур в текстовый файл
void masA::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла:";   cin >> file;
	fout.open(file.c_str());

	//  Защита от неправильного ввода имени файла
	if (fout.fail()) throw ErrFile("не создается файл", file, "masA::outputFile");
	//    генерация исключения (8)

	// Вывод заголовка 
	fout << "_____________________________________________________________________________________________________________________________________\n";
	fout << "|   |                | Дата заключения |                   |                    |          |                             |           |\n";
	fout << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес                       | Телефон   |\n";
	fout << "|" << "_________________________________________________________________________________________________________________________________" << " | " << "\n";

	// Вывод остальных строк таблицы
	for (i = 0; i < n; i++)
		fout << "|" << setw(3) << i + 1 << "|" << setw(16) << px[i].number << "|" << setw(5) << px[i].datzakl.d << "|" << setw(6) << px[i].datzakl.m << "|" << setw(4) << px[i].datzakl.y << "|" << setw(19) << px[i].plata << "|" << setw(20) << px[i].pers.name << "|" << setw(10) << px[i].pers.region << "|" << setw(29) << px[i].pers.adress << "|" << setw(12) << px[i].pers.phone << "| \n";
	fout << "_________________________________________________________________________________________________________________________\n";

	fout.close();
	cout << "Массив структур сохранен в фаил\n";
	system("pause");
}

//Определение перегруженной операции вывода на экран объекта класса masA
ostream& operator<<(ostream& out, masA& z)
{
	int i;
	out << "_________________________________________________________________________________________________________________________\n";
	out << "|   |                | Дата заключения |                   |                    |          |                |           |\n";
	out << "| № | Номер договора | День| Месяц| Год| Абонентская плата | Фамилия и инициалы | Район    | Адрес          | Телефон   |\n";
	out << "_________________________________________________________________________________________________________________________\n";
	for (i = 0; i < z.n; i++)
		out << "|" << setw(3) << i + 1 << z.px[i];
	out << "_________________________________________________________________________________________________________________________\n";
	system("pause");
	return out;
}

