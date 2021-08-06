#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double PI=3.14159265358979323846;

const double EPS=1e-8;


struct Point {
    Point() { xy[0] = xy[1] = 0; }
    Point(double x, double y) { xy[0] = x; xy[1] = y; }
    double xy[2];
    double dist2(const Point& r = Point()) {
        return (this->xy[0] - r.xy[0])*(this->xy[0] - r.xy[0]) + (this->xy[1] - r.xy[1])*(this->xy[1] - r.xy[1]);
    }
    double dist(const Point& r = Point()) {
        return sqrt(dist2(r));
    }
};

struct PointRT {
    PointRT() { rt[0] = rt[1] = 0; }
    PointRT(double r, double t) { 
        rt[0] = r; 
        if (fabs(rt[0]) > EPS) {
            rt[1] = t; 
            rt[1] = rt[1] - floor(rt[1]/(2.0*PI))*2.0*PI; 
        }
    }
    double rt[2];
    void rotate(double t) {
        if (fabs(rt[0]) > EPS) {
            rt[1] += t;
            rt[1] = rt[1] - floor(rt[1]/(2.0*PI))*2.0*PI;
        }
    }
};

bool LessByAngle(const PointRT& l, const PointRT& r)
{
    if ( l.rt[1] != r.rt[1] )
        return l.rt[1] < r.rt[1];
    return l.rt[0] < r.rt[0];
}

bool IsSame(const PointRT& l, const PointRT& r)
{
    double rdiff = l.rt[0] - r.rt[0];
    if (fabs(rdiff) > EPS) return false;

    double tdiff = fabs(l.rt[1] - r.rt[1]);
    tdiff = tdiff - floor(tdiff/(2.0*PI))*2.0*PI;
    if (fabs(tdiff) < EPS ) return true;
    if (fabs(tdiff - 2.0*PI) < EPS) return true;
    return false;
}

int main()
{
    int N;
    cin >> N;

    vector<Point> vzA, vzB;
    for ( int i = 0; i < N; i++ ) {
        int x, y;
        cin >> x >> y;
        Point p( (double)x, (double)y );
        vzA.push_back(p);
    }
    for ( int i = 0; i < N; i++ ) {
        int x, y;
        cin >> x >> y;
        Point p( (double)x, (double)y );
        vzB.push_back(p);
    }

    if ( N == 1 ) {
        cout << "Yes";
        return 0;
    }
    if ( N == 2 ) {
        double dA = vzA[0].dist2(vzA[1]);
        double dB = vzB[0].dist2(vzB[1]);
        if (fabs(dA - dB) < EPS) {
            cout << "Yes";
        } else {
            cout << "No";
        }
        return 0;
    }

    Point pointGa;
    {
        double Gx = 0, Gy = 0;
        for (int i = 0; i < N; i++ ) {
            Gx += vzA[i].xy[0];
            Gy += vzA[i].xy[1];
        }
        pointGa.xy[0] = Gx / (double)N;
        pointGa.xy[1] = Gy / (double)N;
    }
    Point pointGb;
    {
        double Gx = 0, Gy = 0;
        for (int i = 0; i < N; i++ ) {
            Gx += vzB[i].xy[0];
            Gy += vzB[i].xy[1];
        }
        pointGb.xy[0] = Gx / (double)N;
        pointGb.xy[1] = Gy / (double)N;
    }

    for (int i = 0; i < N; i++ ) {
        for ( int k = 0; k < 2; k++ ) vzA[i].xy[k] -= pointGa.xy[k];
        for ( int k = 0; k < 2; k++ ) vzB[i].xy[k] -= pointGb.xy[k];
    }

    // transform to (r, theta) 
    vector<PointRT>  vzAr, vzBr;
    for (int i = 0; i < N; i++ ) {
        if (vzA[i].dist() > EPS) {
            PointRT q(vzA[i].dist(), atan2(vzA[i].xy[0], vzA[i].xy[1]));
            vzAr.push_back(q);
        }
    }
    for (int i = 0; i < N; i++ ) {
        if (vzB[i].dist() > EPS) {
            PointRT q(vzB[i].dist(), atan2(vzB[i].xy[0], vzB[i].xy[1]));
            vzBr.push_back(q);
        }
    }
    N = (int)vzAr.size();

    sort(vzAr.begin(), vzAr.end(), LessByAngle);
    sort(vzBr.begin(), vzBr.end(), LessByAngle);

    // pickup farthest
    int iFar = 0;
    double dFar = vzAr[0].rt[0];
    for ( int i = 1; i < N; i++ ) {
        if (vzAr[i].rt[0] > dFar) {
            dFar = vzAr[i].rt[0];
            iFar = i;
        }
    }
    // rotate
    rotate(vzAr.begin(), vzAr.begin() +iFar, vzAr.end());

    int iBegin = 0;
    for ( int iTry = 0; iTry < N; iTry++ ) {
        int iFound = -1;
        for ( int i = iBegin; i < N; i++ ) {
            if ( fabs(vzAr[0].rt[0] - vzBr[i].rt[0]) < EPS ) {
                iFound = i;
                break;
            }
        }
        if ( iFound < 0 ) {
            cout << "No";
            return 0;
        }

        vector<PointRT>  vzBrRot = vzBr;
        rotate(vzBrRot.begin(), vzBrRot.begin() + iFound, vzBrRot.end());
        double dRot = vzBrRot[0].rt[1] - vzAr[0].rt[1];
        for ( int i = 0; i < N; i++ ) {
            vzBrRot[i].rotate(-dRot);
        }

        bool success = true;
        for ( int i = 0; i < N; i++ ) {
            if ( !IsSame(vzBrRot[i], vzAr[i]) ) {
                success = false;
                break;
            }
        }
        if (success) {
            cout << "Yes";
            return 0;
        }
        iBegin = iFound + 1;
    } 

    cout << "No";

    return 0;
}

