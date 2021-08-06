#include <iostream>

using namespace std;

int main()
{
    int n = 0;

    string s;
    cin >> s;

    for ( int k = 0; k < 3; k++ ) {
        if (s[k] == '1') {
            n++;
        }
    }

    cout << n << "\n";

    return 0;
}

