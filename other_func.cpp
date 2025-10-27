#include<securety_func.h>
#include<iostream>
#include<other_func.h>
using namespace std;


void  chose_input() {
    cout << "Zaur,choice value input_port";
    while (ok != 1) {
        if (!(cin >> a)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            PrintInvalidChoice();
            continue;
        }
        else {
            Input_Port = a;
            ok = 1;
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
    break;
}