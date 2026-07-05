#include <iostream>
#include <algorithm>
using namespace std;
int arr[100005]; 
int main() {
    int n; cin>>n;
    int cnt=0;
    for(int i=0;i<n;i++){
        int nn;cin>>nn;
        arr[i] = nn;
    }

    int maxx = *max_element(arr, arr+n);

    for (int i=0; i < n; i++) {
        if (arr[i] == maxx){
            cnt++;
        }
    }

    cout<<maxx<<"-"<<cnt;

    return 0;
}