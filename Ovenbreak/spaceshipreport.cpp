#include <iostream>
#include <string>
using namespace std;

int main() {
    int a,b,c; cin>>a>>b>>c;
    bool has_error = false;

    if(a < 30) {
        cout << "LOW OXYGEN" << endl;
        has_error = true;
    }

    if(b < 50) {
        cout << "ENGINE ERROR" << endl;;
        has_error = true;
    }

    if(c >= 70) {
        cout << "HULL DAMAGE" << endl;;
        has_error = true;
    }

    if (!has_error) {
        cout << "ALL SYSTEMS STABLE";
    }
    return 0;
}