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

//------------------------------------------------------------------
// 2D geometry class
struct Point 
{
    Point() = default;
    Point(double x0, double y0) : x(x0), y(y0) {}

    Point operator+(const Point& q) const { return {x + q.x, y + q.y}; }
    Point operator-(const Point& q) const { return {x - q.x, y - q.y}; }
    Point operator*(double a) const { return {a * x, a * y}; }

    Point& operator+=(const Point& q) { x += q.x; y += q.y; return *this; }
    Point& operator-=(const Point& q) { x -= q.x; y -= q.y; return *this; }
    Point& operator*=(double a) { x *= a; y *= a; return *this; }

    double sqlen() const {
        return x * x + y * y;
    }

    double len() const {
        return sqrt(sqlen());
    }

    bool equal(const Point &q, double eps = 1e-10) const {
        return fabs(x - q.x) < eps && fabs(y - q.y) < eps;
    }

    Point norm() const {
        double a = 1./len();
        return {a*x, a*y};
    }

    double x;
    double y;
};

bool compare_x(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool compare_y(const Point &a, const Point &b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

typedef Point Vector;

using Polygon = vector<Point>;

double clamp(double x, double min, double max) 
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

double dot(const Vector& p, const Vector& q) 
{
    return p.x * q.x + p.y * q.y;
}

// outer-product of 2D vectors is scalar
double cross(const Vector& p, const Vector& q) {
    return p.x * q.y - p.y * q.x;
} 

Vector rotate(const Vector& v, double theta)
{
    double s = sin(theta);
    double c = cos(theta);
    return { v.x * c + v.y * s, -v.x * s + v.y * c };
}

int main()
{
    int n;
    cin >> n;

    cout << fixed << setprecision(8);

    vector<Point> P(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        P[i] = Point(x, y);
    }

    double dsqmax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            double dsq = (P[i] - P[j]).sqlen();
            if (dsq > dsqmax) {
                dsqmax = dsq;
            }
        }
    }

    cout << sqrt(dsqmax) << endl;

    return 0;
}

#ifdef C

ll n, x;
ll ans = 0;

void dfs(const vector<vector<ll>>& A, ll curr, ll i)
{
    for (auto& a : A[i]) {
        ll mul = (i == 0)? a : curr * a;
        if (i == n-1) {
            if ( mul == x ) {
                ans++;
            }
        }
        else {
            if (mul > x) continue;  // overflow!
            dfs(A, mul, i+1);
        }
    }
}

int main()
{
    cin >> n >> x;

    vector<vector<ll>> A(n);
    for (ll i = 0; i < n; i++) {
        ll l;
        cin >> l;
        A[i].resize(l);
        for (ll j = 0; j < l; j++) {
            cin >> A[i][j];
        }
    }

    dfs(A, 1, 0);

    cout << ans << endl;

    return 0;
}

#endif


