#include <iostream>
#include <set>
using namespace std;

int main() {
    int N;
    cin >> N;
    set<int> setNum;
    int temp_num;
    int count = 0;
    while (cin >> temp_num) {
        setNum.insert(temp_num);
    }

    for (int x : setNum) {
        if (setNum.find(N - x) != setNum.end()) {
            count ++;
        }
    }


    cout << count / 2;

    return 0;
}