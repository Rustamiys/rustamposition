#pragma once
#include <string>


class Pipe {
	private:
		std::string name;
		double length;
		double diametr;
		bool inRepair;
		int id;
		int inputStation;
		int outputStation;
		int throughput;

	public:
		Pipe();

		std::string getName() const;
		double getDiametr() const;
		bool getInRepair() const;
		int getId() const;
		int getInputStation() const;
		int getOutputStation() const;
		static int idP;

		void editPipe(bool inRepair);
		void saveToFile(std::ofstream& fout);
		void setInputStation(int id);
		void setOutputStation(int id);
		void setThroughput();
		void setDiametr(double diametr);
		void downloadFromFile(std::ifstream& fin);
		friend std::istream& operator >> (std::istream& in, Pipe& p);
		friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};


