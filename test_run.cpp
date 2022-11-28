#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>


using namespace std;

using Participant = std::vector<int>(*)(string, string);


ostream& operator<<(ostream& out, vector<int> vec)
{
	for (int x : vec)
		out << x << ',';
	out << endl;

	return out;
}


void Run(string method_name, Participant p, string text, string sample)
{
	auto start = chrono::system_clock::now();
	vector<int> res = p(text, sample);
	auto stop = chrono::system_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

	cout << method_name << "\t"
		<< text.size() << "\t"
		<< ((res.size() != 0) ? to_string(time) + "\tmcs" : "failed") << endl;

	if (res.size() != 0)
		cout << "Number of inclusions: " << res.size() << endl;
	
}

