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

using ll = long long; // ~ 9*10^18


// https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_db

int main()
{
    // a^b ÇãÅÇﬂÇÈ
    ll a, b;
    cin >> a >> b;

    const ll FAC = 1e9 + 7;

    // bÇ2êiêî
    vector<ll>  bib;
    ll r = b;
    while (b > 1) {
        r = b % 2;
        b /= 2;
        bib.push_back(r);
    }
    bib.push_back(1);

    ll sum = 1;
    ll x = a;
    for (auto& B : bib) {
        if (B) {
            sum = sum * x;
            sum = sum % FAC;
        }
        x = x % FAC;
        x = x * x;
        x = x % FAC;
    }

    cout << sum << endl;

    return 0;
}

#ifdef A25
// https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_y

char c[40][40];
ll dp[40][40];

int main()
{
    int h, w;
    cin >> h >> w;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> c[i][j];
            dp[i][i] = 0;
        }
    }
    
    dp[0][0] = 1;
    for (int k = 1; k < h + w -1; k++) {
        for (int i = 0; i <= k; i++) {
            int j = k - i;
            if (i >= h || j >= w) continue;
            if (c[i][j] == '#') continue;
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    cout << dp[h - 1][w - 1] << endl;

    return 0;
}

#endif