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

vector<int> x;
vector<bool> visited;
vector<vector<int>> Sx;

void update(int v, int w)
{
    vector<int> Sall;
    Sall.reserve(40);
    for (int i = 0; i < 20; i++) {
        Sall.push_back(Sx[w][i]);
        Sall.push_back(Sx[v][i]);
    }
    sort(Sall.begin(), Sall.end(), greater<int>());
    copy(Sall.begin(), Sall.begin() + 20, Sx[v].begin());
}

void query(vector<vector<int>>& G, int v, int p)
{
    Sx[v][0] = x[v];

    for (auto & w : G[v]) {
        if (p >= 0 && p == w) {
            continue;
        }
        if (!visited[w]) {
            query(G, w, v);
            update(v, w);
        }
    }

    visited[v] = true;
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<vector<int>> G;
    G.resize(n);

    visited.resize(n);
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    x.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    Sx.resize(n);
    for (int i = 0; i < n; i++) {
        Sx[i] = vector<int>(20, -1);
    }

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    query(G, 0, -1);

    for (int i = 0; i < q; i++) {
        int v, k;
        cin >> v >> k;
        v--; k--;

        cout << Sx[v][k] << endl;
    }

    return 0;
}

#if D

bool isPrime(int &n)
{
    if (n <= 1)  return false;

    for (int i = 2; i < n; ++i)
        if (n % i == 0)
            return false;

    return true;
}

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int min_s = a + c;
    int max_s = b + d;

    set<int> P;
    for (int s = min_s; s <= max_s; s++) {
        if (isPrime(s)) {
            P.insert(s);
        }
    }
    for (int x = a; x <= b; x++) {
        bool not_find = true;
        for (int y = c; y <= d; y++) {
            if (P.count(x + y) > 0) {
                not_find = false;
                break;
            }
        }
        if (not_find) {
            cout << "Takahashi" << endl;
            return 0;
        }
    }

    cout << "Aoki" << endl;

    return 0;
}

#endif

#if C
struct Point {
    Point(int x_, int y_) : x(x_), y(y_) {}

    Point operator+(const Point& q) const { return {x + q.x, y + q.y}; }
    Point operator-(const Point& q) const { return {x - q.x, y - q.y}; }

    bool equal(const Point &q) const {
        return x == q.x && y == q.y;
    }

    int x;
    int y;
};

vector<Point> Get8points(const Point& p) {
    vector<Point> v;
    v.push_back(p + Point(2, 1));
    v.push_back(p + Point(1, 2));
    v.push_back(p + Point(-1, 2));
    v.push_back(p + Point(-2, 1));
    v.push_back(p + Point(-2, -1));
    v.push_back(p + Point(-1, -2));
    v.push_back(p + Point(1, -2));
    v.push_back(p + Point(2, -1));
    return v;
}

int main()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    vector<Point> v1 = Get8points(Point(x1, y1));
    vector<Point> v2 = Get8points(Point(x2, y2));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (v1[i].equal(v2[j])) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}

#endif
