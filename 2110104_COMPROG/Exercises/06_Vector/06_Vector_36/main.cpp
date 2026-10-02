#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    string stu_id;
    string stu_grade;
    int grade_idx;
};

int main() {
    int N;
    cin >> N;
    vector<string> grade = {"F", "D", "D+", "C", "C+", "B", "B+", "A"};
    vector<Student> s;

    string stu_id_temp;
    string stu_grade_temp;
    int grade_idx_temp;

    for (int i = 0; i < N; i++) {
        cin >> stu_id_temp >> stu_grade_temp;
        for (int j = 0; j < grade.size(); j++) {
            if (stu_grade_temp == grade[j]) {
                grade_idx_temp = j;
            }
        }
        s.push_back({stu_id_temp, stu_grade_temp, grade_idx_temp});
    }

    vector<string> ops;
    string tempOps;
    while (cin >> tempOps) {
        ops.push_back(tempOps);
    }

    for (int i = 0; i < ops.size(); i++) {
        char skibidiOps = ops[i][ops[i].length() - 1];
        ops[i].pop_back();

        // cout << "OPS " << ops[i] << "\n";
        // cout << "Skibidi " << skibidiOps << "\n";

        for (int j = 0; j < s.size(); j++) {
            if (ops[i] == s[j].stu_id) { // ✅
                // cout << "TOS : " << to_string(s[j].stu_id) << '\n';
                // cout << "ops[i] : " << ops[i] << '\n';
                if (skibidiOps == '+' && s[j].grade_idx < 7) {
                    // cout << "+ to " << s[j].stu_id << '\n';
                    s[j].grade_idx++;
                } else if ((skibidiOps == '-' && s[j].grade_idx > 0)) {
                    // cout << "NOW " << s[j].stu_id << " HAVE " << s[j].grade_idx  << '\n';
                    // cout << "- to " << s[j].stu_id << '\n';
                    s[j].grade_idx -= 1;
                }
            }
        }
    }

    // 7 index
    sort(s.begin(), s.end(), [](const auto& a, const auto &b) {
        return a.grade_idx > b.grade_idx;
    });

    for (auto &x : s) {
        cout << x.stu_id << " " << grade[x.grade_idx] << '\n';
    }


    return 0;
}