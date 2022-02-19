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

string toBinary(ll n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    reverse(r.begin(), r.end());
    return r;
}

bool exist(string& A, string& S)
{
    int an = A.size();
    int sn = S.size();
    string AA;
    for (int i = 0; i < sn - an; i++) {
        AA += "0";
    }
    AA += A;
    for (int i = 0; i < AA.size(); i++) {
        if (AA[i] == '1') {
            if (i < S.size()) {
                if (S[i] == '1') {
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int t;
    ll a, s;
    cin >> t;
    t = 1;

    for (int i = 0; i < t; i++) {
        cin >> a >> s;

        a = 360288799186493714; s = 788806911317182736;

        string A, S;
        A = toBinary(a);
        S = toBinary(s);

        if (exist(A, S)) {
            cout << "Yes" << endl;
        }else {
            cout << "No" << endl;
        }
    }

    return 0;
}


#ifdef C

int main()
{
    //string sn = "999999999999999999";
    string sn;
    cin >> sn;

    ll M = 998244353;

    int d = sn.size();

    vector<ll> s_digit(d);
    for (int k = 0; k < d; k++) {
        ll n = 9;
        for (int j = 1; j <= k; j++) {
            n *= 10;
        }
        n %= M;
        s_digit[k] = n * (n+1) / 2;
        s_digit[k] %= M;
    }

    ll base;
    string sb = sn;
    sb[0] = '1';
    for (int i = 1; i < d; i++) {
        sb[i] = '0';
    }
    sscanf(sb.c_str(), "%lld", &base);
    base--;
    ll N;
    sscanf(sn.c_str(), "%lld", &N);
    ll amari = N - base;

    ll sum = 0;
    for (int i = 0; i < d-1; i++) {
        sum += (s_digit[i] % M);
        sum %= M;
    }
    sum += (amari%M) * ((amari+1)%M) /2;
    sum %= M;

    cout << sum << endl;

    return 0;
}

#endif
