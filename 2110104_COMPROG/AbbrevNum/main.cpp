#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double num;
    cin >> num;

    if (num < 1000) {
        cout << num;
    } else if (num <= 10000) {
        cout << round((num/1000.0)*10.0) / 10.0 << "K";
    } else if (num <= 100000) {
        cout << round((num/10000.0)*10.0) << "K";
    } else if (num <= 1000000) {
        cout << round((num/10000.0)*10.0) << "K";
    } else if (num <= 10000000) {
        cout << round((num/1000000.0)*10.0)/10.0 << "M";
    } else if (num <= 1000000000) {
        cout << round((num/1000000.0)) << "M";
    } else if (num <= 10000000000) {
        cout << round((num/100000000.0))/10.0 << "B";
    } else if (num <= 100000000000) {
        cout << round((num/1000000000.0)) << "B";
    } else if (num <= 10000000000000) {
        cout << round((num/1000000000.0)) << "B";
    }
    

    return 0;
}