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
    int q;
    cin >> q;

    queue<ll> Q;
    priority_queue<ll, vector<ll>, greater<ll>> PQ;

    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if ( c == 1 ) {
            ll x;
            cin >> x;
            Q.push(x);
        }
        else if ( c == 2 ) {
            ll y;
            if (PQ.empty()) {
                y = Q.front();
                Q.pop();
            } else {
                y = PQ.top();
                PQ.pop();
            }
            cout << y << endl;
        }
        else {
            while (!Q.empty()) {
                ll y = Q.front();
                Q.pop();
                PQ.push(y);
            }
        }
    }

    return 0;
}



#ifdef D

set<ll> S;

int main()
{
    ll L;
    int q;
    cin >> L >> q;
    S.insert(0); S.insert(L);

    for (int i = 0; i < q; i++) {
        int c;
        ll x;
        cin >> c >> x;
        if (c == 1) {
            S.insert(x);
        }
        else {
            auto max = S.upper_bound(x);
            auto min = prev(max);

            ll d = *max - *min;
            cout << d << endl;
        }
    }

    return 0;
}

#endif