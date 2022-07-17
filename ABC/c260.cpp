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

    map<int, vector<int>> m;
    vector<int> eat(n, -1);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        auto ite = m.lower_bound(p);
        if (ite == m.end()) {
            if (k == 1) {
                eat[p] = i + 1;
            }
            else {
                m[p] = vector<int>();
            }
        }
        else {
            m[p].swap(ite->second);
            m[p].push_back(ite->first);
            m.erase(ite->first);
            if (k - 1 == (int)m[p].size()) {
                eat[p] = i + 1;
                for (auto c : m[p]) {
                    eat[c] = i + 1;
                }
                m.erase(p);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << eat[i] << endl;
    }

    return 0;
}

#ifdef D

int main()
{
    int n, k;
    cin >> n >> k;

    map<int, vector<int>> m;
    vector<int> eat(n, -1);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        auto ite = m.lower_bound(p);
        if (ite == m.end()) {
            if (k == 1) {
                eat[p] = i + 1;
            }
            else {
                m[p] = vector<int>();
            }
        }
        else {
            m[p].swap(ite->second);
            m[p].push_back(ite->first);
            m.erase(ite->first);
            if (k - 1 == (int)m[p].size()) {
                eat[p] = i + 1;
                for (auto c : m[p]) {
                    eat[c] = i + 1;
                }
                m.erase(p);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << eat[i] << endl;
    }

    return 0;
}

#endif

#ifdef C

int main()
{
    int n;
    ll x, y;
    cin >> n >> x >> y;

    ll r = 1, b = 0;

    for (int i = n; i > 1; i--) {
        ll r2 = r * (x + 1) + b;
        ll b2 = r * x * y + b * y;
        r = r2;
        b = b2;
    }

    cout << b << endl;

    return 0;
}

#endif

#ifdef B

struct stu {
    int id;
    int m;
    int e;
};

int main()
{
    int n;
    cin >> n;
    int x, y, z;
    cin >> x >> y >> z;

    vector<stu> vp(n);
    for (int i = 0; i < n; i++) {
        vp[i].id = i + 1;
        cin >> vp[i].m;
    }

    for (int i = 0; i < n; i++) {
        cin >> vp[i].e;
    }

    vector<stu> pass;
    sort(vp.begin(), vp.end(), [](auto& a, auto& b) {if (a.m == b.m) { return a.id < b.id; } else return a.m > b.m; });
    copy(vp.begin(), vp.begin() + x, back_inserter(pass));

    vector<stu> vp2;
    copy(vp.begin() + x, vp.end(), back_inserter(vp2));
    vp.swap(vp2);
    sort(vp.begin(), vp.end(), [](auto& a, auto& b) {if (a.e == b.e) { return a.id < b.id; } else return a.e > b.e; });
    copy(vp.begin(), vp.begin() + y, back_inserter(pass));

    vp2.clear();
    copy(vp.begin() + y, vp.end(), back_inserter(vp2));
    vp.swap(vp2);
    sort(vp.begin(), vp.end(), [](auto& a, auto& b) {if (a.m + a.e == b.m + b.e) { return a.id < b.id; } else return a.m + a.e > b.m + b.e; });
    copy(vp.begin(), vp.begin() + z, back_inserter(pass));

    sort(pass.begin(), pass.end(), [](auto& a, auto& b) {return a.id < b.id; });

    for (int i = 0; i < pass.size(); i++) {
        cout << pass[i].id << endl;
    }

    return 0;
}

 
#endif