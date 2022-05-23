// ����� fstream
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
	fs.open(path, ios::in | ios::app); // ����������� 2-� �������.
	// ������� �������� ����� ��� ������ (ios::in), ����� (ios::app) ��� ���������� ������ � �����.
	// ���� �� �������� �������������. ���������� ������� ������� ���� � �������� �������.

	// ������ seekg � seekp:
	// seekg - seek get pointer. �����, ������� ���������� ������ ���������� � ����� ������� �����.
	// seekp - seek put pointer. �����, ������� ���������� ������ ������ � ����� ������� �����.
	// ������ ���������, �.�. ������� �������� �� ���������� �� �������.

	if (fs.is_open())
	{
		cout << "���� ������.\n";
		string str;
		// ������ � ����
		cout << "������� ������:\n";
		getline(cin, str);
		fs << str + "\n";
		cout << "������ ��������� � ����.\n";
		// ���������� �� �����
		fs.seekg(0, ios::beg);
		char sym;
		cout << "���������� �����:\n";
		while (fs.get(sym)) // ����������� ��������� ������ �� �����.
			cout << sym;
	}
	else
		cout << "������ �������� �����.\n";

	fs.close();

	// �������
	cout << "�������.\n������� ������:\n";
	string str;
	getline(cin, str);
	if (fileInput(path, 5, str))
		cout << "������ �������� � ����.\n";
	else
		cout << "������ ���������� �������.\n";
	cout << "\n���������� �����:\n";

	printFile(path);

	// ������ 1
	cout << "������ 1.\n������� �������: ";
	cin >> n;
	cin.ignore();
	cout << "���������� ����� � ������� " << n << ":\n";
	cout << subFile(path, n) << endl;

	// ������ 2
	cout << "������ 2.\n";
	int day = 0, month = 0, year = 0;

	ifstream in; // ����� ������� ���������� �����.
	in.open("date.txt");

	if (in.is_open()) {
		// ������ � ����� 10.01.1970
		string date;
		in >> date;
		day = stoi(date);
		cout << "���� = " << day << endl;
		month = stoi(date.substr(date.find(".") + 1));
		cout << "����� = " << month << endl;
		year = stoi(date.substr(date.rfind(".") + 1));
		cout << "��� = " << year << "\n\n";
	}
	else
		cout << "������ �������� �����.\n";

	in.close();

	// ������ 3
	cout << "������ 3.\n";
	asd(path, false);
		
	return 0;
}
// ������ 1
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
// �������
bool fileInput(string path, int pos, string str) {
	// ��������� �������
	/*ofstream out;
	out.open(path, ios::out | ios::ate);

	if (out.is_open()) {
		out.seekp(pos, ios::beg); // �������� ����� � �������� � ����� ����� � ���������� ������ � ������ �����.
		out << str;
		out.close();
		return true;
	}

	out.close();
	return false;*/
	// ������� �������
	// 1. ������ ����� �����;
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

	// 2. ����������� ����� �����;
	newFile.insert(pos, str);

	// 3. ������� ������ �������� ����� � �� ��� ����� ��������� �����.
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
// ������ 3
void asd(string path, bool a) {
	fstream fs;
	fs.open(path, ios::in | ios::app);

	if (fs.is_open())
		if (a) {
			cout << "���� ������.\n";
			string str;
			// ������ � ����
			cout << "������� ������:\n";
			getline(cin, str);
			fs << str + "\n";
			cout << "������ ��������� � ����.\n";
			fs.close();
		}
	else {
			// ���������� �� �����
			fs.seekg(0, ios::beg);
			char sym;
			cout << "���������� �����:\n";
			while (fs.get(sym)) // ����������� ��������� ������ �� �����.
				cout << sym;
	}
	else
		cout << "������ �������� �����.\n";
	fs.close();
}
// ����� ����������� �����
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