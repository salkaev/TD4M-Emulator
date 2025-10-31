#include "Mybitset.h"
#include"securety_func.h"
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
using namespace std;

// Вспомогательные проверки и безопасные конверторы
bool is_binary(const string& s, size_t expected_len) {
    if (s.size() != expected_len) return false;
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}

bool bin_to_int_safe(const string& s, int& out) {
    if (!is_binary(s, s.size())) return false;
    try {
        out = std::stoi(s, nullptr, 2);
        return true;
    }
    catch (...) {
        return false;
    }
}

MyBitset<4> make_bitset4_safe(const string& s) {
    if (!is_binary(s, 4)) {
        cout << "Warning: invalid 4-bit pattern '" << s << "'. Using 0000.\n";
        return MyBitset<4>(0);
    }
    return MyBitset<4>(s);
}

void trim(string& s) {
    const char* ws = " \t\n\r";
    auto start = s.find_first_not_of(ws);
    auto end = s.find_last_not_of(ws);
    if (start == string::npos) { s.clear(); return; }
    s = s.substr(start, end - start + 1);
}

// Склейка двух 4-битных значений в одно 8-битное //
MyBitset<8> Gluing(MyBitset<4> v1, MyBitset<4> v2) {
    string s1 = v1.to_string();
    string s2 = v2.to_string();
    string s3 = s1 + s2;
    cout<<"\n" << s3;
    MyBitset<8> final(s3);
    cout << "\n" <<final;
    return final;
}

void PrintInvalidChoice() {
    cout << "Zaur, there is no such command!" << endl;
}