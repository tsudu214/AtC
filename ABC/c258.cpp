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
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    for (int i = 0; i < q; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            string sub1 = s.substr(0, n - x);
            string sub2 = s.substr(n - x, x);
            reverse(sub2.begin(), sub2.end());
            s = sub2 + sub1;
        }
        else {
            cout << s[x-1] << endl;
        }
    }

    return 0;
}

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

 
