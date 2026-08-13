#include <iostream>
#include <cmath>
using namespace std;

int factorial(int n) {
    if (n==0) {
        return 1;
    }
    return n*factorial(n-1);
}

int main() {
    cout << (M_PI-(factorial(10) / pow(8,8) ) + pow(log(9.7), (7/sqrt(71) - sin((40*M_PI) / 180.0)))) / (pow(1.2, cbrt(2.3)));

    return 0;
}