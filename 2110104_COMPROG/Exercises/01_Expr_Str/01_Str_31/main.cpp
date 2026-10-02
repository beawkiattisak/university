#include <iostream>
#include <string>
#include <cmath>
using namespace std;

long gcd(long a, long b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    string A, B, C;
    cin >> A >> B >> C;
    int m = B.length();
    int n = C.length();

    int AB = stoi(A+B);
    int ABC = stoi(A+B+C);

    int X = ABC-AB;
    int Expo = pow(10, m + n) - pow(10, m);

    int g = gcd(X, Expo);

    cout << X/g <<  " / " << Expo/g;

    return 0;
}