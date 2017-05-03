
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <cstring>
#include <windows.h>
#include <conio.h>

#define HASHTAB_SIZE 10

using namespace std;

struct actor
{
	string name;
	string surname;
};

struct film
{
	string name;
	actor producer;
	actor actors[5];
	string summary;
	film *next;
};

film *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(string text)
{
	int sum = 0, hash;
	for (int i = 0; i < sizeof(text) / sizeof(string); i++)
		sum += (int)text[i] - (int)'0';
	hash = sum%HASHTAB_SIZE;
	return hash;
}

void hashtab_init(film **hashtab)
{
	for (int i = 0; i < HASHTAB_SIZE; i++)
		hashtab[i] = NULL;
}

void hashtab_add(film **hashtab, string name)
{
	film *node = new film;
	int index = hashtab_hash(name);
	// adding to the begin of list

	if (node != NULL)
	{
		(*node).name = name;
		cout << endl << "������� ��� ��������� " << endl;
		cin >> (*node).producer.name >> (*node).producer.surname;
		cout << endl << "������� 5 ������� " << endl;

		for (int i = 0; i < 5; i++)
		{
			cin >> ((*node).actors[i]).name >> ((*node).actors[i]).surname;
		}

		cout << endl << "���������� ������� ���������� ������" << endl;
		cin.ignore();
		getline(cin, (*node).summary);

		cout << endl;

		node->next = hashtab[index];
		hashtab[index] = node;
	}
}

film *hashtab_lookup(film **hashtab, string text)
{
	int index = hashtab_hash(text);
	film *node;
	for (node = hashtab[index]; node != NULL; node = node->next)
	{
		if (node->name == text)
			return node;
	}
	return NULL;
}

void show(film **hashtab)
{
	cout << "����� ����� �����?" << endl;
	string text;
	cin >> text;
	film *q = hashtab_lookup(hashtab, text);

	if (!q)
		cout << "������ ������ ��� � ������\n";

	if (q)
	{
		cout << endl << "****************************************************************************************" << endl;
		cout << "�� ������� '" << text << "' �������: " << endl;
		cout << "�������� : " << hashtab[hashtab_hash(text)]->producer.name << " " << hashtab[hashtab_hash(text)]->producer.surname << endl;
		cout << "� ������ ��������� : | ";
		for (int i = 0; i < 5; i++)
			cout << hashtab[hashtab_hash(text)]->actors[i].name << " " << hashtab[hashtab_hash(text)]->actors[i].surname << " | ";
		cout << endl << "������� ���������� ������ : " << hashtab[hashtab_hash(text)]->summary << endl;
		cout << "****************************************************************************************" << endl;
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hashtab_init(hashtab);

	cout << "����� �������� ���������?" << endl << "1. �������� ������� � �������." << endl << "2. ����� ���������� � ������." << endl << "3. ��������� ���������." << endl;
	int command;
	cin >> command;

	while (command != 3)
	{
		if (command == 1)
		{
			cout << "������� �������� ������." << endl;
			string text;
			cin >> text;
			hashtab_add(hashtab, text);
			cout << endl << "������� �������" << endl;
			cin >> command;
		}

		if (command == 2)
		{
			show(hashtab);
			cout << "������� �������" << endl;
			cin >> command;
		}
	}

	system("PAUSE");
	return 0;
}


