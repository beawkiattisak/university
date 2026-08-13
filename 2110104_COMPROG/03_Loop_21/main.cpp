#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string pass;
    
    while (getline(cin, pass)) {
        bool hasUpper = false;
        bool hasLower = false;
        bool hasNumber = false;
        bool hasPised = false;

        for (int i = 0; i < pass.length(); i++) {
            if (isupper(pass[i])) {
                hasUpper = true;
            }
            if (islower(pass[i])) {
                hasLower = true;
            }

            if (isdigit(pass[i])) {
                hasNumber = true;
            }

            if (ispunct(pass[i])) {
                hasPised = true;
            }
        }

        if (hasUpper && hasLower && hasPised && hasNumber && pass.length() >= 12) {
            cout << "strong" << endl;
        } else if (hasUpper && hasLower && hasNumber && pass.length() >= 8) {
            cout << "weak" << endl;
        } else {
            cout << "invalid" << endl;
        }
    }

}