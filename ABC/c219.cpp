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

struct bento {
    int i;
    int a;
    int b;
};

int main()
{
    int n, x, y;
    cin >> n >> x >> y;

    int as = 0, bs = 0;
    vector<bento> A(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        A[i] = {i, a, b};
        as += a;
        bs += b;
    }

    if (as < x || bs < y) {
        cout << -1 << endl;
        return 0;
    }

    vector<bento> B = A;
    sort(A.begin(), A.end(), 
    [](bento x, bento y) {
        if (x.a != y.a ) return x.a > y.a;
        else return x.b > y.b;
    } );
    sort(B.begin(), B.end(), 
    [](bento x, bento y) {
        if (x.b != y.b) return x.b > y.b;
        else return x.a > y.a;
    } );

    int ai = 0, bi = 0;
    set<int> picked;
    while (true) {
        if (x <= 0 && y <= 0) break;

        if (x <= 0) {
            if (picked.count(B[bi].i)) {
                bi++;
            }
            else {
                x -= B[bi].a;
                y -= B[bi].b;
                picked.insert(B[bi].i);
                bi++;
            }
        }
        else if (y <= 0) {
            if (picked.count(A[ai].i)) {
                ai++;
            }
            else {
                x -= A[ai].a;
                y -= A[ai].b;
                picked.insert(A[ai].i);
                ai++;
            }
        }
        else {
            if (x > y) {
                if (picked.count(A[ai].i)) {
                    ai++;
                }
                else {
                    x -= A[ai].a;
                    y -= A[ai].b;
                    picked.insert(A[ai].i);
                    ai++;
                }
            } else {
                if (picked.count(B[bi].i)) {
                    bi++;
                }
                else {
                    x -= B[bi].a;
                    y -= B[bi].b;
                    picked.insert(B[bi].i);
                    bi++;
                }
            }
        }
    }

    cout << picked.size() << endl;

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