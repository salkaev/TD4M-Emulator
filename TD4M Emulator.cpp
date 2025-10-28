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
            void processing_for_command();
        }

    }
}
