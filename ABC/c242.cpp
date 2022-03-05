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

int result(const string& s, ll t, ll k) 
{
    int n = s.size();

    int curr = 0;
    int a = 0;
    ll m = k-1;  // S(t) ‚Ì m=0,1,... section
    for (ll i = t; i > 0; i--) {
        int move = m%2 ? 0 : 1;
        int two[2];
        if (curr == 0) {
            two[0] = 1; two[1] = 2;
        }
        if (curr == 1) {
            two[0] = 2; two[1] = 0;
        }
        if (curr == 2) {
            two[0] = 0; two[1] = 1;
        }
        curr = two[move];
        m = m/2;
        if (m == 0 && i > 1) {
            a = (i-1) % 3;
            break;
        }
    }

    int start = s[m] - 'A';
    start += a;
    start %= 3;

    if (curr == 0) {
        return start;
    }
    else if (curr == 1) {
        return (start + 2)%3;
    }
    else {
        return (start + 1)%3;
    }
}

int main()
{
    string s;
    cin >> s;

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        ll t, k;
        cin >> t >> k;

        cout << (char)(result(s, t, k) + 'A') << endl;
    }

    return 0;
}

#ifdef C
int main()
{
    vector<ll> curr(9, 1);
    vector<ll> next(9, 1);
    ll M = 998244353;

    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 0) {
                next[j] = curr[0] + curr[1]; 
            }
            else if (j == 8) {
                next[j] = curr[7] + curr[8];
            }
            else {
                next[j] = curr[j-1] + curr[j] + curr[j+1];
            }
            next[j] %= M;
        }
        copy(next.begin(), next.end(), curr.begin());
    }

    ll s = 0;
    for (int j = 0; j < 9; j++) {
        s += curr[j];
        s %= M;
    }

    cout << s <<  endl;

    return 0;
}

#endif