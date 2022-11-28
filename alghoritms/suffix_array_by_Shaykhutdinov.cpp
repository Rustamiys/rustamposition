#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cmath>

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


//Построение за О(nlog(n))
vector<int> suffix_array(string s) {
    s += '#';  // добавляем нулевой символ в конец строки
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
    
    return vector<int>(p.begin() + 1, p.end());
}

vector <int> find_index_by_suffix_array(string text, string subtext) {
    int n = text.size(), q = subtext.size();
    int n = text.size(), q = subtext.size();

    for (int i = 0; i < n; i++) {
        if (text[i] == " ") text[i] = "_";
    }
    for (int i = 0; i < q; i++) {
        if (subtext[i] == " ") subtext[i] = "_";
    }
    string s = text + subtext;
    vector<int> suf = suffix_array(s);
    vector<int> lcp = kasai(s, suf);
    vector<int> res;

    for (int i = 0; i < n; i++) {
        if (suf[i] == n) {
            for (int j = i; j < n; j++) {
                if (lcp[j] >= q) {
                    res.push_back(suf[j+1]);
                }
                else {
                    break;
                }
            }
            return res;
        }
    }
    return res;
}
