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

//#ifdef C

void reorder(vector<int>& A)
{
    int n = (int)A.size();
    vector<int> S = A;
    sort(S.begin(), S.end());
    S.erase(unique(S.begin(), S.end()), S.end());

    for (int i = 0; i < n; i++) {
        A[i] = (int)(lower_bound(S.begin(), S.end(), A[i]) - S.begin());
    }
}

int main()
{
    int h, w, n;
    cin >> h >> w >> n;

    vector<int> A(n);
    vector<int> B(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        A[i] = a;
        B[i] = b;
    }

    reorder(A);
    reorder(B);

    for (int i = 0; i < n; i++) {
        cout << A[i]+1 << " " << B[i]+1 << endl;
    }

    return 0;
}

//#endif

#ifdef D

void dfs(int v, const vector<vector<int>>& g, vector<bool>& visited, vector<int>& path)
{
    visited[v] = true;
    path.push_back(v);
    vector<int> roads = g[v];
    sort(roads.begin(), roads.end());
    for (int u : roads) {
        if (visited[u]) {
            continue;
        }
        dfs(u, g, visited, path);
        path.push_back(v);
    }
}


int main()
{
    int n;
    cin >> n;

    vector<vector<int>> g(n);

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<bool>  visited(n, false);
    vector<int> path;
    dfs(0, g, visited, path);

    for (size_t j = 0; j < path.size(); j++) {
        if (j > 0) cout << " ";
        cout << path[j] + 1;
    }
    cout << endl;

    return 0;
}

#endif

