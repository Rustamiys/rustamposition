#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipe {
	private:
		std::string name;
		float length;
		float diametr;
		bool inRepair;
		int unsigned id;

	public:
		Pipe();

		std::string getName() const;
		float getLength() const;
		float getDiametr() const;
		bool getInRepair() const;
		unsigned int getId() const;
		static int idP;

		void setName(std::string name);
		void setLength(float length);
		void setDiametr(float diametr);
		void setInRepair(bool in_repair);
		void setId();
		void editPipe();
		void saveToFile(std::ofstream& fout);
		void downloadFromFile(std::ifstream& fin);
};


