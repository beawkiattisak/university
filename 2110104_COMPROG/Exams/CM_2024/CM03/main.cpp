#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long price;
    cin >> price;
    string temp;
    vector<string> vend;
    while (cin >> temp) {
        if (temp.length()>1) {
            temp.erase(0, 1);
            vend.push_back(temp);
        }
    }

    long long totalPrice = 0;

    for (long long i = 0 ; i<vend.size(); i++) {
        // cout << vend[i] << " ";
        totalPrice += stoi(vend[i]) * price;
    }

    // for (auto &x : vend) cout << x << " ";
    cout << totalPrice;


    return 0;
}