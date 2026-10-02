#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

struct party {
    string name;
    int score;
    double member;
    double sett;
};

int main() {
    vector<party> v;
    party temp;
    while (cin >> temp.name && temp.name != "END") {
        cin >> temp.score;
        v.push_back(temp);
    }
    int allSum = 0;
    for (int i = 0; i < v.size(); i++ ) {
        allSum += v[i].score;
    }

    double avg = allSum / 100.0;
    int total_member = 0;

    for (int i = 0; i < v.size(); i++) {
        v[i].member = v[i].score / avg;
        total_member += floor(v[i].member);
        v[i].sett = fmod(v[i].member, 1.0);
    }

    sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.sett < b.sett;
    });

    int idx = v.size()-1;

    while (total_member < 100) {
        v[idx].member += 1;
        idx--;
        total_member++;
    }

    sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.score > b.score;
    });

    // for (auto& p : v) cout << p.name << " " << p.score << " " << p.member <<" " << p.sett << "\n";
    cout << setprecision(0) << fixed; 
    for (auto& p : v) {
        if (floor(p.member) > 0) {
            cout << p.name << " " << floor(p.member) << " " << p.score << "\n";
        }
    }

    return 0;
}
