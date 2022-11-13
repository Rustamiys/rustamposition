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
		<< "0. Выход." << endl;
}

bool checkPipeByInRepair(const Pipe& p, bool parametr) {
	return p.getInRepair() == parametr;
}


bool checkByPercent(const Station& s, double parametr) {
	return parametr / 100.0 >= 1.0 - (double)s.getWorkshopInWork() / (double)s.getWorkshop();
}

set<int> GetIdByUserinput() {
	set <int> vvodId;
	string id, name;
	char ch;
	clearBuffer();
	cout << "Введите id через пробел:";
	getline(cin, name);

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
	if (id != "") {
		vvodId.emplace(stoi(id));
		id = "";
	}
	return vvodId;
}
