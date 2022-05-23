// Класс fstream
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool printFile(string path);
bool fileInput(string path, int pos, string str);
string subFile(string path, int pos = 0);
void asd(string path, bool a);

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	string path = "file.txt";
	
	fstream fs;
	fs.open(path, ios::in | ios::app); // Объединение 2-х режимов.
	// Сначала открытие файла для записи (ios::in), затем (ios::app) для добавление записи в конец.
	// Файл не создаётся автоматически. Необходимо сначала создать файл в каталоге вручную.

	// Методы seekg и seekp:
	// seekg - seek get pointer. Метод, который перемещает курсор считывания в новую пощицию файла.
	// seekp - seek put pointer. Метод, который перемещает курсор записи в новую позицию файла.
	// Методы идентичны, т.к. задумка создания по назначению не удалась.

	if (fs.is_open())
	{
		cout << "Файл открыт.\n";
		string str;
		// Запись в файл
		cout << "Введите строку:\n";
		getline(cin, str);
		fs << str + "\n";
		cout << "Запись добавлена в файл.\n";
		// Считывание из файла
		fs.seekg(0, ios::beg);
		char sym;
		cout << "Содержимое файла:\n";
		while (fs.get(sym)) // Посимвольно считываем данные из файла.
			cout << sym;
	}
	else
		cout << "Ошибка открытия файла.\n";

	fs.close();

	// Задание
	cout << "Задание.\nВведите строку:\n";
	string str;
	getline(cin, str);
	if (fileInput(path, 5, str))
		cout << "Запись помещена в файл.\n";
	else
		cout << "Ошибка выполнения функции.\n";
	cout << "\nСодержимое файла:\n";

	printFile(path);

	// Задача 1
	cout << "Задача 1.\nВведите позицию: ";
	cin >> n;
	cin.ignore();
	cout << "Содержимое файла с позиции " << n << ":\n";
	cout << subFile(path, n) << endl;

	// Задача 2
	cout << "Задача 2.\n";
	int day = 0, month = 0, year = 0;

	ifstream in; // Чтобы считать содержимое файла.
	in.open("date.txt");

	if (in.is_open()) {
		// Данные в файле 10.01.1970
		string date;
		in >> date;
		day = stoi(date);
		cout << "День = " << day << endl;
		month = stoi(date.substr(date.find(".") + 1));
		cout << "Месяц = " << month << endl;
		year = stoi(date.substr(date.rfind(".") + 1));
		cout << "Год = " << year << "\n\n";
	}
	else
		cout << "Ошибка открытия файла.\n";

	in.close();

	// Задача 3
	cout << "Задача 3.\n";
	asd(path, false);
		
	return 0;
}
// Задача 1
string subFile(string path, int pos) {
	ifstream in;
	in.open(path);

	if (in.is_open()) {
		string res;
		char sym;
		in.seekg(pos, ios::beg);
		while (in.get(sym))
			res += sym;
		in.close();
		return res;
	}

	in.close();
	return "";
}
// Задание
bool fileInput(string path, int pos, string str) {
	// Нерабочий вариант
	/*ofstream out;
	out.open(path, ios::out | ios::ate);

	if (out.is_open()) {
		out.seekp(pos, ios::beg); // Открытие файла с курсором в конце файла и перемещаем курсор в начало файла.
		out << str;
		out.close();
		return true;
	}

	out.close();
	return false;*/
	// Рабочий вариант
	// 1. Создаём копию файла;
	string newFile;

	ifstream copy;
	copy.open(path);

	if (!copy.is_open()) {
		copy.close();
		return false;
	}

	char sym;
	while (copy.get(sym))
		newFile += sym;
	copy.close();

	// 2. Редактируем копию файла;
	newFile.insert(pos, str);

	// 3. Стираем старое значение файла и на его место вставляем новое.
	ofstream out;
	out.open(path);

	if (!out.is_open()) {
		out.close();
		return false;
	}
	out << newFile;
	out.close();
	return true;
}
// Задача 3
void asd(string path, bool a) {
	fstream fs;
	fs.open(path, ios::in | ios::app);

	if (fs.is_open())
		if (a) {
			cout << "Файл открыт.\n";
			string str;
			// Запись в файл
			cout << "Введите строку:\n";
			getline(cin, str);
			fs << str + "\n";
			cout << "Запись добавлена в файл.\n";
			fs.close();
		}
	else {
			// Считывание из файла
			fs.seekg(0, ios::beg);
			char sym;
			cout << "Содержимое файла:\n";
			while (fs.get(sym)) // Посимвольно считываем данные из файла.
				cout << sym;
	}
	else
		cout << "Ошибка открытия файла.\n";
	fs.close();
}
// Вывод содержимого файла
bool printFile(string path) {
	ifstream in;
	in.open(path);

	if (in.is_open()) {
		char sym;
		while (in.get(sym))
			cout << sym;
		in.close();
		return true;
	}

	in.close();
	return false;
}