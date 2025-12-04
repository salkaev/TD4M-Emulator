// files.cpp
#include "registers.h"  // Добавьте этот include
#include "Mybitset.h"
#include "securety_func.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>  // Добавьте для std::this_thread

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
void Zaur() {

    
        const vector<string> lines = {
"ZZZZZZZZZZZZZZZZZZZ                                                      ",
"Z:::::::::::::::::Z                                                      ",
"Z:::::::::::::::::Z                                                      ",
"Z:::ZZZZZZZZ:::::Z                                                       ",
"ZZZZZ     Z:::::Z    aaaaaaaaaaaaa  uuuuuu    uuuuuu rrrrr   rrrrrrrrr   ",
"        Z:::::Z      a::::::::::::a u::::u    u::::u r::::rrr:::::::::r  ",
"       Z:::::Z       aaaaaaaaa:::::au::::u    u::::u r:::::::::::::::::r ",
"      Z:::::Z                 a::::au::::u    u::::u rr::::::rrrrr::::::r",
"     Z:::::Z           aaaaaaa:::::au::::u    u::::u  r:::::r     r:::::r",
"    Z:::::Z          aa::::::::::::au::::u    u::::u  r:::::r     rrrrrrr",
"   Z:::::Z          a::::aaaa::::::au::::u    u::::u  r:::::r            ",
"ZZZ:::::Z     ZZZZZa::::a    a:::::au:::::uuuu:::::u  r:::::r            ",
"Z::::::ZZZZZZZZ:::Za::::a    a:::::au:::::::::::::::uur:::::r            ",
"Z:::::::::::::::::Za:::::aaaa::::::a u:::::::::::::::ur:::::r            ",
"Z:::::::::::::::::Z a::::::::::aa:::a uu::::::::uu:::ur:::::r            ",
"ZZZZZZZZZZZZZZZZZZZ  aaaaaaaaaa  aaaa   uuuuuuuu  uuuurrrrrrr            "
        };

        for (const auto& line : lines) {
            cout << line << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        // ������ � ������
        string file = "C:\\Users\\salka\\source\\repos\\salkaev\\TD4M-Emulator\\Zaur.txt";
        ifstream in(file);
        if (!in.is_open()) {
            cout << "Error: cannot open file '" << file << "'." << endl;
        }
        else {



            string data;
            while (std::getline(in, data)) {
                cout << data << endl;
            }
        }
        in.close();

}