#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "Station.h"
#include <map>

using namespace std;

void printMenu() {
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Просмотр всех объектов" << endl;
	cout << "4. Редактировать трубу" << endl;
	cout << "5. Редактировать КС" << endl;
	cout << "6. Сохранить" << endl;
	cout << "7. Загрузить" << endl;
	cout << "0. Выход" << endl;
}

template <typename T>
T GetCorrectNumber(string text, T min, T max) {
	cout << text;
	T number;
	cin >> number;
	for (;;) {
		if (cin.fail() || number < min || number > max) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Введите корректные данные(" << min << "-" << max << "): ";
			cin >> number;
		}
		else {
			return number;
		}
	}
	
}

void addPipe(map <unsigned int, Pipe>&pipes, Pipe& newPipe) {
	cin.clear();
	cin.ignore(1024, '\n');
	string name;
	cout << "Имя трубы: ";
	getline(cin, name);
	newPipe.setName(name);
	newPipe.setLength(GetCorrectNumber("Длина: ", 0.00001, 3.4E+38));
	newPipe.setDiametr(GetCorrectNumber("Диаметр: ", 0.00001, 3.4E+38));
	newPipe.setInRepair(GetCorrectNumber("В работе: ", 0, 1));
	newPipe.id++;
	
	pipes.emplace(newPipe.id, newPipe);
}

void printPipe(map <unsigned int, Pipe>& pipes) {
	int i;
	if (!pipes.empty()) {
		for (auto it : pipes) {
			i = it.first;
			cout << endl << "Имя: " << pipes[i].getName() << endl;
			cout << "ID: " << pipes[i].id << endl;
			cout << "Длина: " << pipes[i].getLength() << endl;
			cout << "Диаметр: " << pipes[i].getDiametr() << endl;
			cout << ((pipes[i].getInRepair())? "В работе " : "Не в работе") << endl << endl;
		}
	}
	else {
		cout << "Труб нет!" << endl;
	}
}

void editPipe(map <unsigned int, Pipe>& pipes, int id) {
	pipes[id].setInRepair(!pipes[id].getInRepair());
}

void editPipes(map <unsigned int, Pipe>& pipes) {
	if (!pipes.empty()) {
		for (auto it : pipes) {
			editPipe(pipes, it.first);
		}
	}
	else {
		cout << "Труб нет!" << endl;
	}
}

void deletePipe(map <unsigned int, Pipe>& pipes) {
	int num = pipes.size();
	
	if (pipes.size() > 0) {
		num = GetCorrectNumber("Id трубы которую хотите удалить: ", 1, num);
		pipes.erase(num);
		cout << "Удалено" << endl;
	}
}

void addStation(map <unsigned int, Station>& stations, Station& newStation) {
	cin.clear();
	cin.ignore(1024, '\n');
	string name;
	cout << "Имя кс: ";
	getline(cin, name);
	newStation.setName(name);
	newStation.setWorkshop(GetCorrectNumber("Количество цехов: ", 1, 2000000000));
	newStation.setWorkshopInWork(GetCorrectNumber("Количество цехов работе: ", 1, 2000000000));
	newStation.setEfficiency(GetCorrectNumber("Эффективность: ", 0.00001, 3.4E+38));
	newStation.id++;
	
	stations.emplace(newStation.id, newStation);
}

void printStation(map <unsigned int, Station>& stations) {
	int i;
	if (!stations.empty()) {
		for (auto it : stations) {
			i = it.first;
			cout << endl << "Имя: " << stations[i].getName() << endl;
			cout << "Id: " << stations[i].id << endl;
			cout << "Количество цехов: " << stations[i].getWorkdhop() << endl;
			cout << "Количество цехов в работе: " << stations[i].getWorkshopInWork() << endl;
			cout << "Эффективность: " << stations[i].getEfficiency() << endl << endl;
		}
	}
	else {
		cout << "Нет станций" << endl;
	}
}

void deleteStation(map <unsigned int, Station>& stations) {
	int num = stations.size();
	if (stations.size() > 0) {
		num = GetCorrectNumber("Id трубы которую хотите удалить: ", 1, num);
		stations.erase(num);
		cout << "Удалено" << endl;
	}
}

void editStation(map <unsigned int, Station>& stations,int id) {
	stations[id].setWorkshopInWork(GetCorrectNumber("Добавить количество станций: ", 1, stations[i].getWorkshop() - stations[i].getWorkshopInWork()));
}

int main()
{
	setlocale(LC_ALL, "Russian");
	map <unsigned int, Pipe> pipes;
	map <unsigned int, Station> stations;
	Pipe newPipe;
	Station newStation;
	


	for (;;) {

		printMenu();
		
		switch (GetCorrectNumber("Выберете действие: ",0, 7)) {
		
		case 0:
		{
			return 0;
		}
		case 1:
		{
			addPipe(pipes, newPipe);
			break;
		}
		case 2:
		{
			addStation(stations, newStation);
			break;
		}
		case 3:
		{
			printPipe(pipes);
			printStation(stations);
			break;
		}
		case 4:
		{
			cout << "1. Редактировать трубу по id." << endl << "2. Редактировать все" << endl << "0.Выход" << endl;
			switch (GetCorrectNumber("Выберете действие: ", 0, 2))
			{
			case 1:
			{
				editPipe(pipes, GetCorrectNumber("", 0, 122222));
				break;
			}
			case 2:
			{
				editPipes(pipes);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 5:
		{
			editStation(stations, GetCorrectNumber("", 0, 122222));
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			break;
		}
		default:
			break;

		}

	}
}
