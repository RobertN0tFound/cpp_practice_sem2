#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#define ARR_SIZE 20

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
	struct Record* prev;
	struct Record* next;
};
struct Record* headList = NULL;

struct Record* searchItem(const char name[20]) {
	struct Record* tmp;
	tmp = headList;
	while (strcmp(name, tmp->name)) {
		tmp = tmp->next;
		if (tmp == NULL)
			break;
	}
	return tmp;
}

void addItem(const char name[20], int freq, int ram, const char type[20], struct Date date) {
	struct Record* tmp;
	if (headList == NULL) { // Список пуст, первый элемент
		headList = new Record;
		strcpy_s(headList->name, name);
		headList->freq = freq;
		headList->ram = ram;
		strcpy_s(headList->type, type);
		headList->date = date;
		headList->next = NULL;
		headList->prev = NULL;
	}
	else {
		tmp = headList;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new Record;
		strcpy_s(tmp->next->name, name);
		tmp->next->freq = freq;
		tmp->next->ram = ram;
		strcpy_s(tmp->next->type, type);
		tmp->next->date = date;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}
}

void insertBeforeItem(const char searchName[20], const char name[20], int freq, int ram, const char type[20], struct Date date) {
	struct Record* tmp;
	struct Record* nexttmp;
	struct Record* prevtmp;
	tmp = searchItem(searchName);
	if (tmp == NULL)
		return;
	nexttmp = tmp->next;
	prevtmp = tmp->prev;
	tmp->prev = new Record;
	strcpy_s(tmp->prev->name, name);
	tmp->prev->freq = freq;
	tmp->prev->ram = ram;
	strcpy_s(tmp->prev->type, type);
	tmp->prev->date = date;
	tmp->prev->next = tmp;
	if (prevtmp == NULL) {
		tmp->prev->prev = NULL;
		headList = tmp->prev;
	}
	else {
		tmp->prev->prev = prevtmp;
		tmp->prev->prev->next = tmp->prev;
	}
}

void insertAfterItem(const char searchName[20], const char name[20], int freq, int ram, const char type[20], struct Date date) {
	struct Record* tmp;
	struct Record* nexttmp;
	tmp = searchItem(searchName);
	if (tmp == NULL)
		return;
	nexttmp = tmp->next;
	tmp->next = new Record;
	strcpy_s(tmp->next->name, name);
	tmp->next->freq = freq;
	tmp->next->ram = ram;
	strcpy_s(tmp->next->type, type);
	tmp->next->date = date;
	if (nexttmp == NULL) {
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}
	else {
		tmp->next->next = nexttmp;
		tmp->next->prev = tmp;
		tmp->next->next->prev = tmp->next;
	}
}

void editItem(const char searchName[20], const char setName[20]) {
	struct Record* tmp;
	tmp = searchItem(searchName);
	if (tmp == NULL)
		return;
	strcpy_s(tmp->name, setName);
}

void deleteItem(const char name[20]) {
	struct Record* tmp;
	tmp = searchItem(name);
	if (tmp == NULL) {
		return;
	}
	if (tmp->prev == NULL && tmp->next == NULL)
	{
		delete[]tmp;
		headList = NULL;
	}
	else if (tmp->prev == NULL) {
		tmp->next->prev = NULL;
		headList = tmp->next;
		delete[]tmp;
	}
	else if (tmp->next == NULL) {
		tmp->prev->next = NULL;
		delete[]tmp;
	}
	else {
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete[]tmp;
	}
}

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
	if (year == 0) {
		cout << "00" << year;
	}
	cout << year;
	cout.width(len); cout << " ";
}

void DrawTable(void)
{
	struct Record* tmp;
	tmp = headList;
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
	while (tmp) {
		cout << "|"; cout << left; cout.width(14);
		cout << tmp->name;
		cout << "|"; cout.width(14);
		cout << tmp->freq;
		cout << "|+ "; cout.width(12);
		cout << tmp->ram;
		cout << "|"; cout.width(14);
		cout << tmp->type;
		cout << "|"; cout.width(13);
		printDate(tmp->date.day, tmp->date.month, tmp->date.year, 27);
		cout << "|" << endl;
		tmp = tmp->next;
	}
	cout << internal; cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout << left; cout.width(85); cout << "|Тип: C - CISC-процессор, R - RISC-процессор"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(85); cout.fill('_'); cout << "|" << endl; cout.fill(' ');
}

void DrawTable(struct Record dinList[ARR_SIZE], int rowCount)
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
	for (int i = 0; i < rowCount; i++) {
		cout << "|"; cout << left; cout.width(14);
		cout << dinList[i].name;
		cout << "|"; cout.width(14);
		cout << dinList[i].freq;
		cout << "|+ "; cout.width(12);
		cout << dinList[i].ram;
		cout << "|"; cout.width(14);
		cout << dinList[i].type;
		cout << "|"; cout.width(13);
		printDate(dinList[i].date.day, dinList[i].date.month, dinList[i].date.year, 27);
		cout << "|" << endl;
	}
	cout << internal; cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout << left; cout.width(85); cout << "|Тип: C - CISC-процессор, R - RISC-процессор"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(85); cout.fill('_'); cout << "|" << endl; cout.fill(' ');
}

bool isNumber(const string& s) {
	return !s.empty() && all_of(s.begin(), s.end(), isdigit);
}

int main()
{
	char sDelete[15];
	int g = 0;
	int arinc;
	char artmp[50];
	int max_i;
	struct Record* tmp;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	addItem("Pentium-III", 233, 16, "C", { 10,10,2020 });
	addItem("AMD-K6", 166, 8, "C", { 11,11,2011 });
	addItem("PowerPC-620", 2000, 16, "R", { 10,10,2010 });
	cout << "Исходные данные:";
	DrawTable();

	cout << endl << "Практическая работа № 1 (Удаление элемента структуры с определенным наименованием)";

	cout << endl << endl << "Введите наименование, которое хотите удалить: ";
	cin.getline(sDelete, 20);
	deleteItem(sDelete);
	DrawTable();

	cout << endl << "Практическая работа № 2 (Динамические массивы)";

	struct Record* A;
	while (1) {
		cout << endl << endl << "Введите число записей, которое нужно добавить в массив A (1-" << ARR_SIZE << "): ";
		cin >> artmp;
		if (!isNumber(artmp)) {
			arinc = 0;
		}
		else {
			arinc = atoi(artmp);
		}
		if (arinc > ARR_SIZE || arinc < 1) {
			cout << endl << "Ошибка. Введенное значение является недопустимым.";
		}
		else
			break;
	}
	A = (Record*)malloc(sizeof(Record) * arinc);
	tmp = headList;
	int i = 0;
	while (tmp && (i < arinc)) {
		A[i] = *tmp;
		i++;
		tmp = tmp->next;
	}
	max_i = i;
	DrawTable();

	struct Record* B;
	B = new Record[max_i];
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		B[i] = A[i];
	}
	free(A);
	A = (Record*)malloc(sizeof(Record) * max_i);
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		A[i] = B[i];
	}
	cout << endl << endl << "Вывод адресов первых элементов массивов: ";
	cout << endl << "Адрес первого элемента Records: " << &headList;
	cout << endl << "Адрес первого элемента A: " << &A[0];
	cout << endl << "Адрес первого элемента B: " << &B[0];

	cout << endl << endl << "Вывод таблицы адресов и строковых значений: ";
	cout << endl << "+"; cout.width(66); cout.fill('-'); cout << "+"; cout.fill(' ');
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		cout << endl << "| Адрес A[" << i << "] | " << &A[i] << " | Строкове поле A[" << i << "] | " << A[i].name << setw(20 - strlen(A[i].name)) << " |";
		cout << endl << "| Адрес B[" << i << "] | " << &B[i] << " | Строкове поле B[" << i << "] | " << B[i].name << setw(20 - strlen(B[i].name)) << " |";
	}
	cout << endl << "+"; cout.width(66); cout.fill('-'); cout << "+"; cout.fill(' ');
	free(A); delete[]B;
	cout << endl << endl << "После освобождения памяти: ";
	cout << endl << "Адрес первого элемента Records: " << &headList;
	cout << endl << "Адрес первого элемента A: " << &A[0];
	cout << endl << "Адрес первого элемента B: " << &B[0];
}