#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <set>
 
using namespace std;
 
 
int main()
{
    int N;
    
    vector<pair<double, double>> range;
    scanf("%d", &N);
 
    for ( int i = 0; i < N; i++ ) {
        int t, l, r; 
        double L, R;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            L = (double)l; R = (double)r;
        }
        if (t == 2) {
            L = (double)l; R = (double)(r-0.5);
        }
        if (t == 3) {
            L = (double)(l+0.5); R = (double)r;
        }
        if (t == 4) {
            L = (double)(l+0.5); R = (double)(r-0.5);
        }
        range.push_back(make_pair(L, R));
    }
 
    int ret = 0;
    for ( int i = 0; i < N; i++ ) {
        auto&  r1 = range[i];
        for ( int j = i+1; j < N; j++ ) {
            auto&  r2 = range[j];
            double late_start = max(r1.first, r2.first);
            double early_end  = min(r1.second, r2.second);
            if (late_start <= early_end) {
                ret++;
            }
        }
    }
 
    printf("%d\n", ret);
    return 0;
}
