#include <iostream>
#include <cmath>
#include <string>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
            return false;
    }

    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string k;
    cin >> n;
    int t = n;

    for (int i = 0; i < t; i++) {
        if (isPrime(i)) {
            while (n % i == 0) {
                n /= i;
                k+=to_string(i)+'*';
                cout << i << endl;
            }
        }
        if (n == 1) {
            break;
        }
    }
    k.pop_back();
    cout << k;


    return 0;
}