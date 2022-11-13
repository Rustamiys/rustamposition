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
	
		static int idS;
		void setWorkshopInWork(int workshopInWork);
		void saveToFile(std::ofstream& fout);
		void downloadFromFile(std::ifstream& fin);
		friend std::istream& operator >> (std::istream& in, Station & s);
		friend std::ostream& operator << (std::ostream& out, const Station& s);
};
