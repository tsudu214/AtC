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
    int n, m;
    cin >> n >> m;

    map<int, set<int>> AB;
    map<int, int> b_count;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        AB[a].insert(b);
        b_count[b]++;
    }
    set<int> Free;
    for (int i = 1; i <= n; i++) {
        if (b_count.count(i) == 0) {
            Free.insert(i);
        }
    }

    set<int> added;
    vector<int> Ans;
    while (true) {
        int p = -1, q = -1;
        if (!Free.empty()) {
            p = *Free.begin();
        }
        if (!AB.empty()) {
            q = AB.begin()->first;
        }
        if (p < 0 && q < 0) {
            break;
        }
        else if ( p < 0 && q > 0) {
            Ans.push_back(q); added.insert(q);
            for ( auto q2 : AB.begin()->second ) {
                if (added.count(q2)) {
                    cout << -1 << endl;
                    return 0;
                }
                if (b_count[q2] == 1) {
                    if (added.count(q2) == 0 ) Free.insert(q2);
                    b_count.erase(q2);
                } else {
                    b_count[q2]--;
                }
            }
            AB.erase(q);
        }
        else if ( q < 0 && p > 0 ) {
            Ans.push_back(p); added.insert(p);
            Free.erase(p);
        }
        else {
            if ( q <= p ) {
                Ans.push_back(q); added.insert(q);
                for ( auto q2 : AB.begin()->second ) {
                    if (added.count(q2)) {
                        cout << -1 << endl;
                        return 0;
                    }
                    if (b_count[q2] == 1) {
                        if (added.count(q2) == 0 ) Free.insert(q2);
                        b_count.erase(q2);
                    } else {
                        b_count[q2]--; 
                    }
                }
                AB.erase(q);
                if (p == q) Free.erase(q);
            }
            else {
                Ans.push_back(p); added.insert(p);
                Free.erase(p);
            }
        }
    }

    if (Ans.size() != n) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << Ans[i];
    }
    cout << endl;

    return 0;
}

