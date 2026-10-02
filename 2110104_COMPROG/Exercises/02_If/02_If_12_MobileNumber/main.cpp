#include <iostream>
#include <string>
using namespace std;

int main() {
    string phoneNumber;
    cin >> phoneNumber;

    if (phoneNumber.length() == 10 && (phoneNumber.substr(0, 2) == "06" ||  phoneNumber.substr(0, 2) == "08" || phoneNumber.substr(0, 2) == "09")) {
        cout << "Mobile number";
    } else {
        cout << "Not a mobile number";
    }
    return 0;
}