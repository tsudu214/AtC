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

int main()
{
    int q;
    cin >> q;

    const ll N = 1048576;
    vector<ll> A(N, -1);
    vector<ll> next(N);
    for (ll i = 0; i < N; i++) {
        next[i] = i+1;
    }
    next[N-1] = 0;

    for (int i = 0; i < q; i++) {
        int t;
        ll  x;
        cin >> t >> x;
        ll  h = x % N;
        if ( t == 1 ) {
            vector<ll>  prev;
            while (true) {
                if (A[h] == -1) {
                    A[h] = x;
                    for (auto& p : prev) {
                        next[p] = next[h];
                    }
                    break;
                }
                else {
                    prev.push_back(h);
                    h = next[h];
                }
            }
        }
        else {
            cout << A[h] << endl;
        }
    }

    return 0;
}
