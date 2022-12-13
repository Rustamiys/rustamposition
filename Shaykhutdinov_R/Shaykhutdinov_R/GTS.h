#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <unordered_set>
#include <vector>
#include <queue>

class GTS
{
	private:
		unordered_map<int, unordered_set<int>> graph;
		unordered_set<int> idks;

		unordered_map<int, int> used;
		vector<int> ans;
		set<int> cycl;
		unordered_map<int, unordered_map<int, double>> matrixmin;
		
	public:
		GTS();
		void addGTS(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations);
		void checkIdStationsInPipe(unordered_map<int, Pipe>& pipes);
		void IncludeToGraph(Pipe p);
		void deleteAll();
		void print();
		void dfs(int v);
		void fillIdks();
		void topological_sort(unordered_map<int, Pipe>& p);
		void createMatrix();
		void printMatrix();
		void MinPath(unordered_map<int, Pipe>& p);
		bool bfs(int s, int t, unordered_map<int, int> & parent);
		void MaxFlow(unordered_map<int, Pipe>& p);
};


