#include <iostream>
#include <cmath>
using namespace std;

int main () {
    double a, b, c, x1, x2;
    cin >> a >> b >> c;

    x1 = (-1*b - (sqrt(pow(b,2) - 4*a*c))) / (2*a);
    x2 = (-1*b + (sqrt(pow(b,2) - 4*a*c))) / (2*a);

    cout << round(x1*1e3)/1e3 << " ";
    cout << round(x2*1e3)/1e3;

    return 0;
}