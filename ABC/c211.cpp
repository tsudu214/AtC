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
int n;
vector<vector<int>> g;
ll M = 1000000007;

int d[200001];
const int INF = INT_MAX;

ll dp[200001];
vector<int> vs;

void bfs(int s)
{
    d[s] = 0;

    queue<int> Q;
    Q.push(s);

    while(!Q.empty()) {
        int v = Q.front(); Q.pop();
        vs.push_back(v);

        for (auto& w : g[v]) {
            if (d[w] < INF) continue;

            d[w] = d[v] + 1;
            Q.push(w);
        }
    }
}

int main()
{
    int m;
    cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }

    bfs(0);

    dp[0] = 1;
    for (int i = 0; i < vs.size(); i++) {
        int v = vs[i];
        for (auto& w : g[v]) {
            if (d[w] == d[v] + 1) {
                dp[w] += dp[v];
                dp[w] = dp[w] % M;
            }
        }
    }

    cout << dp[n-1] << endl;

    return 0;
}


#if 0

int n;
string s;
string m = "chokudai";
ll M = 1000000007;

ll dp[100001][9];

ll match(int i, int j)
{
    if (dp[i][j] >= 0) {
        return dp[i][j];
    }
    if (j == 8) {
        dp[i][j] = 1;
        return 1;
    }
    if (i == n) {
        dp[i][j] = 0;
        return 0;
    }

    if (s[i] == m[j]) {
        ll cnt = match(i+1, j) + match(i+1, j+1);
        cnt = cnt % M;
        dp[i][j] = cnt;
        return dp[i][j];
    } else {
        ll cnt = match(i+1, j);
        cnt = cnt % M;
        dp[i][j] = cnt;
        return dp[i][j];
    }
}

int main()
{
    cin >> s;

    n = (int)s.size();

    for (int i = 0; i < 100001; i++) {
        for (int j = 0; j < 9; j++) {
            dp[i][j] = -1;
        }
    }

    cout << match(0, 0) << endl;

    return 0;
}


#endif
