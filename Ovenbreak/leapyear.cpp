#include <iostream>
#include <cmath>
using namespace std;
int year[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main() {
    int d,m,y;
    cin >> d>>m>>y;
    y-=543;
    bool leap=false;

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        year[1] = 29;   
        leap=true; 
    }

    int sum_day=0;
    int sum_dayofyear=0;

    for (int i=0; i<m-1; i++){
        sum_day+=year[i];
    }

    sum_day+=d; 

    for (int i=0; i<12; i++){
        sum_dayofyear+=year[i];
    }
    
    cout << sum_dayofyear-sum_day;


    return 0;
}