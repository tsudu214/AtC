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

int main()
{
    int n;
    ll x;
    cin >> n >> x;

    ll INF = 1LL << 60;

    vector<ll> a(n);
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cin >> b[i];
    }

    vector<ll> T(n, INF);
    vector<ll> D(n);
    D[0] = a[0] + b[0];
    for (int i = 1; i < n; i++) {
        D[i] = D[i - 1] + a[i] + b[i];
    }

    vector<ll> m(n, INF);
    m[0] = b[0];
    for (int i = 1; i < n; i++) {
        m[i] = min(m[i - 1], b[i]);
    }

    ll ans = INF;
    if (x < n) {
        for (int i = 0; i < x; i++) {
            T[i] = D[i] + (x - 1 - i) * m[i];
            ans = min(ans, T[i]);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            T[i] = D[i] + (n - 1 - i) * m[i];
            ans = min(ans, T[i] + (x - n) * m[i]);
        }
    }
    cout << ans << endl;

    return 0;
}


#ifdef C

int main()
{
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    int start = 0;

    for (int i = 0; i < q; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            start = (start - x + n)%n;
        }
        else {
            cout << s[(start + x - 1)%n] << endl;
        }
    }

    return 0;
}

#endif

#ifdef B

struct pos {
    int x;
    int y;
    pos(int _x, int _y): x(_x), y(_y) {};

    pos next(int n, int k) const{
        int nx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
        int ny[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

        int xx = x + nx[k];
        int yy = y + ny[k];
        if (xx < 0) xx = n - 1;
        if (xx > n - 1) xx = 0;
        if (yy < 0) yy = n - 1;
        if (yy > n - 1) yy = 0;

        return pos(xx, yy);
    }
};

ll ans = 0;

vector<pos> search_max(int n, vector<vector<int>>& A) 
{
    int m = 0;
    vector<pos> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] > m) {
                v.clear();
                m = A[i][j];
                v.push_back(pos(i, j));
            }
            else if (A[i][j] == m) {
                v.push_back(pos(i, j));
            }
        }
    }
    return v;
}

int main()
{
    int n = 0;
    cin >> n;
    vector<vector<int>> A;
    A.resize(n);

    for (int i = 0; i < n; i++) {
        A[i].resize(n);
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            A[i][j] = s[j] - '0';
        }
    }

    vector<pos> s = search_max(n, A);

    ll ans = 0;
    for (int k = 0; k < 8; k++) {
        for (int i = 0; i < s.size(); i++) {
            ll curr = 0;
            pos p = s[i];
            curr = A[p.x][p.y];
            for (int j = 0; j < n - 1; j++) {
                pos q = p.next(n, k);
                int d = A[q.x][q.y];
                curr = curr * 10 + d;
                p = q;
            }
            ans = max(ans, curr);
        }
    }

    cout << ans << endl;

    return 0;
}

#endif

 
