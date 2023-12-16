#ifndef _struct_
#define _struct_
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
class masB;
class masC;
struct person {
	string name;
	string region;
	string adress;
	string phone;
};
struct dat { int d, m, y; };
struct abonent {
	int number;
	int plata;
	person pers;
	dat datzakl;
};
struct PLATAA
{
	int plata;
	int count;
};
#endif