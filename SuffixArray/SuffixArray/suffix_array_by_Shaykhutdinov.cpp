#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>

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
vector<int> suffix_array1(string s) {
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

    return vector<int>(p.begin() + 1, p.end());
}

vector<int> suffix_array2(string s) {
    s += " ";
    int n = s.size();
    vector<int> p(n), c(n);
    {
        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { s[i], i };
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + int(a[i - 1].first != a[i].first);
        }
    }
    int k = 0;
    while ((1 << k) < n && c[p[n - 1]] < n - 1) {  // for early termination
        // k -> k + 1
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { {c[i], c[(i + (1 << k)) % n]}, i };
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + int(a[i - 1].first != a[i].first);
        }
        k++;
    }
    return p;
}


vector<int> suffix_array3(string s) {
    s+=" ";
    int n = s.size();
    int ALPHABET = 256;
    vector<int> c(n), new_c(n), suf(n), new_suf(n), starts(max(n, ALPHABET + 1));
    for (int i = 0; i < n; i++) {
        suf[i] = i;
        c[i] = s[i];
        starts[s[i] + 1]++;
    }
    int sum = 0;
    for (auto& v : starts) {
        sum += v, v = sum;
    }
    for (int l = 0; l < n; l = (l ? 2 * l : 1)) {
        for (auto v : suf) {
            int pos = (v - l + n) % n;
            new_suf[starts[c[pos]]++] = pos;
        }
        int type = -1;
        long long last = -1;
        for (int i = 0; i < n; i++) {
            int v = new_suf[i];
            if (last != (c[v] * 1ll * max(n, ALPHABET + 1) + c[(v + l) % n])) {
                last = (c[v] * 1ll * max(n, ALPHABET + 1) + c[(v + l) % n]);
                starts[++type] = i;
            }
            new_c[v] = type;
        }
        swap(c, new_c);
        swap(suf, new_suf);
    }
    return suf;
}

struct SuffixCmp {
    SuffixCmp(const string& _text) : text(_text) {}

    bool operator()(int i, int j) const
    {
        return text.substr(i) < text.substr(j);
    }

    const string& text;
};

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
static vector<int> suffix_array4(string& text)
{
    vector<int> result;
    int n = (int)text.size();

    for (int i = 0; i < n; i++) {
        result.push_back(i);
    }

    sort(result.begin(), result.end(), SuffixCmp(text));

    return result;
}

vector<int> suffix_array5(string S) {
    int N = S.size();
    vector<int> sa(N), classes(N);
    for (int i = 0; i < N; i++) {
        sa[i] = N - 1 - i;
        classes[i] = S[i];
    }
    stable_sort(sa.begin(), sa.end(), [&S](int i, int j) {
        return S[i] < S[j];
        });
    for (int len = 1; len < N; len *= 2) {
        vector<int> c(classes);
        for (int i = 0; i < N; i++) {
            bool same = i && sa[i - 1] + len < N
                && c[sa[i]] == c[sa[i - 1]]
                && c[sa[i] + len / 2] == c[sa[i - 1] + len / 2];
            classes[sa[i]] = same ? classes[sa[i - 1]] : i;
        }
        vector<int> cnt(N), s(sa);
        for (int i = 0; i < N; i++)
            cnt[i] = i;
        for (int i = 0; i < N; i++) {
            int s1 = s[i] - len;
            if (s1 >= 0)
                sa[cnt[classes[s1]]++] = s1;
        }
    }
    return sa;
}

vector<int> lcp_array(const vector<int>& sa, string S) {
    int N = S.size();
    vector<int> rank(N), lcp(N - 1);
    for (int i = 0; i < N; i++)
        rank[sa[i]] = i;

    int pre = 0;
    for (int i = 0; i < N; i++) {
        if (rank[i] < N - 1) {
            int j = sa[rank[i] + 1];
            while (max(i, j) + pre < S.size() && S[i + pre] == S[j + pre])
                ++pre;
            lcp[rank[i]] = pre;
            if (pre > 0)
                --pre;
        }
    }
    return lcp;
}

vector<int> z_algorithm(string S) {
    int N = S.size(), L = 0, R = 0;
    vector<int> Z(N, 0);
    Z[0] = N;
    for (int i = 1; i < N; i++) {
        if (i < R)
            Z[i] = min(R - i, Z[i - L]);
        while (i + Z[i] < N && S[i + Z[i]] == S[Z[i]])
            ++Z[i];
        if (i + Z[i] > R)
            L = i, R = i + Z[i];
    }
    return Z;
}

vector<int> search(string S, string P) {
    int N = S.size(), M = P.size();
    string combined = P + S;
    vector<int> Z = z_algorithm(combined);
    vector<int> matches;
    for (int i = 0; i < N; i++) {
        if (Z[M + i] >= M) {
            matches.push_back(i);
        }
    }
    return matches;
}

vector<int> brute_force(string s, string p) {
    int M = p.size();
    int N = s.size();

    vector<int> suf;

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
        {
            if (s[i + j] != p[j]) break;
        }
        if (j== M)
            suf.push_back(i);
    }
    return suf;
}


vector <int> find_index_by_suffix_array(string text, string subtext) {
    //vector<int> qw = brute_force(text, subtext);
    vector<int> qw = search(text, subtext);
    //return vector<int> qw = search(text, subtext);
    //for (int i = 0; i < qw.size(); i++) cout << qw[i] << " ";
    return  qw;

    int n = text.size(), q = subtext.size();
    vector<int> p(n, 0);
    for (int i = 0; i < n; i++) {
        if (text[i] == ' ') text[i] = '_';
    }
    for (int i = 0; i < q; i++) {
        if (subtext[i] == ' ') subtext[i] = '_';
    }
    //return p;
    string s = text + subtext;
    vector<int> suf = suffix_array3(s);
   // return p;
    vector<int> lcp = kasai(s, suf);
    //return p;
    vector<int> res;

    for (int i = 0; i < n; i++) {
        if (suf[i] == n) {
            for (int j = i; j < n; j++) {
                if (lcp[j] >= q) {
                    res.push_back(suf[j + 1]);
                }
                else {
                    return res;
                }
            }

            return res;
        }
    }
    return res;
}
