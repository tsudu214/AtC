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

ll Cnk(ll n, ll k)
{
    ll ans = 1;
    for (ll i = 0; i < k; i++) {
        ans *= (n - i);
    }
    for (ll i = 0; i < k; i++) {
        ans /= (i + 1);
    }
    return ans;
}

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;

    int ans = 0;
    while (true) {
        if (a >= b) break;
        a *= k;
        ans++;
    }

    cout << ans << endl;

    return 0;
}


