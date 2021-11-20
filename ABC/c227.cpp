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



int main()
{
    ll n;
    cin >> n;

    ll ans = 0;

    for (ll a = 1; a*a*a <= n; a++) {

        for (ll b = a; b*b <= n/a; b++) {
            ans += (n/b/a - b + 1);
        }
    } 

    cout << ans << endl;
    
    return 0;
}

