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

int gcd(int a, int b){
    if(a%b == 0){
        return b;
    } else {
        return gcd(b, a%b);
    }
}

void learn(vector<int>& x, vector<int>& y, int i, int j, set<pair<int, int>>& M)
{
    int a = x[j] - x[i];
    int b = y[j] - y[i];

    if (a == 0) {
        M.insert(make_pair(0, b > 0?1:-1));
        return;
    }
    if (b == 0) {
        M.insert(make_pair(a>0?1:-1, 0));
        return;
    }

    int g = abs(gcd(a, b));
    a /= g;
    b /= g;

    M.insert(make_pair(a, b));
}

int main()
{
    int n;
    cin >> n;

    vector<int> x(n);
    vector<int> y(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    set<pair<int, int>> M;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            learn(x, y, i, j, M);
        }
    }

    cout << M.size() << endl;
    
    return 0;
}

