#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; cin >>s;
    int mn,mx;cin>>mn>>mx;
    mn--;
    int tile = ((mx * 2) + 1)*((mx * 2) + 1);
    int xx = (((mn) * 2) + 1)*((mn * 2) + 1);

    cout << s << " has " << tile - xx << " attackable grids";


    return 0;
}

// 9, 25, 49
// 3*3,  5*5, 7*7

// ((x * 2) + 1)*((x * 2) + 1)

255 255 255
182 234 249

BANG!!!