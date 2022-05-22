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

using  prime_vector = vector<size_t>;
typedef size_t prime_store_t;

prime_vector simple_algrism(const prime_store_t generate_max) {
    prime_vector prime_num;
    auto p = std::make_unique<char[]>(generate_max + 1);
    p[0] = p[1] = 1;
    for (size_t j = 2; j < generate_max; j++) {
        for (size_t k = j + j; k <= generate_max; k += j) p[k] = 1;
    }
    for (size_t j = 0; j <= generate_max; j++) if (!p[j]) prime_num.push_back(j);
    return prime_num;
}

int main()
{
    ll n;
    cin >> n;

    ll M = 1e6;
    vector<size_t> primes = simple_algrism(M);

    ll p_last, q_last, q_first;
    ll ans = 0;
    for (size_t i = 0; i < primes.size(); i++) {
        ll p = primes[i];
        for (size_t j = i + 1; j < primes.size(); j++) {
            ll q = primes[j];
            if (p > n/q/q/q ) break;
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}


#ifdef C

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> I(n+1, 0);
    for (int x = 1; x <= n; x++) {
        I[x] = x - 1;
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        int id = I[x];
        if (id == n - 1) {
            swap(I[x], I[a[id - 1]]);
            swap(a[id], a[id - 1]);
        }
        else {
            swap(I[x], I[a[id + 1]]);
            swap(a[id], a[id + 1]);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

#endif
