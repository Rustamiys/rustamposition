#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <unordered_set>
#include <vector>

class GTS
{
	private:
		unordered_map<int, unordered_set<int>> graph;
		unordered_set<int> idks;

		unordered_map<int, int> used;
		vector<int> ans;
		set<int> cycl;
		
	public:
		GTS();
		void addGTS(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations);
		void checkIdStationsInPipe(unordered_map<int, Pipe>& pipes);
		void IncludeToGraph(Pipe p);
		void deleteAll();
		void print();
		void dfs(int v);
		void fillIdks();
		void topological_sort();
		void MinPath(unordered_map<int, Pipe>& p);
};


