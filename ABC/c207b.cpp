#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if ( b >= c*d ) {
        cout << -1 ;
        return 0;
    }

    int ret = (int) ceil( a / (double)(c*d - b) );

    cout << ret;
    return 0;
}

