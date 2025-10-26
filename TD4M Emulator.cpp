#define NOMINMAX
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <locale>
#include <clocale>
#include <windows.h>
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sstream>
#include <limits>
#include <fstream>
#include <cctype>
#include"registers.h"
#include"Mybitset.h"
#include"securety_func.h"
#include"files.h"
#include"Core.h"



using namespace std;

string graffiti =
" ####### ######  #          ####### #     # #     # #          #    ####### ####### ######  \n"
"    #    #     # #    #     #       ##   ## #     # #         # #      #    #     # #     # \n"
"    #    #     # #    #     #       # # # # #     # #        #   #     #    #     # #     # \n"
"    #    #     # #    #     #####   #  #  # #     # #       #     #    #    #     # ######  \n"
"    #    #     # #######    #       #     # #     # #       #######    #    #     # #   #   \n"
"    #    #     #      #     #       #     # #     # #       #     #    #    #     # #    #  \n"
"    #    ######       #     ####### #     #  #####  ####### #     #    #    ####### #     # \n";





int main() {
    for (int i = 0; i < 16; i++) {
        coman[i] = MyBitset<8>(); // Создаем пустую карту //
    }
    cout << graffiti;
    cout << "\n\n\n\n\n";
    cout << "Instruction_Set\n" << "ADD A,Im 0000,\nADD B,Im 0101,\nMOV A,Im 0011,\nMOV B,Im 0111,\nMOV A,B 0001\nMOV B,A 0100\nJMP Im 1111\nJNC Im 1110\nIN A 0010\nIN B 0110\nOUT B 1001\nOUT Im 1011";

    while (true) {
        cout << "\n\n\n";
        cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur  9: read file";
        cout << "\n\n\n";

        while (true) {
            if (!(cin >> comand)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                PrintInvalidChoice();
                cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur 9: read file" << endl;
                continue;
            }
            if (comand < 1 || comand > 9) {
                PrintInvalidChoice();
                continue;
            }
            break;
        }


		if (comand == 9) {
            //Работа с файлом //
            string file, line, data;
            vector<string> vector_parts;


            cout << "Enter the file how you want to read\n";
            cin >> file;
            ifstream in(file);
            if (!in.is_open()) {
                cout << "Error: cannot open file '" << file << "'.\n";
                break;
            }

            // читаем весь файл в одну строку (как у вас было)
            line.clear();
            while (std::getline(in, data)) {
                if (!line.empty()) line += ",";
                line += data;
            }
            in.close();

            if (line.empty()) {
                cout << "Warning: file is empty.\n";
                break;
            }

            // безопасный разбор через stringstream и разделитель ',',
            // с защитой от переполнения и некорректных символов
            {
                string token;
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    trim(token);
                    if (!token.empty()) vector_parts.push_back(token);
                }
            }

            //Отфильруем наши данные и превратим их в двоичный код //
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
                    // Попробуем распознать как десятич или как hex без 0x
                    try {
                        // если содержит не-цифры — считаем как ошибка и ставим 0
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
                if (count >= 16) break; // защита от переполнения карты
            }
            break;
        }

        if (comand == 8)
        {
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

            // Работа с файлом
            string file = "Zaur.txt";
            ifstream in(file);
            if (!in.is_open()) {
                cout << "Error: cannot open file '" << file << "'." << endl;
                return 1;
            }

            string data;
            bool isEmpty = true;
            while (std::getline(in, data)) {
                cout << data << endl;
                isEmpty = false;
            }
            in.close();

            if (isEmpty) {
                cout << "Warning: file is empty." << endl;
            }

            return 0;
        }

        if (comand == 6 )

        {
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
            ok = 0; // сброс для следующего раза //
            continue;
        }
        if (comand == 4) {
            cout << "Zaur,See you soon!";
            exit(0);
            if (comand == 3)

                while (true) {
                    try {
                        cout << "Zaur,Enter first the command number from the list, then the command code, and then the command payload";
                        cout << "\n\n\n";
                        if (!(cin >> number_posi >> chose_Instruction >> choce)) {

                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            PrintInvalidChoice();
                            continue;
                        }

                        // Проверка позиции
                        if (number_posi < 0 || number_posi >= 16) {
                            cout << "Error: command position out of range (0..15).\n";
                            continue;
                        }

                        // Проверка формата chose_Instruction
                        string instr_str = chose_Instruction.to_string();
                        if (!is_binary(instr_str, 4)) {
                            cout << "Error: invalid instruction code format. Use 4-bit binary.\n";
                            continue;
                        }

                        auto it = Instruction_Set.find((chose_Instruction));
                        if (it == Instruction_Set.end()) {
                            PrintInvalidChoice();
                            continue;
                        }


                        if (chose_Instruction.to_string() == "0010" || chose_Instruction.to_string() == "0110") {
                            string zxc = "0000";
                            MyBitset<4> tmp;
                            choce = tmp.from_string(zxc);

                        }
                        MyBitset<8> command_and_data = Gluing(chose_Instruction, choce);
                        if (coman.find(number_posi) != coman.end()) {
                            coman.erase(number_posi);
                        }

                        coman.insert({ number_posi,command_and_data });
                        break;
                    }
                    catch (...) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        PrintInvalidChoice();
                    }
                }
            break;
        }
        if (comand == 1) {
            coman.clear();
            break;
        }

        if (comand == 2) {
            cout << "";
            break;
        }

        if (comand == 5) {
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
        if (comand == 7){

            vector<pair<int, MyBitset<8>>> sorted_coman(coman.begin(), coman.end());

            sort(sorted_coman.begin(), sorted_coman.end(),
                [](const auto& a, const auto& b) {
                    return a.first < b.first;
                });

            stop = "";
            string click = "";
            while (stop != "stop") {
                while (click != "auto" && click != "manual") {
                    cout << "Zaur,do you want auto click or manual?";
                    if (!(cin >> click)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        PrintInvalidChoice();
                        continue;
                    }
                    if (click != "auto" && click != "manual") {
                        PrintInvalidChoice();
                    }
                }
                for (int i = 0; i < (int)sorted_coman.size(); ++i) {
                    int position = sorted_coman[i].first;
                    MyBitset<8> val = sorted_coman[i].second;

                    string choice;

                    int test = 0;

                    while (test != 1)
                    {
                        if (click != "auto") {
                            cout << "Click or remove input port? ";
                            cin >> choice;

                            if (choice == "click" || choice == "Click") {
                                test = 1;
                            }
                            else if (choice == "remove" || choice == "Remove") {
                                cout << "Zaur, choice value input_port: ";


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
                                ok = 0;
                            }
                            else {
                                cout << "Zaur,invalid choice. Please enter 'click' or 'remove'." << endl;
                            }
                        }
                        else {

                            break;
                        }
                    }

                    if (pendingC_next) {
                        C_Flag = 1;
                        pendingC_next = false;
                        pendingC_clear_after_show = true;
                    }

                    cout << "|---------------Register--------------|\n";
                    cout << "+-------------+-------------+---------+\n";
                    cout << "| Register A  | Register B  | C Flag  |\n";
                    cout << "+-------------+-------------+---------+\n";
                    cout << "| " << setw(11) << Register_A << " | " << setw(11) << Register_B << " | " << setw(7) << C_Flag << " |\n";
                    cout << "+-------------+-------------+---------+\n";
                    cout << "| PC: " << setw(8) << Program_Counter << "| Out: " << setw(7) << Output_Port << "|" << "Input:" << Input_Port << "|\n";
                    cout << "+-------------+-----------------------+\n";

                    // <<== Изменение: после вывода (печати) порта Output_Port
                    // очищаем его, чтобы значение, установленное инструкцией OUT,
                    // отображалось только один шаг, а затем показывалось 0000.
                    Output_Port = MyBitset<4>(0);

                    Program_Counter += 0001;
                    string s = val.to_string();
                    // safety: ensure s length is 8
                    if (s.size() != 8) {
                        cout << "Error: invalid command encoding at position " << position << ". Skipping.\n";
                        continue;
                    }
                    string instruction = s.substr(0, 4);
                    string payload = s.substr(4, 4);

                    // Вызов fun в try/catch — защита от неожиданных исключений //
                    try {
                        fun(instruction, payload);
                    }
                    catch (const std::exception& ex) {
                        cout << "Exception during instruction execution: " << ex.what() << "\n";
                        continue;
                    }
                    catch (...) {
                        cout << "Unknown exception during instruction execution.\n";
                        continue;
                    }

                    // Обработка перехода после выполнения инструкции, //
                    // чтобы сначала был показан и выполнен шаг, а затем выполнен jump//
                    {
                        string instr_check = instruction;
                        string addr_check = payload;
                        if (instr_check == "1111" || (instr_check == "1110" && C_Flag != 1)) {
                            int new_i = -1;
                            if (!bin_to_int_safe(addr_check, new_i)) {
                                cout << "Warning: invalid jump address '" << addr_check << "'. Ignoring jump.\n";
                            }
                            else {
                                if (new_i >= 0 && new_i < (int)sorted_coman.size()) {
                                    i = new_i - 1;
                                }
                                else {
                                    cout << "Warning: jump target " << new_i << " out of range. Ignored.\n";
                                }
                            }
                        }
                    }

                    if (pendingC_clear_after_show) {
                        C_Flag = 0;
                        pendingC_clear_after_show = false;
                    }

                    if (click == "auto") {
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                        if (click != "auto") {

                            while (true) {
                                cout << "Zaur,Clock or Stop?: ";
                                if (!(cin >> stop)) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    PrintInvalidChoice();
                                    continue;
                                }
                                if (stop == "stop") {
                                    exit(0);
                                }
                                if (stop == "clock") break;
                                PrintInvalidChoice();
                            }
                        }
                    }
                }
            }
            break;



        }

    }
}
