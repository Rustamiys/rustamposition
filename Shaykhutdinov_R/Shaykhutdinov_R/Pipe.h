#pragma once
#include <string>


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
		bool getInRepair() const;
		int getId() const;
		static int idP;

		void setInRepair(bool in_repair);
		void editPipe();
		void saveToFile(std::ofstream& fout);
		void downloadFromFile(std::ifstream& fin);
		friend std::istream& operator >> (std::istream& in, Pipe& p);
		friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};


