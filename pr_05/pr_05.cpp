#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#define ARR_SIZE 20

using namespace std;
char FDB[20] = "Database.txt";
char BDB[20] = "Database.bin";
class RecordClass* Records;

class DateClass {
private:
	unsigned short day;
	unsigned short month;
	unsigned short year;
	const int days_in_month[13] = {31,28,31,30,31,30,31,31,30,31,30,31};

	// Проверка корректности введенных данных
	bool check_date(unsigned short _day, unsigned short _month, unsigned short _year) {
		if (_year > 0 && _year < 9999) {
			if (_month > 0 && _month < 13) {
				if (_month == 2) {
					int feb = (_year % 4 == 0 && _year % 100 != 0) ? 29 : 28;
					if (_day > 0 && _day <= feb) {
						return true;
					}
				}
				else if (_day > 0 && _day <= days_in_month[_month - 1]) {
					return true;
				}
			}
		}
		return false;
	}
	// проверка корректности дня, если нужно поменять ГОД (возможно в новом году 28, а не 29 дней февраля)
	bool check_day(unsigned short _day) {
		if (month == 2) {
			int feb = (year % 4 == 0 && year % 100 != 0) ? 29 : 28;
			if (_day > 0 && _day <= feb) {
				return true;
			}
		}
		else if (_day > 0 && _day <= days_in_month[month - 1]) {
			return true;
		}
		return false;
	}

public:
	DateClass() {
		day = 0;
		month = 0;
		year = 0;
	}

	DateClass(unsigned short _day, unsigned short _month, unsigned short _year) {
		if (check_date(_day, _month, _year)) {
			day = _day;
			month = _month;
			year = _year;
		};
	}
	// Дата правильная?
	bool is_valid(unsigned short _day, unsigned short _month, unsigned short _year) {
		return check_date(_day, _month, _year);
	}

	// Получение данных
	unsigned short getDay() {
		return day;
	}
	unsigned short getMonth() {
		return month;
	}
	unsigned short getYear() {
		return year;
	}
	auto getDate() {
		return to_string(day) + "." + to_string(month) + "." + to_string(year);
	}

	// Установка данных
	void setDay(int _day) {
		if (check_date(_day, month, year)) {
			day = _day;
		}
	}
	void setMonth(int _month) {
		if (check_date(day, _month, year)) {
			month = _month;
		}
	}
	void setYear(int _year) {
		if (check_date(day, month, _year)) {
			year = _year;
		}
	}

	void setDate(int _day, int _month, int _year) {
		if (check_date(_day, _month, _year)) {
			day = _day;
			month = _month;
			year = _year;
		};
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

	void operator = (const DateClass &other) {
		setDate(other.day, other.month, other.year);
	}
};

class RecordClass {
private:
	string name;
	int freq;
	int ram;
	string type;
	class DateClass date;
	class RecordClass* prev;
	class RecordClass* next;

public:
	RecordClass(string _name, int _freq, int _ram, string _type, class DateClass _date, class RecordClass* _prev = NULL) {
		name = _name;
		freq = _freq;
		ram = _ram;
		type = _type;
		date = _date;
		prev = _prev;
		next = NULL;
	}

	RecordClass() {
		name = "";
		freq = 0;
		ram = 0;
		type = "";
		date = DateClass();
		prev = NULL;
		next = NULL;
	}

	void addItem(string _name, int _freq, int _ram, string _type, class DateClass _date) {
		RecordClass* temp;
		temp = this;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new RecordClass(_name, _freq, _ram, _type, _date, temp);
		temp->next->next = NULL;
	}

	class RecordClass* searchItem(string _name) {
		RecordClass* temp;
		temp = this;
		while (_name.compare(temp->name)) {
			temp = temp->next;
			if (temp == NULL)
				break;
		}
		return temp;
	}

	void editItem(string _searchName, string _setName) {
		class RecordClass* temp;
		temp = searchItem(_searchName);
		if (temp == NULL)
			return;
		temp->name.assign(_setName);
	}

	void deleteItem(string _name) {
		class RecordClass* temp;
		temp = searchItem(_name);
		if (temp == NULL) {
			return;
		}
		if (temp->prev == NULL && temp->next == NULL)
		{
			delete temp;
		}
		else if (temp->prev == NULL) {
			temp->next->prev = NULL;
			Records = temp->next;
			delete temp;
		}
		else if (temp->next == NULL) {
			temp->prev->next = NULL;
			delete temp;
		}
		else {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
	}

	void insertBeforeItem(string _searchName, string _name, int _freq, int _ram, string _type, class DateClass _date) {
		class RecordClass* tmp;
		class RecordClass* nexttmp;
		class RecordClass* prevtmp;
		class RecordClass* first;
		first = this->getFirst();
		tmp = searchItem(_searchName);
		if (tmp == NULL)
			return;
		nexttmp = tmp->next;
		prevtmp = tmp->prev;
		tmp->prev = new RecordClass(_name, _freq, _ram, _type, _date);
		tmp->prev->name.assign(_name);
		tmp->prev->freq = _freq;
		tmp->prev->ram = _ram;
		tmp->prev->type.assign(_type);
		tmp->prev->date = _date;
		tmp->prev->next = tmp;
		if (prevtmp == NULL) {
			tmp->prev->prev = NULL;
			first = tmp->prev;
		}
		else {
			tmp->prev->prev = prevtmp;
			tmp->prev->prev->next = tmp->prev;
		}
	}

	void insertAfterItem(string _searchName, string _name, int _freq, int _ram, string _type, class DateClass _date) {
		class RecordClass* tmp;
		class RecordClass* nexttmp;
		tmp = searchItem(_searchName);
		if (tmp == NULL)
			return;
		nexttmp = tmp->next;
		tmp->next = new RecordClass(_name, _freq, _ram, _type, _date);
		tmp->next->name.assign(_name);
		tmp->next->freq = _freq;
		tmp->next->ram = _ram;
		tmp->next->type.assign(_type);
		tmp->next->date = _date;
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
	
	class RecordClass* getFirst() {
		return this;
	}

	string getName() {
		return name;
	}

	int getFreq() {
		return freq;
	}

	int getRAM() {
		return ram;
	}

	string getType() {
		return type;
	}

	void setName(string _name) {
		name = _name;
	}

	void setFreq(int _freq) {
		freq = _freq;
	}

	void setRAM(int _ram) {
		ram = _ram;
	}

	void setDate(class DateClass _date) {
		date = _date;
	}

	void setType(string _type) {
		type = _type;
	}

	void setPrev(class RecordClass* _prev) {
		prev = _prev;
	}

	void setNext(class RecordClass* _next) {
		next = _next;
	}

	class DateClass getDate() {
		return date;
	}

	class RecordClass* getNext() {
		return next;
	}

	class RecordClass* getPrev() {
		return prev;
	}
};

void DrawTable(void)
{
	class RecordClass* temp;
	class DateClass tmp;
	temp = Records->getFirst();
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
	while (temp) {
		tmp = temp->getDate();
		cout << "|"; cout << left; cout.width(14);
		cout << temp->getName();
		cout << "|"; cout.width(14);
		cout << temp->getFreq();
		cout << "|+ "; cout.width(12);
		cout << temp->getRAM();
		cout << "|"; cout.width(14);
		cout << temp->getType();
		cout << "|"; cout.width(15);
		tmp.printDate(tmp.getDay(), tmp.getMonth(), tmp.getYear(), 26);
		cout << "|" << endl;
		temp = temp->getNext();
	}
	cout << internal; cout << "|"; cout.width(85); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
	cout << left; cout.width(85); cout << "|Тип: C - CISC-процессор, R - RISC-процессор"; cout << "|" << endl;
	cout << internal; cout << "|"; cout.width(85); cout.fill('_'); cout << "|" << endl; cout.fill(' ');
}

void DrawTable(class RecordClass dinList[ARR_SIZE], int rowCount)
{
	class DateClass tmp;
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
		tmp = dinList[i].getDate();
		cout << "|"; cout << left; cout.width(14);
		cout << dinList[i].getName();
		cout << "|"; cout.width(14);
		cout << dinList[i].getFreq();
		cout << "|+ "; cout.width(12);
		cout << dinList[i].getRAM();
		cout << "|"; cout.width(14);
		cout << dinList[i].getType();
		cout << "|"; cout.width(13);
		tmp.printDate(tmp.getDay(), tmp.getMonth(), tmp.getYear(), 26);
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
	FILE* textFile;
	FILE* binaryFile;
	char sDelete[15];
	int g = 0;
	int arinc;
	char artmp[50];
	int max_i;
	class DateClass date;
	class RecordClass* tmp;
	class RecordClass readRecords;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Records = new RecordClass("Pentium-III", 233, 16, "C", { 10,10,2020 });
	Records->addItem("AMD-K6", 166, 8, "C", { 11,11,2011 });
	Records->addItem("PowerPC-620", 2000, 16, "R", { 10,10,2010 });
	fopen_s(&textFile, FDB, "w+t");
	fopen_s(&binaryFile, BDB, "w+b");
	tmp = Records;
	while (tmp) {
		date = tmp->getDate();
		fprintf_s(textFile, "%s %d %d %s %hd %hd %hd\n", tmp->getName().c_str(), tmp->getFreq(), tmp->getRAM(), tmp->getType().c_str(), date.getDay(), date.getMonth(), date.getYear());
		fwrite(tmp, sizeof(RecordClass), 1, binaryFile);
		tmp = tmp->getNext();
	}
	fclose(textFile);
	fclose(binaryFile);
	cout << "Исходные данные:";
	DrawTable();

	cout << endl << "Практическая работа № 1 (Удаление элемента структуры с определенным наименованием)";

	cout << endl << endl << "Введите наименование, которое хотите удалить: ";
	cin.getline(sDelete, 20);
	Records->deleteItem(sDelete);
	DrawTable();

	cout << endl << "Практическая работа № 2 (Динамические массивы)";

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
	class RecordClass* A{ new RecordClass[arinc] };
	tmp = Records;
	int i = 0;
	while (tmp && (i < arinc)) {
		A[i].setName(tmp->getName());
		A[i].setFreq(tmp->getFreq());
		A[i].setRAM(tmp->getRAM());
		A[i].setType(tmp->getType());
		A[i].setDate(tmp->getDate());
		i++;
		tmp = tmp->getNext();
	}
	max_i = i;
	DrawTable(A, arinc);

	class RecordClass* B{ new RecordClass[max_i] };
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		B[i] = A[i];
	}
	delete[]A;
	A = { new RecordClass[max_i] };
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		A[i] = B[i];
	}
	cout << endl << endl << "Вывод адресов первых элементов массивов: ";
	cout << endl << "Адрес первого элемента Records: " << &Records;
	cout << endl << "Адрес первого элемента A: " << &A[0];
	cout << endl << "Адрес первого элемента B: " << &B[0];

	cout << endl << endl << "Вывод таблицы адресов и строковых значений: ";
	cout << endl << "+"; cout.width(74); cout.fill('-'); cout << "+"; cout.fill(' ');
	for (int i = 0; (i < max_i) && (i < 10); i++) {
		cout << endl << "| Адрес A[" << i << "] | " << &A[i] << " | Строкове поле A[" << i << "] | " << A[i].getName() << setw(20 - A[i].getName().length()) << " |";
		cout << endl << "| Адрес B[" << i << "] | " << &B[i] << " | Строкове поле B[" << i << "] | " << B[i].getName() << setw(20 - B[i].getName().length()) << " |";
	}
	cout << endl << "+"; cout.width(74); cout.fill('-'); cout << "+"; cout.fill(' ');
	delete[]A; delete[]B;
	cout << endl << endl << "После освобождения памяти: ";
	cout << endl << "Адрес первого элемента Records: " << &Records;
	cout << endl << "Адрес первого элемента A: " << &A[0];
	cout << endl << "Адрес первого элемента B: " << &B[0];

	cout << endl << endl << "Практическая работа № 4 (Работа с файлами)";

	/*fopen_s(&textFile, FDB, "rt");
	fopen_s(&binaryFile, BDB, "rb");
	char temp[20];
	date = readRecords.getDate();
	while (!feof(textFile)) {
		fscanf_s(textFile, "%s", readRecords.getName(), _countof(readRecords.getName()));
		fscanf_s(textFile, "%d", readRecords.getFreq());
		fscanf_s(textFile, "%d", readRecords.getRAM());
		fscanf_s(textFile, "%s", readRecords.getType(), _countof(readRecords.getType()));
		fscanf_s(textFile, "%hd", date.getDay());
		fscanf_s(textFile, "%hd", date.getMonth());
		fscanf_s(textFile, "%hd\n", date.getYear());

		snprintf(temp, 20, "%s-t", readRecords.getName());
		readRecords.addItem(
			temp,
			readRecords.getFreq(),
			readRecords.getRAM(),
			readRecords.getType(),
			{ readRecords.date.day,
			readRecords.date.month,
			readRecords.date.year });

		fread(&readRecords, sizeof(RecordClass), 1, binaryFile);
		snprintf(temp, 20, "%s-b", readRecords.getName());
		readRecords.addItem(
			temp,
			readRecords.freq,
			readRecords.ram,
			readRecords.type,
			{ readRecords.date.day,
			readRecords.date.month,
			readRecords.date.year });
	}
	fclose(textFile);
	fclose(binaryFile);
	DrawTable();*/
}