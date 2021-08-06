#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    int n;
    int a, b;

    cin >> n >> a >> b;

    int count = 0;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++ ) {
            for (int z = 0; z < 10; z++ ) {
                for (int w = 0; w < 10; w++ ) {
                    int val = 1000*w + 100*x + 10*y + z;
                    int sum = x + y + z + w;
                    if ( val <= n && a <= sum && sum <= b ) {
                        count += val;
                    }
                }
            }
        }
    }
    if (a == 1 && n == 10000) {
        count += 10000;
    }


    cout << count << "\n";

    return 0;
}

