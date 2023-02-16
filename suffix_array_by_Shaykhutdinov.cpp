#include <iostream>
#include <cmath>
#include <algorithm>

#include <chrono>
#include <fstream>
#include <set>
using namespace std;


@ - 163, 115 + 165, 9 @@ vector<int> suffix_array3(string s) {
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
    auto start = chrono::system_clock::now();
    int M = p.size();
    int N = s.size();

    @ - 286, 16 + 182, 17 @@ vector<int> brute_force(string s, string p) {
        if (j == M)
            suf.push_back(i);
    }
    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << time << endl;
    return suf;
}


vector <int> find_index_by_suffix_array(string text, string subtext) {
    //vector<int> qw = brute_force(text, subtext);
    vector<int> qw = search(text, subtext);
    //return vector<int> qw = search(text, subtext);
    //for (int i = 0; i < qw.size(); i++) cout << qw[i] << " ";
    return  qw;
    //return  qw;
    auto start = chrono::system_clock::now();

    int n = text.size(), q = subtext.size();
    vector<int> p(n, 0);
    @ - 308, 10 + 205, 13 @@ vector <int> find_index_by_suffix_array(string text, string subtext) {
        //return p;
        string s = text + subtext;
        vector<int> suf = suffix_array3(s);
        // return p;
        vector<int> lcp = kasai(s, suf);
        //return p;
        vector<int> lcp = kasai(s, suf);
        //return p; 
        vector<int> res;
        auto stop = chrono::system_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
        cout << "Sort suffix array1: " << time << endl;

        for (int i = 0; i < n; i++) {
            if (suf[i] == n) {
                @ - 320, 12 + 220, 200 @@ vector <int> find_index_by_suffix_array(string text, string subtext) {
                    res.push_back(suf[j + 1]);
                }
            else {
                auto stop1 = chrono::system_clock::now();
                auto time1 = chrono::duration_cast<chrono::microseconds>(stop1 - stop).count();
                cout << "Find in Suffix array1:" << time1 << endl;
                return res;
            }
            }

            //stop = chrono::system_clock::now();
            //auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
            //cout << time << endl;
            return res;
        }
    }
    //auto stop = chrono::system_clock::now();
    //auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    //cout << time << endl;
    return res;
}


vector<int> find_LCP(string s, string p) {
    auto start = chrono::system_clock::now();

    int n = s.size(), q = p.size();

    vector<int> suf = suffix_array3(s);
    vector<int> lcp = kasai(s, suf);
    vector<int> res;

    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << "Sort suffix array2: " << time << endl;

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

    /*res.push_back(suf[l]);
    for (int i = l; i <= s.size(); i++) {
        if (lcp[i] >= p.size()) {
            res.push_back(suf[i+1]);
        }
        else {
            break;
        }
    }*/

    for (int i = l; i < l1; i++)
        res.push_back(suf[i]);


    auto stop1 = chrono::system_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(stop1 - stop).count();

    cout << "Sort suffix array2: ";
    cout << time1 << endl;

    return res;
}


int main() {
    ifstream fin;

    fin.open("dataSet1.txt", ios::in);
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
    vector<int> res3 = find_LCP(text, sample);


    set<int> suf, br, suf1;

    for (int i : res1)
        suf.emplace(i);

    for (int i : res1)
        br.emplace(i);

    for (int i : res3)
        suf1.emplace(i);


    cout << (br == suf) << endl;
    cout << (br == suf1) << endl;



    return 0;
}

//145306




// C program for iterative implementation
// of the above approach

#include <stdio.h>

// Function to implement lower_bound
int lower_bound(int arr[], int N, int X)
{
    int mid;

    int low = 0;
    int high = N;
    while (low < high) {
        mid = low + (high - low) / 2;

        if (X <= arr[mid]) {
            high = mid;
        }

        else {
            low = mid + 1;
        }
    }
    return low;
}
int upper_bound(int arr[], int N, int X)
{
    int mid;
    int low = 0;
    int high = N;

    while (low < high) {
        mid = low + (high - low) / 2;

        if (X >= arr[mid]) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    return low;
}
