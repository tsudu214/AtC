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
    char s[200010];
    cin >> s;
    int k;
    cin >> k;
    int L = strlen(s);

    vector<int> Xs;

    // "." array pos & len
    vector<pair<int, int>> dots;
    bool isdot = false;
    int first = 0;
    int last = 0;
    if (s[0] == '.') {
        isdot = true;
    }
    for (int i = 1; i < L; i++) {
        if (isdot) {
            if (s[i] == '.') {
                last = i;
            }
            else {
                dots.push_back({first, last - first + 1});
                isdot = false;
            }
        } else {
            if (s[i] == '.') {
                first = i;
                last = i;
                isdot = true;
            }
            else {
            }
        }
    }
    if (isdot) {
        dots.push_back({first, L-first});
    }

    int h = 0;


    return 0;
}
