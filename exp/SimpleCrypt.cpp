#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define CSIZE 256

using namespace std;


void initLetters(char** &base)
{
	char abv[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	char abc[] = "abcdefghjklmnopqrstuvwxyz";

	base = new char*[2];

	base[0] = new char[strlen(abv) + 1];
	base[1] = new char[strlen(abc) + 1];

	strcpy(base[0], abv);
	strcpy(base[1], abc);
}

struct Crypt
{
	FILE* file;
	int size;
	char* text;
};

template <typename T>
bool removeElement(T* &arr, int &size, int id)
{
	if (size == 0)
		return false;

	if (size == 1 && id == 0)
	{
		delete[] arr;
		size--;
		return true;
	}

	T* newArr = new T[size - 1];
	if (id < 0 || id > size - 1) return false;
	for (int i = 0, k = 0; i < size; i++)
	{
		if (i != id)
			newArr[k++] = arr[i];
	}
	size--;
	delete[] arr;
	arr = newArr;
	return true;
}

template <typename T>
void addElement(T* &arr, int &size, T elem)
{
	if (size == 0)
	{
		T* newArr = new T[++size];
		newArr[0] = elem;
		arr = newArr;
		return;
	}

	T* newArr = new T[++size];
	for (int i = 0; i < size - 1; i++)
	{
		newArr[i] = arr[i];
	}
	newArr[size - 1] = elem;

	delete[] arr;
	arr = newArr;
	return;
}

template <typename T>
void delete2d(T** arr, int size)
{
	for (int i = 0; i < size; i++)
		delete[] arr[i];

	delete[] arr;
}

bool isNum(char* num)
{
	if (num == NULL) return false;
	if (strcmp("0", num) && !atoi(num)) return false;
	return true;
}

void readFile(char* &command, Crypt &crypt)
{
	if (crypt.file) fclose(crypt.file);
	if (crypt.size>0) delete[] crypt.text;
	crypt.size = 0;

	crypt.file = fopen(command, "r");
	if (!crypt.file)
	{
		cout << "Wrong Name" << endl;
		return;
	}
	char symb;
	while (!feof(crypt.file))
	{
		symb = (char)fgetc(crypt.file);
		addElement(crypt.text, crypt.size, symb);
	}
	fclose(crypt.file);
	cout << "File readed" << endl;

}

void saveFile(char* &command, Crypt &crypt)
{
	if (crypt.file) fclose(crypt.file);

	crypt.file = fopen(command, "w");
	if (!crypt.file) return;
	fputs(crypt.text,crypt.file);
	fclose(crypt.file);
	cout << "File saved" << endl;

}

char cryptChar(char symb,char** base, int key)
{
	int index;
	for (int i = 0; i < 2; i++)
	{
		int size = strlen(base[i]);
		for (int j = 0; j < size; j++)
		{
			if (symb == base[i][j])
			{
				if (key > 0)
				for (int k = 0; k < key; k++)
				{
					j++;
					if (j>size-1) j= 0;
				}
				else
				for (int k = 0; k < abs(key); k++)
				{
					j--;
					if (j<0) j = size-1;
				}
				return base[i][j];
			}
		}
	}
	return symb;
}

void cryptFile(int key, char** base, Crypt &crypt)
{

	int len = strlen(crypt.text);
	for (int i = 0; i < len-1; i++)
	{
		crypt.text[i] = cryptChar(crypt.text[i], base, key);
	}
}

bool isActive = 1;

void command(char* command, char** base, Crypt &crypt)
{
	command = strtok(command, " ");
	if (!command) return;
	if (!strcmp(command, "read"))
	{
		command = strtok(NULL, " ");
		if (command)
		readFile(command, crypt);
		return;
	}

	if (!strcmp(command, "save"))
	{
		command = strtok(NULL, " ");
		if (command)
			saveFile(command, crypt);
		return;
	}

	if (!strcmp(command, "crypt"))
	{
		command = strtok(NULL, " ");
		if (!isNum(command))
		{
			cout << "Wrong code" << endl;
			return;
		}
		int key = atoi(command);
		if (command)
			cryptFile(key, base, crypt);
		return;
	}
	if (!strcmp(command, "decrypt"))
	{
		command = strtok(NULL, " ");
		if (!isNum(command))
		{
			cout << "Wrong code" << endl;
			return;
		}
		int key = atoi(command);
		if (command)
			cryptFile(-key, base, crypt);
		return;
	}
	if (!strcmp(command, "help"))
	{
		cout << "read \"filename\"" << endl;
		cout << "save \"filename\"" << endl;
		cout << "crypt key" << endl;
		cout << "decrypt key" << endl;
		return;
	}

	if (!strcmp(command, "exit"))
	{
		isActive = false;
		return;
	}


	cout << "Wrong command" << endl;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char** abc;
	Crypt crypt;
	crypt.file = 0;
	crypt.size = 0;
	crypt.text = 0;
	initLetters(abc);
	char input[CSIZE];

	while (isActive)
	{
		//cout << cryptChar(_getch(), abc, 3) << endl;
		cin.getline(input, CSIZE);
		if (command)
		{
			_strlwr(input);
			command(input, abc, crypt);
		}
		
	}
	delete2d(abc, 2);
}
