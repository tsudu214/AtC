#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    int n = 0;

    cin >> n;

    deque<long> A;
    for (int i = 0; i < n; i++ ) {
        int a;
        cin >> a;
        A.push_back(a);
    }

    int iCount = 0;
    while (1) {
        bool  stop = false;
        for (int i = 0; i < n; i++ ) {
            if (A[i] %2 == 1) {
                stop = true;
                break;
            }
        }
        if (stop) {
            break;
        }
        for (int i = 0; i < n; i++ ) {
            A[i] /= 2;
        }
        iCount++;
    } 

    cout << iCount << "\n";

    return 0;
}

