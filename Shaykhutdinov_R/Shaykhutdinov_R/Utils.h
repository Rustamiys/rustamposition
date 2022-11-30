#pragma once
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"

using namespace std;

void clearBuffer();

void printMenu();

set<int> GetIdByUserinput();

template <typename T>
T GetCorrectNumber(string text, T min, T max) {
	cout << text;
	
	T number;
	cin >> number;
	if (max <= min) return max;
	for (;;) {
		if (cin.fail() || number < min || number > max) {
			clearBuffer();
			cout << "¬ведите корректные данные(" << min << "-" << max << "): ";
			cin >> number;
		}
		else {
			return number;
		}
	}
}

template <typename T1, typename T2>
using Filter = bool(*)(const T1& obj, T2 parametr);
template <typename T1, typename T2>
set<int> findByFilter(unordered_map<int, T1>& objects, Filter<T1, T2> f, T2 parametr) {
	set<int> result;
	for (auto& it : objects)
	{
		if (f(it.second, parametr))
		{
			result.emplace(it.first);
		}
	}
	return result;
}

template <typename T>
bool checkByName(const T& obj, string parametr) {
	size_t q = obj.getName().find(parametr);
	return obj.getName().find(parametr) != string::npos;
}

bool checkPipeByInRepair(const Pipe& p, bool parametr);

bool checkPipeByDiametr(const Pipe& p, double parametr);

bool checkByPercent(const Station& s, double parametr);

template <typename T>
void deleteObject(unordered_map <int, T>& obj, int id) {
	obj.erase(id);
}

template <typename T>
void deleteObject(unordered_map <int, T>& obj) {
	obj.clear();
}

void downloadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations);

void saveToFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations);
