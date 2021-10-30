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

class DisjointSet
{
public:
    DisjointSet(){}
    DisjointSet(int size){
        p.resize(size+1, 0);
        c.resize(size+1, 0);
        for (int i = 0; i < size; i++) {
            makeSet(i+1);
        }
    }

    void makeSet(int x)
    {
        p[x] = x;
        c[x] = x;
    }

    void unite(int x, int y)
    {
        p[y] = x;
        c[x] = y;
    }

    void separate(int x, int y)
    {
        c[x] = x;
        p[y] = y;
    }

    int findTop(int x) 
    {
        int s = x;
        while (p[s] != s) {
            s = p[s];
        }
        return s;
    }

    vector<int> get(int x) {
        vector<int>  v;
        int t = findTop(x);
        v.push_back(t);
        while (c[t] != t) {
            v.push_back(c[t]);
            t = c[t];
        }
        return v;
    }

    void print(int x)
    {
        vector<int> v = get(x);
        int m = v.size();
        cout << m;
        for (int j = 0; j < m; j++) {
            cout << " " <<  v[j];
        }
        cout << endl;
    }

private:
    vector<int> p;
    vector<int> c;

};


int main()
{
    int n, q;
    cin >> n >> q;

    DisjointSet  S(n);

    for (int i = 0; i < q; i++) {
        int com = 0, x = 0, y = 0;
        cin >> com;
        if (com == 1) {
            cin >> x >> y;
            S.unite(x, y);
        }
        else if (com == 2) {
            cin >> x >> y;
            S.separate(x, y);
        }
        else {
            cin >> x;
            S.print(x);
        }
    }
    
    return 0;
}

