    #include <iostream>
    #include <set>
    #include <string>
    using namespace std;

    int main() {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        multiset<char> ms1, ms2;

        for (char c1 : s1) {
            if (isspace(c1)) continue;
            ms1.insert(tolower(c1));
        } 
        
        for (char c2 : s2) {
            if (isspace(c2)) continue;
            ms2.insert(tolower(c2));
        }  
        
        // cout << endl;

        // for (auto &c1 : ms1) {
        //     cout << c1;
        // }
        // cout << endl;
        // for (auto &c1 : ms1) {
        //     cout << c1;
        // }

        if (ms1 == ms2) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        
        return 0;
    }