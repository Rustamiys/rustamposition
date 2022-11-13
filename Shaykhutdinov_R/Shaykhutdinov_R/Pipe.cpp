#include "Pipe.h"
#include "Utils.h"

using namespace std;

int Pipe::idP = 0;

Pipe::Pipe(){
	idP++;
	id = idP;
	name = '0';
	length = 0;
	diametr = 0;
	inRepair = 0;
}

string Pipe::getName() const
{
	return name;
}

bool Pipe::getInRepair() const
{
	return inRepair;
}

int Pipe::getId() const
{
	return id;
}

void Pipe::setInRepair(bool inRepair) {
	this->inRepair = inRepair;
}

void Pipe::editPipe()
{
	inRepair = !inRepair;
}

void Pipe::saveToFile(ofstream& fout)
{
	fout << "p" << endl
		<< name << endl
		<< id << endl
		<< length << endl
		<< diametr << endl
		<< inRepair << endl;
}

void Pipe::downloadFromFile(ifstream& fin)
{
	fin >> ws;
	getline(fin, name);
	fin >> id >> length >> diametr >> inRepair;
}

ostream& operator << (ostream& out, const Pipe& p) {
	out << endl << "Труба" << endl << "Имя: " << p.name << endl
		<< "ID: " << p.id << endl
		<< "Длина: " << p.length << endl
		<< "Диаметр: " << p.diametr << endl
		<< ((p.inRepair) ? "В работе " : "Не в работе") << endl;

	return out;
}

istream& operator >> (istream& in, Pipe& p) {
	string name;
	clearBuffer();
	cout << "Имя трубы: ";
	getline(cin, name);
	p.name = name;
	p.length = GetCorrectNumber("Длина: ", 0.1, 3.4E+38);
	p.diametr = GetCorrectNumber("Диаметр: ", 0.1, 3.4E+38);
	p.inRepair = (bool)GetCorrectNumber("В работе: ", 0, 1);
	return in;
}
