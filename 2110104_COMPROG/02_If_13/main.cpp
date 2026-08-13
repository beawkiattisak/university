#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a, b, c, d, max_val, min_val;
    cin >> a >> b >> c >> d;
    max_val = a;
    min_val = a;
    if (b > max_val) {
        max_val = b;
    } 
    if (c > max_val) {
        max_val = c;
    } 
    if (d > max_val) {
        max_val = d;
    }

    if (b < min_val) {
        min_val = b;
    }
    if (c < min_val) {
        min_val = c;
    }
    if (d < min_val) {
        min_val = d;
    }

    double x = (a+b+c+d-min_val-max_val)/2.0;

    cout << round(x*100.0)/100.0;

    return 0;
}