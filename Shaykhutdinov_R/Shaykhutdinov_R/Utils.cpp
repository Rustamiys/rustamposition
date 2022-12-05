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
		<< "12. �������� � ���." << endl
		<< "13. �������������� ����������." << endl
		<< "0. �����." << endl;
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
	cout << "������� id ����� ������:";
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
	cout << "������� ��� �����: ";
	getline(cin, name);
	fout.open(name);

	if (fout.is_open()) {
		for (auto& it : pipes) {
			it.second.saveToFile(fout);
		}

		for (auto& it : stations) {
			it.second.saveToFile(fout);
		}
		cout << "������� ���������" << endl;
		fout.close();
	}
	else {
		cout << "�� ���������� ������� ����." << endl;
	}
}

void downloadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
	string name;
	ifstream fin;

	clearBuffer();
	deleteObject(pipes);

	deleteObject(stations);

	cout << "������� ��� �����: ";
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
		cout << ((empty) ? "������� �����������" : "���� ������") << endl;
		fin.close();
	}
	else {
		cout << "�� ���������� ������� ����." << endl;
	}
}
