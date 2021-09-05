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

const double PI = 3.14159265358979323846;
const double EPS = 1e-8;

double A[100][2];
double B[100][2];

struct rt {
    double t_;
    double r_;
};

void normalize(double& r, double& t)
{
    if (r < EPS) {
        r = 0;
        t = 0;
    } else {
        t = t - floor(t/(2*PI))*2*PI;
    }
}

void normalize(double& t)
{
    t = t - floor(t/(2*PI))*2*PI;
}

vector<rt> st_MakeRt( int n, double A[][2])
{
    vector<rt> vP;
    for (int i = 0; i < n; i++) {
        rt P;
        P.r_ = sqrt(A[i][0]*A[i][0] + A[i][1]*A[i][1]);
        P.t_ = atan2(A[i][1], A[i][0]);
        normalize(P.r_, P.t_);
        if (P.r_ > EPS) {
            vP.push_back(P);
        }
    }

    sort(vP.begin(), vP.end(), [](auto const& lhs, auto const& rhs) {
        if (fabs(lhs.t_ - rhs.t_) > EPS) return lhs.t_ < rhs.t_;
        return lhs.r_ < rhs.r_;
    });

    return vP;
}

void Rot(vector<rt>& Art, double t)
{
    for (auto& p : Art) {
        if (p.r_ > EPS) {
            p.t_ += t;
            normalize(p.r_, p.t_);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    if (n == 1) {
        cout << "Yes" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        A[i][0] = (double)a;
        A[i][1] = (double)b;
    }
    for (int i = 0; i < n; i++) {
        int c, d;
        cin >> c >> d;
        B[i][0] = (double)c;
        B[i][1] = (double)d;
    }

    // calc gravity
    double Ag[2] = {0, 0};
    double Bg[2] = {0, 0};
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            Ag[k] += A[i][k];
            Bg[k] += B[i][k];
        }
        Ag[k] /= (double)n;
        Bg[k] /= (double)n;
    }

    // make coordinate relative to G
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 2; k++) {
            A[i][k] -= Ag[k];
            B[i][k] -= Bg[k];
        }
    }

    // get sorted (r, t) coord: ignoring r = 0 point
    vector<rt> Art = st_MakeRt( n, A );
    vector<rt> Brt = st_MakeRt( n, B );

    size_t nn = Art.size();
    if (nn != Brt.size()) { // one includes r=0, the other does not.
        cout << "No" << endl;
        return 0;
    }

    for (int i = 0; i < nn; i++) {
        if (i > 0) {
            auto it = next(Brt.begin());
            rotate(Brt.begin(), it, Brt.end());
        }
        if ( fabs(Art[0].r_ - Brt[0].r_) > EPS) {
            continue;
        }
        Rot(Brt, Art[0].t_ - Brt[0].t_);

        bool isSame = true;
        for (int j = 1; j < nn; j++) {
            double tdiff = Art[j].t_ - Brt[j].t_;
            normalize(tdiff);
            if ( tdiff < 2*PI - EPS && tdiff > EPS ) {
                isSame = false;
                break;
            }
            if ( fabs(Art[j].r_ - Brt[j].r_) > EPS) {
                isSame = false;
                break;
            }
        }
        if (isSame) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}


#ifdef C

int main()
{
    int n;
    cin >> n;

    double X[2010][2];

    for (int i = 0; i < n; i++) {
        int t;
        ll l, r;
        cin >> t >> l >> r;
        double dl, dr;
        if (t == 1) {
            dl = (double)l - 0.1;
            dr = (double)r + 0.1;
        }
        else if (t == 2) {
            dl = (double)l - 0.1;
            dr = (double)r - 0.1;
        }
        else if (t == 3) {
            dl = (double)l + 0.1;
            dr = (double)r + 0.1;
        }
        else {
            dl = (double)l + 0.1;
            dr = (double)r - 0.1;
        }
        X[i][0] = dl;
        X[i][1] = dr;
    }

    int cnt = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (X[j][0] < X[i][1] && X[i][0] < X[j][1]) {
                cnt++;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}

#endif
