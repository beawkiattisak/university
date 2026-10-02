#include <iostream>
#include <string>
using namespace std;

bool isVowel(char a) {
    if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') {
        return 1;
    }
    return 0;
}

int main() {
    string s;
    getline(cin, s);
    int countVowelIdx=0;
    int countVowelLastIdx=0;
    int countUntilSpace = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            countUntilSpace++;
        } else {
            countUntilSpace++;
            break;
        }
    }
    // countUntilSpace = 4;
    // mee ther khon deaw 
    // meaw ther knon dee

    for (int i = 0; i < s.length(); i++) {
        if (isVowel(s[i])) {
            countVowelIdx=i;
            break;
        }
    }

    for (int i = countVowelIdx+1; i < s.length(); i++) {
        if (isVowel(s[i])) {
            countVowelLastIdx=i;
            break;
        }
    }


    cout << s.substr(s.length() - countVowelIdx - 2, countUntilSpace) << '\n';
    cout << s.substr(countVowelLastIdx, countUntilSpace - 1) << '\n';
    cout << countVowelIdx << '\n';
    cout << countVowelLastIdx << '\n';
    cout << countUntilSpace << '\n';
    
    return 0;
}