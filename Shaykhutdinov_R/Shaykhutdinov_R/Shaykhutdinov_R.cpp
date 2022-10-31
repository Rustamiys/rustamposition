#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <vector>

using namespace std;

void clearBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

template <typename T>
T GetCorrectNumber(string text, T min, T max) {
	cout << text;
	T number;
	cin >> number;
	for (;;) {
		if (cin.fail() || number < min || number > max) {
			clearBuffer();
			cout << "Введите корректные данные(" << min << "-" << max << "): ";
			cin >> number;
		}
		else {
			return number;
		}
	}
}

template <typename T>
using FilterP = bool(*)(const Pipe& p, T parametr);
template <typename T>
vector<int> findPipeByFilter(unordered_map<int, Pipe>& pipes, FilterP<T> f, T parametr){
	vector<int> result;
	for (auto& it : pipes)
	{
		if (f(it.second, parametr))
		{
			result.push_back(it.first);
		}
	}
	return result;
}


bool checkPipeByInRepair(const Pipe& p, bool parametr) {
	return p.getInRepair() == parametr;
}

bool checkPipeByName(const Pipe& p, string parametr) {
	return p.getName() == parametr;
}

template <typename T>
using FilterS = bool(*)(Station& s, T parametr);
template <typename T>
vector <int> findStationByFilter(unordered_map<int, Station>& stations, FilterS<T> f, T parametr) {
	vector <int> result;
	for (auto& it : stations) {
		if (f(it.second, parametr)) {
			result.push_back(it.first);
		}
	}
	return result;
}

bool checkStationByName(Station& s, string parametr) {
	return s.getName() == parametr;
}

bool checkStationByPercent(Station& s, double parametr) {
	return parametr / 100.0 == 1.0 - (double)s.getWorkshopInWork() / (double)s.getWorkshop();
}

ostream& operator << (ostream& out, Pipe& p) {
	out << endl << "Труба" << endl << "Имя: " << p.getName() << endl
		<< "ID: " << p.getId() << endl
		<< "Длина: " << p.getLength() << endl
		<< "Диаметр: " << p.getDiametr() << endl
		<< ((p.getInRepair()) ? "В работе " : "Не в работе") << endl;
	
	return out;
}

istream& operator >> (istream& in, Pipe& p) {
	string name;
	clearBuffer();
	cout << "Имя трубы: ";
	getline(cin, name);
	p.setName(name);
	p.setLength(GetCorrectNumber("Длина: ", 0.1, 3.4E+38));
	p.setDiametr(GetCorrectNumber("Диаметр: ", 0.1, 3.4E+38));
	p.setInRepair((bool)GetCorrectNumber("В работе: ", 0, 1));
	p.idP++;
	p.setId();
	return in;
}

ostream& operator << (ostream& out, Station&s) {
	out << endl << "Компрессорная Станция" << endl << "Имя: " << s.getName() << endl
		<< "ID: " << s.getId() << endl
		<< "Количество цехоы: " << s.getWorkshop() << endl
		<< "Количество цехов в работе: " << s.getWorkshopInWork() << endl
		<< "Эффективность: " << s.getEfficiency() << endl;
	
	return out;
}

istream& operator >> (istream& in, Station&s) {
	string name;
	clearBuffer();
	cout << "Имя станции: ";
	getline(cin, name);
	s.setName(name);
	s.setWorkshop(GetCorrectNumber("Количество цехов: ", 1, 2000000000));
	s.setWorkshopInWork(GetCorrectNumber("Количество цехов работе: ", 0, s.getWorkshop()));
	s.setEfficiency(GetCorrectNumber("Эффективность: ", 0.0, 100.0));
	s.idS++;
	s.setId();
	return in;
}

void printMenu() {
	cout << "1. Добавить трубу." << endl
		 << "2. Добавить КС." << endl
		 << "3. Просмотр всех объектов." << endl
		 << "4. Редактирование труб." << endl
		 << "5. Редактирование КС." << endl
		 << "6. Сохранить." << endl
		 << "7. Загрузить." << endl
		 << "8. Поиск трубы по фильтру." << endl
		 << "9. Поиск КС по фильтру." << endl
		 << "10. Удалить трубу." << endl
		 << "11. Удалить станцию." << endl
		 << "0. Выход." << endl;
}

void editPipe(unordered_map <int, Pipe>& pipes, int id, bool inRepair) {
	pipes[id].setInRepair(inRepair);
}

void deletePipe(unordered_map <int, Pipe>& pipes) {
	if (pipes.size() > 0) {
		int num = GetCorrectNumber("Id трубы которую хотите удалить: ", 1, Pipe::idP);
		for (auto& it : pipes) {
			if (it.first == num) {
				pipes.erase(num);
				cout << "Удалено" << endl;
				break;
			}
			else {
				num = 0;
			}
		}
		if (num == 0) cout << "Трубы с таким id нет" << endl;
	}
	else {
		cout << "Труб нет" << endl;
	}
}

void deleteStation(unordered_map <int, Station>& stations) {
	if (stations.size() > 0) {
		int num = GetCorrectNumber("Id станции которую хотите удалить: ", 1, Station::idS);
		for (auto& it : stations) {
			if (it.first == num) {
				stations.erase(num);
				cout << "Удалено" << endl;
				break;
			}
			else {
				num = 0;
			}
		}
		if (num == 0) cout << "Станции с таким id нет" << endl;
	}
	else {
		cout << "Компрессорных станций нет" << endl;
	}
}



void editStation(unordered_map <int, Station>& stations,int id) {
	cout << "Всего цехов" << stations[id].getWorkshop() << endl << "" << stations[id].getWorkshopInWork() << endl;
	cout << "1. Запуск цехов" << endl << "2. Отключение цехов" << endl;
	switch (GetCorrectNumber("Выберете действие: ", 1, 2))
	{
	case 1:
	{
		stations[id].setWorkshopInWork(stations[id].getWorkshopInWork() + GetCorrectNumber("Количество цехов: ", 0, stations[id].getWorkshop() - stations[id].getWorkshopInWork()));
	}
	case 2:
	{
		stations[id].setWorkshopInWork(stations[id].getWorkshopInWork() - GetCorrectNumber("Количество цехов: ", 0, stations[id].getWorkshopInWork()));
	}
	}
}

void saveToFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations, Pipe& p, Station& s) {
	string name;
	ofstream fout;
	clearBuffer();
	cout << "Введите имя Файла: ";
	getline(cin, name);
	fout.open(name);


	if (fout.is_open()) {
		for (auto& it : pipes) {
			it.second.saveToFile(fout);
		}

		for (auto& it : stations) {
			it.second.saveToFile(fout);
		}
		cout << "Успешно сохранено" << endl;
		fout.close();
	}
	else {
		cout << "Не получилось открыть файл." << endl;
	}
}

void downloadFromFile(unordered_map<int, Pipe> & pipes, unordered_map<int, Station>& stations, Pipe&p, Station&s) {
	string name;
	ifstream fin;
	clearBuffer();
	cout << "Введите имя Файла: ";
	getline(cin, name);
	fin.open(name);

	if (fin.is_open()) {
		bool some = false;
		while (!fin.eof()) {
			char ch;
			some = true;
			fin >> ch;
			if (ch == 'p') {
				Pipe::idP++;
				p.downloadFromFile(fin);
				p.setId();
				pipes.emplace(p.getId(), p);
			}
			if (ch == 's') {
				Station::idS++;
				s.downloadFromFile(fin);
				s.setId();
				stations.emplace(s.getId(), s);
			}
			ch = 'N';
		}
		cout << ((some) ? "Успешно загрузилось" : "Файл пустой") << endl;
		fin.close();
	}
	else {
		cout << "Не получилось открыть файл." << endl;
	}
}

void printObjects(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
	if (!pipes.empty()) {
		for (auto& it : pipes) {
			cout << pipes[it.first];
		}
	}
	else {
		cout << "Труб нет" << endl;
	}

	if (!stations.empty()) {
		for (auto& it : stations) {
			cout << stations[it.first];
		}
	}
	else {
		cout << "Станций нет" << endl;
	}
}

void selectPipe(unordered_map<int, Pipe>& pipes, Pipe & p) {
	vector <int> foundPipes;
	cout << "1. Bыбрать трубу по названию." << endl << "2. Bыбрать трубу по статусу \"в работе\"." << endl << "0. Выход." << endl;
	switch (GetCorrectNumber("выберете действие: ", 1, 2)) {

	case 0:
		break;

	case 1:
	{
		string name;
		clearBuffer();
		cout << "Название: ";
		getline(cin, name);
		foundPipes = findPipeByFilter(pipes, checkPipeByName, name);
		break;
	}

	case 2:
		foundPipes = findPipeByFilter(pipes, checkPipeByInRepair, (bool)GetCorrectNumber("B работе: ", 0, 1));
		break;
	}

	if (!foundPipes.empty()) {
		for (int i : foundPipes)
			cout << pipes[i];
		cout << "1. Редактировать." << endl << "2. Удалить." << endl << "0. Выход." << endl;
		switch (GetCorrectNumber("Выберете действие", 0, 2))
		{
		case 0:
			break;

		case 1:
		{
			bool inRepair = (bool)GetCorrectNumber("В работе:", 0, 1);
			for (int i : foundPipes)
				editPipe(pipes, i, inRepair);
			break;
		}
		case 2:
			for (int i : foundPipes)
				pipes.erase(i);
			break;
		}

	}
	else {
		cout << "Таких труб нет." << endl;
	}
}

void selectStation(unordered_map <int, Station>& stations, Station& s) {
	vector <int> foundStations;
	cout << "1. Bыбрать кс по названию." << endl << "2. Bыбрать кс проценту незадействованных цехов." << endl << "0. Выход." << endl;
	switch (GetCorrectNumber("Bыберете действие: ", 1, 2)) {

	case 0:
		break;

	case 1:
	{
		string name;
		clearBuffer();
		cout << "Название: ";
		getline(cin, name);
		foundStations = findStationByFilter(stations, checkStationByName, name);

		break;
	}

	case 2:
	{
		foundStations = findStationByFilter(stations, checkStationByPercent, GetCorrectNumber("Процент: ", 0.0, 100.0));

		break;
	}
	}

	if (!foundStations.empty()) {
		for (int i : foundStations)
			cout << stations[i];
		cout << "1. Редактировать." << endl << "2. Удалить." << endl << "0. Выход." << endl << endl;
		switch (GetCorrectNumber("Выберете действие", 0, 2))
		{
		case 0:
			break;
		case 1:
			for (int i : foundStations)
				editStation(stations, i);
		case 2:
			for (int i : foundStations)
				stations.erase(i);
		}
	}
	else {
		cout << "Таких КС нет." << endl;
	}
}

int main() {

	setlocale(LC_ALL, "Russian");
	unordered_map <int, Pipe> pipes;
	unordered_map <int, Station> stations;
	Pipe p;
	Station s;

	for (;;) {

		printMenu();

		switch (GetCorrectNumber("Выберете действие: ", 0, 11)) {

		case 0:
			return 0;

		case 1:
			cin >> p;
			pipes.emplace(Pipe::idP, p);
			break;

		case 2:
			cin >> s;
			stations.emplace(Station::idS, s);
			break;

		case 3:
			printObjects(pipes, stations);
			break;

		case 4:
			if (!pipes.empty()) {
				int id = GetCorrectNumber("Введите id трубы: ", 1, Pipe::idP);
				editPipe(pipes, id, !pipes[id].getInRepair());
			}
			else { 
				cout << "Труб нет" << endl;
			}
			break;

		case 5:
		{
			if (!stations.empty()) {
				editStation(stations, GetCorrectNumber("Выберете станцию: ", 1, Station::idS));
			}
			else {
				cout << "Станций не найдено" << endl;
			}
			break;
		}
		case 6:
			saveToFile(pipes, stations, p, s);
			break;

		case 7:
			downloadFromFile(pipes, stations, p, s);
			break;

		case 8:
		{
			selectPipe(pipes, p);
			break;
		}
		case 9:
		{
			selectStation(stations, s);
			break;
		}

		case 10:
		{
			deletePipe(pipes);
			break;
		}

		case 11:
		{
			deleteStation(stations);
			break;
		}
		}
	}
}

