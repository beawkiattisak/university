#include <iostream>
using namespace std;
int main() {
    int h; cin>>h;

    for (int i=0; i < h; i++) {
        for (int j = i; j < h-1; j++) {
            cout << " ";
        }
        for (int k = 1; k <= (2 * i + 1); k++) {
            cout << "*";
        }

        cout << "\n";
    }

    return 0;
}