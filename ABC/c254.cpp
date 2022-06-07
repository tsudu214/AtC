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

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) { // 前処理。spf を求める
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) { // nの素因数分解を求める
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};

int main()
{
    ll n;
    cin >> n;

    ll ans = 0;
    for (size_t i = 1; i <= n; i++) {
        PrimeFact<ll> SPF(i);
        map<ll, ll> m = SPF.get(i);
        ll y = 1;
        for (auto& c : m) {
            y *= (c.second + 1);
        }
        ans += y;
    }

    cout << ans << endl;

    return 0;
}


#ifdef C

int main()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> A(k);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int m = i % k;
        A[m].push_back(a);
    }
    for (int m = 0; m < k; m++) {
        sort(A[m].begin(), A[m].end());
    }

    int count = 0;
    int last = 0;
    while (true) {
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < k; m++) {
                if (last > A[m][i]) {
                    cout << "No" << endl;
                    return 0;
                }
                last = A[m][i];
                count++;
                if (count == n) {
                    cout << "Yes" << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}

#endif

