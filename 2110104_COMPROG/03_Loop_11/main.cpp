#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    float n;
    float total=0, count=0;

    while (cin >> n && n != -1) {
        total+=n;
        count++;
    }

    if (count == 0) {
        cout << "No Data";
    } else {
        float avg = total/count;
        cout << round(avg*100)/100.0;
    }

    return 0;
}