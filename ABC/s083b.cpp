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

using namespace std;

int main()
{
    int n, s;

    cin >> n >> s;

    int min = 1*n;
    int max = 6*n;

    if ( min <= s && s <= max ) {
        cout << "Yes\n";
    }
    else {
        cout << "No";
    }

    return 0;
}

