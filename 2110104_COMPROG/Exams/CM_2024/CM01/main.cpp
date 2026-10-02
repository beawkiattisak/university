#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int x, y, z;

    if (x < 50) {
        if (y > z) {
            do {
                x = x - (y - z);
                y = y + 1;
            } while (y % 2 != 0);

            x += pow(y, 2) + pow(z, 2);

            if (y % 10 == 4) {
                cout << x << " " << y << " " << z;
                return 0;
            }

        }
    }

    return 0;
}