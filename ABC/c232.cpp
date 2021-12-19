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
    ll h, w, k;
    cin >> h >> w >> k;

    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ll M = 998244353;

    if (k == 1) {
        if (x1 == x2 || y1 == y2) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }
    if (k == 2) {
        if (x1 == x2 && y1 == y2) {
            cout << w + h - 2 << endl;
        }
        else if (x1 == x2) {
            cout << w-1 << endl;
        }
        else if (y1 == y2) {
            cout << h-1 << endl;
        }
        else {
            cout << 2 << endl;
        }
        return 0;
    }

    x1--;x2--;y1--;y2--;

    // k >= 3
    vector<vector<ll>> C;
    C.resize(h);
    for (ll i = 0; i < h; i++) {
        C[i].resize(w);
    }

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if (i == x2 && j == y2) 
                C[i][j] = w + h - 2;
            else if (i == x2) 
                C[i][j] = w - 1;
            else if (j == y2)
                C[i][j] = h - 1;
        }
    }

    for (ll n = 3; n <= k; n++) {
        for (ll i = 0; i < h; i++) {
            for (ll j = 0; j < w; j++) {
              for (ll ii = 0; ii < h; ii++) {
                  if (ii != i) {
                      C[i][j] += 1;
                      C[i][j] %= M;
                  }
              }
              for (ll jj = 0; jj < w; jj++) {
                  if (jj != j) {
                      C[i][j] += 1;
                      C[i][j] %= M;
                  }
              }
            }
        }
    }

    cout << C[x1][y1] << endl;

    return 0;
}

#if D
int main()
{
    int h, w;
    cin >> h >> w;

    vector<vector<int>> C;
    C.resize(h);
    for (int i = 0; i < h; i++) {
        C[i].resize(w);
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c;
            cin >> c;
            if (c == '#') C[i][j] = -1;
            else C[i][j] = 0;
        }
    }

    typedef pair<int, int> P;

    queue<P>  Q;
    Q.push(make_pair(0, 0));
    C[0][0] = 1;
    
    while(!Q.empty()) {
        P curr = Q.front(); Q.pop();
        int i = curr.first;
        int j = curr.second;
        if (i < h-1 && C[i+1][j] == 0) {
            P next = make_pair(i+1, j);
            C[i+1][j] = C[i][j] + 1;
            Q.push(next);
        }
        if (j < w-1 && C[i][j+1] == 0) {
            P next = make_pair(i, j+1);
            C[i][j+1] = C[i][j] + 1;
            Q.push(next);
        }
    }

    int ans = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ans = max(C[i][j], ans);
        }
    }

    cout << ans << endl;

    return 0;
}
#endif


#if C
struct Toy {
    void add(int a, int b) {
        if (a > b) swap(a, b);
        g.push_back(make_pair(a, b));
    }
    void complete() {
        sort(g.begin(), g.end());
    }
    vector<int> dump() {
        vector<int> data;
        for ( auto& e : g) {
            data.push_back(e.first);
            data.push_back(e.second);
        }
        return data;
    }
    vector<pair<int, int>> g;
};

int main()
{
    int n, m;
    cin >> n >> m;

    Toy Ta, Ao;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        Ta.add(a, b);
    }
    Ta.complete();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        Ao.add(a, b);
    }
    Ao.complete();

    vector<int>  TaData = Ta.dump();
    vector<int>  AoData = Ao.dump();

    // convert v[]
    std::vector<int> v;
    for (int k = 1; k<=n; k++) { v.push_back(k); }

    do {
        Toy Mov;
        for (int i = 0; i < m; i++) {
            int a = TaData[2*i];
            int b = TaData[2*i+1];
            a = v[a-1];
            b = v[b-1];
            Mov.add(a, b);
        }
        Mov.complete();
        vector<int> MovData = Mov.dump();
        if (AoData == MovData) {
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(v.begin(), v.end()));

    cout << "No" << endl;

    return 0;
}

#endif