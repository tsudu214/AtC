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


