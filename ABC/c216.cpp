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

vector<ll>  A;
vector<int> idx_lower;

int main()
{
    int n, k;
    cin >> n >> k;

    A.resize(n);
    idx_lower.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    int index_curr = 0;
    ll  last = A[0];
    idx_lower[0] = index_curr;
    for (int i = 1; i < n; i++) {
        if (A[i] == A[i-1]) {
            idx_lower[i] == index_curr;
        } else {
            idx_lower[i] = i;
            index_curr = i;
        }
    }

    ll S = 0;

    for (int i = 0; i < k; i++) {
        ll M = A[n-1];
        if (M <= 0) break;
        int lower = idx_lower[n-1];
        A[lower]--;
        if (lower > 0 && A[lower] == A[lower-1]) {
            idx_lower[lower] = idx_lower[lower-1];
        }
        if (lower < n-1 && A[lower] < A[lower+1]) {
            idx_lower[lower+1] = lower+1;
        }
        S += M;
    }

    cout << S << endl;

    return 0;
}


#ifdef D

vector<queue<int>> vQ;

int main()
{
    int n, m;
    cin >> n >> m;

    vQ.resize(m);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            vQ[i].push(a);
        }
    }

    vector<int> first_pos(n+1, -1);

    int remain = n;
    while (remain > 0) {
        bool found = false;
        fill(first_pos.begin(), first_pos.end(), -1);
        for (int i = 0; i < m; i++) {
            if (vQ[i].empty()) continue;
            int top = vQ[i].front();
            int prev= first_pos[top];
            if (prev >= 0) {
                vQ[prev].pop();
                vQ[i].pop();
                remain--;
                found = true;
                break;
            }
            else {
                first_pos[top] = i;
            }
        }
        if (found == false) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;


    return 0;
}

#endif

#ifdef C

int main()
{
    ll n;
    cin >> n;

    vector<char> S;
    while (n != 0) {
        if (n % 2 == 1) {
            n -= 1;
            S.push_back('A');
        }
        else {
            n /= 2;
            S.push_back('B');
        }
    }

    reverse(S.begin(), S.end());
    for ( auto& c : S ) {
        cout << c;
    }
    cout << endl;

    return 0;
}

#endif