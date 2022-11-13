#pragma once
#include "Station.h"
#include "Utils.h"

using namespace std;

int Station::idS = 0;

Station::Station()
{
	idS++;
	id = idS;
	name = ' ';
	workshop = 0;
	workshopInWork = 0;
	efficiency = 0;
}

string Station::getName() const
{
	return name;
}

int Station::getWorkshop() const
{
	return workshop;
}

int Station::getWorkshopInWork() const
{
	return workshopInWork;
}

double Station::getEfficiency() const
{
	return efficiency;
}

int Station::getId() const
{
	return id;
}

void Station::setWorkshopInWork(int workshopInWork)
{
	/*if (workshopInWork > workshop) {
		this->workshopInWork = workshop;
	}
	else if (workshopInWork < 0) {
		this->workshopInWork = 0;
	}
	else {
		this->workshopInWork = workshopInWork;
	}*/
	this->workshopInWork = workshopInWork;
}

void Station::saveToFile(ofstream& fout)
{
	fout << "s" << endl
		<< name << endl
		<< id << endl
		<< workshop << endl
		<< workshopInWork << endl
		<< efficiency << endl;
}

void Station::downloadFromFile(ifstream& fin)
{
	fin >> ws;
	getline(fin, name);
	fin >> id >> workshop >> workshopInWork >> efficiency;
}

istream& operator >> (istream& in, Station& s) {
	string name;
	clearBuffer();
	cout << "��� �������: ";
	getline(cin, name);
	s.name = name;
	s.workshop = GetCorrectNumber("���������� �����: ", 1, 2000000000);
	s.workshopInWork = GetCorrectNumber("���������� ����� ������: ", 0, s.getWorkshop());
	s.efficiency = GetCorrectNumber("�������������: ", 0.0, 100.0);
	return in;
}

ostream& operator << (ostream& out, const Station& s) {
	out << endl << "������������� �������" << endl << "���: " << s.name << endl
		<< "ID: " << s.id << endl
		<< "���������� �����: " << s.workshop << endl
		<< "���������� ����� � ������: " << s.workshopInWork << endl
		<< "�������������: " << s.efficiency << endl;
	return out;
}