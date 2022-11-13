#include "Utils.h"

void clearBuffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

void printMenu() {
	cout << "1. �������� �����." << endl
		<< "2. �������� ��." << endl
		<< "3. �������� ���� ��������." << endl
		<< "4. �������������� ����." << endl
		<< "5. �������������� ��." << endl
		<< "6. ���������." << endl
		<< "7. ���������." << endl
		<< "8. ����� ����� �� �������." << endl
		<< "9. ����� �� �� �������." << endl
		<< "10. ������� �����." << endl
		<< "11. ������� �������." << endl
		<< "0. �����." << endl;
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
	cout << "������� id ����� ������:";
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
