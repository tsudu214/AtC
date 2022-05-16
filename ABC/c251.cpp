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

int main()
{
    int w;
    cin >> w;

    cout << 297 << endl;
    int h = 1;
    for (int k = 0; k < 3; k++) {
        for (int i = 1; i < 100; i++) {
            if (i > 0) cout << " ";
            cout << i * h;
        }
        h *= 100;
    }
    cout << endl;

    return 0;
}

#ifdef E

ll n;
vector<ll> A;
ll inf = 1LL << 60;

vector<ll> dp[2];

void dfs(ll i, int first)
{
    if (i == n-1) {
        if (first == 0) {
            dp[0][n - 1] = inf;
            dp[1][n - 1] = A[n - 1];
        }
        else {
            dp[0][n - 1] = 0;
            dp[1][n - 1] = A[n - 1];
        }
        return;
    }
    dfs(i + 1, first);

    dp[0][i] = dp[1][i + 1];
    dp[1][i] = min(dp[0][i + 1], dp[1][i + 1]) + A[i];

    if (i == 0) {
        dp[1 - first][0] = inf;
    }
}

int main()
{
    cin >> n;

    A.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> A[i];
    }

    dp[0].resize(n+1, inf);
    dp[1].resize(n+1, inf);

    dfs(0, 0);
    ll val0 = dp[0][0];
    dfs(0, 1);
    ll val1 = dp[1][0];

    cout << min(val0, val1) << endl;

    return 0;
}

#endif