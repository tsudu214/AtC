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
    ll n, k;
    cin >> n >> k;

    vector<ll> sum(n+1);
    sum[0] = 0;
    for (ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        sum[i+1] = sum[i] + a;
    }

    ll ans = 0;
    for (int s = 0; s < n; s++) {
        auto t = lower_bound(sum.begin() + s, sum.end(), sum[s] + k);
        if ( t != sum.end()) {
            auto n = upper_bound(t, sum.end(), sum[s] + k);
            for (auto i = t; i < n; ++i) {
                if (*i == sum[s] + k) ans ++;
            }
        }
    }

    cout << ans << endl;

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


