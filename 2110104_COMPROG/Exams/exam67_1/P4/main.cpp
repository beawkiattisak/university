#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> v;
    int tempNum;

    for (int i = 0; i < N; i++) {
        cin >> tempNum;
        v.push_back(tempNum);
    }

    vector<int> temp;
    vector<int> allSum;

    for (int k = 0; k <= N; k++) {
        temp = v;
        if (k == N) {
        } else {
            temp.erase(temp.begin() + k);
        }
        int sz = temp.size();
        int idx;
        for (int i = 0; i < sz; i++) {
            int sum = temp[i];
            for (int j = 0; j < sz-1; j++) {
                idx = (i + j) % sz;
                if (temp[idx] <= temp[(idx+1) % sz]) {
                    sum += temp[(idx+1) % sz];
                } else {
                    break;
                }
            }
            allSum.push_back(sum);
        }
    }

    // for (auto& x : allSum) cout << x << " ";
    cout << *max_element(allSum.begin(), allSum.end());
    return 0;
}