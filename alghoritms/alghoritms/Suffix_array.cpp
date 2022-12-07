#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <string>;

using namespace std;

vector < int > kasai(string s, vector < int > suf) {
    int n = suf.size();

    vector < int > lcp(n, 0);

    vector < int > inverseSuff(n, 0);
    int i, j;
    for (i = 0; i < n; i++)
        inverseSuff[suf[i]] = i;

    int k = 0;

    for (i = 0; i < n; i++) {
        if (inverseSuff[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suf[inverseSuff[i] + 1];

        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;

        lcp[inverseSuff[i]] = k;

        if (k > 0)
            k--;
    }

    return lcp;
}


vector<int> brute_force(string s, string p) {
    auto start = chrono::system_clock::now();
    int M = p.size();
    int N = s.size();
    vector<int> res;

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
        {
            if (s[i + j] != p[j]) break;
        }
        if (j == M)
            res.push_back(i);
    }

    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << "Find by brute force: " << time << endl;
    return res;
}

vector<int> suffix_array(string s) {
    s += ' ';
    int n = (int)s.size(),
        cnt = 0,  // вспомогательная переменная: счётчик для сортировки 
        cls = 0;  // количество классов эквивалентности
    vector<int> c(n), p(n);
    map<int, vector<int>> t;

    for (int i = 0; i < n; i++)
        t[s[i]].push_back(i);

    // «нулевой» этап
    for (auto& x : t) {
        for (int u : x.second)
            c[u] = cls, p[cnt++] = u;
        cls++;
    }

    // пока все суффиксы не стали уникальными
    for (int l = 1; cls < n; l++) {
        vector< vector<int> > a(cls);  // массив для сортировки подсчётом
        vector<int> _c(n);  // новые классы эквивалентности
        int d = (1 << l) / 2;
        int _cls = cnt = 0;  // новое количество классов

        for (int i = 0; i < n; i++) {
            int k = (p[i] - d + n) % n;
            a[c[k]].push_back(k);
        }

        for (int i = 0; i < cls; i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                // если суффикс начинает новый класс эквивалентности
                if (j == 0 || c[(a[i][j] + d) % n] != c[(a[i][j - 1] + d) % n])
                    _cls++;
                _c[a[i][j]] = _cls - 1;
                p[cnt++] = a[i][j];
            }
        }

        c = _c;
        cls = _cls;
    }

    return vector<int>(p.begin() + 1 , p.end());
}



vector<int> find_index_by_suffix_array(string s, string p) {
    auto start = chrono::system_clock::now();

    int n = s.size(), q = p.size();

    vector<int> suf = suffix_array(s);
    vector<int> lcp = kasai(s, suf);
    vector<int> res;

    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << "Sort suffix array: " << time << endl;

    //lower_bound
    int l = 0, r = s.size() - 1;
    int m;
    int b;

    while (r > l) {
        m = (l + r) / 2;
        for (int i = 0; i < q; i++) {
            string tt{ s[suf[m] + i] }, pp{ p[i] };
            b = strcmp(tt.c_str(), pp.c_str());
            if (b != 0) break;
        }

        if (b == -1) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }
    //upper_bound
    int l1 = 0, r1 = s.size() - 1;
    int m1;
    int b1;

    while (r1 > l1) {
        m1 = (r1 + l1) / 2;

        for (int i = 0; i < q; i++) {
            string tt{ s[suf[m1] + i] }, pp{ p[i] };
            b1 = strcmp(tt.c_str(), pp.c_str());
            if (b1 != 0) break;
        }

        if (b1 == 1) {
            r1 = m1;
        }
        else {
            l1 = m1 + 1;
        }

    }

    res.push_back(suf[l]);
    for (int i = l; i <= s.size(); i++) {
        if (lcp[i] >= p.size()) {
            res.push_back(suf[i+1]);
        }
        else {
            break;
        }
    }

    for (int i = l; i < l1; i++)
        res.push_back(suf[i]);


    auto stop1 = chrono::system_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(stop1 - stop).count();

    cout << "Find in suffix array: ";
    cout << time1 << endl;

    return res;
}


int main() {
    ifstream fin;

    fin.open("DataSet.txt", ios::in);
    string text;

    while (!fin.eof())
    {
        string newLine;
        getline(fin, newLine);
        text += newLine;
    }

    fin.close();

    string sample = "ab";

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') text[i] = '_';
    }
    for (int i = 0; i < sample.size(); i++) {
        if (sample[i] == ' ') sample[i] = '_';
    }

    vector<int> res1 = find_index_by_suffix_array(text, sample);
    vector<int> res2 = brute_force(text, sample);



    set<int> suf, br, suf1;

    for (int i : res1)
        suf.emplace(i);

    for (int i : res2)
        br.emplace(i);
    
    cout << (br == suf? "Equal " : "not equal ") << endl;

    cout << "Size " << text.size();


    return 0;
}

