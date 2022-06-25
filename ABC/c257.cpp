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

class DisjointSet
{
public:
    DisjointSet() {}
    DisjointSet(int size) {
        rank.resize(size, 0);
        p.resize(size, 0);
        for (int i = 0; i < size; i++) {
            makeSet(i);
        }
    }

    void makeSet(int x)
    {
        p[x] = x;
        rank[x] = 0;
    }

    void unite(int x, int y)
    {
        x = findSet(x);
        y = findSet(y);
        if (rank[x] > rank[y]) {
            p[y] = x;
        }
        else {
            p[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

    int findSet(int x)
    {
        if (p[x] != x) {
            p[x] = findSet(p[x]);
        }
        return p[x];
    }

    bool isUnited()
    {
        int p0 = findSet(0);
        for (size_t i = 1; i < p.size(); i++) {
            if (findSet(i) != p0) {
                return false;
            }
        }
        return true;
    }

private:
    vector<int> rank;
    vector<int> p;
};


struct edge {
    int i; 
    int j;
    ll  D;
    double d;
};

int main()
{
    int n;
    cin >> n;
    vector<ll> p(n);
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> p[i];
    }

    vector<edge> E;
    E.reserve(n * (n - 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            ll D = llabs(x[i] - x[j]) + llabs(y[i] - y[j]);
            double d = (double)D / (double)p[i];
            edge e = { i, j, D, d };
            E.push_back(e);
        }
    }
    sort(E.begin(), E.end(), [](auto& a, auto& b) { return a.d < b.d; });

    DisjointSet DS(n);

    ll s = 1;
    for (int i = 0; i < E.size(); i++) {
        if (E[i].D <= s * p[E[i].i]) {
            DS.unite(E[i].i, E[i].j);
        }
        else {
            if (DS.isUnited()) break;
            s = ll(E[i].D / (double)p[E[i].i] + 0.5);
            DS.unite(E[i].i, E[i].j);
        }
        if (DS.isUnited()) break;
    }

    cout << s << endl;

    return 0;
}

#ifdef C

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int n0 = 0;
    int n1 = 0;
    vector<pair<int, int>> vP;
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        int a = (s[i] == '0') ? 0 : 1;
        vP.push_back(make_pair(w, a));
        if (a == 0) n0++;
        else n1++;
    }
    sort(vP.begin(), vP.end());

    int count = n1;
    int cmax = n1;
    for (int i = 0; i < n; i++) {
        int w = vP[i].first;
        int a = vP[i].second;
        if (a == 0) count++;
        else count--;
        if (i == n - 1 || vP[i + 1].first != w) {
            cmax = max(cmax, count);
        }
    }

    cout << cmax << endl;

    return 0;
}

#endif


