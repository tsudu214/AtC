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

using ll = long long; // 9,223,372,036,854,775,807 = 9*10^18

vector<ll>  A;

vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    return ret;
}

int main()
{
    int n;
    cin >> n;

    map<ll, int> M;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        M[a]++;
    }

    for (auto& i : M) {
        int in = i.second;
        vector<ll> div = divisor(i.first);


    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<ll> div = divisor(A[i]);

        for (int d1 = 0; d1 < div.size(); d1++) {
            bsearch(div[d1], )
            ll d2 = A[i] / div[d1];
        }
}
        for (int j = 0; j < n && A[j] <= A[i]; j++ ) {
            for (int k = 0; k < n && A[k] <= A[j]; k++ ) {
                if (A[i] == A[k]*A[j]) {
                    ans += 1;
                    if (k != j) {
                        ans ++;
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}

#ifdef C

static int max_ans = 0;
static int best_add = -1;

int value(vector<int>&counter, int k) 
{
    int val = 0;
    for (auto& i : counter) {
        if (i == k) val++;
    }
    return val;
}

void go_next(int id, int add, int n, vector<vector<int>>& vc, int k, vector<int> counter)
{
    if ( id == n) {
        if (value(counter, k) > max_ans) {
            max_ans = value(counter, k);
            best_add = add;
        }
        return;
    }
    go_next(id + 1, add, n, vc, k, counter);

    for (int i = 0; i < 26; i++) {
        counter[i] += vc[id][i];
    }
    go_next(id + 1, add + 1, n, vc, k, counter);
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> counter(26, 0);
    vector<vector<int>> vc(n);

    for (int i = 0; i < n; i++) {
        vc[i] = vector<int>(26, 0);
        string s;
        cin >> s;

        for (auto& c: s) {
            vc[i][(int)c - 'a']++;
        }
    }

    go_next(0, 0, n, vc, k, counter);

    cout << max_ans << endl;

    return 0;
}

#endif