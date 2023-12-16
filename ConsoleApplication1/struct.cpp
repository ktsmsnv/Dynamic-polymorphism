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
struct record {
	int price;
	int kol;
};
struct comp
{
	string marka;
	string type;
	int ntype;
	int gerz;
	int ram;
	int hdd;
	int vga;
	record pers;
};
struct marki {
	string marka;
	int count;
};
#endif