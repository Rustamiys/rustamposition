#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Station
{
	private:
		std::string name;
		int workshop;
		int workshopInWork;
		float efficiency;

	public:
		Station();
		std::string getName() const;
		int getWorkdhop() const;
		int getWorkshopInWork() const;
		float getEfficiency() const;
	
		void setName(std::string name);
		void setWorkshop(int workshop);
		void setWorkshopInWork(int workshopInWork);
		void setEfficiency(float efficiency);
		static int id;
};
