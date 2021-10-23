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

struct node {
    node(int L, int e, int t[9]) {
        level = L;
        empty = e;
        for ( int i = 0; i < 9; i++) { table[i] = t[i]; }
    }
    int level;
    int empty;
    int table[9];
};

bool is_complete(node& N) 
{
    for ( int i = 0; i < 9; i++) {
        if (N.table[i] >= 0 && N.table[i] != i) {
            return false;
        }
    }
    return true;
}

int get_hash(int t[9])
{
    int sum = 0;
    for ( int i = 0; i < 9; i++) {
        int add = t[i] >= 0? t[i] : 9;
        for (int j = 0; j < i; j++) {
            add *= 10;
        }
        sum += add;
    }
    return sum;
}

void gen_next(node& N, vector<vector<int>>& g, vector<node>& next, set<int>& checked)
{
    for (auto& v : g[N.empty]) {
        node M = N;
        swap(M.table[N.empty], M.table[v]);
        M.empty = v;
        M.level++;
        int h = get_hash(M.table);
        if (checked.count(h) == 0) {
            next.push_back(M);
            checked.insert(h);
        }
    }
}

int main()
{
    int m;
    cin >> m;

    vector<vector<int>> g(9);

    for (int i = 0; i < m; i++) {
        int v, k;
        cin >> v; v--;
        cin >> k; k--;
        g[v].push_back(k);
        g[k].push_back(v);
    }

    int table[9];
    for (int i = 0; i < 9; i++) {
        table[i] = -1;
    }

    for (int i = 0; i < 8; i++) {
        int p;
        cin >> p; p--;
        table[p] = i;
    }
    int empty = -1;
    for (int i = 0; i < 9; i++) {
        if (table[i] < 0) {
            empty = i;
            break;
        }
    }

    queue<node> Q;
    node Nini(0, empty, table);
    set<int> checked;

    Q.push(Nini);
    checked.insert(get_hash(table));

    while (!Q.empty()) {
        node N = Q.front(); Q.pop();
        if (is_complete(N)) {
            cout << N.level << endl;
            return 0;
        }
        vector<node> next;
        gen_next(N, g, next, checked);

        for (auto& Ni : next) {
            Q.push(Ni);
        }
    }

    cout << -1 << endl;
    
    return 0;
}

