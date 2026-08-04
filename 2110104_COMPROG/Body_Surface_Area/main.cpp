#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double W, H;
    cin >> W >> H;

    double mons, hay, boyd;

    mons=sqrt(W*H)/60.0;
    hay=0.024265*pow(W,0.5378)*pow(H,0.3964);
    boyd=0.0333*pow(W,0.6157-0.0188*log10(W))*pow(H,0.3);

    cout << setprecision(15) << mons << endl;
    cout << setprecision(15) << hay << endl;
    cout << setprecision(15) << boyd << endl;


    return 0;
}