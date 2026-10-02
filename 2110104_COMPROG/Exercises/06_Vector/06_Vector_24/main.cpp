#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Product {
    string name;
    double price;
    double sumPrice;
    bool operator < (const Product&x) const {
        if (sumPrice == x.sumPrice)
        {
            return x.name > name;
        }
        return x.sumPrice < sumPrice;
    }
};

int main() {
    int count = 0;
    string temp;
    float price;
    vector<Product> v;
    while (cin >> temp && temp != "END") {
        cin >> price;
        v.push_back({temp, price});
        count ++;
    }
    bool isEmpty = true;
    string paimuengtor;
    while (cin >> paimuengtor) {
        for (int i = 0; i < count; i ++) {
            if (v[i].name == paimuengtor) {
                v[i].sumPrice += v[i].price;
                isEmpty = false;
            }
        }
    }

    if (isEmpty) {
        cout << "No Sales";
        return 0;
    }

    sort(v.begin(), v.end());
    for (int i = 0; i < 3; i++) {
        
        if (v[i].sumPrice > 0) {
            cout << v[i].name << " " << v[i].sumPrice << "\n";
        }
    }

    return 0;
}