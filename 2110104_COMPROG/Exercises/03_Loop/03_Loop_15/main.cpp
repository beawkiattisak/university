#include <iostream>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    getline(cin, s);

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '('){
            s[i] = '[';
        }

        else if (s[i] == '['){
            s[i] = '(';
        }

        else if (s[i] == ')'){
            s[i] = ']';
        }

        else if (s[i] == ']'){
            s[i] = ')';
        }
    }

    cout << s;  


    return 0;
}