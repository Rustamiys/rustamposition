#include "GTS.h"

GTS::GTS() {

};

void GTS::addGTS(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations) {
	
	int idStationIn = GetCorrectNumber("ID станции входа: ", 1, Station::idS);
	int idStationOut = GetCorrectNumber("ID станции выхода: ", 1, Station::idS);
	if ((idStationIn == idStationOut) || (!stations.contains(idStationOut)) || (!stations.contains(idStationIn))) {
		cout << "ERROR" << endl;
		return;
	}
	double d;
	cout << "Выберете диаметр(1 - 500; 2 - 700; 3 - 1400)" << endl;
	switch (GetCorrectNumber("Диаметр: ", 1, 3))
	{
		case 1:
		{
			d = 500.0;
			break;
		}
		case 2:
		{
			d = 700.0;
			break;
		}
		case 3:
		{
			d = 1400.0;
			break;
		}
	}
	set<int> foundPipes = findByFilter(pipes, checkPipeByDiametr, d);
	int q = 0;

	for (int i : foundPipes) {
		if (pipes[i].getInputStation() == 0) {
			pipes[i].setInputStation(idStationIn);
			pipes[i].setOutputStation(idStationOut);
			q = i;
			IncludeToGraph(pipes[q]);
			break;
		}
	}

	if (q == 0) {
		Pipe p;
		cin >> p;
		p.setDiametr(d);
		q = p.getId();
		pipes[q].setInputStation(idStationIn);
		pipes[q].setOutputStation(idStationOut);
		p.setThroughput();
		IncludeToGraph(pipes[q]);
	}
}

void GTS::checkIdStationsInPipe(unordered_map <int, Pipe>& pipes) {
	deleteAll();
	for (auto& it : pipes)
		if (it.second.getInputStation() != 0)
			IncludeToGraph(it.second);
}


void GTS::IncludeToGraph(Pipe p) {
	int in = p.getInputStation();
	int out = p.getOutputStation();

	if (!graph.contains(in)) {
		unordered_set<int> qw;
		qw.emplace(out);
		graph.emplace(in, qw);
	}
	else {
		graph[in].emplace(out);
	}
}

void GTS::deleteAll() {
	graph.clear();
	idks.clear();
}

void GTS::print() {
	for (auto& it : graph)
	{
		cout << "Вершина " << it.first << "{";
		for (int i : it.second) {
			cout << i << ";";
		}
		cout << "}" << endl;
	}
}

void GTS::dfs(int v) {
	used[v] = 1;
	for (int i : graph[v]) {
		if (used[i] == 0)
			dfs(i);
		else if (used[i] == 1) {
			cycl.emplace(-1);
			return;
		}
	}
	cycl.emplace(1);
	ans.push_back(v);
	used[v] = -1;
}


void GTS::topological_sort() {
	int j = 0;
	for (auto& it : graph) {
		idks.emplace(it.first);
		for (int i : it.second) {
			if (!idks.contains(i)) idks.emplace(i);
		}
	}
	
	for (int i : idks) {
		used.emplace(i, 0);
		j++;
	}

	ans.clear();	

	for (int i : idks) {
		if (!used[i]) dfs(i);
	}

	if (cycl.size() == 2) {
		cout << "В графе имеется цикл" << endl;
		return;
	}

	reverse(ans.begin(), ans.end());
	used.clear();
	for (int i : ans) {
		cout << i << " -> ";
	}
	cout << endl;
}


void GTS::MinWay() {

}
