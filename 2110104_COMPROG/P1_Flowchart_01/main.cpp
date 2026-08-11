#include <iostream>

using namespace std;

int main() {
    int x1, x2, x3, x4, x5;
    cin >> x1 >> x2 >> x3 >> x4 >> x5;

    if ((x1-x5) > x2) {
        // Y
        if (x2 > (x3+x1)) {
            // Y
            if ((x3+x5) > x4) {
                // Y
                cout << "C5" << endl;
            } else {
                // N
                if (x3 < x5) {
                    // Y
                    cout << "C6" << endl;
                } else {
                    // N
                    cout << "C7" << endl;
                }
                cout << "C8" << endl;

            } // end if x3+x5 > x4
        } else {
            // N
        }
    } else {
        // N
        if ((x2-x1) > x3) {
            // Y
        } else {
            // N
            if (x4<(x5+x1)) {
                // Y
                if ((x3+x2)>x5) {
                    // Y
                    cout << "C3" << endl;
                } else {
                    // N
                    cout << "C2" << endl;
                }
                cout << "C4" << endl;
            } else {
                // N
                cout << "C1" << endl;
            }
        }

    } // end if x1-x5 > x2


    return 0;
}