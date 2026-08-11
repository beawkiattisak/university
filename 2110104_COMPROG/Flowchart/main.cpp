#include <iostream>

using namespace std;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a == 1) {
        // Y
        a = b+c+d;
        if (b == 1) {
            // Y
            c+=c+d;
        } else if (b == 2) {
            c += c-d;
        } else { 
            if (b > 4) {
                c += c*d;
            }
        

            if (b > 5) {
                // Y
                c += c%d;
            } else {
                c+=c/d;
            }
        }

        cout << c << endl;
    } else {
        while (b < c) {
            b++;

            if (b > a) {
                break;
            }

            c--;

            if (a > d) {
                break;
            }

            a += c;
        }
    }
    
    cout << a << " " << b << " " << c << " " << d << endl;


    return 0;
}