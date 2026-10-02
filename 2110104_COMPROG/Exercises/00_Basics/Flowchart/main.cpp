#include <iostream>

using namespace std;

int main() {
    int A, B, C;
    cin >> A >> B >> C;

    if (A > 100) {
        if ( B > C ) {
            if ( B % 2 == 0) {
                A = A + B;
                C = C + 2;
            } else {
                A = A - C;
                B = B + 3;
            }
        } else {
            C = C+10;
            A = A - 5;
        }

        if (A % 5 == 0) {
            B = B - 1;
        } else {
            C = C + 1;
        }

        while (A <= (3 * abs(B + C))) {
            if ( B > C ) {
            if ( B % 2 == 0) {
                A = A + B;
                C = C + 2;
            } else {
                A = A - C;
                B = B + 3;
            }
            } else {
                C = C+10;
                A = A - 5;
            }

            if (A % 5 == 0) {
                B = B - 1;
            } else {
                C = C + 1;
            }
        }

    } else {
        if ( A < B) {
            if (C % 3 == 0) {
                A = A * 2;
                B = B - 1;
            } else {
                A = A + B;
                C = C * 2;
            }
        } else {
            A = A + B;
            C = C * 2;
        }

        if (B < C) {
            B = B + C;
            A = A + 1;
        } else {
            C = C - B;
            A = A - 2;
        }
    }

    cout << A << '\n';
    cout << B << '\n';
    cout << C << '\n';

    return 0;
}