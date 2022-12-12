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
		p.setWeight();
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

void GTS::fillIdks() {
	idks.clear();
	for (auto& it : graph) {
		idks.emplace(it.first);
		for (int i : it.second) {
			if (!idks.contains(i)) idks.emplace(i);
		}
	}
}

void GTS::topological_sort(unordered_map<int, Pipe>& p) {
	checkIdStationsInPipe(p);
	fillIdks();
	int j = 0;
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

void GTS::createMatrix() {
	for (int i : idks) {
		unordered_map<int, double> q;
		for (int j : idks) {
			q.emplace(j, INFINITY);
		}
		matrixmin.emplace(i, q);
	}
}


void GTS::MinPath(unordered_map<int, Pipe>& p) {
	matrixmin.clear();
	checkIdStationsInPipe(p);
	fillIdks();

	int begin_index = GetCorrectNumber("Введите начальную вершину: ", 0, Station::idS);
	int end_index = GetCorrectNumber("Введите конечную вершину: ", 0, Station::idS);
	if (!idks.contains(begin_index) && !idks.contains(end_index)) {
		cout << "ERROR" << endl;
		return;
	}
	if (begin_index == end_index) {
		cout << "Минимальный вес: 0" << endl;
		return;
	}
	createMatrix();
	for (auto& it : p)
		if (it.second.getInputStation() != 0)
			matrixmin[it.second.getInputStation()][it.second.getOutputStation()] = it.second.getWeight();
	
	//Дейкстра
	unordered_map<int, double> minweight;
	unordered_map<int, bool> used;
	unordered_map<int, int> par;
	for (int j : idks) {
		minweight.emplace(j, INFINITY);
		used.emplace(j, false);
	}
	
	minweight[begin_index] = 0;
	
	int index = begin_index, u = 0;
	for (auto& it : matrixmin) {
		double min = INFINITY;
		for (auto& q : minweight) {
			if (!used[q.first] && q.second < min) {
				min = q.second;
				index = q.first;
			}
		}

		used[index] = true;
		for (auto& qm : it.second) {
			int j = qm.first;
			if (!used[j] && matrixmin[index][j] != INFINITY && minweight[index] != INFINITY && (minweight[index] + matrixmin[index][j]) < minweight[j]) {
				minweight[j] = minweight[index] + matrixmin[index][j];
				par[j] = index;
			}
		}
	}
	cout << "MIN way: " << minweight[end_index] << endl;

	//Восстановление пути
	vector<int> path;
	for (int v = end_index; v != begin_index; v = par[v])
		path.push_back(v);
	path.push_back(begin_index);
	reverse(path.begin(), path.end());

	//Вывод пути
	cout << endl << "{";
	for (int i : path)
		cout << i << "->";
	cout << "}" << endl;

	// Вывод матрицы
	for (auto& it : matrixmin) {
		cout << it.first << "{ ";
		for (auto& qw : it.second) {
			cout << qw.second << " ";
		}
		cout << "}" << endl;
	}
}

void GTS::MaxFlow(unordered_map<int, Pipe> &p){
	matrixmin.clear();
	checkIdStationsInPipe(p);
	fillIdks();
	createMatrix();

	int begin_index = GetCorrectNumber("Введите начальную вершину: ", 0, Station::idS);
	int end_index = GetCorrectNumber("Введите конечную вершину: ", 0, Station::idS);
	if (!idks.contains(begin_index) && !idks.contains(end_index)) {
		cout << "ERROR" << endl;
		return;
	}
	if (begin_index == end_index) {
		cout << "Максимальный поток: Inf" << endl;
		return;
	}
	for (auto& it : p)
		if (it.second.getInputStation() != 0)
			matrixmin[it.second.getInputStation()][it.second.getOutputStation()] = it.second.getThroughput();

}