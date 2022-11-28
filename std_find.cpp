#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<int> std_find(string text, string sample)
{
	vector<int> wordPositions;
	
	int i = 0;

	for (i = text.find(sample); i != string::npos; i = text.find(sample, i + 1))
	{
		wordPositions.push_back(i);
	}
	return wordPositions;
}