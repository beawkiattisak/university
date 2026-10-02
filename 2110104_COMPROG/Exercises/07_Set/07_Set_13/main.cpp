#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    string temp_win;
    string temp_lose;
    set<string> winner;
    set<string> loser;
    set<string> alwayWin;
    
    while (cin >> temp_win >> temp_lose) {
        winner.insert(temp_win);
        loser.insert(temp_lose);
        alwayWin.erase(temp_lose);
        if (loser.find(temp_win) == loser.end()) {
            alwayWin.insert(temp_win);
        }
    }

    if (alwayWin.size() > 0) {
        for (string s : alwayWin) {
            cout << s << " ";
        }
    } else {
        cout << "None";
    }



    return 0;
}