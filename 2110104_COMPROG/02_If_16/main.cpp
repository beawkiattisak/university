#include <iostream>
using namespace std;
int main() {
    int number;
    cin >> number;

    if (number == 0) {
        cout << "zero" << endl;
    } else if (number > 0) {
        cout << "positive" << endl;
    } else {
        cout << "negative" << endl;
    }

    if (number % 2 == 0) {
        cout << "even" << endl;
    } else {
        cout << "odd" << endl;
    }


    return 0;
}