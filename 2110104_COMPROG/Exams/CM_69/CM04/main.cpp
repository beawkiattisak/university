#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    
    vector<int> mt;

    vector<pair<int, vector<int>>> allVisited;


    vector<int> best;
    int bestD;

    int tempNum;
    for (int i = 0; i < N; i++) {
        cin >> tempNum;
        mt.push_back(tempNum);
    }

    if (N == 1) {
        cout << 1 << endl;
        cout << mt[0];
        return 0;
    }
    
    for (int i = 1; i < N; i++) {
        vector<bool> isVisited(N, false);
        int idx = 0;
        vector<int> visited;
        for (int j = 0; j < N; j++) {
            if (isVisited[idx]) {
                break;
            }
            isVisited[idx] = true;
            visited.push_back(mt[idx]);

            idx = (idx + i) % N;
        }
        if (visited.size() == N) {
            if (best.empty() || visited > best) {
                best = visited;
                bestD = i;
            }
        }
    }

    sort(allVisited.begin(), allVisited.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    });
    cout << bestD << '\n';

    for (int x : best) {
        cout << x << " ";
    }

    return 0;
}