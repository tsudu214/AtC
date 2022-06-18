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

struct Person {
    int id;
    int dislike;
    ll  cost;
};

int main()
{
    int n;
    cin >> n;
    vector<Person> P(n);
    for (int i = 0; i < n; i++) {
        P[i].id = i;
        cin >> P[i].dislike;
    }
    for (int i = 0; i < n; i++) {
        cin >> P[i].cost;
    }

    sort(P.begin(), P.end(), [](auto a, auto b) { return a.cost > b.cost; });
    
    ll ans = 0;

    cout << ans << endl;

    return 0;
}

#ifdef D

ll INF = 2e5 + 10;

int main() 
{
    int n; 
    cin >> n; 
    set<pair<ll, ll>> st;

    st.insert(make_pair(-INF, -INF));
    st.insert(make_pair(INF, INF));
    for (int i = 0; i < n; i++) {
        ll x, y; 
        cin >> x >> y;; 

        auto it = st.lower_bound(make_pair(x, y)); it--;

        if (it->first <= x && x <= it->second) {
            x = min(x, it->first); 
            y = max(y, it->second);
            st.erase(it);
        }

        it = st.lower_bound(make_pair(x, y));
        while (1) { 
            if (x <= it->first && it->first <= y) {
                y = max(y, it->second);
                it = st.erase(it); 
            }
            else break;
        }
        st.insert(make_pair(x, y));
    }

    for (auto& r : st) {
        if (r.first == INF || r.first == -INF) continue;
        cout << r.first << " " << r.second << endl;
    }
}

#endif

#ifdef C

int main()
{
    int h1, h2, h3, w1, w2, w3;
    cin >> h1 >> h2 >> h3 >> w1 >> w2 >> w3;

    int ans = 0;
    for (int i = 1; i <= min(h1-2, w1-2); i++) {
        for (int j = 1; j <= min(h1 - 2, w2 - 2); j++) {
            for (int l = 1; l <= min(h2 - 2, w1 - 2); l++) {
                for (int m = 1; m <= min(h2 - 2, w2 - 2); m++) {
                    int k = h1 - i - j;
                    int n = h2 - l - m;
                    if (k <= 0 || n <= 0) continue;
                    int o = w1 - i - l;
                    int p = w2 - j - m;
                    if (o <= 0 || p <= 0) continue;
                    int q1 = h3 - o - p;
                    int q2 = w3 - k - n;
                    if (q1 != q2) continue;
                    if (q1 <= 0) continue;
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}

#endif