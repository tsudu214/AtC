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
    ll n;
    ll k;
    cin >> n >> k;
    vector<ll> A(n);
    vector<ll> An(n);

    for (ll i = 0; i < n; i++) {
        cin >> A[i];
        An[i] = A[i] % n;
    }
    map<ll, ll> xn;
    ll x = 0;
    xn[0]++;
    for (ll i = 1; i < k; i++) {
        ll b = x % n;
        x += An[b];
        x = x % n;
        xn[x]++;
    }
    ll s = 0;
    for (auto t : xn) {
        s += t.second * A[t.first];
    }

    cout << s << endl;


    return 0;
}

#ifdef D
int main()
{
    int q;
    cin >> q;

    map<ll, int> A;
    for (int i = 0; i < q; i++) {
        int fnc, k;
        ll x;
        cin >> fnc >> x;
        if (fnc == 1) {
            A[x]++;
        }
        else if (fnc == 2) {
            cin >> k;
            auto it = A.upper_bound(x);
            if (it == A.begin()) {
                cout << -1 << endl;
            }
            else {
            it--;
            vector<ll> Q;
            int count = 0;
            for (int j = 0; j < 5 && count <= 5; j++) {
                for (int v = 0; v < it->second; v++) {
                    Q.push_back(it->first);
                    count++;
                }
                if (it == A.begin()) break;
                it--;
            }
            if (count < k) {
                cout << -1 << endl;
            } else {
                cout << Q[k-1] << endl;
            }
            }
        }
        else {
            cin >> k;
            auto it = A.lower_bound(x);
            vector<ll> Q;
            int count = 0;
            for (int j = 0; j < 5 && count <= 5; j++) {
                if (it == A.end()) break;
                for (int v = 0; v < it->second; v++) {
                    Q.push_back(it->first);
                    count++;
                }
                it++;
            }
            if (count < k) {
                cout << -1 << endl;
            } else {
                cout << Q[k-1] << endl;
            }

        }
    }

    return 0;
}
#endif

#ifdef C

int collect(vector<vector<int>>& S, int flag, int i, int j)
{
    int x = 0;
    if (flag == 0) {
        for (int k = 0; k < 6; k++) {
            x += S[i+k][j+k];
        }
        return x;
    }
    else if (flag == 1) {
        for (int k = 0; k < 6; k++) {
            x += S[i+k][j+5-k];
        }
        return x;
    }
    else if (flag == 2) {
        for (int k = 0; k < 6; k++) {
            x += S[i][j+k];
        }
        return x;
    }
    else {
        for (int k = 0; k < 6; k++) {
            x += S[i+k][j];
        }
        return x;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> S(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<int> si(n);
        for (int j = 0; j < n; j++) {
            if (s[j] == '#') {
                si[j] = 1;
            } else {
                si[j] = 0;
            }
        }
        S[i] = si;
    }

    for (int i = 0; i <= n-6; i++) {
        for (int j = 0; j <= n-6; j++) {
            int x = collect(S, 0, i, j);
            if (x >= 4) {
                cout << "Yes" << endl;
                return 0;
            }
            x = collect(S, 1, i, j);
            if (x >= 4) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n-6; j++) {
            int x = collect(S, 2, i, j);
            if (x >= 4) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i <= n-6; i++) {
        for (int j = 0; j < n; j++) {
            int x = collect(S, 3, i, j);
            if (x >= 4) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}

#endif