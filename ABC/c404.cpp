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

#define B

#ifdef B

string rotate(string& s, int n)
{
    string next = s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            next[j * n + (n - i - 1)] = s[i * n + j];
        }
    }
    return next;
}

int main()
{
    int n;
    cin >> n;
    char c;
    string s;
    string t;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            cin >> c;
            s.push_back(c);
        }
    }
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            cin >> c;
            t.push_back(c);
        }
    }

    int min_cost = n * n;
    string rot = s;
    for (int r = 0; r < 4; r++) {
        int cost = r;
        for (int i = 0; i < n * n; i++) {
            if (rot[i] != t[i]) {
                cost++;
            }
        }
        min_cost = min(cost, min_cost);
        rot = rotate(rot, n);
    }

    cout << min_cost << endl;

    return 0;
}
#endif

#ifdef D
int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> c;
    for (int i = 0; i < n; i++) {
        int cost;
        cin >> cost;
        c.push_back(make_pair(i, cost));
    }
    vector<vector<int>> A(m);
    for (int j = 0; j < m; j++) {
        A[j] = vector<int>(n);
        int kn;
        cin >> kn;
        for (int k = 0; k < kn; k++) {
            int ai;
            cin >> ai; ai--;
            A[j][ai] = 1;
        }
    }

    sort(c.begin(), c.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });

    map<int, int> saw;
    for (int j = 0; j < m; j++) {
        saw[j] = 0;
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int loop = 0; loop < 2 * n; loop++) {
            int I = c[i].first;
            int plus = -1;
            int success = 0;
            for (int j = 0; j < m; j++) {
                if (saw[j] < 2) {
                    if (A[j][I]) {
                        plus = c[i].second;
                        saw[j]++;
                    }
                }
                else {
                    success++;
                }
            }
            if (success == m) {
                cout << sum << endl;
                return 0;
            }
            if (plus >= 0) {
                sum += plus;
            }
            else {
                break;
            }
        }
    }

    return 0;
}
#endif

#ifdef C

void visit(vector<vector<int>>& G, int start, set<int>& visited)
{
    if (visited.count(start))
        return;
    visited.insert(start);
    for (int next : G[start]) {
        if (visited.count(next))
            continue;
        visit(G, next, visited);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n);
    for (int j = 0; j < m; j++) {
        int a, b;
        cin >> a; a--;
        cin >> b; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (G[i].size() != 2) {
            cout << "No" << endl;
            return 0;
        }
    }

    set<int> visited;
    visit(G, 0, visited);
    if (visited.size() == n) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}

#endif

