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
		double efficiency;
		int id;

	public:
		Station();
		std::string getName() const;
		int getWorkshop() const;
		int getWorkshopInWork() const;
		double getEfficiency() const;
		int getId() const;
	
		void setName(std::string name);
		void setWorkshop(int workshop);
		void setWorkshopInWork(int workshopInWork);
		void setEfficiency(double efficiency);
		void setId();
		static int idS;
		void saveToFile(std::ofstream& fout);
		void downloadFromFile(std::ifstream& fin);
};
