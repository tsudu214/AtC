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

    map<ll, ll> event;

    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;

        event[a]++;
        event[a+b]--;
    }

    vector<ll> d(n+1);

    ll last = 0;
    ll current = 0;
    for (auto & e : event) {
        d[current] += e.first - last;
        current += e.second;
        last = e.first;
    }

    for (int i = 1; i <= n; i++ ) {
        if (i > 1) cout << " ";
        cout << d[i];
    }
    cout << endl;

    return 0;
}


#ifdef C

int main()
{
    int n;
    cin >> n;

    vector<int>  digit;

    while (n > 0) {
        int p = n/10;
        int q = n - p*10;
        n = p;
        digit.push_back(q);
    }

    sort(digit.begin(), digit.end(), greater<int>());

    int m = digit.size();
    ll a = 0, b = 0;
    if (m % 2 == 0) {
        for (int i = 0; i < m/2; i++) {
            if (i > 0) {
                a *= 10;
                b *= 10;
            }
            if (a < b) {
                a += (ll)digit[2*i];
                b += (ll)digit[2*i+1];
            } else {
                b += (ll)digit[2*i];
                a += (ll)digit[2*i+1];
            }
        }
    }
    else {
        for (int i = 0; i < m/2; i++) {
            if (i > 0) {
                a *= 10;
                b *= 10;
            }
            if (a < b) {
                a += (ll)digit[2*i];
                b += (ll)digit[2*i+1];
            } else {
                b += (ll)digit[2*i];
                a += (ll)digit[2*i+1];
            }
        }
        if (a < b) {
            a = a*10 + (ll)digit[m-1];
        } else {
            b = b*10 + (ll)digit[m-1];
        }
    }

    cout << a * b << endl;

    return 0;
}

#endif