#include <iostream>
using namespace std;

bool isPass(char com_prog, char cal1, char cal2) {
    if (com_prog == 'A' && (cal1 == 'A' || cal1 == 'B' || cal1 == 'C') && (cal2 == 'A' || cal2 == 'B' || cal2 == 'C')) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char com_prog1, com_prog2, cal11, cal21, cal12, cal22;
    long long id1, id2;
    double gpax1, gpax2;
    cin >> id1 >> gpax1 >> com_prog1 >> cal11 >> cal21;
    cin >> id2 >> gpax2 >> com_prog2 >> cal12 >> cal22;

    if (isPass(com_prog1, cal11, cal21) && isPass(com_prog2, cal12, cal22)) {
        if (gpax1 > gpax2) {
            cout << id1;
        } else if (gpax1 < gpax2) {
            cout << id2;
        } else {
            if (cal11 < cal12) {
                cout << id1;
            } else if ((cal11 > cal12)) {
                cout << id2;
            } else {
                if (cal21 < cal22) {
                    cout << id1;
                } else if (cal21 > cal22) {
                    cout << id2;
                } else {
                    cout << "Both";
                }
            }
        }
    } else if (isPass(com_prog1, cal11, cal21)) {
        cout << id1;
    } else if (isPass(com_prog2, cal12, cal22)) {
        cout << id2;
    } else {
        cout << "None";
    }
    

    return 0;
}