#include <string>
#include <iostream>
#include <cmath>
using namespace std;
int main() {

    double targetFrequency,realFrequency;
    char unit;
    cin >> targetFrequency >> unit;
    cin >> realFrequency;
    double unittgcal=targetFrequency;
    
    if(unit == 'k'){
        unittgcal*=1000;
    } else if(unit == 'm') {
        unittgcal*=1000000;
    }

    double percentDiff = fabs((realFrequency - unittgcal) / unittgcal) * 100.0;

    if (percentDiff <= 0.001) {
        cout << "MESSAGE RECEIVED";
    } else if (percentDiff <= 5.0) {
        cout << "PARTIAL MATCH";
    } else if (realFrequency > unittgcal) {
        cout << "SIGNAL TOO HIGH";
    } else {
        cout << "SIGNAL TOO LOW";
    }

    return 0;
}