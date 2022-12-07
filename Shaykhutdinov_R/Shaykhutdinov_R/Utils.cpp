#include "Utils.h"

void clearBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
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
		<< "12. Добавить в ГТС." << endl
		<< "13. Топологическая сортировка." << endl
		<< "0. Выход." << endl;
}

bool checkPipeByInRepair(const Pipe& p, bool parametr) {
	return p.getInRepair() == parametr;
}

bool checkByPercent(const Station& s, double parametr) {
	return parametr >= 100 * (1 - (double)s.getWorkshopInWork() / (double)s.getWorkshop());
}

bool checkPipeByDiametr(const Pipe& p, double parametr) {
	return parametr == p.getDiametr();
}

set<int> GetIdByUserinput() {
	set <int> vvodId;
	string id, name;
	char ch;
	clearBuffer();
	cout << "Введите id через пробел:";
	getline(cin, name);
	name += "$";

	for (int i = 0; i < name.size(); i++) {
		ch = name[i];
		if (isdigit(ch)) {
			id += ch;
		}
		else {
			if (id != "") {
				vvodId.emplace(stoi(id));
				id = "";
			}
		}
	}
	
	return vvodId;
}

void saveToFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
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

void downloadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
	string name;
	ifstream fin;

	clearBuffer();
	deleteObject(pipes);

	deleteObject(stations);

	cout << "Введите имя Файла: ";
	getline(cin, name);
	fin.open(name);

	if (fin.is_open()) {
		bool empty = false;
		while (!fin.eof()) {
			char ch;
			empty = true;
			fin >> ch;
			if (ch == 'p') {
				Pipe p;
				p.downloadFromFile(fin);
				pipes.emplace(p.getId(), p);
			}
			if (ch == 's') {
				Station s;
				s.downloadFromFile(fin);
				stations.emplace(s.getId(), s);
			}
			ch = 'N';
		}
		cout << ((empty) ? "Успешно загрузилось" : "Файл пустой") << endl;
		fin.close();
	}
	else {
		cout << "Не получилось открыть файл." << endl;
	}
}
