#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipe {
	private:
		std::string name;
		double length;
		double diametr;
		bool inRepair;
		int id;

	public:
		Pipe();

		std::string getName() const;
		double getLength() const;
		double getDiametr() const;
		bool getInRepair() const;
		int getId() const;
		static int idP;

		void setName(std::string name);
		void setLength(double length);
		void setDiametr(double diametr);
		void setInRepair(bool in_repair);
		void setId();
		void editPipe();
		void saveToFile(std::ofstream& fout);
		void downloadFromFile(std::ifstream& fin);
};


