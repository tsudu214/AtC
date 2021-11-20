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

ll search_a(ll n)
{
    ll low = 1;
    ll high = n;
    ll mid = (1+n)/2;
    while (low <= high) {
        mid = (low + high) / 2;
        if (mid*mid*mid > n) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return mid;
}

ll search_b(ll a, ll n)
{
    ll low = a;
    ll high = n;
    ll mid = (1+n)/2;
    while (low <= high) {
        mid = (low + high) / 2;
        if (a*mid*mid > n) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return mid;
}

ll search(ll a, ll b, ll n)
{
    ll low = b;
    ll high = n;
    ll mid = (b+n)/2;
    while (low <= high) {
        mid = (low + high) / 2;
        if (a*b*mid > n) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return mid;
}

int main()
{
    ll n;
    cin >> n;

    ll ans = 0;

    ll am = search_a(n);

    for (ll a = 1; a <= am; a++) {
        if (a*a*a > n) break;

        ll bm = search_b(a, n);
        for (ll b = a; b <= bm; b++) {
            if (a*b*b > n) break;

            ll m = search(a, b, n);
            if (a*b*m > n) {
                m--;
            }
            if (m >= b) {
                ans += (m - b + 1);
            } else {
                break;
            }
        }
    } 

    cout << ans << endl;
    
    return 0;
}

