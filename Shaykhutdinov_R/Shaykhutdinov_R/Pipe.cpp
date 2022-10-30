#include "Pipe.h"

int Pipe::idP = 0;

Pipe::Pipe(){
	name = "";
	length = 0;
	diametr = 0;
	inRepair = 0;
	id = 0;
}

std::string Pipe::getName() const
{
	return name;
}


float Pipe::getLength() const {
	return length;
}

float Pipe::getDiametr() const {
	return diametr;
}

bool Pipe::getInRepair() const
{
	return inRepair;
}

unsigned int Pipe::getId() const
{
	return id;
}


void Pipe::setName(std::string name)
{
	this->name = name;
}

void Pipe::setLength(float length) {
	this->length = length;
}

void Pipe::setDiametr(float diametr) {
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
	fin >> name >> length >> diametr >> inRepair;
}

