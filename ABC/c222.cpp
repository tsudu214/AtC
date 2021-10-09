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

vector<ll> A, B;
int n;
const ll M = 998244353;

ll dp[3010][3010];

ll dfs(ll prev, int j) {
    if (j == n-1) {
        return B[n-1] - max(A[j], prev) + 1;
    }
    ll cnt = 0;
    for (ll c = max(A[j], prev); c <= B[j]; c++) {
        if (dp[c][j+1] < 0) {
            dp[c][j+1] = dfs(c, j+1);
        }
        cnt += dp[c][j+1];
        cnt %= M;
    }
    dp[prev][j] = cnt;
    return cnt;
}

int main()
{
    cin >> n;

    A.resize(n);
    B.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    for (int i = 0; i < 3010; i++) {
        for (int j = 0; j < 3010; j++) {
            dp[i][j] = -1;
        }
    }

    ll ans = dfs(A[0], 0);

    cout << ans << endl;

    return 0;
}


#ifdef C

struct p {
    int id; int cnt;
}; 

int iswin(char a, char b) {
    if (a == b) {
        return 0;
    }
    if (a == 'G') {
        if (b == 'C') return 1;
        if (b == 'P') return -1;
    }
    if (a == 'C') {
        if (b == 'G') return -1;
        if (b == 'P') return 1;
    }
    if (a == 'P') {
        if (b == 'G') return 1;
        if (b == 'C') return -1;
    }
    return 0;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<p> P;
    for (int i = 0; i < 2*n; i++) {
        P.push_back( {i, 0} );
    }

    vector<vector<char>> te;
    for (int i = 0; i < 2*n; i++) {
        vector<char> tete(m);
        for (int j = 0; j < m; j++) {
            cin >> tete[j];
        }
        te.push_back(tete);
    }

    for (int j = 0; j < m; j++) {
        sort(P.begin(), P.end(), [](auto const&a, auto const& b){
            if (a.cnt != b.cnt) return a.cnt > b.cnt;
            else return a.id < b.id;
        } );

        for (int k = 0; k < n; k++) {
            char a = te[P[2*k].id][j];
            char b = te[P[2*k+1].id][j];
            int win = iswin(a, b);
            if (win > 0) {
                P[2*k].cnt++;
            }
            else if (win < 0) {
                P[2*k+1].cnt++;
            }
        }
    }

    sort(P.begin(), P.end(), [](auto const&a, auto const& b){
        if (a.cnt != b.cnt) return a.cnt > b.cnt;
        else return a.id < b.id;
    } );

    for (int i = 0; i < 2*n; i++) {
        cout << P[i].id+1 << endl;
    }

    return 0;
}


#endif
