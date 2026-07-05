#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    int n; cin>>n;
    double count =0;
    float sum=0;
    while(n--){
        double nn; cin >>nn;
        if(nn>0.0) {
            sum+=nn;
            count++;
        }
    }
    cout << fixed << setprecision(2);

    cout << "Cleaned ML Mean: " << sum / count;


    return 0;
}