#include <iostream>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string target, s;
    int count=0;
    cin >> target;
    cin.ignore();
    getline(cin, s);
    int tlen = target.length();
    int slen = s.length();
    int max_idx = slen-tlen;
    
    for (int i = 0; i <= max_idx; i++) {
        if (s.substr(i, tlen) == target) {
            count++;
        }
    }

    cout << count;

}