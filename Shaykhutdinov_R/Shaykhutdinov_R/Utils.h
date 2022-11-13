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
	return obj.getName().find(parametr) != string::npos;
}

bool checkPipeByInRepair(const Pipe& p, bool parametr);

bool checkByPercent(const Station& s, double parametr);
