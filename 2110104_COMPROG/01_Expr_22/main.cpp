#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double xe, ye, re, rp, xm, ym, xp, yp;

    cin >> xe >> ye >> re >> rp >> xm >> ym;

    double A = xm - xe;
    double B = ym - ye;
    double C = sqrt(pow(A, 2) + pow(B, 2));

    double c = re - rp;
    double a = (c*A) / C;
    double b = (c*B) / C;

    cout << round(xe+a) << " " << round(ye+b);

    return 0;
}