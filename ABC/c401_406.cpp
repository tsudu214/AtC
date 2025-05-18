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

vector<pair<char, int>> runLength(const std::string& input) {
    int n = input.length();
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
    int n = s.size();
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


#ifdef _405_D

char S[1009][1009];
int  T[1009][1009];

void walk(int h, int w, char S[][1009], int T[][1009], int i, int j, int step, int prev)
{
    int dirs[4][2] = { {i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1} };
    int prev_dir[4] = { 1, 0, 3, 2 };
    char back[4] = { '^', 'V', '<', '>' };
    for (int dir = 0; dir < 4; dir++) {
        if (dir == prev) continue;
        int ii = dirs[dir][0];
        int jj = dirs[dir][1];
        if (ii < 0 || ii >= h) continue;
        if (jj < 0 || jj >= w) continue;

        int t = T[ii][jj];
        if (t == 1000000) continue;

        if (t < 0) {
            T[ii][jj] = step + 1;
            S[ii][jj] = back[dir];
            walk(h, w, S, T, ii, jj, step + 1, prev_dir[dir]);
        }
        else if (t > step + 1) {
            T[ii][jj] = step + 1;
            S[ii][jj] = back[dir];
            walk(h, w, S, T, ii, jj, step + 1, prev_dir[dir]);
        }
    }
}

int main()
{
    int h, w;
    cin >> h >> w;

    const int HUGE = 1000000;

    vector<pair<int, int>> vE;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> S[i][j];
            T[i][j] = HUGE;
            if (S[i][j] == 'E') {
                T[i][j] = 0;
                vE.push_back(make_pair(i, j));
            }
            if (S[i][j] == '.') {
                T[i][j] = -1;
            }
        }
    }

    for (auto& e : vE) {
        int i = e.first;
        int j = e.second;
        walk(h, w, S, T, i, j, 0, -1);
    }
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << S[i][j];
        }
        cout << endl;
    }

    return 0;
}

#endif

#ifdef _405_C

int main()
{
    ll n;
    unordered_map<ll, ll> A;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        A[a]++;
    }

    ll sum = 0;
    ll m = 0;
    vector<ll> vA;
    for (auto& e : A) {
        vA.emplace_back(e.first);
    }
    m = vA.size();
    for (ll i = 0; i < m - 1; i++) {
        ll Ai = vA[i];
        for (ll j = i + 1; j < m; j++) {
            ll Aj = vA[j];
            sum += Ai * Aj * A[Ai] * A[Aj];
        }
    }
    cout << sum << endl;

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

