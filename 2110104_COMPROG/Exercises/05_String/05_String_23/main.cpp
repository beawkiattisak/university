#include <iostream>
#include <string>
using namespace std;

int main() {
    string plate;
    int N;
    cin >> plate >> N;

    int first = plate[0] - '0';
    string letters = plate.substr(1, 2);
    int num = stoi(plate.substr(4, 3));

    for (int i = 0; i < N; i++) {
        num++;

        if (num == 1000) {
            num = 0;
            first++;

            if (first == 10) {
                first = 0;

                // เพิ่มตัวอักษร
                // กรณีต้องการ logic เพิ่ม letters ต้องทำตรงนี้
            }
        }
    }

    cout << first << letters << "-" << num << '\n';

    return 0;
}