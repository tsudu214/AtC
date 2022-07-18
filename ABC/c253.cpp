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

ll MOD = 998244353;


int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<ll>> dp(m);
    for (int a = 0; a < m; a++) {
        dp[a].resize(n);
        dp[a][0] = max<ll>(0, a - k + 1) + max<ll>(0, m - a - k);
    }
    for (int i = 1; i < n-1; i++) {
        for (int a = 0; a < m; a++) {
            dp[a][i] = 0;
            for (int b = 0; b < m; b++) {
                if (abs(a - b) < k) continue;
                dp[a][i] += dp[b][i-1];
                dp[a][i] %= MOD;
            }
        }
    }

    ll ans = 0;
    for (int a = 0; a < m; a++) {
        ans += dp[a][n - 2];
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}

#ifdef D

ll gcd(ll a, ll b) {
    if (a % b == 0) {
        return b;
    }
    else {
        return gcd(b, a % b);
    }
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

ll sum(ll a, ll n) 
{
    return a * n * (n + 1) / 2;
}

int main()
{
    ll a, b, n;
    cin >> n >> a >> b;

    ll c = lcm(a, b);

    ll S = sum(1, n);
    ll sa = sum(a, n / a);
    ll sb = sum(b, n / b);
    ll sc = sum(c, n / c);

    cout << S - sa - sb + sc << endl;

    return 0;
}

#endif

#ifdef C

int main()
{
    map<int, int> S;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k, x, c;
        cin >> k;
        if (k == 1) {
            cin >> x;
            S[x]++;
        }
        else if (k == 2) {
            cin >> x >> c;
            if (S[x] > c) {
                S[x] -= c;
            }
            else {
                S.erase(x);
            }
        } 
        else {
            if (!S.empty()) {
                cout << S.rbegin()->first - S.begin()->first << endl;
            }
        }
    }

    return 0;
}

#endif