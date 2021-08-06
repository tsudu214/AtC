#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int sum = a + b + c;
    int m = min({a, b, c});

    cout << sum - m;
    return 0;
}

