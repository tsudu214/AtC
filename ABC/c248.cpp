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

using ll = long long; // ~ 9*10^18

#ifdef D

int main()
{
    int n;
    cin >> n;

    map<int, vector<int>> A;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        A[a].push_back(i);
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;

        l--;
        int ans = 0;
        if (A.count(x)) {
            auto it = lower_bound(A[x].begin(), A[x].end(), l);
            int iL = it - A[x].begin();
            it = lower_bound(A[x].begin(), A[x].end(), r);
            int iR = it - A[x].begin();
            ans = iR - iL;
        }
        cout << ans << endl;
    }

    return 0;
}

#endif

#ifdef C

ll M = 998244353;

vector<vector<ll>> dp;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    dp = vector<vector<ll>>(n + 1, vector<ll>(k + 1, 0));
    for (int kk = 1; kk <= m; kk++) dp[1][kk] = 1;

    for (int nn = 2; nn <= n; nn++) {
        for (int kk = nn; kk <= k; kk++) {
            for (int mm = 1; mm <= m && mm < kk; mm++) {
                dp[nn][kk] += dp[nn - 1][kk - mm];
                dp[nn][kk] %= M;
            }
        }
    }

    ll ans = 0;
    for (int kk = n; kk <= k; kk++) {
        ans += dp[n][kk];
        ans %= M;
    }

    cout << ans << endl;

    return 0;
}

#endif

