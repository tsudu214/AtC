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

const int INF = 10000;
const int M = 310;

int  dp[M][M][M];  // n, a, b

int main()
{
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        A[i] = a; B[i] = b;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= A[i]; j++) {
            for (int k = 0; k <= B[i]; k++) {
                dp[i+1][j][k] = 1;
            }
        }

        for (int j = 0; j <= x; j++) {
            for (int k = 0; k <= y; k++) {
                dp[i+1][j][k] = min(dp[i+1][j][k], dp[i][j][k]);
                dp[i+1][min(x, j+A[i])][min(y, k+B[i])] = min(dp[i+1][min(x, j+A[i])][min(y, k+B[i])], dp[i][j][k] + 1);
            }
        }
    }

    int ans = dp[n][x][y];
    if (ans == INF) {
        ans = -1;
    }

    cout << ans << endl;

    return 0;
}

#ifdef C

string convert(string& s, unordered_map<char, int>& ctoi) 
{
    string ss;
    for (auto& a : s) {
        ss.push_back('a' + ctoi[a]);
    }
    return ss;
}

int main()
{
    string x;
    int n;
    cin >> x >> n;

    unordered_map<char, int> ctoi;
    for (int i = 0; i < 26; i++) {
        ctoi[x[i]] = i;
    }

    vector<pair<string, string>> S;
    for (int i = 0; i < n; i++) {
        string s, ss;
        cin >> s;
        ss = convert(s, ctoi);
        S.push_back(make_pair(ss, s));
    }

    sort(S.begin(), S.end());

    for (auto & x : S) {
        cout << x.second << endl;
    }

    return 0;
}

#endif