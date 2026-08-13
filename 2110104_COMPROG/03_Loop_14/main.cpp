#include <iostream>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    int count = 0;
    cin >> s1 >> s2;

    for (int i = 0; i < s1.length(); i++) {
        for (int j = 0; j < i; j++) {
            if (s1[i] == s1[j]) {
                count++;
            }
        }
    }

    cout << count;

    return 0;
}