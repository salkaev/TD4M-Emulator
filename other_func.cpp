#include "other_func.h"
#include "registers.h"
#include "securety_func.h" 
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

void chose_input() {
    cout << "Zaur,choice value input_port: ";
    
    MyBitset<4> a;
    bool input_ok = false;
    
    while (!input_ok) {
        if (!(cin >> a)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            PrintInvalidChoice();
            cout << "Please enter a valid value (0-15): ";
        }
        else {
            Input_Port = a;
            input_ok = true;
            cout << "Input port set to: " << Input_Port << endl;
        }
    }
}

void  Empty() {
    if (coman.empty()) {
        cout << "Zaur,Memory is empty\n";
    }
    else {
        vector<pair<int, MyBitset<8>>> sorted(coman.begin(), coman.end());

        sort(sorted.begin(), sorted.end(),
            [](const auto& a, const auto& b) {
                return a.first < b.first;
            });

        for (const auto& i : sorted) {
            cout << "Position " << i.first << ": " << i.second << "\n";
        }
    }
}