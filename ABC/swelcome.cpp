#include <iostream>

using namespace std;

int main()
{
    int a, b;

    cin >> a >> b;

    if ( a * b % 2 == 1 ) {
        cout << "Odd";
    } else {
        cout << "Even";
    }

    return 0;
}

