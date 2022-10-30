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
T GetCorrectNumber(std::string text, T min, T max) {
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
vector<unsigned int> findPipeByFilter(unordered_map<unsigned int, Pipe>& pipes, FilterP<T> f, T parametr){
	vector<unsigned int> result;
	for (auto& it : pipes)
	{
		if (f(it.second, parametr))
		{
			result.push_back(it.second.getId());
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
	p.setLength(GetCorrectNumber("Длина: ", 0.00001, 3.4E+38));
	p.setDiametr(GetCorrectNumber("Диаметр: ", 0.00001, 3.4E+38));
	p.setInRepair(GetCorrectNumber("В работе: ", 0, 1));
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
	s.setWorkshop(GetCorrectNumber("Длина: ", 1, 2000000000));
	s.setWorkshopInWork(GetCorrectNumber("Количество цехов работе: ", 0, 2000000000));
	s.setEfficiency(GetCorrectNumber("Эффективность: ", 0.00001, 3.4E+38));
	s.idS++;
	s.setId();
	return in;
}

template <typename T>
using FilterS = bool(*)(Station& s, T parametr);
template <typename T>
vector <unsigned int> findStationByFilter(unordered_map<unsigned int, Station>& stations, FilterS<T> f, T parametr) {
	vector <unsigned int> result;
	for (auto& it : stations) {
		if (f(it.second, parametr)) {
			result.push_back(it.second);
		}
	}
	return result;
}

bool checkStationByName(Station& s, string parametr) {
	return s.getName() == parametr;
}

bool checkStationByPercent(Station& s, float parametr) {
	return parametr/100.0 == 1.0 - (float)s.getWorkshopInWork()/(float)s.getWorkshop();
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

void editPipe(unordered_map <unsigned int, Pipe>& pipes, int id) {
	pipes[id].setInRepair(!pipes[id].getInRepair());
}

void editPipes(unordered_map <unsigned int, Pipe>& pipes) {
	if (!pipes.empty()) {
		for (auto& it : pipes) {
			editPipe(pipes, it.first);
		}
	}
	else {
		cout << "Труб нет!" << endl;
	}
}

void deletePipe(unordered_map <unsigned int, Pipe>& pipes) {
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

void deleteStation(unordered_map <unsigned int, Station>& stations) {
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



void editStation(unordered_map <unsigned int, Station>& stations,int id) {
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

int main()
{
	setlocale(LC_ALL, "Russian");
	unordered_map <unsigned int, Pipe> pipes;
	unordered_map <unsigned int, Station> stations;
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
			if (pipes.size() > 0) {
				for (auto& it : pipes) {
					cout << pipes[it.first];
				}
			}
			else {
				cout << "Труб нет" << endl;
			}

			if (stations.size() > 0) {
				for (auto& it : stations) {
					cout << stations[it.first];
				}
			}
			else {
				cout << "Станций нет" << endl;
			}
			
			break;

		case 4:
			cout << "1. Редактировать трубу по id." << endl << "2. Редактировать по статусу \"в работе\"."  << endl <<"3. Редактировать по названию." <<endl<<"4. Редактировать все." << "0.Выход" << endl;
			switch (GetCorrectNumber("Выберете действие: ", 0, 2))
			{
			case 0:
				break;

			case 1:
				editPipe(pipes, GetCorrectNumber("", 1, Pipe::idP));
				break;

			case 2:
				editPipes(pipes);
				break;

			case 3:
			{
				string name;
				clearBuffer();
				cout << "Название: ";
				getline(cin, name);
				for (int i : findPipeByFilter(pipes, checkPipeByName, name))
					editPipe(pipes, i);

				break;
			}

			case 4:
				for (int i : findPipeByFilter(pipes, checkPipeByInRepair, (bool)GetCorrectNumber("B работе: ", 0, 1)))
					editPipe(pipes, i);
				break;
			}

		case 5:
			if (stations.size() > 0) {
				editStation(stations, GetCorrectNumber("Выберете станцию: ", 1, Station::idS));
			}
			else {
				cout << "Станций не найдено" << endl;
			}
			break;

		case 6:
		{
			string name;
			ofstream fout;
			cout << "Введите имя: ";
			cin.sync();
			getline(cin, name);
			fout.open(name.c_str());
			

			if (fout.is_open()) {
				for (auto& it : pipes) {
					it.second.saveToFile(fout);
				}
			}
			else {
				cout << "Не получилось открыть файл.";
			}
			fout.close();
			break;
		}
		case 7:
			
			break;

		case 8:
		{
			vector <unsigned int> foundPipes;
			cout << "1. Bыбрать трубу по названию." << endl << "2. Bыбрать трубу по статусу \"в работе\"." << endl;
			switch (GetCorrectNumber("выберете действие: ", 1, 2)) {

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
			{
				foundPipes = findPipeByFilter(pipes, checkPipeByInRepair, (bool)GetCorrectNumber("B работе: ", 0, 1));

				break;
			}
			}
			if (!foundPipes.empty()) {
				for (unsigned int i : foundPipes)
					cout << pipes[i];
			}
			else {
				cout << "Такой трубы не найдено " << endl;
			}
			break;
		}
		case 9:
		{
			vector <unsigned int> foundStations;
			cout << "1. Bыбрать кс по названию." << endl << "2. Bыбрать кс проценту незадействованных цехов." << endl;
			switch (GetCorrectNumber("Bыберете действие: ", 1, 2)) {

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
				foundStations = findStationByFilter(stations, checkStationByPercent, (float)GetCorrectNumber("Процент: ", 0.0, 100.0));

				break;
			}
			}
			if (!foundStations.empty()) {
				for (unsigned int i : foundStations)
					cout << stations[i];
			}
			else {
				cout << "Такой КС не найдено " << endl;
			}
			break;
		}

		case 10:
			deletePipe(pipes);
			break;

		case 11:
			deleteStation(stations);
			break;

		}
	}
}
