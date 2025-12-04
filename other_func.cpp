#include "other_func.h"
#include "registers.h"
#include "securety_func.h" 
#include <iostream>
#include <limits>
#include <algorithm>
#include "Core.h"
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

void starter_pack() {
    cout << "Zaur, please choice a programs";
    cout << "Zaur, 3 programs = 3 in the task sheet and so on ";
    int choice = 0;
    cin >> choice;
    


    if (choice == 3) {
        coman[0] = "00110011";  //in a
        coman[1] = "10000001";  //neg a
        coman[3] = "10001001"; //st a
        coman[4] = "10001010"; //ld a
        coman[5] = "00100011"; // in a
        coman[6] = "10000000";  //add a, b
        coman[7] = "00001001"; //add 5
        coman[8] = "10000111"; //out a
    }

    else if (choice == 4) {
        coman[0] = "01100011"; //in b 3
        coman[1] = "10001011"; //st b
        coman[2] = "10001010"; //lb a
        coman[3] = "00100011";// mov b=a+3
        coman[4] = "10000010";// not a
        coman[5] = "10000000";// add a+b
        coman[6] = "00000100";//add a+4
        coman[7] = "10000111";// out a
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