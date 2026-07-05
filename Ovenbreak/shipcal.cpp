#include <iostream>
using namespace std;
int main () {

    double a,b;cin>>a>>b;

    if (b == 0) {
        cout << "Invalid!";
        return 0; 
    }

    double cal = (a/b)*100.0;

    if (cal > 100.0 || cal < 0.0) {
        cout << "Invalid!";
    } else if (cal <= 10.0) {
        cout << "Very weak";
    } else if (cal <= 30.0) {
        cout << "Normal";
    } else if (cal <= 50.0) {
        cout << "Acceptable";
    } else if (cal <= 80.0) {
        cout << "Interesting";
    } else {
        cout << "Remarkable";
    }

    return 0;
}