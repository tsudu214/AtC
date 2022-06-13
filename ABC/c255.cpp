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
    int n, m;
    cin >> n >> m;

    vector<ll> s(n-1);
    set<ll> X;
    for (int i = 0; i < n - 1; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        ll x;
        cin >> x;
        X.insert(x);
    }

    vector<ll> b(n);
    b[0] = 0;
    for (int i = 1; i < n; i++) {
        b[i] = s[i-1] - b[i - 1];
    }
    // a[i] = -a0 + b[i] (i%2 == 1)
    //      =  a0 + b[i] (i%2 == 0)

    map<ll, int> a0count;
    for (auto & x : X) {
        // x[j] = a[i]
        for (int i = 0; i < n; i++) {
            ll a0;
            if (i % 2 == 0) {
                a0 = x - b[i];
                a0count[a0]++;
            }
            else {
                a0 = b[i] - x;
                a0count[a0]++;
            }
        }
    }

    int nmax = 0;
    for (auto& a : a0count) {
        nmax = max(nmax, a.second);
    }

    cout << nmax << endl;

    return 0;
}


#ifdef D

int main()
{
    int n, q;;
    cin >> n >> q;

    vector<int> a(n);
    vector<ll>  s(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int m = a[0];
    int M = a[n - 1];
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        s[i] = sum;
    }

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        ll ans = 0;

        if (x <= m) {
            ans = s[n - 1] - (ll)x * n;
        }
        else if (x >= M) {
            ans = (ll)x * n - s[n - 1];
        }
        else {
            int k = lower_bound(a.begin(), a.end(), x) - a.begin();
            ll ans1 = (ll)x * k - s[k-1];
            ll ans2 = s[n - 1] - s[k-1] - (ll)x * (n - k);
            ans = ans1 + ans2;
        }
        cout << ans << endl;
    }

    return 0;
}

#endif

#ifdef C

int main()
{
    ll x, a, d, n;
    cin >> x >> a >> d >> n;

    ll m, M;
    if (d > 0) {
        m = a;
        M = a + (n - 1) * d;
    }
    else {
        M = a;
        m = a + (n - 1) * d;
    }

    ll  ans = 0;
    if (x <= m) {
        ans = labs(x - m);
    }
    else if (x >= M) {
        ans = labs(x - M);
    }
    else {
        ll s = x - m;
        ll b = s / labs(d);
        ll r = s - labs(d) * b;
        ans = min(labs(d) - r, r);
    }

    cout << ans << endl;

    return 0;
}

#endif



