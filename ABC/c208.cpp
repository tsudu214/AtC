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

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX;

struct edge {
    int to;
    ll  cost;
    edge(int t, ll c): to(t), cost(c) {}
};

ll dp[400][400]; // [s][t] min. cost

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<edge>> g(n);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back(edge(b, c));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dp[i][j] = 0;
            else dp[i][j] = INF;
        }
    }

    for (int s = 0; s < n; s++) {
        for (auto & e : g[s]) {
            dp[s][e.to] = e.cost;
        }
    }

    ll sum = 0;
    for (int k = 0; k < n; k++) {
        for (int s = 0; s < n; s++) {
            for (int t = 0; t < n; t++) {
                if (dp[s][k] != INF && dp[k][t] != INF) {
                    dp[s][t] = min(dp[s][t], dp[s][k] + dp[k][t]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] < INF) {
                    sum += dp[i][j];
                }
            }
        }
    }
    
    cout << sum << endl;

    return 0;
}

#ifdef ABC_208_C

#define NMAX 1000000000
bool cnt[ NMAX+1 ];  // ID->num

int main()
{
    long long n; 
    long long k;

    for (auto i = 0; i < NMAX+1; i++) {
        cnt[i] = 0;
    }

    cin >> n >> k;

    deque<long long> A;
    for (auto i = 0; i < n; i++ ) {
        long long a;
        cin >> a;
        A.push_back(a);
    }
    deque<long long> B = A;
    sort(B.begin(), B.end());

    long long base = k / n;
    k = k - n*base;

    for (auto i = 0; i < k; i++) {
        cnt[B[i]] = true;
    }

    for (auto i = 0; i < n; i++ ) {
        cout << (cnt[A[i]]? 1 : 0) + base << "\n";
    }

    return 0;
}
#endif

#ifdef ABC_208_B

int main()
{
    long int p;
    int n[10] = {0};

    cin >> p;

    long int v[10] = {0};
    v[0] = 1;
    for (int i = 1; i < 10; i++ ) {
        v[i] = (i+1)*v[i-1];
    }

    long int rest = p;
    for (int i = 9; i >= 0; i--) {
        n[i] = rest / v[i];
        rest = rest - n[i]*v[i];
    }

    cout << accumulate(n+0, n+10, 0) << "\n";

    return 0;
}
#endif

#ifdef ABC_208_A
int main()
{
    int n, s;

    cin >> n >> s;

    int min = 1*n;
    int max = 6*n;

    if ( min <= s && s <= max ) {
        cout << "Yes\n";
    }
    else {
        cout << "No";
    }

    return 0;
}

#endif