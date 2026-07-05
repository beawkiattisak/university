#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float n;cin>>n;

    cout << fixed << setprecision(2);
    if (n<0) {
        cout << "Activated Signal: " << 0.00; 
    } else {
        cout << "Activated Signal: " << n; 
    }


    return 0;
}