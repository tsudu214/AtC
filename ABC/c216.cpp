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
    int n, k;
    cin >> n >> k;

    deque<ll> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    sort(A.begin(), A.end(), greater<ll>());
    A.push_back(0);

    ll ans = 0;
    ll ns = 0;
    ll k_cnt = 0;
    for (auto i = 0; i < n; i++) {
        ns ++;
        if (A[i] == A[i+1]) continue;

        if (k_cnt + ns * (A[i] - A[i+1]) > k) {
            ll remain = k - k_cnt;
            ll row = remain / ns;
            ans += ns * row * (A[i] + A[i] - row + 1) / 2;
            ll col = remain - row * ns;
            ans += col * (A[i] - row);
            break;
        }
        k_cnt += ns * (A[i] - A[i+1]);
        ans += ns * (A[i] - A[i+1]) * (A[i] + A[i+1] + 1) / 2;
    }

    cout << ans << endl;

    return 0;
}

#ifdef D

vector<queue<int>> vQ;

int main()
{
    int n, m;
    cin >> n >> m;

    vQ.resize(m);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            vQ[i].push(a);
        }
    }

    map<int, int> top_color;  // color => id
    queue<pair<int, int>> top_pairs;
    for (int i = 0; i < m; i++) {
        if (vQ[i].empty()) continue;
        int top = vQ[i].front();
        auto it = top_color.find(top);
        if (it != top_color.end()) {
            top_pairs.push(make_pair(it->second, i));
        }
        else {
            top_color[top] = i;
        }
    }

    int removed = 0;
    while (!top_pairs.empty()) {
        auto pair = top_pairs.front();
        top_pairs.pop();

        int remove_color = vQ[pair.first].front();
        top_color.erase(remove_color);

        int ids[2] = {pair.first, pair.second};

        for (int j = 0; j < 2; j++) {
            int id = ids[j];
            vQ[id].pop();
            if (vQ[id].empty()) continue;
            int new_color = vQ[id].front();
            auto it = top_color.find(new_color);
            if (it != top_color.end()) {
                top_pairs.push(make_pair(it->second, id));
            }
            else {
                top_color[new_color] = id;
            }
        }
        removed++;
    }

    if (removed == n) 
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}

#endif



