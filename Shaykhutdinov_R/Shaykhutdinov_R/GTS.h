#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <set>
#include <vector>

class GTS
{
	private:
		set<vector<int>> GTS;
		int id;
	public:
		unordered_map <int, Pipe> pipes;
		unordered_map <int, Station> stations;
		static int idG;
};

