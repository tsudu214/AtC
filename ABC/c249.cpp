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

int main()
{
    int n;
    cin >> n;

    ll M = 0;
    vector<ll> C(20010, 0);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        C[a]++;
        if (a > M) M = a;
    }

    ll ans = 0;
    for (ll j = 1; j <= M; j++) {
        for (ll k = 1; k*j <= M; k++) {  
            ans += C[j*k] * C[j] * C[k];
        }
    }

    cout << ans << endl;

    return 0;
}


#ifdef D_1

vector<ll>  A;

vector<long long> divisors(long long N) {
    vector<long long> res;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i != 0) continue;

        // i ‚Í–ñ”
        res.push_back(i);

        // N € i ‚à–ñ”‚Å‚ ‚é (d•¡‚É’ˆÓ)
        if (N / i != i) res.push_back(N / i);
    }

    // ¬‚³‚¢‡‚É•À‚Ñ‘Ö‚¦‚Äo—Í
    sort(res.begin(), res.end());
    return res;
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
    int nn = (int)M.size();
    vector<ll>  A;
    vector<int> C;
    for (auto& m : M) {
        A.push_back(m.first);
        C.push_back(m.second);
    }

    ll ans = 0;
    for (int i = 0; i < nn; i++) {
        vector<ll> divs = divisors(A[i]);

        for (auto& div : divs) {
            auto it = lower_bound(A.begin(), A.end(), div);
            unsigned int j = distance(A.begin(), it);
            if (A[j] != div) 
                continue;

            ll q = A[i] / A[j];
            auto it2 = lower_bound(A.begin(), A.end(), q);
            unsigned int k = distance(A.begin(), it2);
            if (A[k] != q) 
                continue;

            ans += (ll) C[i] * C[j] * C[k];
        }
    }

    cout << ans << endl;

    return 0;
}

#endif

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