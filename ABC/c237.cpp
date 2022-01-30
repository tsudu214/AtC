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

#ifdef D
const static int INF = -1;
struct node {
    node(int p = INF) {parent = p; left = INF; right = INF;}
    int parent;
    int left;
    int right;
};

vector<node> T;

void dfs(int v)
{
    if (T[v].left != INF) 
        dfs(T[v].left);

    cout << T[v].parent + 1 << " ";

    if (T[v].right != INF)
        dfs(T[v].right);
}

int main()
{
    int n;
    string s;
    cin >> n >> s;

    T.push_back(node());
    for (int i = 0; i < n; i++) {
        T.push_back(node(i));
        if (s[i] == 'L') {
            T[i].left = i+1;
        } else {
            T[i].right = i+1;
        }
    }

    dfs(0);

    return 0;
}

#endif

#ifdef C
int main()
{
    
    string s;
    cin >> s;

    int n = s.size();
    int l = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'a') break;
        l++;
    }
    if (l == n) {
        cout << "Yes" << endl;
        return 0;
    }

    int m = 0;
    for (int i = n-1; i >= 0; i--) {
        if (s[i] != 'a') break;
        m++;
    }
    if (l > m) {
        cout << "No" << endl;
        return 0;
    }

    string sa(s.begin() + l, s.begin() + n - m);

    string rev = sa;
    reverse(rev.begin(), rev.end());
    if (sa == rev) {
        cout << "Yes" << endl;
        return 0;
    }

    cout << "No" << endl;

    return 0;
}

#endif