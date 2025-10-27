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
#include"other_func.h"


using namespace std;

string graffiti =
"TTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDDDD               444444444  MMMMMMMM               MMMMMMMM     EEEEEEEEEEEEEEEEEEEEEEMMMMMMMM               MMMMMMMMUUUUUUUU     UUUUUUUULLLLLLLLLLL                            AAA         TTTTTTTTTTTTTTTTTTTTTTT     OOOOOOOOO     RRRRRRRRRRRRRRRRR   \n"
"T:::::::::::::::::::::TD::::::::::::DDD           4::::::::4  M:::::::M             M:::::::M     E::::::::::::::::::::EM:::::::M             M:::::::MU::::::U     U::::::UL:::::::::L                           A:::A        T:::::::::::::::::::::T   OO:::::::::OO   R::::::::::::::::R  \n"
"T:::::::::::::::::::::TD:::::::::::::::DD        4:::::::::4  M::::::::M           M::::::::M     E::::::::::::::::::::EM::::::::M           M::::::::MU::::::U     U::::::UL:::::::::L                          A:::::A       T:::::::::::::::::::::T OO:::::::::::::OO R::::::RRRRRR:::::R \n"
"T:::::TT:::::::TT:::::TDDD:::::DDDDD:::::D      4::::44::::4  M:::::::::M         M:::::::::M     EE::::::EEEEEEEEE::::EM:::::::::M         M:::::::::MUU:::::U     U:::::UULL:::::::LL                         A:::::::A      T:::::TT:::::::TT:::::TO:::::::OOO:::::::ORR:::::R     R:::::R\n"
"TTTTTT  T:::::T  TTTTTT  D:::::D    D:::::D    4::::4 4::::4  M::::::::::M       M::::::::::M       E:::::E       EEEEEEM::::::::::M       M::::::::::M U:::::U     U:::::U   L:::::L                          A:::::::::A     TTTTTT  T:::::T  TTTTTTO::::::O   O::::::O  R::::R     R:::::R\n"
"        T:::::T          D:::::D     D:::::D  4::::4  4::::4  M:::::::::::M     M:::::::::::M       E:::::E             M:::::::::::M     M:::::::::::M U:::::D     D:::::U   L:::::L                         A:::::A:::::A            T:::::T        O:::::O     O:::::O  R::::R     R:::::R\n"
"        T:::::T          D:::::D     D:::::D 4::::4   4::::4  M:::::::M::::M   M::::M:::::::M       E::::::EEEEEEEEEE   M:::::::M::::M   M::::M:::::::M U:::::D     D:::::U   L:::::L                        A:::::A A:::::A           T:::::T        O:::::O     O:::::O  R::::RRRRRR:::::R \n"
"        T:::::T          D:::::D     D:::::D4::::444444::::444M::::::M M::::M M::::M M::::::M       E:::::::::::::::E   M::::::M M::::M M::::M M::::::M U:::::D     D:::::U   L:::::L                       A:::::A   A:::::A          T:::::T        O:::::O     O:::::O  R:::::::::::::RR  \n"
"        T:::::T          D:::::D     D:::::D4::::::::::::::::4M::::::M  M::::M::::M  M::::::M       E:::::::::::::::E   M::::::M  M::::M::::M  M::::::M U:::::D     D:::::U   L:::::L                      A:::::A     A:::::A         T:::::T        O:::::O     O:::::O  R::::RRRRRR:::::R \n"
"        T:::::T          D:::::D     D:::::D4444444444:::::444M::::::M   M:::::::M   M::::::M       E::::::EEEEEEEEEE   M::::::M   M:::::::M   M::::::M U:::::D     D:::::U   L:::::L                     A:::::AAAAAAAAA:::::A        T:::::T        O:::::O     O:::::O  R::::R     R:::::R\n"
"        T:::::T          D:::::D     D:::::D          4::::4  M::::::M    M:::::M    M::::::M       E:::::E             M::::::M    M:::::M    M::::::M U:::::D     D:::::U   L:::::L                    A:::::::::::::::::::::A       T:::::T        O:::::O     O:::::O  R::::R     R:::::R\n"
"        T:::::T          D:::::D    D:::::D           4::::4  M::::::M     MMMMM     M::::::M       E:::::E       EEEEEEM::::::M     MMMMM     M::::::M U::::::U   U::::::U   L:::::L         LLLLLL    A:::::AAAAAAAAAAAAA:::::A      T:::::T        O::::::O   O::::::O  R::::R     R:::::R\n"
"      TT:::::::TT      DDD:::::DDDDD:::::D            4::::4  M::::::M               M::::::M     EE::::::EEEEEEEE:::::EM::::::M               M::::::M U:::::::UUU:::::::U LL:::::::LLLLLLLLL:::::L   A:::::A             A:::::A   TT:::::::TT      O:::::::OOO:::::::ORR:::::R     R:::::R\n"
"      T:::::::::T      D:::::::::::::::DD           44::::::44M::::::M               M::::::M     E::::::::::::::::::::EM::::::M               M::::::M  UU:::::::::::::UU  L::::::::::::::::::::::L  A:::::A               A:::::A  T:::::::::T       OO:::::::::::::OO R::::::R     R:::::R\n"
"      T:::::::::T      D::::::::::::DDD             4::::::::4M::::::M               M::::::M     E::::::::::::::::::::EM::::::M               M::::::M    UU:::::::::UU    L::::::::::::::::::::::L A:::::A                 A:::::A T:::::::::T         OO:::::::::OO   R::::::R     R:::::R\n"
"      TTTTTTTTTTT      DDDDDDDDDDDDD                4444444444MMMMMMMM               MMMMMMMM     EEEEEEEEEEEEEEEEEEEEEEMMMMMMMM               MMMMMMMM      UUUUUUUUU      LLLLLLLLLLLLLLLLLLLLLLLLAAAAAAA                   AAAAAAATTTTTTTTTTT           OOOOOOOOO     RRRRRRRR     RRRRRRR\n";





int main() {
    for (int i = 0; i < 16; i++) {
        coman[i] = MyBitset<8>(); // Создаем пустую карту //
    }
    cout << graffiti;
    cout << "\n\n\n\n\n";
    cout << "Instruction_Set\n" << "ADD A,Im 0000,\nADD B,Im 0101,\nMOV A,Im 0011,\nMOV B,Im 0111,\nMOV A,B 0001\nMOV B,A 0100\nJMP Im 1111\nJNC Im 1110\nIN A 0010\nIN B 0110\nOUT B 1001\nOUT Im 1011";

    while (true) {
        cout << "\n\n\n";
        cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur (new version !!! )  9: read file";
        cout << "\n\n\n";

        while (true) {
            if (!(cin >> comand)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                PrintInvalidChoice();
                cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur  9: read file" << endl;
                continue;
            }
            if (comand < 1 || comand > 9) {
                PrintInvalidChoice();
                continue;
            }
            break;
        }


		if (comand == 9) {
            read_file();
        }

        if (comand == 8){
            Zaur();
        }

        if (comand == 6 )

        {
            chose_input();
            break;
        }
        if (comand == 4) {
            cout << "Zaur,See you soon!";
            exit(0);
        }
            if (comand == 3){
                Commands_from_the_register();
               
        }
        if (comand == 1) {
            coman.clear();
        }

        if (comand == 2) {
            cout << "";
        }

        if (comand == 5) {
            Empty();
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
