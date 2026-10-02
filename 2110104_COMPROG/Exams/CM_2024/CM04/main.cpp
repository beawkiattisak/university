#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    int total;
    cin >> N >> total;
    int sum = 0;
    int temp;
    vector<int> cs;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        cs.push_back(temp);
        sum+=temp;
    }

    for (int i = 0; i < N; i ++) {
        for (int j = i+1; j < N; j++) {
            if ((sum - (cs[i] + cs[j]) == total)) {
                cout << i << " " << cs[i] << '\n';
                cout << j << " " << cs[j] << '\n';
                break;
            }
        }
    }

    return 0;
}