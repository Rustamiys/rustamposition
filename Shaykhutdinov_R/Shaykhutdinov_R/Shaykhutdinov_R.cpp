#include "Utils.h"
#include "Pipe.h"
#include "Station.h"
#include "GTS.h"

void editStation(unordered_map <int, Station>& stations,int id) {
	cout << "Всего цехов: " << stations[id].getWorkshop() << endl << "Цехов в работе: " << stations[id].getWorkshopInWork() << endl;
	cout << "1. Запуск цехов." << endl << "2. Отключение цехов." << endl;
	switch (GetCorrectNumber("Выберете действие: ", 1, 2))
	{
	case 1:
	{//!!!
		stations[id].setWorkshopInWork(stations[id].getWorkshopInWork() + GetCorrectNumber("Количество цехов: ", 0, stations[id].getWorkshop() - stations[id].getWorkshopInWork()));
	}
	case 2:
	{//!!!
		stations[id].setWorkshopInWork(stations[id].getWorkshopInWork() - GetCorrectNumber("Количество цехов: ", 0, stations[id].getWorkshopInWork()));
	}
	}
}

void printObjects(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
	if (pipes.empty()) cout << "Труб нет!" << endl;
	for (auto& it : pipes) 
		cout << pipes[it.first];

	if (stations.empty()) cout << "Станций нет!" << endl;
	for (auto& it : stations)
		cout << stations[it.first];
}

set <int> selectPipesByFilter(unordered_map<int, Pipe>& pipes) {
	set <int> foundPipes;

	cout << "1. Bыбрать трубу по названию." << endl << "2. Bыбрать трубу по статусу \"в работе\"." << endl << "0. Выход." << endl;
	
	switch (GetCorrectNumber("выберете действие: ", 0, 2)) {

	case 0:
		break;

	case 1:
	{
		string name;
		clearBuffer();
		cout << "Название: ";
		getline(cin, name);
		foundPipes = findByFilter(pipes, checkByName, name);
		break;
	}

	case 2:
		foundPipes = findByFilter(pipes, checkPipeByInRepair, (bool)GetCorrectNumber("B работе: ", 0, 1));
		break;
	}
	return foundPipes;
}

void editPipeByFilter(unordered_map<int, Pipe>& pipes, set <int> foundPipes) {
	if (!foundPipes.empty()) {
		for (int i : foundPipes)
			cout << pipes[i];
		cout << "1. Редактировать все." << endl << "2. Редактирование по фильтру." << endl <<
			"3. Удалить все." << endl << "4. Удалить по фильтру." << endl << "0. Выход." << endl;

		switch (GetCorrectNumber("Выберете действие: ", 0, 4))
		{
		case 0:
			break;

		case 1:
		{
			bool inRepair = (bool)GetCorrectNumber("В работе:", 0, 1);
			for (int i : foundPipes)
				pipes[i].editPipe(inRepair);
			break;
		}
		case 2:
		{
			set <int> foundP = selectPipesByFilter(pipes);
			for (int i : foundP)
				if (foundPipes.contains(i)) cout << pipes[i];
			
			cout << "1. Редактировать все." << endl << "2. По вводу." << endl << "0. Выход." << endl;

			switch (GetCorrectNumber("Выберете действие: ", 0, 2))
			{
			case 0:
				break;

			case 1:
			{
				bool inRepair = (bool)GetCorrectNumber("В работе:", 0, 1);
				for (int i : foundP)
					if (foundPipes.contains(i)) pipes[i].editPipe(inRepair);
				cout << "Успешно" << endl;
				break;
			}

			case 2:
			{
				bool inRepair = (bool)GetCorrectNumber("В работе:", 0, 1);
				set<int> vvodId = GetIdByUserinput();

				for (int i : vvodId)
					if (foundPipes.contains(i) && foundP.contains(i)) 
						pipes[i].editPipe(inRepair);

				cout << "Успешно" << endl;
				break;
			}
			}
			break;

		}

		case 3:
		{
			for (int i : foundPipes)
				pipes.erase(i);
			break;
		}

		case 4:
		{

			set <int> foundP = selectPipesByFilter(pipes);
			for (int i : foundP)
				cout << pipes[i];
			cout << "1. Удалить все." << endl << "2. По вводу." << endl << "0. Выход." << endl;

			switch (GetCorrectNumber("Выберете действие: ", 0, 4))
			{
			case 0:
				break;

			case 1:
			{
				for (int i : foundP)
					if (foundPipes.contains(i)) pipes.erase(i);
				break;
			}

			case 2:
			{
				set<int> vvodId = GetIdByUserinput();

				for (int i : vvodId)
					if (foundPipes.contains(i) && foundP.contains(i)) deleteObject(pipes, i);
				break;
			}
			}
			break;
		}
		}
	}
	else {
		cout << "Таких труб нет." << endl;
	}
}

void selectStation(unordered_map <int, Station>& stations) {
	set <int> foundStations;
	cout << "1. Bыбрать кс по названию." << endl << "2. Bыбрать кс проценту незадействованных цехов." << endl << "0. Выход." << endl;
	switch (GetCorrectNumber("Bыберете действие: ", 0, 2)) {

	case 0:
		break;

	case 1:
	{
		string name;
		clearBuffer();
		cout << "Название: ";
		getline(cin, name);
		foundStations = findByFilter(stations, checkByName, name);

		break;
	}

	case 2:
	{
		foundStations = findByFilter(stations, checkByPercent, GetCorrectNumber("Процент: ", 0.0, 100.0));

		break;
	}
	}

	if (!foundStations.empty()) {
		for (int i : foundStations)
			cout << stations[i];
		cout << "1. Редактировать все." << endl << "2. Удалить все." << endl << "0. Выход." << endl << endl;
		switch (GetCorrectNumber("Выберете действие: ", 0, 2))
		{
		case 0:
			break;
		case 1:
			for (int i : foundStations)
				editStation(stations, i);
			break;
		case 2:
			for (int i : foundStations)
				stations.erase(i);
			break;
		}
	}
	else {
		cout << "Таких КС нет." << endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	GTS gts;
	unordered_map <int, Pipe> pipes;
	unordered_map <int, Station> stations;
	
	
	for (;;) {
		cout << endl << endl;
		printMenu();
		cout << endl << endl;
		switch (GetCorrectNumber("Выберете действие: ", 0, 14)) {

		case 0:
			return 0;

		case 1:
		{
			Pipe p;
			cin >> p;
			pipes.emplace(p.getId(), p);
			break;
		}

		case 2:
		{
			Station s;
			cin >> s;
			stations.emplace(s.getId(), s);
			break;
		}

		case 3:
			printObjects(pipes, stations);
			gts.print();
			break;

		case 4:
			if (!pipes.empty()) {
				int id = GetCorrectNumber("Введите id трубы: ", 1, Pipe::idP);
				pipes[id].editPipe(!pipes[id].getInRepair());
			}
			else {
				cout << "Труб нет" << endl;
			}
			break;

		case 5:
			if (!stations.empty()) {
				editStation(stations, GetCorrectNumber("Выберете станцию: ", 1, Station::idS));
			}
			else {
				cout << "Станций не найдено" << endl;
			}
			break;

		case 6:
			saveToFile(pipes, stations);
			break;

		case 7:
			gts.deleteAll();
			downloadFromFile(pipes, stations);
			for (auto& it : pipes)
				if (it.second.getInputStation() != 0) gts.IncludeToGraph(it.second);
			break;

		case 8:
		{
			set <int> selectedPipes = selectPipesByFilter(pipes);
			editPipeByFilter(pipes, selectedPipes);
			break;
		}

		case 9:
			selectStation(stations);
			break;

		case 10:
			if (pipes.size() > 0) {
				int num = GetCorrectNumber("Id трубы которую хотите удалить: ", 1, Pipe::idP);
				deleteObject(pipes, num);
			}
			else {
				cout << "Труб нет" << endl;
			}
			break;

		case 11:
			if (stations.size() > 0) {
				int num = GetCorrectNumber("Id станции которую хотите удалить: ", 1, Station::idS);
				deleteObject(stations, num);
			}
			else {
				cout << "Станций нет" << endl;
			}
			break;
		case 12:

			gts.addGTS(pipes, stations);

			break;
		case 13:
			gts.checkIdStationsInPipe(pipes);
			gts.topological_sort();

			break;
		case 14:
			gts.MinPath(pipes);
			break;
		}
	}
}

