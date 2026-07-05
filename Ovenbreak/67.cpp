#include<iostream>
#include <cmath>
using namespace std;

int main() {
    int r, g, b; cin>>r>>g>>b;
    int x, y, z; cin>>x>>y>>z;
    int sum = abs((r-x)+(g-y)+(b-z));
    int cnt = 0;
    if(sum >= 100){
        cout << "BANG!!!";
    } else {
        // 60 -> 65 -> 70 -> 75 -> 80 -> 85 -> 90 -> 95 ->
        while (sum<95) {
            cnt++;
            sum+=5;
        }
        cout << cnt;
    }
    return 0;
}