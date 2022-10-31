#include "Pipe.h"

int Pipe::idP = 0;

Pipe::Pipe(){}

std::string Pipe::getName() const
{
	return name;
}

double Pipe::getLength() const {
	return length;
}

double Pipe::getDiametr() const {
	return diametr;
}

bool Pipe::getInRepair() const
{
	return inRepair;
}

int Pipe::getId() const
{
	return id;
}


void Pipe::setName(std::string name)
{
	this->name = name;
}

void Pipe::setLength(double length) {
	this->length = length;
}

void Pipe::setDiametr(double diametr) {
	this->diametr = diametr;
}

void Pipe::setInRepair(bool inRepair) {
	this->inRepair = inRepair;
}

void Pipe::setId() {
	id = idP;
}

void Pipe::editPipe()
{
	inRepair = !inRepair;
}

void Pipe::saveToFile(std::ofstream& fout)
{
	fout << "p" << std::endl
		<< name << std::endl
		<< length << std::endl
		<< diametr << std::endl
		<< inRepair << std::endl;
}

void Pipe::downloadFromFile(std::ifstream& fin)
{
	fin >> std::ws;
	getline(fin, name);
	fin >> length >> diametr >> inRepair;
}

