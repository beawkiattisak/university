#include <iostream>
#include <cmath>
#include <numbers>
#include <iomanip>

using namespace std;

long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
  const double pi = acos(-1.0);

  cout << (pi*pi - tan(pi/4) * (pow(4.3,(2.0/7.0)) )) / (cbrt(11)+((factorial(8))/((pow(3,4)*(pow(2,3)))))) << setprecision(4);


  return 0;
}
