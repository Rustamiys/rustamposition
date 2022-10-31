#include "Station.h"

int Station::idS = 0;

Station::Station()
{}

std::string Station::getName() const
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

void Station::setName(std::string name)
{
	this->name = name;
}

void Station::setWorkshop(int workshop)
{
	this->workshop = workshop;
}

void Station::setWorkshopInWork(int workshopInWork)
{
	this->workshopInWork = workshopInWork;
}

void Station::setEfficiency(double efficiency)
{
	this->efficiency = efficiency;
}

void Station::setId()
{
	id = idS;
}

void Station::saveToFile(std::ofstream& fout)
{
	fout << "s" << std::endl
		<< name << std::endl
		<< workshop << std::endl
		<< workshopInWork << std::endl
		<< efficiency << std::endl;
}

void Station::downloadFromFile(std::ifstream& fin)
{
	fin >> std::ws;
	getline(fin, name);
	fin >> workshop >> workshopInWork >> efficiency;
}
