#include <iostream>
#include <set>

using namespace std;

int main() {
    bool flag = true;
    int n;
    int count = 0;
    set<int> s;
    while (cin >> n) {
        count++;
        if(s.count(n) >= 1) {
            cout << count;
            
            return 0;
        }
        s.insert(n);
    }

    cout << "-1";




    return 0;
}