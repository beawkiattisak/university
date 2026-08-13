#include <iostream>
#include <cmath>
using namespace std;

double physical(int t) {
    return sin((2*M_PI*t)/23.0);
}

double emotional(int t) {
    return sin((2*M_PI*t)/28.0);
}

double intellectual(int t) {
    return sin((2*M_PI*t)/33.0);
}

bool isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
} 

int main() {
    int d1, m1, y1, d2, m2, y2, total;
    cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;
    int total_day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    y1-=543;
    y2-=543;
    total = (y2-y1-1)*365;

    if ((m1 <= 2) && (isLeapYear(y1))){
        total++;
    }

    if ((m2 > 2) && (isLeapYear(y2))){
        total++;
    }

    for (int i = m1; i <= 12; i++) {
        total += total_day[i];
    }

    total -= d1;

    for (int i = 1; i < m2; i++) {
        total += total_day[i];
    }

    total += d2;

    cout << total << " " << round(physical(total)*100.0)/100.0 << " " << round(emotional(total)*100.0)/100.0 << " " << round(intellectual(total)*100.0)/100.0;

    return 0;
}