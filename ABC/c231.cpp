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

int CalcSum(ll x, vector<ll>& A)
{
    int n = A.size();
    vector<int> P(n, 0);
    int sum = 0;
    for (int i = n-1; i >= 0; i--) {
        ll c = x / A[i];
        x = x - c * A[i];
        P[i] = c;
        sum += c;
    } 
    return sum;
}

int main()
{
    int n;
    cin >> n;
    ll x;
    cin >> x;
    vector<ll> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    ll xx = x;
    vector<int> P(n, 0);
    for (int i = n-1; i >= 0; i--) {
        ll c = xx / A[i];
        xx = xx - c * A[i];
        P[i] = c;
    } 

    ll d = x / A[n-1];
    ll large = (d+1) * A[n-1]; 
    for (int i = n-1; i >= 0; i--) {
        if (P[i] != 0) break;
        large = A[i];
    }

    int min = 100000;
    for (ll y = x; y <= large; y++) {
        int pay = CalcSum(y, A);
        int charge = CalcSum(y-x, A);
        if (pay + charge < min) {
            min = pay + charge;
        }
    } 

    cout << min << endl;


    return 0;
}

#ifdef D

struct NB { 
    NB() { cnt = 0; n[0] = -1; n[1] = -1;}
    int cnt;
    int n[2]; 

    int Add(int b) {
        if (cnt < 2) {
            n[cnt] = b;
            cnt++;
            return cnt;
        }
        else {
            return 3;
        }
    }
};

class DisjointSet
{
public:
    DisjointSet(){}
    DisjointSet(int size){
        rank.resize(size, 0);
        p.resize(size, 0);
        for (int i = 0; i < size; i++) {
            makeSet(i);
        }
    }

    void makeSet(int x)
    {
        p[x] = x;
        rank[x] = 0;
    }

    void unite(int x, int y)
    {
        x = findSet(x);
        y = findSet(y);
        if (rank[x] > rank[y]) {
            p[y] = x;
        }
        else {
            p[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

    int findSet(int x) 
    {
        if (p[x] != x) {
            p[x] = findSet(p[x]);
        }
        return p[x];
    }

    void CollectAllSets( vector<vector<int> >& vAllSets )
    {
        unordered_map<int,vector<int> > mapRoot2All;
        for ( size_t i = 0; i < p.size(); i++ ) {
            mapRoot2All[findSet(i)].push_back(i);
        }

        vAllSets = vector<vector<int>>( mapRoot2All.size());
        unordered_map<int, vector<int> >::iterator it = mapRoot2All.begin();
        for ( size_t i = 0; it != mapRoot2All.end(); ++it, i++ ) {
            vAllSets[i].swap( it->second );
        }
    }


private:
    vector<int> rank;
    vector<int> p;

};

int main()
{
    int n, m;
    cin >> n >> m;

    DisjointSet ds(n);

    vector<NB> link(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int ret = link[a].Add(b);
        if (ret > 2) {
            cout << "No" << endl;
            return 0;
        }
        ret = link[b].Add(a);
        if (ret > 2) {
            cout << "No" << endl;
            return 0;
        }
        ds.unite(a, b);
    }

    vector<vector<int> > vvset;
    ds.CollectAllSets(vvset);

    for (int i = 0; i < vvset.size(); i++) {
        int nBothLink = 0;
        int num = vvset[i].size();
        for (int j = 0; j < num; j++) {
            if (link[vvset[i][j]].cnt == 2) {
                nBothLink++;
            }
        }
        if (nBothLink == num) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}

#endif