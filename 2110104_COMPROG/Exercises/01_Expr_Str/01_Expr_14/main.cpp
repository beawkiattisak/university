#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int year, ans;
    cin >> year;
    year-=543;
    int y = year%100;
    ans = (y+floor(y/4)+11);
    cout << ans%7;

    return 0;
}