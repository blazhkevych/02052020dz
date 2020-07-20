Лабораторная работа по курсу  «C++»
Тема : Структуры.
Цель : Научиться  применять структуры.
Необходимые инструменты : MS Visual Studio
Документация :
Ориентировочное время исполнения : ? часа.
Требования к отчету : Отчет должен быть оформлен в виде электронного документа : программный код с комментариями, выводы о результатах выполняемых действий и копии экрана.Размер файла отчета до 2 МБ со скриншотами.
Задание :

	Напишите информационную систему "Сотрудники" со следующими требованиями :
-использовать графический интерфейс(пример меню у Вас есть);
-динамическое изменение размеров массива для хранения информации;
-организуйте ввод и вывод данных;
-организуйте сортировку данных по всех полях;
-добавление, изменение и удаление информации о сотрудниках;
-поиск сотрудника;

Данные про сотрудников в информационной системе на украинском языке.
/*
Напишите информационную систему "Сотрудники" со следующими требованиями:
- использовать графический интерфейс (пример меню у Вас есть);
- динамическое изменение размеров массива для хранения информации;
- организуйте ввод и вывод данных;
- организуйте сортировку данных по всех полях;
- добавление, изменение и удаление информации о сотрудниках;
- поиск сотрудника;

Данные про сотрудников в информационной системе на украинском языке.
*/

#include <string.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <algorithm>
using namespace std;
#define MENUTOP 4 
#define MENULEFT 20 
#define BACKGROUND 0                     
#define FOREGROUND 10                         
#define SELECTITEM 13
void gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Color(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
void paintmenu(const char** s, int sizem, int  pm, int left, int top) {
	system("cls");
	gotorc(top, left);
	Color(BACKGROUND, FOREGROUND);
	cout << "-------Menu-------\n";
	for (int i = 0; i < sizem; i++)
	{
		gotorc(top + i + 1, left);
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int  pm = 0, int left = MENULEFT, int top = MENUTOP) {
	char c = 80;
	while (true)
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, pm, left, top);
		c = _getch();
		switch (c)
		{
		case 27: //код кнопки "esc" 27
			return -1;
		case 80: //down
			pm++;
			if (pm == sizem) pm = 0;
			break;
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm;
		}
	}
}
struct employees {
	char PIB[50]{ 0 };
	char position[50]{ 0 };
	int age;
	int postindex;
	double salary;
};
void FillEmploye(employees& person) {
	cout << "Enter PIB: "; cin.getline(person.PIB, 50);
	cout << "Enter position: "; cin.getline(person.position, 50);
	cout << "Enter age: "; cin >> person.age;
	cout << "Enter postindex: "; cin >> person.postindex;
	cout << "Enter salary: "; cin >> person.salary;
}
void AddEmployees(employees*& groupOfEmployees, size_t& n) {
	employees* newgroupOfEmployees = new employees[n + 1];
	memcpy(newgroupOfEmployees, groupOfEmployees, sizeof(employees) * n);
	FillEmploye(newgroupOfEmployees[n]);
	delete[]groupOfEmployees;
	groupOfEmployees = newgroupOfEmployees;
	n++;
}
void Print(employees& person) {
	printf_s("|%-35s|%-15s|%-3d|%-5d|%-10.2lfUAH|\n",
		person.PIB, person.position, person.age,
		person.postindex, person.salary);
}
void PrintGroup(employees* groupOfEmployees, size_t n) {
	cout << "-----------------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < n; i++)
		Print(groupOfEmployees[i]);
	cout << "-----------------------------------------------------------------------------" << endl;
}
void InputGroup(employees* groupOfEmployees, size_t n) {
	for (size_t i = 0; i < n; i++)
	{
		FillEmploye(groupOfEmployees[i]);
		cout << "-----------------------------------------------" << endl;
	}
}
const char** ToString(employees* groupOfEmployees, int n) {
	const char** list = new const char* [n] {0};
	for (size_t i = 0; i < n; i++) {
		char buf[200]{ 0 };
		sprintf(buf, "|%-35s|%-15s|%-3d|%-5d|%-10.2lfUAH|",
			groupOfEmployees[i].PIB, groupOfEmployees[i].position, groupOfEmployees[i].age,
			groupOfEmployees[i].postindex, groupOfEmployees[i].salary);
		list[i] = strdup(buf);
	}
	return list;
}
void Edit(employees* groupOfEmployees, size_t n) {
	const char* Editing_menu[]{
		"Редагувати поле \"Прізвище, ім'я, по батькові\"",
		"Редагувати поле \"Посада\"",
		"Редагувати поле \"Вік\"",
		"Редагувати поле \"Індекс\"",
		"Редагувати поле \"Заробітна плата\""
	};
	int size_of_Editing_menu = sizeof(Editing_menu) / 4;
	int i = 0;
	bool boо = true;
	while (boо)
	{
		i = menu(Editing_menu, size_of_Editing_menu, 0, 2);
		system("cls");
		switch (i)
		{
		case -1:
			boо = false;
			break;
		case 0:
			cout << "Теперішнє \"Прізвище, ім'я, по батькові\" : ";
			cout << groupOfEmployees[n].PIB << endl;
			printf_s("Введіть нові дані : ");
			scanf_s("%s", &groupOfEmployees[n].PIB, 50);
			break;
		case 1:
			cout << "Теперішня \"Посада\" : ";
			cout << groupOfEmployees[n].position << endl;
			printf_s("Введіть нові дані : ");
			scanf_s("%s", &groupOfEmployees[n].position, 50);
			break;
		case 2:
			cout << "Теперішній \"Вік\" : ";
			cout << groupOfEmployees[n].age << endl;
			printf_s("Введіть нові дані : ");
			scanf_s("%d", &groupOfEmployees[n].age);
			break;
		case 3:
			cout << "Теперішній \"Індекс\" : ";
			cout << groupOfEmployees[n].postindex << endl;
			printf_s("Введіть нові дані : ");
			scanf_s("%d", &groupOfEmployees[n].postindex);
			break;
		case 4:
			cout << "Теперішня \"Заробітна плата\" : ";
			cout << groupOfEmployees[n].salary << endl;
			printf_s("Введіть нові дані : ");
			scanf_s("%lf", &groupOfEmployees[n].salary);
			break;
		}
	}
} // не працює нормально
void FindByPIB(employees* groupOfEmployees, size_t n, const char* p_i_b) {
	cout << "\nРезультат пошуку:\n\n";
	int k = 0;
	for (size_t i = 0; i < n; i++)
		if (strstr(_strlwr(strdup(groupOfEmployees[i].PIB)), _strlwr(strdup(p_i_b)))) {
			Print(groupOfEmployees[i]);
			k++;
		}
	if (k) cout << "\nЗнайдено записів : " << k;
	else cout << "За вашим запитом нічого не знайдено";
}
void FindByPosition(employees* groupOfEmployees, size_t n, const char* p_o_s_i_t_i_o_n) {
	cout << "\nРезультат пошуку:\n\n";
	int k = 0;
	for (size_t i = 0; i < n; i++)
		if (strstr(_strlwr(strdup(groupOfEmployees[i].position)), _strlwr(strdup(p_o_s_i_t_i_o_n)))) {
			Print(groupOfEmployees[i]);
			k++;
		}
	if (k) cout << "\nЗнайдено записів : " << k;
	else cout << "За вашим запитом нічого не знайдено";
}
void FindByAge(employees* groupOfEmployees, size_t n) {
	cout << "Пошук по полю \"Вік\"" << endl;
	cout << "Введіть дані для пошуку: ";
	int a_g_e;
	cin >> a_g_e;
	cout << "\nРезультат пошуку:\n\n";
	int k = 0;
	for (size_t i = 0; i < n; i++)
		if (groupOfEmployees[i].age == a_g_e) {
			Print(groupOfEmployees[i]);
			k++;
		}
	if (k) cout << "\nЗнайдено записів : " << k;
	else cout << "За вашим запитом нічого не знайдено";
}
void FindByPostindex(employees* groupOfEmployees, size_t n) {
	cout << "Пошук по полю \"Індекс\"" << endl;
	cout << "Введіть дані для пошуку: ";
	int p_s_t_i_n_d;
	cin >> p_s_t_i_n_d;
	cout << "\nРезультат пошуку:\n\n";
	int k = 0;
	for (size_t i = 0; i < n; i++)
		if (groupOfEmployees[i].postindex == p_s_t_i_n_d) {
			Print(groupOfEmployees[i]);
			k++;
		}
	if (k) cout << "\nЗнайдено записів : " << k;
	else cout << "За вашим запитом нічого не знайдено";
}
void FindBySalary(employees* groupOfEmployees, size_t n) {
	cout << "Пошук по полю \"Заробітна плата\"" << endl;
	cout << "Введіть дані для пошуку: ";
	double s_a_l_a_r_y;
	cin >> s_a_l_a_r_y;
	cout << "\nРезультат пошуку:\n\n";
	int k = 0;
	for (size_t i = 0; i < n; i++)
		if (groupOfEmployees[i].salary == s_a_l_a_r_y) {
			Print(groupOfEmployees[i]);
			k++;
		}
	if (k) cout << "\nЗнайдено записів : " << k;
	else cout << "За вашим запитом нічого не знайдено";
}
typedef bool (*TCMP)(employees, employees);
bool SortByPIBAsc(employees a, employees b) {
	return strcmp(a.PIB, b.PIB) > 0;
}
bool SortByPIBDesc(employees a, employees b) {
	return strcmp(a.PIB, b.PIB) < 0;
}
bool SortByPositionAsc(employees a, employees b) {
	return strcmp(a.position, b.position) > 0;
}
bool SortByPositionDesc(employees a, employees b) {
	return strcmp(a.position, b.position) < 0;
}
bool SortByAgeAsc(employees a, employees b) {
	return a.age > b.age;
}
bool SortByAgeDesc(employees a, employees b) {
	return a.age < b.age;
}
bool SortByPostindexAsc(employees a, employees b) {
	return a.age > b.age;
}
bool SortByPostindexDesc(employees a, employees b) {
	return a.age < b.age;
}
bool SortBySalaryAsc(employees a, employees b) {
	return a.age > b.age;
}
bool SortBySalaryDesc(employees a, employees b) {
	return a.age < b.age;
}

void InsertSort(employees* a, long size, TCMP CMP) {
	employees x;
	long i, j;
	for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
		x = a[i];
		// поиск места элемента в готовой последовательности 
		for (j = i - 1; j >= 0 && CMP(a[j], x); j--)
			a[j + 1] = a[j];  	// сдвигаем элемент направо, пока не дошли
		  // место найдено, вставить элемент
		a[j + 1] = x;
	}
}

int main() {
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	SetConsoleCP(1251); //встановлює потрібну кодову таблицю, на потік введення
	SetConsoleOutputCP(1251); //встановлює потрібну кодову таблицю, на потік виводу.
	size_t	n = 3;
	employees* Data = new employees[n]{
		{"Скороход Ярослав Петрович ", "бухгалтер", 11, 11111, 1111.11},
		{"Щербина Анна Вікторівна ", "секретар", 22, 22222, 2222.22},
		{"Бовсунівський Петро Олександрович ", "юрист", 33, 33333, 3333.33}
	};
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	const char* Main_menu[]{
		"Пошук",
		"Сортування",
		"Редагування",
		"Ввід",
		"Вивід"
	};
	const char* Sorting_menu[]{
		"Сортувати по полю \"Прізвище, ім'я, по батькові\"",
		"Сортувати по полю \"Посада\"",
		"Сортувати по полю \"Вік\"",
		"Сортувати по полю \"Індекс\"",
		"Сортувати по полю \"Заробітна плата\"",
	};
	const char* Searching_menu[]{
		"Пошук по полю \"Прізвище, ім'я, по батькові\"",
		"Пошук по полю \"Посада\"",
		"Пошук по полю \"Вік\"",
		"Пошук по полю \"Індекс\"",
		"Пошук по полю \"Заробітна плата\"",
	};
	const char* SortByABC_menu[]{
			"а, б, ... я",
			"я, ю, ... а"
	};
	const char* SortBy123_menu[]{
			"1, 2, ... 9",
			"9, 8, ... 1"
	};
	int size_of_Main_menu = sizeof(Main_menu) / 4;
	int size_of_Sorting_menu = sizeof(Sorting_menu) / 4;
	int size_of_Searching_menu = sizeof(Searching_menu) / 4;
	int size_of_SortByABC_menu = sizeof(SortByABC_menu) / 4;
	int size_of_SortBy123_menu = sizeof(SortBy123_menu) / 4;
	bool bo = true;
	int pm = 0;
	char temp[50]{ 0 };
	while (true)
	{
		pm = menu(Main_menu, size_of_Main_menu, pm);
		system("cls");
		switch (pm) // Main_menu
		{
		case -1: return 0;
		case 0: // Searching_menu		
			bo = true;
			pm = 0;
			pm = menu(Searching_menu, size_of_Searching_menu, pm);
			system("cls");
			{
				switch (pm)
				{
				case -1:
					bo = false;
					break;
				case 0:
					cout << "Пошук по полю \"Прізвище, ім'я, по батькові\"" << endl;
					cout << "Введіть дані для пошуку: ";
					cin.getline(temp, 50);
					FindByPIB(Data, n, temp);
					break;
				case 1:
					cout << "Пошук по полю \"Посада\"" << endl;
					cout << "Введіть дані для пошуку: ";
					cin.getline(temp, 50);
					FindByPosition(Data, n, temp);
					break;
				case 2: //search by age
					FindByAge(Data, n); // знаходить лише по точному співпадінню
					break;
				case 3: //search by postindex					
					FindByPostindex(Data, n); // знаходить лише по точному співпадінню
					break;
				case 4: //search by salary
					FindBySalary(Data, n); // знаходить лише по точному співпадінню
					break;
				}
				Color(BACKGROUND, 2);
				//cout << "\ndone\n";
				//_getch();
			}
			break;
		case 1: //sorting
			bo = true;
			pm = 0;
			pm = menu(Sorting_menu, size_of_Sorting_menu, pm);
			system("cls");
			{
				switch (pm) {
				case -1:
					bo = false;
					break;
				case 0: // sort by PIB					
					bo = true;
					pm = 0;
					pm = menu(SortByABC_menu, size_of_SortByABC_menu, pm);
					system("cls");
					switch (pm)
					{
					case -1:
						bo = false;
						break;
					case 0: // "a, b, ... z",						
						InsertSort(Data, n, SortByPIBAsc);
						PrintGroup(Data, n);
						break;
					case 1: // "z, y, ... a"
						InsertSort(Data, n, SortByPIBDesc);
						PrintGroup(Data, n);
						break;
					}
					Color(BACKGROUND, 2);
					break;
				case 1: //sort by position
					bo = true;
					pm = 0;
					pm = menu(SortByABC_menu, size_of_SortByABC_menu, pm);
					system("cls");
					switch (pm)
					{
					case -1:
						bo = false;
						break;
					case 0: // "a, b, ... z",						
						InsertSort(Data, n, SortByPositionAsc);
						PrintGroup(Data, n);
						break;
					case 1: // "z, y, ... a"
						InsertSort(Data, n, SortByPositionDesc);
						PrintGroup(Data, n);
						break;
					}
					Color(BACKGROUND, 2);
					break;
				case 2: // sort by age
					bo = true;
					pm = 0;
					pm = menu(SortBy123_menu, size_of_SortBy123_menu, pm);
					system("cls");
					switch (pm) {
					case -1:
						bo = false;
						break;
					case 0: // "1, 2, ... 9"
						InsertSort(Data, n, SortByAgeAsc);
						PrintGroup(Data, n);
						break;
					case 1: // "9, 8, ... 1"
						InsertSort(Data, n, SortByAgeDesc);
						PrintGroup(Data, n);
						break;
					}
					Color(BACKGROUND, 2);
					break;
				case 3: //sort by postindex
					bo = true;
					pm = 0;
					pm = menu(SortBy123_menu, size_of_SortBy123_menu, pm);
					system("cls");
					switch (pm) {
					case -1:
						bo = false;
						break;
					case 0: // "1, 2, ... 9"
						InsertSort(Data, n, SortByPostindexAsc);
						PrintGroup(Data, n);
						break;
					case 1: // "9, 8, ... 1"
						InsertSort(Data, n, SortByPostindexDesc);
						PrintGroup(Data, n);
						break;
					}
					Color(BACKGROUND, 2);
					break;
				case 4: //sort by salary
					bo = true;
					pm = 0;
					pm = menu(SortBy123_menu, size_of_SortBy123_menu, pm);
					system("cls");
					switch (pm) {
					case -1:
						bo = false;
						break;
					case 0: // "1, 2, ... 9"
						InsertSort(Data, n, SortBySalaryAsc);
						PrintGroup(Data, n);
						break;
					case 1: // "9, 8, ... 1"
						InsertSort(Data, n, SortBySalaryDesc);
						PrintGroup(Data, n);
						break;
					}
					Color(BACKGROUND, 2);
					break;
				}
				Color(BACKGROUND, 2);
				//cout << "\ndone\n";
				//_getch();
			}
			break;
		case 2: //editing
		{
			pm = 0;
			const char** list = ToString(Data, n);
			pm = menu(list, n, pm, 0, 1);
			Edit(Data, 1);
			delete[] list;
			system("cls");
		}break;
		case 3: // input
			AddEmployees(Data, n);
			break;
		case 4: //output			
			PrintGroup(Data, n);
			break;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		_getch();
	}
	delete[] Data;
}