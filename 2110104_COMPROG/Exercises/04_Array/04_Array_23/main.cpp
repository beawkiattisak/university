#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<pair<string, int>> flight; 
    string tempAirport;
    int tempPrice;
    for (int i = 0; i < N; i++) {
        cin >> tempAirport >> tempPrice;
        flight.push_back({tempAirport, tempPrice});
    }

    int totalPrice = 0; 

    string SingleFlightFromAllFlight;
    string tempFlight;
    vector<string> allFlight;
    while (cin >> tempFlight) {
        allFlight.push_back(tempFlight);
    }

    for (int i = 1; i < allFlight.size(); i++) {
        string sub_flight = allFlight[i].substr(4,2);
        // cout << sub_flight << '\n';
        for (int j = 0; j < flight.size(); j++) {
            if (sub_flight == flight[j].first) {
                // cout << "allFlight[i]: " << allFlight[i] << '\n';
                // cout << "sub_flight: " << sub_flight << '\n';
                if (allFlight[i-1].substr(4, 2) == sub_flight) {
                    // Do Nothing
                    // cout << "SAME!" << '\n';
                } else{
                    // cout << "add : " << flight[j].second << '\n';
                    totalPrice += flight[j].second;
                }
            }
        }
    }

    cout << totalPrice;

    return 0;
}