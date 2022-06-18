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
    int n; 
    cin >> n; 

    vector<pair<ll, ll>> vRange;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;;
        vRange.push_back(make_pair(x, y));
    }

    sort(vRange.begin(), vRange.end());

    vector<pair<ll, ll>> vAns;
    pair<ll, ll>  curr = *vRange.begin();
    for (int i = 1; i < n; i++) {
        if (curr.second < vRange[i].first) {
            vAns.push_back(curr);
            curr = vRange[i];
        }
        else {
            curr.second = max(curr.second, vRange[i].second);
        }
    }
    vAns.push_back(curr);

    for (auto& r : vAns) {
        cout << r.first << " " << r.second << endl;
    }
}


#ifdef C

int main()
{
    int h1, h2, h3, w1, w2, w3;
    cin >> h1 >> h2 >> h3 >> w1 >> w2 >> w3;

    int ans = 0;
    for (int i = 1; i <= min(h1-2, w1-2); i++) {
        for (int j = 1; j <= min(h1 - 2, w2 - 2); j++) {
            for (int l = 1; l <= min(h2 - 2, w1 - 2); l++) {
                for (int m = 1; m <= min(h2 - 2, w2 - 2); m++) {
                    int k = h1 - i - j;
                    int n = h2 - l - m;
                    if (k <= 0 || n <= 0) continue;
                    int o = w1 - i - l;
                    int p = w2 - j - m;
                    if (o <= 0 || p <= 0) continue;
                    int q1 = h3 - o - p;
                    int q2 = w3 - k - n;
                    if (q1 != q2) continue;
                    if (q1 <= 0) continue;
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}

#endif