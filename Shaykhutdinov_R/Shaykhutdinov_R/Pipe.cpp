#include "Pipe.h"

int Pipe::id = 0;

Pipe::Pipe(){
	name = "";
	length = 0;
	diametr = 0;
	inRepair = 0;
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
