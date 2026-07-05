#include <iostream>
#include <string>
using namespace std;

int main() {
    float n; cin>>n;
    
    if(n < 0 || n > 100) {
        cout << "Invalid Score";
    }
    else if(n >= 80){
        cout << "A";
    } else if (n >= 70) {
        cout << "B";
    } else if (n >= 60) {
        cout << "C";
    } else if (n>=50) {
        cout << "D";
    } else {
        cout << "F";
    }

    return 0;
}