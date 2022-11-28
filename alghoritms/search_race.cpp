// search_race.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <array>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

using Participant = std::vector<int>(*)(string, string);

void Run(string method_name, Participant p, string text, string sample);

string readFrom(ifstream&);


#define RUN(x) {                \
    Run(#x, x, text, sample);           \
}


//place your method name here
vector<int> std_find(string, string);
vector <int> rabinKarp(string, string);
vector<int> knut_morris_pratt(string, string);
vector<int> AXAMAC(string, string);
vector<int> find_index_by_suffix_array(string, string);


int main()
{
    string text;
    ifstream fin;
    fin.open("dataSet1.txt", ios::in);
    /*
    * Здесь будут подставляться входные данные
      Попозже подыщу какие-нибудь универсальные наборы, пока можете на этом случайном попробовать
    */
    text = readFrom(fin);
   
    fin.close();

    string sample = "ab";

    fin.open("dataSet2.txt", ios::in);
    sample = readFrom(fin);

    fin.close();

    //run your method here
    RUN(std_find);
    RUN(rabinKarp);
    RUN(knut_morris_pratt);
    RUN(AXAMAC);
    RUN(find_index_by_suffix_array);
}



string readFrom(ifstream& fin)
{
    string text;
    while (!fin.eof())
    {
        string newLine;
        getline(fin, newLine);
        text += newLine;
    }
    return text;
}