#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct student {
    string student_id;
    int grade;
};

int main() {
    vector<student> allStudent;
    string temp_id, temp_grade;

    string grade[] = {"F", "D", "D+", "C", "C+", "B", "B+", "A"};

    while (true) {
        cin >> temp_id;
        
        if (temp_id == "q") {
            break;
        }

        cin >> temp_grade;

        int temp_grade_num;
        if (temp_grade == "A") {
            temp_grade_num = 7;
        } else if (temp_grade == "B+") {
            temp_grade_num = 6;
        } else if (temp_grade == "B") {
            temp_grade_num = 5;
        } else if (temp_grade == "C+") {
            temp_grade_num = 4;
        } else if (temp_grade == "C") {
            temp_grade_num = 3;
        } else if (temp_grade == "D+") {
            temp_grade_num = 2;
        } else if (temp_grade == "D") {
            temp_grade_num = 1;
        } else if (temp_grade == "F") {
            temp_grade_num = 0;
        }
        allStudent.push_back({temp_id, temp_grade_num});
    }

   

    string student_id_to_calculate;
    while (cin >> student_id_to_calculate) {
        for (int i = 0; i < allStudent.size(); i++) {
            if (student_id_to_calculate == allStudent[i].student_id) {
                if (allStudent[i].grade == 7) {

                } else {
                    allStudent[i].grade++;
                }
            }
        }
    }
    
    for (int i = 0; i < allStudent.size(); i++) {
        cout << allStudent[i].student_id << " " << grade[allStudent[i].grade] << '\n';
    }

    return 0;
}