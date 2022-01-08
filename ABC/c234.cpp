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
    
    ll x;
    cin >> x;

    int deci = 0;
    ll  r = x;
    while (r > 0) {
        deci++;
        r /= 10;
    }
    if (deci <= 2) {
        cout << x << endl;
        return 0;
    }

    vector<ll> v;

    int j;

    // D = 0
    for (int i = 1; i <= 9; i++) {
        for (int d = 3; d <= 16; d++) {
            ll c = i;
            for (j = 1; j < d; j++) {
                c *= 10;
                c += i;
            }
            if (j == d)
            v.push_back(c);
        }
    } 
    // D = 1
    for (int i = 1; i <= 9; i++) {
        for (int d = 3; d <= 16; d++) {
            ll c = i;
            for (j = 1; j < d && i+j <= 9; j++) {
                c *= 10;
                c += i+j;
            }
            if (j == d)
            v.push_back(c);
            if (c % 10 == 9) break;
        }
    } 
    for (int i = 1; i <= 9; i++) {
        for (int d = 3; d <= 16; d++) {
            ll c = i;
            for (j = 1; j < d && i-j >= 0; j++) {
                c *= 10;
                c += i-j;
            }
            if (j == d)
            v.push_back(c);
            if (c % 10 == 0) break;
        }
    } 
    // D = 2
    for (int i = 1; i <= 9; i++) {
        for (int d = 3; d <= 16; d++) {
            ll c = i;
            for (j = 1; j < d && i+j*2 <= 9; j++) {
                c *= 10;
                c += i+j*2;
            }
            if (j == d)
            v.push_back(c);
            if (c % 10 >= 8) break;
        }
    } 
    for (int i = 1; i <= 9; i++) {
        for (int d = 3; d <= 16; d++) {
            ll c = i;
            for (j = 1; j < d && i-j*2 >= 0; j++) {
                c *= 10;
                c += i-j*2;
            }
            if (j == d)
            v.push_back(c);
            if (c % 10 <= 1) break;
        }
    } 
    // D = 3
    v.push_back(147);
    v.push_back(258);
    v.push_back(369);
    v.push_back(9630);
    v.push_back(963);
    v.push_back(630);
    v.push_back(852);
    v.push_back(741);
    // D = 4
    v.push_back(159);
    v.push_back(951);
    v.push_back(840);

    sort(v.begin(), v.end());

    auto it = lower_bound(v.begin(), v.end(), x);

    cout << *it << endl;

    return 0;
}

#ifdef D
int main()
{
    int n, k;
    cin >> n >> k;

    set<int> S;
    int p;
    for (int i = 0; i < k; i++) {
        cin >> p;
        S.insert(p);
    }
    cout << *S.begin() << endl;
    int m = 1e10;
    for (int i = k; i < n; i++) {
        cin >> p;
        if (!S.empty()) m = *S.begin();
        if (p > m) {
            S.erase(S.begin());
            S.insert(p);
            m = *S.begin();
        }
        cout << m << endl;
    }

    return 0;
}

#endif

#ifdef C

string toBinary(ll n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    reverse(r.begin(), r.end());
    return r;
}

int main()
{
    ll k;
    cin >> k;

    string s = toBinary(k);

    int L = s.length();
    for (int i = 0; i < L; i++) {
        if (s[i] == '1') s[i] = '2';
    }

    cout << s << endl;

    return 0;
}

#endif

