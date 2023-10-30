#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>

using namespace std;

const int n = 256;

vector<int> get_frequency(const vector<unsigned char> text) {
	vector<int> period(n);
	for (auto j : text) {
		period[j]++;
	}
	return period;
}

long float match_index(const vector<unsigned char> text) {
	vector<int> period(n);
	long float sum = 0;
	int m = text.size();
	period = get_frequency(text);
	for (int i = 0; i < n; i++) {
		sum += period[i] * (period[i] - 1);
	}
	return sum / (m * (m - 1));
}

int max_symbol_frequency(const vector<unsigned char> text) {
	int max = 0;
	vector<int> period(n);
	period = get_frequency(text);
	for (int i = 0; i < n; i++)
		if (period[max] < period[i])
			max = i;
	return max;
}

int key_len(const vector<unsigned char> text, const vector<unsigned char> text1) {
	float MIref = match_index(text);
	float sum = 0;
	float max = 1;
	int q = 0;
	int maxLen = 50;
	vector<unsigned char> str;
	for (int i = 1; i < maxLen; i++) {
		for (int k = 0; k < text1.size(); k += i)
			str.push_back(text1[k]);
		sum = match_index(str);
		str.clear();
		
		cout << sum << "\t" << i << endl;
		if (abs(sum - MIref) < max) {
			max = abs(sum-MIref);
			q = i;
		}
		sum = 0;
	}
	cout << MIref << "\t" << q << "\t" << abs(max - MIref) << endl;
	cout << "Key Length: " << q << endl;
	return q;
}

void encrypt(vector<unsigned char> text, vector<unsigned char> text1) {
	string file_name;
	cout << "Файл для выгрузки дешифрованного текста: ";
	getline(cin, file_name);


	int q = key_len(text, text1);

	int max = max_symbol_frequency(text);
	int max1;


	vector<unsigned char> str;
	int shift;

	cout << "Ключ: ";
	for (int j = 0; j < q; j++) {
		for (int k = j; k < text1.size(); k += q)
			str.push_back(text1[k]);
		max1 = max_symbol_frequency(str);

		shift = (n + (max1-max)) % n;
		cout << unsigned char(shift);
		for (int k = j; k < text1.size(); k += q)
			text1[k] = unsigned char (n + int(text1[k]) - shift);

		str.clear();
	}

	cout << endl;

	ofstream out(file_name, ios::binary);
	if (out.is_open())
	{
		for (unsigned char i : text1)
			out << i;
	}
	out.close();
}


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
		cout << "1. Декодирование" << endl << "2. Кодирование" << endl
			<< "3. Декодирование без ключа" << endl << "0. Закончить программу" << endl;
		cout << "Выберите число : ";
		cin >> number;
		cin.clear();
		cin.ignore(1024, '\n');
		if (number == 1 || number == 2)
		{
			file_name_load.clear();
			file_name_read.clear();
			cout << "Input read filename : ";
			getline(cin, file_name_read);
			cout << "Input load filename : ";
			getline(cin, file_name_load);
			cout << "Ключ: ";
			getline(cin, key);

			ifstream in(file_name_read, ios::binary);
			ofstream out(file_name_load, ios::binary);

			if (in.is_open() && out.is_open())
			{
				unsigned char ch;
				unsigned char key_ch;
				char curr_char;
				int cnt = 0;
				while (!in.eof() && in.get(curr_char))
				{
					key_ch = key[cnt % key.size()];
					ch = n + int(pow(-1, number)) * int(key_ch) + int(unsigned char(curr_char));
					out << ch;
					cnt++;
				}
			}
			out.close();
			in.close();
		}
		else if (number == 3) {
			string file_name;
			cout << "Input reference filename : ";
			getline(cin, file_name);
			ifstream in(file_name, ios::binary);
			vector<unsigned char> text;
			vector<char> v((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
			for (auto i : v)
				text.push_back(i);
			file_name.clear();
			in.close();

			cout << "Input encrypted filename : ";
			getline(cin, file_name);
			ifstream in1(file_name, ios::binary);
			vector<unsigned char> text1;
			vector<char> v1((istreambuf_iterator<char>(in1)), istreambuf_iterator<char>());
			for (auto i : v1)
				text1.push_back(i);
			file_name.clear();
			in1.close();

			encrypt(text, text1);
		}
		else {
			return 0;
		}
	}
}