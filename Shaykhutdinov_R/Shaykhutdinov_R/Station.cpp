#include "Station.h"

int Station::id = 0;

Station::Station()
{
	name = "0";
	workshop = 0;
	workshopInWork = 0;
	efficiency = 0;
}

std::string Station::getName() const
{
	return name;
}

int Station::getWorkdhop() const
{
	return workshop;
}

int Station::getWorkshopInWork() const
{
	return workshopInWork;
}

float Station::getEfficiency() const
{
	return efficiency;
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

void Station::setEfficiency(float efficiency)
{
	this->efficiency = efficiency;
}
