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

void make_f(int F[10][10])
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            F[i][j] = (i + j)%10;
        }
    }
}

void make_g(int G[10][10])
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            G[i][j] = (i * j)%10;
        }
    }
}

int main()
{
    int n;
    cin >> n;

    ll M = 998244353;

    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    vector<ll [10]> dp(n+1);
    for (int k = 0; k < 10; k++) {
        dp[1][k] = (A[0] == k)? 1 : 0;
    }

    int F[10][10];
    make_f(F);

    int G[10][10];
    make_g(G);

    for (int i = 2; i <= n; i++) {
        for (int k = 0; k < 10; k++) {
            int x = dp[i-1][k];
            int z = F[k][A[i-1]];
            dp[i][z] += (ll)x;
            dp[i][z] = dp[i][z] % M;
            int y = G[k][A[i-1]];
            dp[i][y] += (ll)x;
            dp[i][y] = dp[i][y] % M;
        }
    }

    for (int k = 0; k < 10; k++) {
        cout << dp[n][k] << endl;
    }

    return 0;
}

#ifdef F

template<typename T> class segtree {
private:
    int n,sz;
    vector<pair<T, int> > node;
public:
    void resize(const vector<T>& v){
        sz = (int)v.size();
        n = 1;
        while(n < sz){
            n *= 2;
        }
        node.resize(2*n);
        for(int i = 0; i < sz; i++){
            node[i+n] = make_pair(v[i], i);
        }
        for(int i=n-1; i>=1; i--){
            node[i] = min(node[2*i], node[2*i+1]);
        }
    }
    pair<T, int> query(int a,int b)
    {
        pair<T, int> res1 = make_pair(numeric_limits<T>::max(), -1);
        pair<T, int> res2 = make_pair(numeric_limits<T>::max(), -1);
        a += n, b += n;
        while(a != b){
            if(a % 2) res1 = min(res1, node[a++]);
            if(b % 2) res2 = min(res2, node[--b]);
            a >>= 1, b >>= 1;
        }
        return min(res1, res2);
    }
};
 
class LCA{
private:
    int V;
    vector<vector<int> > G;
    vector<int> ord,depth,id;
    segtree<int> st;
    void dfs(int u,int p,int k){
        id[u] = (int)ord.size();
        ord.push_back(u);
        depth[u] = k;
        for(int v : G[u]){
            if(v != p){
                dfs(v,u,k+1);
                ord.push_back(u);
            }
        }
    }
 
public:
    LCA(int node_size) : V(node_size), G(V), depth(V), id(V, -1){}
    void add_edge(int from,int to){
        G[from].push_back(to),G[to].push_back(from);
    }
    void build(){
        ord.reserve(2*V-2);
        for(int i = 0; i < V; i++){
            if(id[i] < 0){
                dfs(i,-1,0);
            }
        }
        vector<int> stvec(2*V-2);
    	for(int i = 0; i < 2*V-2; i++){
    		stvec[i] = depth[ord[i]];
    	}
        st.resize(stvec);
    }
    int lca(int u,int v){
        return ord[st.query(min(id[u],id[v]),max(id[u],id[v])+1).second];
    }
    int dist(int u,int v){
        int lca_ = lca(u,v);
        return depth[u] + depth[v] - 2*depth[lca_];
    }
};


int main()
{
    int n;
    cin >> n;

    LCA T(n);

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        T.add_edge(u, v);
    }

    T.build();

    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            s += T.dist(i, j);
        }
        cout << s << endl;
    }

    return 0;
}

#endif

#ifdef C

int main()
{
    int n;
    cin >> n;

    ll s = 0;
    vector<ll> S(n);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        s += a;
        S[i] = s;
    }
    ll x;
    cin >> x;

    ll m = x / s;
    ll res = x - m*s;

    auto it = upper_bound(S.begin(), S.end(), res);
    ll index = it - S.begin() + 1;

    cout << n * m + index << endl;

    return 0;
}

#endif