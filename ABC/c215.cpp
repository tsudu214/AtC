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
    int n;
    cin >> n;

    ll dist_x = 0, dist_y = 0;

    map<ll, int> Sx, Sy;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        Sx[x]++;
        Sy[y]++;
    }

    ll prev_x = -1, prev_y = -1;
    for ( auto& x : Sx ) {
        if (prev_x >= 0) {
            dist_x = max(dist_x, x.first - prev_x);
        }
        prev_x = x.first;
    }
    for ( auto& y : Sy ) {
        if (prev_y >= 0) {
            dist_y = max(dist_x, y.first - prev_y);
        }
        prev_y = y.first;
    }

    cout << min(dist_x, dist_y) << endl;

    return 0;
}


#ifdef C

int main()
{
    string s;
    int k;
    cin >> s >> k;

    int n = s.size();
    vector<char> sc(n);
    for (int i = 0; i < n; i++) {
        sc[i] = s[i];
    }
    sort(sc.begin(), sc.end());

    for (int j = 1; j < k; j++) {
        next_permutation(sc.begin(), sc.end());
    }

    for (int i = 0; i < n; i++) {
        cout << sc[i];
    }
    cout << endl;

    return 0;
}

#endif

#ifdef D

vector<pair<ll, ll> > prime_factorize(ll N) {
    vector<pair<ll, ll> > res;
    for (ll a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
        long long ex = 0; 

        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        res.push_back({a, ex});
    }

    if (N != 1) res.push_back({N, 1});
    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<bool> v(m+1, true);
    set<ll> S;
    for (int i = 0; i < n; i++){
        vector<pair<ll, ll>> pk = prime_factorize((ll)a[i]);
        for (auto&  p : pk) {
            S.insert(p.first);
        }
    }

    for (auto& k : S) {
        for (int j = 1; j * k <= m; j++) {
            v[j*k] = false;
        }
    }

    vector<int>  ans;
    ans.push_back(1);
    for (int i = 2; i <= m; i++) {
        if (v[i]) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << endl;
    for (auto & a : ans) {
        cout << a << endl;
    }

    return 0;
}

#endif