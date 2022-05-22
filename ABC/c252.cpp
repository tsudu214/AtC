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

using ll = long long; // ~ 9*10^18

struct edge {
    int a;
    int b;
    ll c;
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n);

    vector<edge> E(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        E[i] = { a, b, c };

        G[a].push_back(i);
        G[b].push_back(i);
    }

    vector<ll> cost(n, LLONG_MAX);
    cost[0] = 0;
    vector<int> prev(n, -1);

    typedef pair<ll, int> P; // cost, next
    priority_queue<P, vector<P>, greater<P>> PQ;
    
    PQ.push({0, 0});
    while (!PQ.empty())
    {
        P q = PQ.top(); PQ.pop();
        int curr = q.second;
        ll d = q.first;
        if (cost[curr] < d) continue;
        for (auto& e : G[curr]) {
            int next = (E[e].a == curr ? E[e].b : E[e].a);
            if (cost[curr] + E[e].c < cost[next]) {
                cost[next] = cost[curr] + E[e].c;
                prev[next] = e;
                PQ.push({ cost[next], next });
            }
        }
    }

    for (int i = 1; i < n; i++) {
        cout << prev[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}


#ifdef D

ll Cn2(ll n)
{
    return n * (n - 1) / 2;
}

ll Cn3(ll n) 
{
    return n * (n - 1) * (n - 2) / 6;
}

int main()
{
    int n;
    cin >> n;

    ll M = 0;
    vector<ll> C(200010, 0);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        C[a]++;
        if (a > M) M = a;
    }
    ll d = 0;
    for (ll j = 1; j <= M; j++) {
        if (C[j] >= 2) {
            d += Cn2(C[j]) * (n - C[j]);
        }
        if (C[j] >= 3) {
            d += Cn3(C[j]);
        }
    }

    ll ans = Cn3(n) - d;

    cout << ans << endl;

    return 0;
}

#endif

#ifdef C

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> SI(n);
    for (int i = 0; i < n; i++) {
        SI[i].resize(10);
        for (int j = 0; j < 10; j++) {
            char c;
            cin >> c;
            SI[i][c - '0'] = j;
        }
    }

    int min_t = 100000;
    for (int x = 0; x < 10; x++) {
        set<int> tx;
        for (int i = 0; i < n; i++) {
            int t = SI[i][x];
            while (true) {
                if (tx.count(t)) {
                    t += 10;
                }
                else {
                    tx.insert(t);
                    break;
                }
            }
        }
        int tmax = *tx.rbegin();
        if (tmax < min_t) {
            min_t = tmax;
        }
    }

    cout << min_t << endl;

    return 0;
}

#endif