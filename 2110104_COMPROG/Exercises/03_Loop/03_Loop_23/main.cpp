#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string t;
    int k;
    int count = 0;
    cin >> t;
    cin >> k;

    for (int i = 0; i < t.length() - 1; i++) {
        if (t[i+1] == t[i]) {
            count++;
        }
        if (count <= k) {
            
        }
    }



    return 0;
}