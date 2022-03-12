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

using ll = long long; // 9,223,372,036,854,775,807 = 9*10^18

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
    int cost;
};

void kruskal(int v, vector<edge>& edges, vector<edge>& mst, int** D)
{
    sort(edges.begin(), edges.end(), 
        [](const auto& a, const auto& b) { return a.cost < b.cost; }
    );

    mst.clear();

    DisjointSet ds(v);
    for ( auto& e : edges ) {
        if (ds.findSet(e.from) != ds.findSet(e.to)) {
            ds.unite(e.from, e.to);
            mst.push_back(e);
            if (e.cost)
            D[e.from][e.to] = D[e.to][e.from] = e.cost;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    int D[300][300];
    int INF = 2000000000;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            D[i][j] = INF;
        }
    }

    vector<edge> edges(m);

    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a--; b--;
        edges[i] = {a, b, c};
    }

    vector<edge> mst;
    kruskal(n, edges, mst, D);

    cout << m - mst.size() << endl;

    return 0;
}


#ifdef D
int main()
{
    int n;
    ll  x;
    cin >> n >> x;

    string s;
    cin >> s;

    string s2;
    int last = -1;
    for (int i = 0; i < n; i++) {
        if (last >= 0 && s[i] == 'U' && s2[last] != 'U') {
            last--;
            s2.pop_back();
        }
        else {
            s2.push_back(s[i]);
            last++;
        }
    }

    for (int i = 0; i < s2.size(); i++) {
        if (s2[i] == 'U') {
            x /= 2;
        }
        else if (s2[i] == 'L') {
            x = 2*x;
        }
        else {
            x = 2*x + 1;
        }
    }

    cout << x << endl;

    return 0;
}

#endif

#ifdef C
struct Point{
    Point() {}
    Point(int i, ll xx, ll yy) : id(i),  x(xx), y(yy) {}
    int id;
    ll x;
    ll y;
};

bool collide(vector<Point>& group, string& s)
{
    int m = (int)group.size();
    if (m < 2) return false;

    sort(group.begin(), group.end(), [](auto& a, auto& b){ return a.x < b.x; } );

    int R = m;
    for (int i = 0; i < m; i++ ) {
        if (s[group[i].id] == 'R') {
            R = i;
        }
        else {
            if (i > R) return true;
        }
    }

    return false;
}

int main()
{
    int n;
    cin >> n;

    vector<Point> v(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        v[i] = Point(i, x, y);
    }
    string s;
    cin >> s;

    map<ll, vector<Point>> mapY;
    for (int i = 0; i < n; i++) {
        mapY[v[i].y].push_back(v[i]);
    }

    for (auto e : mapY) {
        if (collide(e.second, s)) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}

#endif