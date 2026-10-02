#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double x;
    cin >> x;
    double result;
    double A, B, xdeg;
    const double PI = acos(-1.0);
    xdeg = x * PI/180.0;

    A = sqrt(pow(x,2) + pow(cos(xdeg),2));
    B = sin(xdeg) + (((pow(cos(xdeg), 3)))/((pow(x, 2) + 1)));
    result = A / B;
    cout << fixed << setprecision(1);
    cout << result;

    return 0;
}