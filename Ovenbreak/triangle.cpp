#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

double rad2deg(double radians) {
    double PI = 3.141592653589793;
    return radians * (180.0 / PI);
}

int main() {
    double a,b,c; cin>>a>>b>>c;
    double ans1=a+b+c;
    double s=(a+b+c)/2.0;
    double ans2=sqrt(s*(s-a)*(s-b)*(s-c));

    double cosa = acos( (b*b + c*c - a*a) / (2.0*b*c) );
    double cosb = acos( (a*a + c*c - b*b) / (2.0*a*c) );
    double cosc = acos( (a*a + b*b - c*c) / (2.0*a*b) );

    double ans3 = min({cosa, cosb, cosc});
    cout << fixed << setprecision(4) << ans1 << endl;
    cout << fixed << setprecision(4)<< ans2 << endl;
    cout << fixed << setprecision(4) << rad2deg(ans3) << endl;

    return 0;
}