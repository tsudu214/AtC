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

int query(vector<vector<int>>& G, int x, int k, vector<vector<int>>& dp)
{
    if (dp[x][k] > 0) {
        return dp[x][k];
    }
    int sum = x;
    for (auto q : G[x]) {
        int s = query(G, q, k - 1, dp);
        sum += s;
    }
    dp[x][k] = sum;
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<vector<int>> dp(n + 1);
    for (int i = 0; i < n + 1; i++) {
        dp[i] = { i, 0, 0, 0 };
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        int ans = query(G, x, k, dp);
        cout << ans << endl;
    }

    return 0;
}


#ifdef D

int main()
{
    ll n;
    cin >> n;

    vector<ll> x(n);
    for (ll i = 0; i < n; i++) {
        x[i] = i+1;
    }

    for (ll i = 2; i <= n; i++) {
        ll s = i * i;
        if (s > n) break;

        for (ll j = s; j <= n; j += s) {
            while (x[j - 1] % s == 0) {
                x[j - 1] /= s;
            }
        }
    }

    vector<ll> cnt(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        cnt[x[i]]++;
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += cnt[i] * cnt[i];
    }

    cout << ans << endl;

    return 0;
}
#endif

#ifdef C

int main()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> A(k);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int m = i % k;
        A[m].push_back(a);
    }
    for (int m = 0; m < k; m++) {
        sort(A[m].begin(), A[m].end());
    }

    int count = 0;
    int last = 0;
    while (true) {
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < k; m++) {
                if (last > A[m][i]) {
                    cout << "No" << endl;
                    return 0;
                }
                last = A[m][i];
                count++;
                if (count == n) {
                    cout << "Yes" << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}

#endif

