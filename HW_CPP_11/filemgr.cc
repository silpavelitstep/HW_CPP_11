#include "filemgr.h"

//Здесь находятся функции переименования и удаления
#include <stdio.h>
//Здесь находятся функции для поиска файлов
#include <iostream>
#include <string.h>
#include <io.h>
#include <fstream>
using namespace std;
#pragma warning(disable:4996)
#define AUTOFILE "ON"

void fileStart() {
#ifndef AUTOFILE
	//предлагаем выбрать пункт меню для выполнения
	cout << "Please, select preffer number...\n";
	//выбор пользователя
	char ch;
	do {
		cout << "\n1 - Rename\n"; //Переименовать
		cout << "2 - Remove\n";   //Удалить
		cout << "3 - View some folder\n"; //Просмотреть некоторую папку(каталог)
		cout << "0 - Exit\n\n"; //Выход
		cin >> ch;
		//анализируем и вызываем соответствующую функцию
		switch (ch) {
		case '1':
			RenameFile();
			break;
			case '2':
			RemoveFile();
			break;
		case '3':
			Dir();
			break;
		}
	} while (ch != '0'); //Выход из программы
#else
	cout << "check create new file , then rename, then create second file, then find, last remove:\n";
	//new file
	fstream f("E:\\first.txt",ios::app); //создать
	if (f) cout << "Ok...\n";
	f.close();
	//rename
	RenameFile();
	//create second file
	f.open("E:\\SsubstrSTst.txt", ios::app); //создать
	if (f) cout << "Ok...\n";
	f.close();
	//find
	Dir();//find "substr"
	//delete
	RemoveFile();




#endif // !AUTOFILE
}

//Переименовать существующий файл
void RenameFile() {
	char oldName[50], newName[50];
#ifndef AUTOFILE
	//В одной переменной запомним существующее имя
	//(oldName),
	cout << "enter old name:";
	cin >> oldName;
	//А в другой новое имя(newName)
	cout << "enter new name:";
	cin >> newName;
#else
	strcpy(oldName, "E:\\first.txt");
	strcpy(newName, "E:\\1substr2.txt");//substr
#endif // !AUTOFILE
	//Произведем переименование и проверку результата
	if (rename(oldName, newName) != 0)
		cerr << "error: Could not rename file. Check old and new filename...\n";
	else
		cout << "Ok...\n";
}

//Удалить существующий файл
void RemoveFile() {
	char Name[50];
#ifndef AUTOFILE
	//Получаем имя и путь к удаляемому файлу
	cout << "enter name:";
	cin >> Name;

	//Удаляем файл и проверяем результат
	if (remove(Name) != 0)
		cout << "error: Could not remove file. Check filename...\n";
	else
		cout << "Ok...\n";
#else
	if (remove("E:\\1substr2.txt") != 0 || remove("E:\\SsubstrSTst.txt") != 0)
		cout << "error: Could not remove file. Check filename...\n";
	else
		cout << "Ok...\n";
#endif // !AUTOFILE
}

//Поиск файлов в каталоге
void Dir() {
	char path[70];
	char mask[15];
#ifndef AUTOFILE
	//Запросим ПУТЬ (например, папка Temp на диске C,
	// запишется таким вот образом: c:\temp\)
	
	cout << "\nEnter full path (for example, C:\\):";
	cin >> path;
	//Запросим маску файлов
	
	cout << "\nEnter mask (for example, *.* or *.txt):";
	cin >> mask;
#else
	strcpy(path, "E:\\");
	strcpy(mask,"*sub*");
#endif // !AUTOFILE
	//Соединив две строки, мы получим результат
	// т.е. что хочет найти пользователь и где
	strcat(path, mask);
	//Объявление указателя fileinfo на структуру _finddata_t
	//и создание динамического объекта структуры _finddata_t
	_finddata_t *fileinfo = new _finddata_t;
	//Начинаем поиск
	long done = _findfirst(path, fileinfo);
	//если done будет равняться -1,
	//то поиск вести бесмысленно
	int MayWeWork = done;
	//Счетчик, содержит информацию о количестве
	//найденых файлов.
	int count = 0;
	while (MayWeWork != -1) {
		count++;
		//Распечатали имя найденного файла
		cout << fileinfo->name << "\n\n";
		//Пытаемся найти следующий файл из группы
		MayWeWork = _findnext(done, fileinfo);
	}
	//Вывод сообщения о количестве найденных файлов.
	cout << "\nInformation: was found " << count;
	cout << " file(s) in folder..." << path << "\n\n";

	//Очистка памяти
	 _findclose(done);
	delete fileinfo;
}
