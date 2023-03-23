#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

struct Date {
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct Record {
	char name[20];
	int freq;
	int ram;
	char type[20];
	struct Date date;
};

void printDate(unsigned short day, unsigned short month, unsigned short year, int wLine) {
	int w = 10;
	int len = (wLine - w) / 2 - 1;
	cout << left;
	cout.width(len); cout << " ";
	if (day > 9) {
		cout << day;
	}
	else {
		cout << "0" << day;
	}
	cout << ".";
	if (month > 9) {
		cout << month;
	}
	else {
		cout << "0" << month;
	}
	cout << ".";
	cout << year;
	cout.width(len); cout << " ";
}

void DrawTable(struct Record* records, int RowCount)
{
	cout << endl;
	cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl;
	cout.width(85); cout.fill(' '); cout << left; cout << "|Характеристика ПЭВМ"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout.width(15); cout << left; cout << "|Процессор";
	cout.width(15); cout << "|Частота (Mgz)";
	cout.width(15); cout << "|RAM (Mb)";
	cout.width(15); cout << "|Тип";
	cout.width(15); cout << "|Дата начала производства";
	cout << "|" << endl; cout << internal;
	cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	for (int i = 0; i < RowCount; i++) {
		cout << "|"; cout << left; cout.width(14);
		cout << records[i].name;
		cout << "|"; cout.width(14);
		cout << records[i].freq;
		cout << "|+ "; cout.width(12);
		cout << records[i].ram;
		cout << "|"; cout.width(14);
		cout << records[i].type;
		cout << "|"; cout.width(13);
		printDate(records[i].date.day, records[i].date.month, records[i].date.year, 27);
		cout << "|" << endl;
	}
	cout << internal; cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout << left; cout.width(85); cout << "|Тип: C - CISC-процессор, R - RISC-процессор"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(85); cout.fill('_'); cout << "|" << endl; cout.fill(' ');
}

int main()
{
	char sDelete[15];
	int g = 0;
	int index;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	struct Record records[20] = {
		{ "Pentium-III", 233, 16, "C", {10,10,2020} },
		{ "AMD-K6", 166, 8, "C", {11,11,2011} },
		{ "PowerPC-620", 2000, 16, "R", {10,10,2010} }
	};
	struct Record newrecords[20];

	cout << "Исходные данные:";
	DrawTable(records, 3);

	cout << endl << endl << "Введите наименование, которое хотите удалить: ";
	cin.getline(sDelete, 20);

	for (int i = 0; i < 3; i++) {
		if (strcmp(records[i].name, sDelete) != 0) {
			newrecords[g] = records[i];
			g++;
		}
	}
	DrawTable(newrecords, g);

	cout << endl << endl << "Введите номер строки для удаления: ";
	cin >> index;
	g = 0;
	for (int i = 0; i < 3; i++) {
		if (index != i+1) {
			newrecords[g] = records[i];
			g++;
		}
	}
	DrawTable(newrecords, g);
}