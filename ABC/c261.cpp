#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits> 
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>
#include <array>
#include <numeric>
#include <unordered_map>

using namespace std;
using ll = long long;

int op(int x, int t, int a)
{
    if (t == 1) return x & a;
    else if (t == 2) return x | a;
    else return x ^ a;
}

int main()
{
    int n, c;
    cin >> n >> c;

    vector<int> t(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> a[i];
    }

    vector<int> fnc[2];
    fnc[0].resize(n);
    fnc[1].resize(n);

    for (int i = 0; i < n; i++) {
    }



    return 0;
}

#ifdef D

int main()
{
    int n, m;
    cin >> n >> m;

    vector<ll> X(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i];
    }
    vector<ll> Y(n+1, 0);
    for (int i = 0; i < m; i++) {
        int c; 
        ll  y;
        cin >> c >> y;
        Y[c] = y;
    }
    vector<ll> s(n + 1, 0);
    vector<ll> s2(n + 1, 0);
    ll M = 0;

    for (int i = 0; i < n; i++) {
        s2[0] = max(s[0], M);
        M = 0;
        for (int c = 1; c <= i+1; c++) {
            s2[c] = s[c - 1] + X[i] + Y[c];
            M = max(M, s2[c]);
        }
        s.swap(s2);
    }

    cout << M << endl;

    return 0;
}

#endif
