#include <iostream>
#include <vector>

using namespace std;
void preKmp(string x, vector<int> kmpNext);
vector<int> AXAMAC(string x, string y);


void preKmp(string x, vector<int> kmpNext) {
    int i, j;
    int m = x.length();

    i = 0;
    j = kmpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = kmpNext[j];
        i++;
        j++;
        if ((i < m) && (x[i] == x[j]))
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}
vector<int> AXAMAC(string y, string x) {
    int m = x.length(), n = y.length();
    int i, j, k, ell;
    vector<int> kmpNext(m+1, 0);
    vector<int> v;


    preKmp(x, kmpNext);
    for (ell = 1; x[ell - 1] == x[ell]; ell++);
    if (ell == m)
        ell = 0;


    i = ell;
    j = k = 0;
    while (j <= n - m) {
        while (i < m && x[i] == y[i + j])
            ++i;
        if (i >= m) {
            while (k < ell && x[k] == y[j + k])
                ++k;
            if (k >= ell)
                v.push_back(j);
        }
        j += (i - kmpNext[i]);
        if (i == ell)
            k = max(0, k - 1);
        else
            if (kmpNext[i] <= ell) {
                k = max(0, kmpNext[i]);
                i = ell;
            }
            else {
                k = ell;
                i = kmpNext[i];
            }
    }
    return v;
}
