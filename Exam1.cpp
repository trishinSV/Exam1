// Exam1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cstdlib>
#include <locale.h>
#include <iostream>
#include <string>
#include <iomanip>
//#include <sstream>
using namespace std;

struct list
{
	char surname[32];
	char name[16];
	char secondname[16];
	char year[16];
	char phone[16];
	char region[32];
};
typedef struct list DataType;


struct Notes
{
	DataType data;
	struct Notes * next;
};
typedef struct Notes * notes;

DataType input(void);
notes read_file(char * filename, notes begin);
notes add(notes begin, DataType list);
notes del(notes begin);
void delete_notes(notes begin);
void write_file(char * filename, notes begin);
void write_fileAS(notes begin);
void print1(notes pos);
void edit(notes begin);
void show(notes begin);
DataType input_m(void);

DataType lastAdded;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	char file[300];
	char menu;
	notes sked = NULL;
	if (argc != 2)
	{
		puts("Введите имя файла данных: ");
		gets_s(file);
	}
	else strcpy_s(file, argv[1]);
	sked = read_file(file, sked);
	do {
		system("cls");
		puts("1. Вывод полного списка");
		puts("2. Сохранить");
		puts("3. Сохранить как");
		puts("4. Добавление записи");
		puts("5. Редактирование записи");
		puts("6. Удаление записи");
		puts("7. Отменить");
		puts("8. Выход");
		menu = getchar();
		switch (menu) {
		case '1': show(sked); break;
		case '2': {
			system("cls");
			write_file(file, sked);
			cout << "Сохранение прошло успешно\n";
			system("pause");
			break;
		}
		case '3': write_fileAS(sked); break;
		case '4': sked = add(sked, input_m()); break;
		case '5': edit(sked); break;
		case '6': sked = del(sked); break;
		case '7': {	system("cls");
			sked = NULL;
			sked = read_file(file, sked);
			cout << "Отмена прошла успешно\n";
			system("pause");
			break;
		}
		default: break;
		}
	} while (menu != '8');
	delete_notes(sked);
	return 0;
}

DataType input(void)
{
	DataType sked;
	fflush(stdin);
	system("cls");
	printf("Введите фамилию: ");
	cin >> sked.surname;
	printf("Введите имя: ");
	cin >> sked.name;
	printf("Введите отчество: ");
	cin >> sked.secondname;
	printf("Введите год рождения:");
	cin >> sked.year;
	printf("Введите телефон: ");
	cin >> sked.phone;
	printf("Введите регион: ");
	cin >> sked.region;
	return sked;
}

DataType input_m(void)
{
	char ch;
	char ch2;
	char temp[256];
	string title2;
	DataType sked;
	fflush(stdin);
	system("cls");

	printf("Введите фамилию:");
	cin >> sked.surname;
	cin.get();

	printf("Введите имя:");
	cin >> sked.name;
	cin.get();

	cout << "Введите отчество: ";
	getline(cin, title2);
	if (title2.empty()) {
		strcpy_s(sked.secondname, "null");
	}
	else {
		strcpy_s(sked.secondname, title2.c_str());
	}
	title2.clear();

	printf("Введите год рождения:");
	getline(cin, title2);
	if (title2.empty()) {
		strcpy_s(sked.year, "null");
	}
	else {
		strcpy_s(sked.year, title2.c_str());
	}
	title2.clear();

	cout << "Введите телефон:";
	getline(cin, title2);
	if (title2.empty()) {
		strcpy_s(sked.phone, "null");
	}
	else {
		strcpy_s(sked.phone, title2.c_str());
	}
	title2.clear();

	printf("Введите регион:");
	getline(cin, title2);
	if (title2.empty()) {
		strcpy_s(sked.region, "null");
	}
	else {
		strcpy_s(sked.region, title2.c_str());
	}
	title2.clear();
	return sked;
}
notes add(notes end, DataType list)
{
	notes temp;
	if (end == NULL)
	{
		end = new struct Notes;
		temp = end;
	}
	else
	{
		temp = end;
		while (temp->next) temp = temp->next;
		temp->next = new struct Notes;
		temp = temp->next;
	}
	temp->data = list;
	temp->next = NULL;
	return end;
}

notes read_file(char * filename, notes begin)
{
	FILE * f;
	DataType label;
	fopen_s(&f, filename, "rb");
	if (f == NULL)
	{
		perror("Error open file");
		getchar();
		return begin;
	}
	while (fread(&label, sizeof(label), 1, f))
		begin = add(begin, label);
	fclose(f);
	return begin;
}
void delete_notes(notes begin)
{
	notes temp = begin;
	while (temp)
	{
		begin = temp->next;
		free(temp);
		temp = begin;
	}
}

void write_file(char * filename, notes begin)
{
	FILE * f;
	fopen_s(&f, filename, "w+b");
	if (f == NULL)
	{
		perror("Error create file");
		system("pause");
		return;
	}

	while (begin)
	{
		fwrite(&begin->data, sizeof(DataType), 1, f);
		begin = begin->next;
	}
	fclose(f);
}
void write_fileAS(notes begin)
{
	system("cls");
	FILE * f;
	cout << "Введите имя файла\n";
	char  filename[10];
	cin >> filename;
	fopen_s(&f, filename, "w+b");
	if (f == NULL)
	{
		perror("Error create file");
		system("pause");
		return;
	}
	else {
		cout << "Файл успешно создан" << endl;
		system("pause");
	}
	while (begin)
	{
		fwrite(&begin->data, sizeof(DataType), 1, f);
		begin = begin->next;
	}
	fclose(f);
}
void print1(notes begin) {
	cout << "Фамилия: " << setw(10) << begin->data.surname << " | "
		<< "Имя: " << setw(10) << begin->data.name << " | "
		<< "Отчество: " << setw(14) << begin->data.secondname << " | "
		<< "Год рождения: " << setw(4) << begin->data.year << " | "
		<< "Телефон: " << setw(12) << begin->data.phone << " | "
		<< "Регион: " << setw(16) << begin->data.region;
	cout << "\n";
}

void edit(notes begin)
{
	int n = 1, z = 0;
	char yes, name[21];

	system("cls");
	fflush(stdin);
	if (begin == NULL)
	{
		puts("Список пуст!");
		system("pause");
		return;
	}
	printf("Введите имя человека: ");
	cin >> name;
	while (begin) {
		if (!strcmp(begin->data.name, name)) {
			z++;
			printf("\n   Запись №%d\n", z);
			puts("———————————————————————————————");
			print1(begin);
			puts("Редактировать? (y/n)");
			do
				yes = getchar();
			while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
			if (yes == 'y' || yes == 'Y')
			{
				begin->data = input_m();
				n = 0;
			}
		}
		begin = begin->next;
	}
	if (!z) puts("Такой человек не найден!");
	else if (!n) puts("Данные успешно изменены!");
	else  puts("Данные не были изменены!");
	system("pause");
}

void show(notes begin)
{
	int k = 0, u = 0;
	notes pos = begin;
	system("cls");
	if (begin == NULL)
	{
		puts("Список пуст");
		system("pause");
		return;
	}
	system("cls");
	while (begin) {
		cout << setw(2) << ++k << " | "
			<< "Фамилия: " << setw(10) << begin->data.surname << " | "
			<< "Имя: " << setw(10) << begin->data.name << " | "
			<< "Отчество: " << setw(14) << begin->data.secondname << " | "
			<< "Год рождения: " << setw(4) << begin->data.year << " | "
			<< "Телефон: " << setw(12) << begin->data.phone << " | "
			<< "Регион: " << setw(16) << begin->data.region;
		cout << "\n";
		begin = begin->next;
	}
	system("pause");
}
notes del(notes begin)
{
	int n = 0, z = 0, p = 0, w = 0;
	char yes, name[21];
	notes temp, temp1, cur;
	system("cls");
	fflush(stdin);
	if (begin == NULL)
	{
		puts("Список пуст!");
		system("pause");
		return begin;
	}
	cur = begin;
	printf("Введите имя человека: ");
	cin >> name;
	temp1 = begin;
	while (temp1) {
		if (!strcmp(temp1->data.name, name)) w++;
		temp1 = temp1->next; p++;
	}
	if (!w) {
		puts("Такой человек не найден!");
		system("pause");
		return cur;
	}
	temp1 = begin;
	while (begin) {
		if (n<p - 1)temp1 = temp1->next;
		n++;
		if ((!strcmp(begin->data.name, name)) && n == 1) {
			z++;
			printf("\n   Запись №%d\n", z);
			puts("———————————————————————————————");
			print1(begin);
			puts("Удалить? (y/n)");
			do
				yes = getchar();
			while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
			if (yes == 'y' || yes == 'Y')
			{
				temp = begin;
				begin = begin->next;
				free(temp);
				puts("\nДанные успешно удалены!");
				system("pause");
				return begin;
			}
		}
		if (!strcmp(temp1->data.name, name) && n<p) {
			z++;
			printf("\n   Запись №%d\n", z);
			puts("———————————————————————————————");
			print1(temp1);
			puts("Удалить? (y/n)");
			do
				yes = getchar();
			while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
			if (yes == 'y' || yes == 'Y')
			{
				temp = begin->next;
				begin->next = temp->next;
				free(temp);
				puts("\nДанные успешно удалены!");
				system("pause");
				return cur;
			}
		}
		begin = begin->next;
	}
	return cur;
}