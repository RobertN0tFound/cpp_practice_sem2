#include <iostream>
#include <windows.h>
#define STR_SIZE 50
using namespace std;

void Split(char* str, char res[][STR_SIZE])
{
	char* str1;
	char* str2;
	char* str3;
	str1 = strtok_s(str, " ", &str2);
	strcpy_s(res[0], str1);
	str1 = strtok_s(str2, " ", &str3);
	strcpy_s(res[1], str1);
	strcpy_s(res[2], str3);
}

void header(void)
{
	cout << endl << endl;
	cout << "|"; cout.width(60); cout.fill('-'); cout << "|" << endl;
	cout.width(60); cout.fill(' '); cout << left; cout << "|Характеристика ПЭВМ"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(60); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout.width(15); cout << left; cout << "|Процессор";
	cout.width(15); cout << "|Частота (Mgz)";
	cout.width(15); cout << "|RAM (Mb)";
	cout.width(15); cout << "|Тип";
	cout << "|" << endl; cout << internal;
	cout << "|"; cout.width(60); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
}

void footer(void)
{
	cout << internal; cout << "|"; cout.width(60); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout << left; cout.width(60); cout << "|Тип: C - CISC-процессор, R - RISC-процессор"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(60); cout.fill('_'); cout << "|" << endl; cout.fill(' ');
}

void rows(char* core, char* freq, char* type)
{
	cout << "|"; cout << left; cout.width(14);
	cout << core;
	cout << "|"; cout.width(14);
	cout << freq;
	cout.width(15); cout << "|"; cout << "|"; cout.width(14);
	cout << type;
	cout << "|" << endl;
}

int main()
{
	char str[STR_SIZE];
	char core[3][STR_SIZE];
	char type[3][STR_SIZE];
	char freq[3][STR_SIZE];

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << endl << "Введите процессоры: ";
	cin.getline(str, 50);
	Split(str, core);
	cout << endl << "Введите частоты: ";
	cin.getline(str, 50);
	Split(str, freq);
	cout << endl << "Введите типы: ";
	cin.getline(str, 50);
	Split(str, type);

	header();
	rows(core[0], freq[0], type[0]);
	rows(core[1], freq[1], type[1]);
	rows(core[2], freq[2], type[2]);
	footer();
}