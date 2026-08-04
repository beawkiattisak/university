#include <iostream>
#include <string>
using namespace std;
int main () {
    string cid;
    cin >> cid;
    int sum=0, n12;
    for (int i=0;i<12;i++){
        sum+=(13 - i)*(cid[i] - '0');
    }

    n12=(11 - (sum) % 11) % 10;

    cout << cid[0] << "-" << cid.substr(1,4) << "-" << cid.substr(5,5) << "-" << cid.substr(10,2) << "-" << n12;

    return 0;
}
