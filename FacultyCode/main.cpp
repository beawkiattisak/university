#include <iostream>
#include <string>
using namespace std;

int main() {
    string FacultyCode;
    cin >> FacultyCode;

    if (FacultyCode == "01" || 
        FacultyCode == "02" ||
        FacultyCode == "20" ||
        FacultyCode == "20" ||
        FacultyCode == "21" ||
        FacultyCode == "22" ||
        FacultyCode == "23" ||
        FacultyCode == "24" ||
        FacultyCode == "25" ||
        FacultyCode == "26" ||
        FacultyCode == "27" ||
        FacultyCode == "28" ||
        FacultyCode == "29" ||
        FacultyCode == "30" ||
        FacultyCode == "31" ||
        FacultyCode == "32" ||
        FacultyCode == "33" ||
        FacultyCode == "34" ||
        FacultyCode == "35" ||
        FacultyCode == "36" ||
        FacultyCode == "37" ||
        FacultyCode == "38" ||
        FacultyCode == "39" ||
        FacultyCode == "40" ||
        FacultyCode == "51" ||
        FacultyCode == "53" ||
        FacultyCode == "55" ||        
        FacultyCode == "58"
    ) {
        cout << "OK";
    } else {
        cout << "Error";
    }

    return 0;
}