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
    DisjointSet(){}
    DisjointSet(int size){
        rank_.resize(size, 0);
        p_.resize(size, 0); 
        size_.resize(size, 0);
        for (int i = 0; i < size; i++) {
            makeSet(i);
        }
    }

    void makeSet(int x)
    {
        p_[x] = x;
        rank_[x] = 0;
        size_[x] = 1;
    }

    int size(int x) {
        return size_[findSet(x)];
    }

    void unite(int x, int y)
    {
        x = findSet(x);
        y = findSet(y);
        if (rank_[x] > rank_[y]) {
            p_[y] = x;
            size_[x] += size_[y];
        }
        else {
            p_[x] = y;
            if (rank_[x] == rank_[y]) {
                rank_[y]++;
            }
            size_[y] += size_[x];
        }
    }

    int findSet(int x) 
    {
        if (p_[x] != x) {
            p_[x] = findSet(p_[x]);
        }
        return p_[x];
    }

private:
    vector<int> rank_;
    vector<int> p_;
    vector<int> size_;

};

struct edge {
    int from;
    int to;
    int cost;
};

int main()
{
    int n;
    cin >> n;
    vector<edge> edges(n-1);

    for (int i = 0; i < n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        edges[i] = edge {u, v, w};
    }

    sort(edges.begin(), edges.end(), 
        [](auto a, auto b) { return a.cost < b.cost; }
    );
    ll sum = 0;

    DisjointSet Ds(n);

    for (auto& E : edges) {
        sum += (ll)Ds.size(E.from) * (ll)Ds.size(E.to) * (ll)E.cost;
        Ds.unite(E.from, E.to);
    }

    cout << sum << endl;

    return 0;
}

#ifdef C

ll INF = LLONG_MAX;

int main()
{
    int n;
    cin >> n;

    vector<ll> s(n);
    vector<ll> t(n);

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    vector<ll> ans(n, INF);

    while (true) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            int prev = (i+n-1)%n;
            ll x = t[i];
            if (ans[prev] != INF ) {
                x = min(x, ans[prev] + s[prev]);
            }
            if (x < ans[i]) {
                update = true;
                ans[i] = x;
            }
        }
        if (!update) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}

#endif

