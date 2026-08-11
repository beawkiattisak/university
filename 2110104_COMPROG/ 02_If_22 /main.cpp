#include <iostream>
using namespace std;

int main() {
    int day, month, year, total = 0;
    cin >> day >> month >> year;
    year-=543;
    // 31 = มค มีค พค กค สค ตค ธค
    // 1, 3, 5, 7, 8, 10, 12

    if (month == 2) {
        total += 31;
    } else if (month == 3) {
        total += 31 + 28;
    } else if (month == 4) {
        total += 31 + 28 + 31;
    } else if (month == 5) {
        total += 31 + 28 + 31 + 30;
    } else if (month == 6) {
        total += 31 + 28 + 31 + 30 + 31;
    } else if (month == 7) {
        total += 31 + 28 + 31 + 30 + 31 + 30;
    } else if (month == 8) {
        total += 31 + 28 + 31 + 30 + 31 + 30 + 31;
    } else if (month == 9) {
        total += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
    } else if (month == 10) {
        total += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
    } else if (month == 11) {
        total += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
    } else if (month == 12) {
        total += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
    }
    

    if (year % 400 == 0) {
    if (month > 2) {
        total++;
    }
    } else if (year % 100 == 0) {
    } else if (year % 4 == 0) {
        if (month > 2) {
            total++;
        }
    }
    total += day;

    cout << total;

    return 0;
}