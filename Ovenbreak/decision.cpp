#include <iostream>
using namespace std;

int main() {
    int density, size;
    cin >> density >> size;

    if (density<=500) {
        if(size <=30) { 
            cout << "DT Action: IGNORE";
        } else {
            cout << "DT Action: SHOOT";
        }
    } else {
        if(size <=100) { 
            cout << "DT Action: REFLECT";
        } else {
            cout << "DT Action: WARP_EVADE";
        }
    }

    return 0;
}