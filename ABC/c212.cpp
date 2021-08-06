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

ll dp[5010][5010];  //[k][v]
ll M = 998244353;
 
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
 
    vector<vector<int>> g(n);
 
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    for (int i = 0; i < k+1; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
 
    ll total = 1;
    for (int i = 1; i <= k; i++) {
        for (int v = 0; v < n; v++) {
            dp[i][v] = total - dp[i-1][v];
            for (auto& u : g[v]) {
                dp[i][v] -= dp[i-1][u];
            }
            dp[i][v] = (dp[i][v]%M + M)%M;
        }
        total = 0;
        for (int u = 0; u < n; u++) {
            total = total + dp[i][u];
            total %= M;
        }
    }
 
    cout << dp[k][0] << endl;
 
    return 0;
}

#ifdef D

priority_queue<ll, deque<ll>, greater<ll>> Q;

int main()
{
    int q;
    cin >> q;

    ll sum = 0;

    for (int i = 0; i < q; i++) {
        int com;
        ll x;
        cin >> com;
        if (com == 1) {
            cin >> x;
            Q.push(x - sum);
        }
        if (com == 2) {
            cin >> x;
            sum += x;
        }
        if (com == 3) {
            ll xmin = Q.top(); Q.pop();
            cout << xmin + sum << endl;
        }
    }

    return 0;
}

#endif
