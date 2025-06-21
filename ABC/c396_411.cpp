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
#include <unordered_set>
#include <sstream>

using namespace std;

using ll = long long; // ~ 9*10^18

int main()
{
    int n, q;
    cin >> n >> q;

    vector<string> vs;
    vector<int> server;
    int server_id = -1;
    vector<vector<int>> pc(n);
    string s;
    for (int i = 0; i < q; i++) {
        int c, p;
        cin >> c >> p;
        p--;
        if (c == 1) {
            if (server_id < 0) {
                pc[p].swap(server);
                server_id = p;
            }
            else {
                pc[p] = pc[server_id];
            }
        }
        else if (c == 2) {
            cin >> s;
            vs.push_back(s);
            if (p == server_id) {
                server = pc[p];
                server_id = -1;
            }
            pc[p].push_back(vs.size() - 1);
        }
        else if (c == 3) {
            server_id = p;
            server.clear();
        }
    }

    if (server_id < 0) {
        for (auto a : server) {
            cout << vs[a];
        }
        cout << endl;
    }
    else {
        for (auto a : pc[server_id]) {
            cout << vs[a];
        }
        cout << endl;
    }

    return 0;
}

#ifdef _411_C

int main()
{
    int n, q;
    cin >> n >> q;

    map<int, int> A;
    int num = 0;
    
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        a--;
        if (A.count(a) == 0) {
            if (a > 0 && A.count(a - 1) && a < n && A.count(a + 1)) {
                A.insert(make_pair(a, A[a - 1]));
                num--;
            }
            else if (a > 0 && A.count(a - 1)) {
                A.insert(make_pair(a, A[a - 1]));
            }
            else if (a < n && A.count(a + 1)) {
                A.insert(make_pair(a, A[a + 1]));
            }
            else {
                num++;
                A.insert(make_pair(a, num));
            }
        }
        else {
            if (a > 0 && A.count(a - 1) && a < n && A.count(a + 1)) {
                A.erase(a);
                num++;
            }
            else if (a > 0 && A.count(a - 1)) {
                A.erase(a);
            }
            else if (a < n && A.count(a + 1)) {
                A.erase(a);
            }
            else {
                num--;
                A.erase(a);
            }
        }

        cout <<num << endl;
    }

    return 0;
}
#endif

#ifdef _409_D

int main()
{
    int t;
    cin >> t;

    for (int q = 0; q < t; q++) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        int l = 0;
        int r = 0;
        for (l = 0; l < n-1; l++) {
            if (s[l] > s[l+1]) {
                for (r = l+1; r < n; r++) {
                    if (s[r] > s[r-1]) {
                        break;
                    }
                    swap(s[r], s[r-1]);
                }
                break;
            }
        }
        cout << s << endl;
    }

    return 0;
}
#endif

#ifdef _409_C

int main()
{
    int n, l;
    cin >> n >> l;

    vector<int> d(n);
    d[0] = 0;
    for (int i = 0; i < n-1; i++) {
        cin >> d[i+1];
    }
    for (int i = 1; i < n; i++) {
        d[i] += d[i - 1];
        d[i] = d[i] % l;
    }

    if (l % 3 != 0) {
        cout << 0 << endl;
        return 0;
    }

    map<int, ll> cnt;
    for (int i = 0; i < n; i++) {
        cnt[d[i]]++;
    }

    ll ans = 0;
    int D = l / 3;
    for (int s = 0; s < D; s++) {
        if (cnt.count(s) && cnt.count(s + D) && cnt.count(s + 2 * D)) {
            ans += cnt[s] * cnt[s + D] * cnt[s + 2 * D];
        }
    }

    cout << ans << endl;
    return 0;
}

#endif

#ifdef _396_D

using Graph = vector<vector<pair<int, ll>>>;

void dfs(Graph& G, int s, vector<ll>& path, set<int>& visited, ll& ans)
{
    for (auto e : G[s]) {
        if (e.first == G.size() - 1) {
            ll result = 0;
            for (int i = 0; i < path.size(); ++i) {
                result ^= path[i];
            }
            result ^= e.second;
            ans = min(ans, result);
        }
        else {
            if (visited.count(e.first)) continue;
            visited.insert(e.first);
            path.push_back(e.second);
            dfs(G, e.first, path, visited, ans);
            path.pop_back();
            visited.erase(e.first);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;


    Graph G(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--; b--;
        G[a].emplace_back(make_pair(b, w));
        G[b].emplace_back(make_pair(a, w));
    }

    vector<ll> path;
    set<int> visited;

    ll ans = (1LL << 63) - 1;
    visited.insert(0);
    dfs(G, 0, path, visited, ans);

    cout << ans << endl;

    return 0;
}

#endif

#ifdef _396_C

int main()
{
    int n, m;
    cin >> n >> m;

    vector<ll> b(n), w(m);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }
    sort(b.begin(), b.end(), greater<ll>());
    sort(w.begin(), w.end(), greater<ll>());

    for (int i = 1; i < n; i++) {
        b[i] += b[i-1];
    }
    if (w[0] < 0) w[0] = 0;
    for (int i = 1; i < m; i++) {
        w[i] = max(w[i - 1], w[i-1] + w[i]);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i < m) {
            ans = max(ans, b[i] + w[i]);
        }
        else {
            ans = max(ans, b[i] + w[m-1]);
        }
    }

    cout << ans << endl;

    return 0;
}

#endif


#ifdef _407_E

ll a[400009];
ll b[200009];

int main()
{
    ll t;
    cin >> t;

    for (ll q = 0; q < t; q++) {
        ll n;
        cin >> n;
        for (ll i = 0; i < n * 2; i++) {
            cin >> a[i];
        }

        ll bs = 0;
        ll bn = 1;
        ll bi = 0;
        ll bimax = 0;
        b[0] = 0;
        for (ll i = 0; i < n * 2; i++) {
            if (b[bs] < a[i]) {
                b[bs] = a[i];
                bimax = i;
            }
            b[bs] = max(b[bs], a[i]);
            bi++;
            if (bi == bn) {
                i = bimax + 1;
                bn++;
                bi = 0;
                b[bs] = 0;
            }
            if (bs == n) {
                break;
            }
        }

        ll sum = 0;
        for (ll i = 0; i < n; i++) {
            sum += b[i];
        }

        cout << sum << endl;
    }

    return 0;
}

#endif

#ifdef _405_D

int main()
{
    int h, w;
    cin >> h >> w;

    struct cell {
        int i;
        int j;
        int d;
    };
    queue<cell> Q;

    vector<string> s(h);
    const int INF = 1e9;
    vector<vector<int>> d(h, vector<int>(w, INF));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c;
            cin >> c;
            s[i].push_back(c);
            if (c == 'E') {
                d[i][j] = 0;
                Q.push(cell{ i, j, 0 });
            }
            if (c == '.') {
                d[i][j] = -1;
            }
        }
    }

    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    while (!Q.empty()) {
        auto q = Q.front();
        Q.pop();
        for (int k = 0; k < 4; k++) {
            int ii = q.i + dx[k];
            int jj = q.j + dy[k];
            int dd = q.d + 1;
            if (0 <= ii && ii < h && 0 <= jj && jj < w && d[ii][jj] == -1) {
                d[ii][jj] = dd;
                Q.push(cell{ ii, jj, dd });
            }
        }
    }

    char dir[4] = { 'v', '>', '^', '<' };
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '.') {
                for (int k = 0; k < 4; k++) {
                    int ii = i + dx[k];
                    int jj = j + dy[k];
                    int dd = d[i][j] - 1;
                    if (0 <= ii && ii < h && 0 <= jj && jj < w && d[ii][jj] == dd) {
                        s[i][j] = dir[k];
                    }
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        cout << s[i] << endl;
    }

    return 0;
}

#endif

#ifdef _405_C

int main()
{
    ll n;
    cin >> n;

    vector<ll> A(n);
    for (ll i = 0; i < n; i++) {
        cin >> A[i];
    }
    vector<ll> B(n);
    B[0] = A[0];
    for (ll i = 1; i < n; i++) {
        B[i] = B[i-1]+A[i];
    }

    ll sum = 0;
    for (ll i = n - 1; i >= 1; i--) {
        sum += A[i] * B[i - 1];
    }
    cout << sum << endl;

    return 0;
}

#endif

#ifdef _407_C

int main()
{
    string s;
    cin >> s;

    int n = s.size();

    int ans = s[n-1] - '0';
    for (int d = n - 1; d > 0; d--) {
        ans += (s[d - 1] + 10 - s[d]) % 10;
    }
    ans += n;

    cout << ans << endl;

    return 0;
}

#endif

#ifdef _408_D

int dp0[200009];
int dp1[200009];
int dp10[200009];

int main()
{
    int t;
    cin >> t;

    for (int q = 0; q < t; q++) {
        int n;
        string s;
        cin >> n >> s;

        vector<char> val;
        vector<int> an;
        char last = s[0];
        an.push_back(1);
        val.push_back(last);
        for (int i = 1; i < n; i++) {
            if (s[i] == last) {
                an.back()++;
            }
            else {
                an.push_back(1);
                val.push_back(s[i]);
                last = s[i];
            }
        }
        int m = an.size();
        if (m <= 2) {
            cout << 0 << endl;
            continue;
        }

        if (val[0] == '0') {
            dp0[0] = 0;
            dp1[0] = an[0];
            dp10[0] = 0;
        }
        else {
            dp0[0] = an[0];
            dp1[0] = 0;
            dp10[0] = 0;
        }

        for (int i = 1; i < m; i++) {
            if (val[i] == '0') {
                dp0[i] = dp0[i - 1];
                dp1[i] = min(dp0[i - 1] + an[i], dp1[i-1] + an[i]);
                dp10[i] = min(dp1[i - 1], dp10[i-1]);
            }
            else {
                dp0[i] = dp0[i - 1] + an[i];
                dp1[i] = min(dp0[i - 1], dp1[i-1]);
                dp10[i] = min(dp1[i-1] + an[i], dp10[i-1]+an[i]);
            }
        }

        cout << min(min(dp0[m-1], dp1[m-1]), dp10[m-1]) << endl;
    }

    return 0;
}

#endif

#ifdef _397_C
int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> a1, a2;
    vector<int> n1(n, 0), n2(n, 0);
    for (int i = 0; i < n; i++) {
        a1.insert(a[i]);
        n1[i] = a1.size();
    }
    for (int i = n-1; i >= 0; i--) {
        a2.insert(a[i]);
        n2[i] = a2.size();
    }

    int M = 0;
    for (int i = 0; i < n-1; i++) {
        int m = n1[i] + n2[i+1];
        M = max(M, m);
    }

    cout << M << endl;

    return 0;
}
#endif

#ifdef _398_D

int main()
{
    int n;
    cin >> n;
    int r, c;
    cin >> r >> c;
    string s;
    cin >> s;

    int f[2] = { 0, 0 };
    int taka[2] = { r, c };
    using P = pair<int, int>;

    set<P> kemu;
    kemu.insert(P{ f[0], f[1] });
    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') {
            f[0]++; taka[0]++;
        }
        if (s[i] == 'S') {
            f[0]--; taka[0]--;
        }
        if (s[i] == 'E') {
            f[1]--; taka[1]--;
        }
        if (s[i] == 'W') {
            f[1]++; taka[1]++;
        }
        kemu.insert(P{ f[0], f[1] });

        if (kemu.count(P{ taka[0], taka[1] })) {
            cout << "1";
        }
        else {
            cout << "0";
        }
    }

    cout << endl;

    return 0;
}

#endif

#ifdef _398_E

void dfs(vector<vector<int>>& G, int s, int color, vector<int>& bw, vector<bool>& visited)
{
    if (visited[s]) return;
    visited[s] = true;
    bw[s] = color;
    color = 1 - color;
    for (int v = 0; v < G[s].size(); v++) {
        dfs(G, G[s][v], color, bw, visited);
    }
    return;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> G(n);

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> bw(n);
    vector<bool> visited(n, false);

    dfs(G, 0, 0, bw, visited);

    set<pair<int, int>> safe;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bw[i] != bw[j]) {
                if (find(G[i].begin(), G[i].end(), j) == G[i].end()) {
                    safe.insert(make_pair(i, j));
                }
            }
        }
    }

    if (safe.size() % 2 == 1) {
        cout << "First" << '\n';
        auto it = safe.begin();
        cout << it->first+1 << " " << it->second+1 << '\n';
        safe.erase(it);
    }
    else {
        cout << "Second" << '\n';
    }

    while (true) {
        int u, v;
        cin >> u >> v;
        if (u < 0 && v < 0) return 0;
        u--; v--;
        if (u > v) swap(u, v);
        pair<int, int> p = make_pair(u, v);
        auto itr = safe.find(p);
        if (itr != safe.end()) {
            safe.erase(itr);
        }
        auto it = safe.begin();
        cout << it->first + 1 << " " << it->second + 1 << '\n';
        safe.erase(it);
    }

    return 0;
}

#endif

#ifdef _399_D

int64_t hash_pair(int x, int y) {
    return (static_cast<int64_t>(x) << 32) | y;
}

int main()
{
    int t;
    cin >> t;

    for (int q = 0; q < t; q++) {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
        }

        int ans = 0;
        map<int64_t, int> store;
        for (int i = 0; i < 2 * n - 1; i++) {
            int p = a[i];
            int q = a[i + 1];
            if (p > q) swap(p, q);
            int64_t h = hash_pair(p, q);
            if (store.count(h) == 0) {
                store[h] = i;
            }
            else {
                int prev = store[h];
                if (i > 0 && prev == i - 1) continue;
                if (i > 1 && prev == i - 2 && a[i - 1] == a[i]) continue;
                ans++;
            }
        }

        cout << ans << '\n';
    }


    return 0;
}
#endif

#ifdef _399_C

class UnionFind {
    vector<int> parent;

public:
    UnionFind(int n) {
        parent.resize(n, -1);
    }

    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]); // Œo˜Hˆ³k
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false; // “¯‚¶ƒOƒ‹[ƒv ¨ •Â˜H‚ª‚ ‚é
        if (parent[x] > parent[y]) swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        return true;
    }
};


int main()
{
    int n, m;
    cin >> n >> m;

    vector<int[2]> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i][0] >> e[i][1];
        e[i][0]--; e[i][1]--;
    }

    UnionFind uf(n);

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (!uf.unite(e[i][0], e[i][1])) {
            cnt++;
        }
    }

    cout << cnt << '\n';

    return 0;
}

#endif

#ifdef _400_C

int main()
{
    ll n;
    cin >> n;

    vector<ll> p;
    p.push_back(1);

    while (true) {
        p.emplace_back(2 * p.back());
        if (p.back() > n) break;
    }
    ll A = p.size() - 2;

    ll B = 1;
    while (true) {
        if (2 * B * B > n) break;
        B++;
    }

    ll sum = 0;
    for (ll a = 1; a <= A; a++) {
        ll r = B;
        ll l = 1;
        while (r - l > 1) {
            ll m = (l + r) / 2;
            if (m * m <= n / p[a])   // NG!! p[a] * m * m <= n   << p[a]‚ª‘å‚«‚¢‚Æ‚«–³—
                l = m;
            else
                r = m;
        }
        sum += (l + 1) / 2;
    }

    cout << sum << '\n';

    return 0;
}
#endif

#ifdef _400_D

int m[1009][1009];

void walk(vector<string>& S, int h, int w, int a, int b, int step, set<tuple<int,int,int>>& wall)
{
    int next[4][2] = { {a - 1, b}, {a + 1, b}, {a, b - 1}, {a, b + 1} };
    for (int k = 0; k < 4; k++) {
        int aa = next[k][0];
        int bb = next[k][1];
        if ( aa >= 0 && aa < h && bb >= 0 && bb < w && m[aa][bb] == -1) {
            if (S[aa][bb] == '.') {
                m[aa][bb] = step;
                walk(S, h, w, aa, bb, step, wall);
            }
            else {
                wall.insert(make_tuple(a, b, k));
            }
        }
    }
}

void kick(vector<string>& S, int h, int w, tuple<int, int, int> wall, int step, set<pair<int, int>>& knext)
{
    int a = get<0>(wall);
    int b = get<1>(wall);
    int k = get<2>(wall);
    int next[4][2] = { {a - 1, b}, {a + 1, b}, {a, b - 1}, {a, b + 1} };
    int next2[4][2] = { {a - 2, b}, {a + 2, b}, {a, b - 2}, {a, b + 2} };

    int aa = next[k][0];
    int bb = next[k][1];
    if (aa >= 0 && aa < h && bb >= 0 && bb < w && m[aa][bb] == -1) {
        if (S[aa][bb] == '#') {
            S[aa][bb] = '.';
            m[aa][bb] = step;
            knext.insert(make_pair(aa, bb));
        }
    }
    aa = next2[k][0];
    bb = next2[k][1];
    if (aa >= 0 && aa < h && bb >= 0 && bb < w && m[aa][bb] == -1) {
        if (S[aa][bb] == '#') {
            S[aa][bb] = '.';
            m[aa][bb] = step;
            knext.insert(make_pair(aa, bb));
        }
    }
}

int main()
{
    int h, w;
    cin >> h >> w;

    vector<string> S(h);
    for (int i = 0; i < h; i++) {
        cin >> S[i];
    }

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--; b--; c--; d--;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            m[i][j] = -1;
        }
    }

    m[a][b] = 0;
    int step = 0;
    set<tuple<int, int, int>> n0;
    set<pair<int, int>> n1;
    n1.insert(make_pair(a, b));

    while (true) {
        for (auto& nn : n1) {
            walk(S, h, w, nn.first, nn.second, step, n0);
        }
        n1.clear();
        if (m[c][d] >= 0) {
            cout << m[c][d] << '\n';
            return 0;
        }

        step++;
        for (auto& nn : n0) {
            kick(S, h, w, nn, step, n1);
        }
        n0.clear();
        if (m[c][d] >= 0) {
            cout << m[c][d] << '\n';
            return 0;
        }
    }

    return 0;
}

#endif



#if _401_D

vector<pair<char, int>> runLength(const std::string& input) {
    int n = (int)input.length();
    vector<pair<char, int>> encode;
    for (int i = 0; i < n; ) {
        char current = input[i];
        int count = 1;
        while (i + count < n && input[i + count] == current) {
            count++;
        }
        encode.push_back(make_pair(current, count));
        i += count;
    }
    return encode;
}

string decode(const vector<pair<char, int>>& s)
{
    string out;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < s[i].second; k++) {
            out.push_back(s[i].first);
        }
    }
    return out;
}

string ReplaceForceDot(const string& s) 
{
    auto encode = runLength(s);
    vector<pair<char, int>> mod;
    for (int i = 0; i < encode.size(); i++) {
        if (encode[i].first == '?') {
            bool left = false, right = false;
            if (i > 0 && encode[i - 1].first == 'o') {
                left = true;
            }
            if (i < encode.size() - 1 && encode[i + 1].first == 'o') {
                right = true;
            }
            if (encode[i].second == 1) {
                if (left || right) {
                    encode[i].first = '.';
                }
                mod.push_back(encode[i]);
            }
            else if (encode[i].second >= 2) {
                if (left) {
                    encode[i].second--;
                }
                if (right) {
                    encode[i].second--;
                }
                if (left) {
                    mod.push_back(make_pair('.', 1));
                }
                mod.push_back(encode[i]);
                if (right) {
                    mod.push_back(make_pair('.', 1));
                }
            }
        }
        else {
            mod.push_back(encode[i]);
        }
    }

    return decode(mod);
}

void checkFreePoint(vector<pair<char, int>>& encode, int* count, int* any, int* max_add)
{
    for (int i = 0; i < encode.size(); i++) {
        if (encode[i].first == '?') {
            *any += encode[i].second;
            *max_add += (encode[i].second + 1) / 2;
        }
        if (encode[i].first == 'o') {
            *count += encode[i].second;
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string ss = ReplaceForceDot(s);

    int count = 0;
    int any = 0;
    int max_add = 0;

    auto ec = runLength(ss);

    checkFreePoint(ec, &count, &any, &max_add);

    int add = k - count;
    vector<pair<char, int>> mod;
    string t;
    if (add == 0) {
        for (int i = 0; i < ec.size(); i++) {
            if (ec[i].first == '?') {
                ec[i].first = '.';
            }
            mod.push_back(ec[i]);
        }
        t = decode(mod);
    }
    else if (add == max_add) {
        for (int i = 0; i < ec.size(); i++) {
            if (ec[i].first == '?') {
                if (ec[i].second % 2 == 1) {
                    for (int k = 0; k < ec[i].second / 2; k++) {
                        mod.push_back(make_pair('o', 1));
                        mod.push_back(make_pair('.', 1));
                    }
                    mod.push_back(make_pair('o', 1));
                }
                else {
                    mod.push_back(ec[i]);
                }
            }
            else {
                mod.push_back(ec[i]);
            }
        }
        t = decode(mod);
    }
    else {
        t = decode(ec);
    }

    cout << t << '\n';

    return 0;
}

#endif


#ifdef _401_C

int main()
{
    ll n, k;
    cin >> n >> k;

    const ll MOD = 1e9;

    vector<ll> A(max(k+1, n+1));

    for (int i = 0; i < k; i++) {
        A[i] = 1;
    }
    if (n < k) {
        cout << 1 << '\n';
        return 0;
    }
    if (n == k) {
        cout << k << '\n';
        return 0;
    }

    // n > k
    A[k] = k;
    for (int i = k+1; i <= n; i++) {
        A[i] = (A[i - 1] + A[i - 1]) % MOD;
        A[i] = (A[i] - A[i - k - 1] + MOD) % MOD;
    }

    cout << A[n] << '\n';

    return 0;
}

#endif

#ifdef _402_D


int main()
{
    ll n, m;
    cin >> n >> m;

    vector<int> va(m);
    vector<int> vb(m);
    map<int, ll> mod;

    for (int i = 0; i < m; i++) {
        cin >> va[i] >> vb[i]; va[i]--; vb[i]--;
    }

    for (int i = 0; i < m; i++) {
        int mo = (va[i] + vb[i] + n) % n;
        mod[mo]++;
    }
    ll para = 0;
    for (auto& e : mod) {
        para += e.second * (e.second - 1) / 2;
    }

    cout << m * (m - 1) / 2 - para << endl;

    return 0;
}

#endif


#ifdef _402_C

int main()
{
    int n, m;
    cin >> n >> m;

    int nok = 0;
    vector<vector<int>> dish(m);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            dish[i].emplace_back(a);
        }
    }

    vector<int> b(n);
    map<int, int> b_index;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b_index[b[i]] = i;
    }

    vector<int> max_b(m);
    for (int i = 0; i < m; i++) {
        int mid = 0;
        for (int j = 0; j < dish[i].size(); j++) {
            mid = max(mid, b_index[dish[i][j]]);
        }
        max_b[i] = mid;
    }

    sort(max_b.begin(), max_b.end());

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        while (cnt < m) {
            if (max_b[cnt] <= i) {
                cnt++;
            }
            else {
                break;
            }
        }
        cout << cnt << endl;
    }

    return 0;
}

#endif

#ifdef _406_C

int main()
{
    int n;
    cin >> n;
    vector<int> p(n);

    for (int i = 0; i < n; i++) cin >> p[i];

    vector<ll> peak;
    peak.push_back(0);
    for (int i = 1; i < n - 1; i++) {
        if (p[i - 1] < p[i] && p[i] > p[i + 1]) {
            peak.push_back(i);
        }
        if (p[i - 1] > p[i] && p[i] < p[i + 1]) {
            peak.push_back(i);
        }
    }
    peak.push_back(n - 1);

    ll cnt = 0;
    int np = peak.size();
    if (np < 4) {
        cout << cnt << "\n";
        return 0;
    }

    for (int i = 0; i+3 < np; i++) {
        if (p[peak[i + 1]] > p[peak[i]] && p[peak[i + 3]] > p[peak[i + 2]]) {
            cnt += (peak[i + 3] - peak[i + 2]) * (peak[i + 1] - peak[i]);
        }
    }

    cout << cnt << "\n";

    return 0;
}

#endif

#if _406_D

int main()
{
    int h, w, n, q;
    cin >> h >> w >> n;
    vector<set<int>> X(h);
    vector<set<int>> Y(w);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        X[x].insert(y);
        Y[y].insert(x);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int qu;
        int z;
        cin >> qu >> z; z--;

        if (qu == 1) {
            cout << X[z].size() << "\n";
            for (auto& yy : X[z]) {
                Y[yy].erase(z);
            }
            X[z].clear();
        }
        if (qu == 2) {
            cout << Y[z].size() << "\n";
            for (auto& xx : Y[z]) {
                X[xx].erase(z);
            }
            Y[z].clear();
        }
    }

    return 0;
}

#endif


#ifdef _403_C

int main()
{
    ll n, m, q;
    cin >> n >> m >> q;

    vector<bool> x_admin(n, false);
    vector<set<ll>> x_y(n);

    for (ll i = 0; i < q; i++) {
        ll act, x, y;
        cin >> act >> x; x--;
        if (act == 1) {
            cin >> y; y--;
            if (x_admin[x]) continue;
            else x_y[x].insert(y);
        }
        if (act == 2) {
            x_admin[x] = true;
        }
        if (act == 3) {
            cin >> y; y--;
            if (x_admin[x]) {
                cout << "Yes" << endl;
            }
            else {
                if (x_y[x].count(y)) {
                    cout << "Yes" << endl;
                }
                else {
                    cout << "No" << endl;
                }
            }
        }
    }
    return 0;
}

#endif

#ifdef _403_B

int main()
{
    string t, u;
    cin >> t;
    cin >> u;

    auto tn = t.size();
    auto un = u.size();

    for (int i = 0; i <= tn - un; i++) {
        bool ok = true;
        for (int j = 0; j < un; j++) {
            if (t[i + j] == '?') continue;
            if (t[i + j] != u[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;
}
#endif

#ifdef _405_B

int main()
{
    int m, n;
    cin >> n >> m;

    int Afirst[109] = { 0 };
    for (int i = 0; i < 101; i++) {
        Afirst[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (Afirst[a - 1] < 0) Afirst[a - 1] = i;
    }
    int imax = 0;
    for (int j = 0; j < m; j++) {
        if (Afirst[j] < 0) {
            cout << (int)0 << endl;
            return 0;
        }
        imax = max(imax, Afirst[j]);
    }
    cout << n-imax << endl;

    return 0;
}

#endif

#ifdef _404_D

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> c;
    for (int i = 0; i < n; i++) {
        int cost;
        cin >> cost;
        c.push_back(cost);
    }
    vector<vector<int>> A(m);
    for (int j = 0; j < m; j++) {
        A[j] = vector<int>(n, 0);
        int kn;
        cin >> kn;
        for (int k = 0; k < kn; k++) {
            int ai;
            cin >> ai; ai--;
            A[j][ai] = 1;
        }
    }

    vector<int> p3(n+1, 1);
    for (int i = 0; i < n; i++) p3[i+1] = p3[i]*3;

    ll min_cost = LLONG_MAX;
    for (int a = 0; a < p3[n]; a++) {
        vector<int> nc(n, 0);
        for (int i = 0; i < n; i++) {
            nc[i] = a / p3[i] % 3;
        }
        ll cost = 0;
        bool success = true;
        for (int i = 0; i < n; i++) {
            cost += nc[i] * c[i];
        }
        for (int j = 0; j < m; j++) {
            int an = 0;
            for (int i = 0; i < n; i++) {
                an += A[j][i] * nc[i];
            }
            if (an < 2) {
                success = false;
                break;
            }
        }
        if (success) {
            min_cost = min(min_cost, cost);
        }
    }

    cout << min_cost << endl;

    return 0;
}

#endif

#ifdef _404_B

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

#ifdef _404_C

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

