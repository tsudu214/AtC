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

using namespace std;

#ifdef ABC209_C

int main()
{
    const int Mod = 1000000007;
    int n;
    cin >> n;
    vector<int> c(n);

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    
    sort(c.begin(), c.end());

    long long m = 1;
    for (int i = 0; i < n; i++) {
        m = m * max((c[i] - i), 0) % Mod;
    }

    cout << m << endl;

    return 0;
}
#endif

#ifdef ABC209_D

#define WHITE (0)
#define BLACK (1)

vector<int>  type;
vector<vector<int>> g;

void setchild(int r, int p = -1)
{
    int ptype = type[r];
    for (int u : g[r]) {
        if (u == p) continue;
        type[u] = 1 - ptype;
        setchild(u, r);
    }
}

int main()
{
    int n, q;

    cin >> n >> q;

    type.resize(n);
    g.resize(n);
   
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
   }

    type[0] = WHITE;
    setchild(0);

    for (int i = 0; i < q; i++) {
        int c, d;
        cin >> c >> d;
        c--; d--;

        if (type[c] == type[d]) {
            cout << "Town" << endl;
        }
        else {
            cout << "Road" << endl;
        }
    }

    return 0;
}

#endif



