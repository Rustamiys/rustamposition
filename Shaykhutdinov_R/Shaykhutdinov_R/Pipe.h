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
		

	public:
		Pipe();

		std::string getName() const;
		float getLength() const;
		float getDiametr() const;
		bool getInRepair() const;
		static int id;

		void setName(std::string name);
		void setLength(float length);
		void setDiametr(float diametr);
		void setInRepair(bool in_repair);
};


