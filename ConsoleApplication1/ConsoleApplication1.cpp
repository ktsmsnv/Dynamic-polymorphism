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
#include  "masc.h"

using namespace std;
class masC;

//Прототипы функций, использующих механизм виртуальных функций
void print(masA& z);
void printFile(masA* p);
void sort3(masA* p);
//Определение функций, использующих механизм виртуальных функций
void print(masA& z)
{
	z.outputMas();
}
void printFile(masA* p)
{
	p->outputFile();
}
void sort3(masA* z)
{
	z->sort3();
}

void printA(masC* p);  //  Вывод 1-й таблицы
void printB(masC* p);
void printC(masC* p);

void printA(masC* p)                     //  Вывод 1-й таблицы
{
	p->masA::outputMas();
}

void printB(masC* p)               //  Вывод 2-й таблицы
{
	p->masB::outputMas();
}

void printC(masC* p)                //  Вывод 3-й таблицы
{
	p->masC::outputMas();
}
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	masA* pa, * pb, * pc;
	masC* pd;
	int j;
	char ch;

	//  Выделение памяти для объектов основного *pa(*pd) и рабочих *pb,*pc
	try {
		pa = pd = new masC;
		pb = new masC;
		pc = new masC;
	}
	catch (bad_alloc)
	{
		cout << "Ошибка: нет памяти для объектов\n";
		_getch(); return;
	}


	while (1)
	{
		try {
			system("cls"); //clrscr(); очистка экрана
			cout << "1. Загрузка исходного массива из файла\n";
			cout << "2. Вывод исходного массива на экран\n";
			cout << "3. Сохранение исходного массива в текстовом файле\n";
			cout << "4. Добавление записи в исходный массив\n";
			cout << "5. Удаление записи из исходного массива\n";
			cout << "6. Алфавитная сортировка по Ф.И.О. исходного массива\n";
			cout << "7. Сортировка по дате заключения договора исходного массива\n";
			cout << "8. Числовая сортировка по номеру договора исходного массива\n";
			cout << "9. Формирование перечня абонентских плат (1-ый выходной массив)\n";
			cout << "10. Вывод перечня абонентских плат на экран\n";
			cout << "11. Вывод перечня абонентских плат в текстовый файл\n";
			cout << "12. Сортировка перечня абонентских плат по стоимости платы \n";
			cout << "13. Сортировка перечня абонентских плат по количеству абонентов в каждом типе платы \n";
			cout << "14. Поиск абонентов по району (2-ой выходной массив)\n";
			cout << "15. Вывод результатов поиска абонентов на экран\n";
			cout << "16. Вывод результатов поиска абонентов в текстовый файл\n";
			cout << "17. Сортировка поиска абонентов по районам по Ф.И.О.\n";
			cout << "18. Сортировка поиска абонентов по районам по дате заключения\n";
			cout << "19. Проверка конструктора копирования\n";
			cout << "20.Проверка обычной операции присваивания\n";
			cout << "21.Проверка виртуальной операции присв-я \n";
			cout << "22.Выход из программы\n\n";

			cout << "Ваш выбор (1-21): ";

			try
			{
				if (char(cin.peek()) == '\n')
					cin.ignore();

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
				}
				cin >> j;
				if (cin.fail())
				{
					throw Err("Это не пункт меню", "main()");
				}
			}
			catch (Err& ex)
			{
				throw;
			}

			//    Реализация выбранного пункта меню
			switch (j)
			{
			case 1: pa->inputFile(); break;
			case 2: pa->masA::outputMas();  break;
			case 3: pa->masA::outputFile();  break;
			case 4: pa->addAbonent(); break;
			case 5: pa->deleteAbonent(); break;
			case 6: pa->sort1();  break;
			case 7: pa->sort2();  break;
			case 8: pa->masA::sort3(); break;
			case 9: ((masB*)pa)->masB::makePerech(); break;
			case 10:((masB*)pa)->masB::outputMas(); break;
			case 11: {((masB*)pa)->masB::outputFile(); break;
			case 12: ((masB*)pa)->masB::sort1();  break;
			case 13: ((masB*)pa)->masB::sort3();  break;
			case 14: ((masC*)pa)->findRegion();  break;
			case 15: pa->outputMas();  break;
			case 16: pa->outputFile(); break;
			case 17: ((masC*)pa)->sort1(); break;
			case 18:((masC*)pa)->sort2(); break;
			case 19: { masC c(*pd);          //  конструктор копирования
				printA(pd); printA(&c);
				printB(pd); printB(&c);
				printC(pd); printC(&c);
			} break;
			case 20: { masC a, b;
				a = b = *pd;                 //  каскадное обычное присваивание
				printA(pd); printA(&b); printA(&a);
				printB(pd); printB(&b); printB(&a);
				printC(pd); printC(&b); printC(&a);
			}  break;
			case 21: { masC* pb2, * pc2;
				*pc = *pb = *pa;           //  каскадное виртуальное присваивание
				pb2 = (masC*)pb;    //  понижающее присваивание указателей
				pc2 = (masC*)pc;     //  понижающее присваивание указателей
				printA(pd); printA(pb2); printA(pc2);
				printB(pd); printB(pb2); printB(pc2);
				printC(pd); printC(pb2); printC(pc2);
			}  break;
			case 22: cout << "Конец работы\n";
				delete pa;
				delete pb;
				delete pc;
				system("pause"); return;

			default:  throw Err("Нет такого пункта в меню", "main()");
			}
			}// Конец внешнего блока try
		}
		catch (Err& ex) { ex.ErrOutput(); }
		catch (...)
		{
			cout << "Непредусмотренное исключение\n"; _getch();
		}
	}
}
