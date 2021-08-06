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

#if 1

ll getmin(vector<vector<ll>>& A, ll c)
{
    ll INF = (ll)1e18;
    int h = (int)A.size();
    int w = (int)A[0].size();

    ll ans = INF;
    // cost = A[i'][j'] - C(i'+j') + A[i][j] + C(i+j) 
    //      = start_cost_min + A[i][j] + C(i+j)
    vector<vector<ll>> SCost(h, vector<ll>(w, INF));
    SCost[0][0] = A[0][0];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (j > 0) {
                SCost[i][j] = min(SCost[i][j], SCost[i][j-1]);
            }
            if (i > 0) {
                SCost[i][j] = min(SCost[i][j], SCost[i-1][j]);
            }
            ans = min(SCost[i][j] + A[i][j] + c * (i + j), ans);
            SCost[i][j] = min(A[i][j] - c * (i + j), SCost[i][j]);
        }
    }


    return ans;
}

int main()
{
    int h, w; 
    ll c;
    cin >> h >> w >> c;

    vector<vector<ll>> A(h, vector<ll>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> A[i][j];
        }
    }

    ll cost1 = getmin(A, c);

    reverse(A.begin(), A.end());

    ll cost2 = getmin(A, c);

    cout << min(cost1, cost2) << endl;

    return 0;
}

#endif

#if 0
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    map<int, int>  counter;

    int imax = 0;
    int i = 0;
    for (i = 0; i < k; i++) {
        counter[c[i]]++;
    }
    int kindmax = counter.size();

    int kind = kindmax;
    for (int s = 1; s <= n-k; s++ ) {
        if (counter[c[s-1]] > 0) {
            counter[c[s-1]]--;
            if (counter[c[s-1]] == 0) {
                kind--;
            }
        }
        if (counter[c[s+k-1]] == 0) {
            kind++;
        }
        counter[c[s+k-1]]++;

        if (kind > kindmax) {
            kindmax = kind;
            imax = s;
        }
    }

    cout << kindmax << endl;

    return 0;
}

#endif


