#include <iostream>
using namespace std;
int main () {

    float a,b;cin>>a>>b;
    float cal = (a/b)*100.0;

    if (cal > 100 || cal < 0) {
        cout << "Invalid!";
    } else if (cal <= 10) {
        cout << "Very weak";
    } else if (cal <= 30) {
        cout << "Normal";
    } else if (cal <= 50) {
        cout << "Acceptable";
    } else if (cal <= 80) {
        cout << "Interesting";
    } else {
        cout << "Remarkable";
    }

    return 0;
}