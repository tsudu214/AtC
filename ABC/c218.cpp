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

private:
    vector<int> rank;
    vector<int> p;

};

struct edge {
    int from;
    int to;
    ll  cost;
};

void kruskal(int v, vector<edge>& edges, vector<edge>& mst)
{
    sort(edges.begin(), edges.end(), 
        [](const auto& a, const auto& b) { return a.cost < b.cost; }
    );

    mst.clear();

    DisjointSet ds(v);
    for ( auto& e : edges ) {
        if ( e.cost < 0 ) {
            ds.unite(e.from, e.to);
            mst.push_back(e);
        }
        else if (ds.findSet(e.from) != ds.findSet(e.to)) {
            ds.unite(e.from, e.to);
            mst.push_back(e);
        }
    }
}

int main()
{
    int v, e;
    cin >> v >> e;

    vector<edge> edges;

    for (int i = 0; i < e; i++) {
        int s, t; ll w;
        cin >> s >> t >> w;
        s--; t--;
        if (s > t) swap(s, t);
        edge E = {s, t, w};
        edges.push_back(E);
    }

    ll sum_ini = accumulate(edges.begin(), edges.end(), 
        0LL, 
        [](ll sum, auto& e){ return sum + e.cost;}
    );

    vector<edge> mst;
    kruskal(v, edges, mst);

    ll sum = accumulate(mst.begin(), mst.end(), 
        0LL, 
        [](ll sum, auto& e){ return sum + e.cost;}
    );

    cout << sum_ini - sum << endl;

    return 0;
}


#ifdef D

struct point {
    int xy[2];
    point(int x, int y) { xy[0] = x; xy[1] = y;}
    int x() const { return xy[0]; }
    int y() const { return xy[1]; }

    bool operator<(const point& p) const {
        if (x() != p.x()) 
            return x() < p.x();
        else 
            return y() < p.y();
    } 
};

int main()
{
    vector<point> X;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        X.push_back(point(x, y));
    }

    sort(X.begin(), X.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (X[i].x() >= X[j].x()) continue;
            if (X[i].y() >= X[j].y()) continue;

            point p = point(X[i].x(), X[j].y());
            if ( binary_search(X.begin(), X.end(), p) == false ) continue;
            point q = point(X[j].x(), X[i].y());
            if ( binary_search(X.begin(), X.end(), q) == false ) continue;
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}

#endif

#ifdef C

struct point {
    int xy[2];
    point(int x, int y) { xy[0] = x; xy[1] = y;}
    int x() const { return xy[0]; }
    int y() const { return xy[1]; }

    bool operator<(const point& p) const {
        if (x() != p.x()) 
            return x() < p.x();
        else 
            return y() < p.y();
    } 
};

int main()
{
    int n;

    cin >> n;

    vector<point> S[4], T;

    for (int i = 0; i < n; i++) {
        string buf;
        cin >> buf;
        for (int j = 0; j < n; j++) {
            if (buf[j] == '#') {
                S[0].push_back(point(i,j));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        string buf;
        cin >> buf;
        for (int j = 0; j < n; j++) {
            if (buf[j] == '#') {
                 T.push_back(point(i,j));
            }
        }
    }

    int m = (int)S[0].size();

    if (m != T.size()) {
        cout << "No" << endl;
        return 0;
    }
    if (m == 1) {
        cout << "Yes" << endl;
        return 0;
    }

    for (auto& p : S[0]) {
        S[1].push_back(point(p.y(), n - 1 - p.x()));
        S[2].push_back(point(n - 1 - p.x(), n - 1 - p.y()));
        S[3].push_back(point(n - 1 - p.y(), p.x()));
    }

    for (int t = 1; t < 4; t++) {
        sort(S[t].begin(), S[t].end());
    }

    for (int t = 0; t < 4; t++) {
        vector<point> SS = S[t];
        int vx = T[0].x() - SS[0].x();
        int vy = T[0].y() - SS[0].y();
        for (auto & p : SS) {
            p.xy[0] = p.x() + vx;
            p.xy[1] = p.y() + vy;
        }

        bool same = true;
        for (int i = 0; i < m; i++) {
            if (SS[i].x() != T[i].x() || SS[i].y() != T[i].y()) {
                same = false;
            }
        }
        if (same) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}

#endif