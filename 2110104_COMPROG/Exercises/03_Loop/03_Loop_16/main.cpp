#include <iostream>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h;
    cin >> h;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h+i; j++) {
            if (j == h+i-1 || i == h-1 || i == h-j-1) {
                cout << "*";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }   

}