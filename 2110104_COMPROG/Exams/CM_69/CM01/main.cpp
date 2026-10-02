#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a,b,c;
    int n;
    cin >> a >> b >> c >> n;

    while (a <= b) {
        if (b > c) {
            a = exp(b/a) + a/b;
            b = b + c/b;
        } else {
            if (a > c) {
                b = b*sin(b);
                c = c - log(a);
            } else {
                c = c - b/a;
                a = 1/cos(b) + a/b;
            }
        }
    }

    a = abs(a);

    if (a < 1) {
        a = 1/a;
    }

    double l = 0;
    double r = a;
    double x;
    while (r - l >= pow(10, -5)) {
        x = (l+r)/2.0;
        if (pow(x,n) < a) {
            l = x;
        } else {
            r = x;
        }
    }

    cout << fixed << setprecision(5);
    cout << "a: " << a << endl;
    cout << "b: " << b<< endl;
    cout << "c: " << c<< endl;
    cout << "x: " << x<< endl;

    return 0;
}