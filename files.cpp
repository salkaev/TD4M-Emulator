#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<fstream>
#include<sstream>
#include"Mybitset.h"
#include"registers.h"
#include"securety_func.h"

//�������� ��������� ����� � ������ ��� � ����� ������ //

using namespace std;


void read_file() {

    //������ � ������ //
    string file, line, data;
    vector<string> vector_parts;


    cout << "Enter the file how you want to read\n";
    cin >> file;
    ifstream in(file);
    if (!in.is_open()) {
        cout << "Error: cannot open file '" << file << "'.\n";
    }

    // ������ ���� ���� � ���� ������ (��� � ��� ����)
    line.clear();
    while (std::getline(in, data)) {
        if (!line.empty()) line += ",";
        line += data;
    }
    in.close();

    if (line.empty()) {
        cout << "Warning: file is empty.\n";
    }

    // ���������� ������ ����� stringstream � ����������� ',',
    // � ������� �� ������������ � ������������ ��������
    {
        string token;
        stringstream ss(line);
        while (getline(ss, token, ',')) {
            trim(token);
            if (!token.empty()) vector_parts.push_back(token);
        }
    }

    //���������� ���� ������ � ��������� �� � �������� ��� //
    int count = 0;
    for (auto part : vector_parts) {
        trim(part);
        if (part.size() >= 3 && (part[0] == '0') && (part[1] == 'x' || part[1] == 'X')) {
            string hex_str = part.substr(2);
            try {
                int hex_value = std::stoi(hex_str, nullptr, 16);
                MyBitset<8> value(static_cast<unsigned long long>(hex_value));
                coman[count] = value;
            }
            catch (...) {
                cout << "Warning: invalid hex token '" << part << "'. Using 0.\n";
                coman[count] = MyBitset<8>(0);
            }
        }
        else {
            // ��������� ���������� ��� ������� ��� ��� hex ��� 0x
            try {
                // ���� �������� ��-����� � ������� ��� ������ � ������ 0
                bool all_hex = true;
                for (char c : part) {
                    if (!isxdigit(static_cast<unsigned char>(c))) { all_hex = false; break; }
                }
                if (all_hex && !part.empty()) {
                    int hex_value = std::stoi(part, nullptr, 16);
                    coman[count] = MyBitset<8>(static_cast<unsigned long long>(hex_value));
                }
                else {
                    cout << "Warning: unrecognized token '" << part << "'. Using 0.\n";
                    coman[count] = MyBitset<8>(0);
                }
            }
            catch (...) {
                cout << "Warning: error parsing token '" << part << "'. Using 0.\n";
                coman[count] = MyBitset<8>(0);
            }
        }
        ++count;
        if (count >= 16) break; // ������ �� ������������ �����
    }
}