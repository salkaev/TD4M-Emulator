#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include"Mybitset.h"
using namespace std;

// ��������������� �������� � ���������� ����������
bool is_binary(const string& s, size_t expected_len);

bool bin_to_int_safe(const string& s, int& out);
MyBitset<4> make_bitset4_safe(const string& s);

void trim(string& s);

// ������� ���� 4-������ �������� � ���� 8-������ //
MyBitset<8> Gluing(MyBitset<4> v1, MyBitset<4> v2);



struct BitsetHash {
    size_t operator()(const MyBitset<4>& b) const {
        return b.to_ullong();
    }
};
//
void PrintInvalidChoice();

