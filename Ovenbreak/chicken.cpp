#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;

double roundChicken(double n) {
    return 6+7*(log(pow(n + 1, 1.2)));
}

int main() {    
    double x; cin>> x;
    double rad = roundChicken(x) / 2.0;
    double vol = (4.0/3.0)*M_PI*(pow(rad,3.0));
    cout << fixed << setprecision(2);
    cout << vol;

    return 0;
}