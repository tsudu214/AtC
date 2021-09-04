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

multiset<ll>S;
deque<ll> A;

int main()
{
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int c;
        ll x;
        cin >> c;
        if (c == 1) {
            cin >> x;
            A.push_back(x);
            S.insert(x);
        }
        else if (c == 2) {
            ll y = A.front();
            A.pop_front();
            cout << y << endl;
            S.erase(S.find(y));
        }
        else {
            copy(S.begin(), S.end(), A.begin());
        }
    }

    return 0;
}

#ifdef D

set<ll> S;
set<ll, greater<ll>> R;

int main()
{
    ll L;
    int q;
    cin >> L >> q;
    S.insert(0); S.insert(L);
    R.insert(0); R.insert(L);

    for (int i = 0; i < q; i++) {
        int c;
        ll x;
        cin >> c >> x;
        if (c == 1) {
            S.insert(x);
            R.insert(x);
        }
        else {
            auto min = R.upper_bound(x);
            auto max = S.upper_bound(x);

            ll d = *max - *min;
            cout << d << endl;
        }
    }

    return 0;
}

#endif