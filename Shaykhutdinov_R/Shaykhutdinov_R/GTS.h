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
		set<int> idSelectedPipes;
		int id;
		unordered_map<int, unordered_set<int>> graph;
		unordered_set<int> idks;
		
		unordered_map<int, int> used;
		
		vector<int> ans;
		set<int> cycl;
		vector<int> cl;
	public:
		GTS();
		static int idG;
		void addGTS(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations);
		void IncludeToGraph(Pipe p);
		vector<int> tsort();
		void dfs(int v);
		void dfs1(int v, int p);
		void topological_sort();
};


