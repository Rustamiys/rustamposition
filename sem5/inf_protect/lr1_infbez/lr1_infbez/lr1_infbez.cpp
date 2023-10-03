#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const int n = 256;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string key;
	unsigned char word_ch;
	unsigned char key_ch;
	string file_name_read;
	string file_name_load;
	int number;

	while (true) {
		cout << "1. Кодирование" << endl << "2. Декодирование" << endl
			<< "0. Закончить программу" << endl;
		cout << "Выберите число : ";
		cin >> number;
		cin.clear();
		cin.ignore(1024, '\n');
		if (number==1 || number==2)
		{
			file_name_load.clear();
			file_name_read.clear();
			cout << "Input read filename : ";
			getline(cin, file_name_read);
			cout << "Input load filename : ";
			getline(cin, file_name_load);
			cout << "Ключ: ";
			getline(cin, key);

			ifstream ining(file_name_read, ios::binary);
			ofstream outing(file_name_load, ios::binary);

			if (ining.is_open() && outing.is_open())
			{
				unsigned char ch;
				unsigned char key_ch;
				char curr_char;
				int cnt = 0;
				while (!ining.eof() && ining.get(curr_char))
				{
					key_ch = unsigned char(key[cnt % key.size()]);
					ch = unsigned char((n + int(pow(-1, number))*int(key_ch) + int(unsigned char(curr_char))) % n);
					outing << ch;
				}
			}

			outing.close();
			ining.close();
		}
		else {
			return 0;
		}
	}
}
