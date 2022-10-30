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
		unsigned int id;

	public:
		Station();
		std::string getName() const;
		int getWorkshop() const;
		int getWorkshopInWork() const;
		float getEfficiency() const;
		unsigned int getId() const;
	
		void setName(std::string name);
		void setWorkshop(int workshop);
		void setWorkshopInWork(int workshopInWork);
		void setEfficiency(float efficiency);
		void setId();
		static int idS;
};
