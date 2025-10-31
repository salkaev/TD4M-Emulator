#define NOMINMAX
#include <iostream>
#include <map>
#include <cstdlib>
#include <sstream>
#include <limits>
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

    MyBitset<4>zxc = 0001;
    cout << (zxc * ( - 1));
    for (int i = 0; i < 256; i++) {
        coman[i] = MyBitset<8>(); // Создаем пустую карту //
    }
    cout << graffiti;
    cout << "\n\n\n\n\n";
    cout << "Instruction_Set\n"
        << "Краткое описание\n"
        << "Влияние на флаги\tTD4\n"
        << "B7..B4\tB3..B0\t\tZ\tC\n\n"

        << "1\t0000\tIm\tADD A, Im\tA <= A + Im\t+\n\n"
        << "2\t0001\t0000\tMOV A, B\tA <= B\t0\t0\tда\t+\n\n"
        << "3\t0001\tN\tADD A, B, N\tA <= B + N\t+\n\n"
        << "4\t0010\t0000\tIN A\tA <= input\t0\t0\tда\t+\n\n"
        << "5\t0010\tN\tIN A + N\tA <= input + N\t+\n\n"
        << "6\t0011\tIm\tMOV A, Im\tA <= Im\t0\t0\tда\t+\n\n"
        << "7\t0100\t0000\tMOV B, A\tB <= A\t0\t0\tда\t+\n\n"
        << "8\t0100\tN\tADD B, A, N\tB <= A + N\t+\n\n"
        << "9\t0101\tIm\tADD B, Im\tB <= B + Im\t+\n\n"
        << "10\t0110\t0000\tIN B\tB <= input\t0\t0\tда\t+\n\n"
        << "11\t0110\tN\tIN B + N\tB <= input + N\t+\n\n"
        << "12\t0111\tIm\tMOV B, Im\tB <= Im\t0\t0\tда\t+\n\n"
        << "13\t1000\t0000\tADD A, B\tA <= A + B\t\n\n"
        << "14\t1000\t0001\tNEG A\tA <= -A\t\n\n"
        << "15\t1000\t0010\tNOT A\tA <= not A\t0\t+\n\n"
        << "16\t1000\t0011\tOR A, B\tA <= A or B\t0\t+\n\n"
        << "17\t1000\t0100\tAND A, B\tA <= A and B\t0\t+\n\n"
        << "18\t1000\t0101\tXOR A, B\tA <= A xor B\t0\t+\n\n"
        << "19\t1000\t0110\tSUB A, B\tA <= A - B\t\n\n"
        << "20\t1000\t0111\tOUT A\toutput <= A\t0\t0\tнет\t\n\n"
        << "21\t1000\t1000\tLD A\tA <= RAM(XY)\t0\t0\tнет\t\n\n"
        << "22\t1000\t1001\tST A\tRAM(XY) <= A\t0\t0\tнет\t\n\n"
        << "23\t1000\t1010\tLD B\tB <= RAM(XY)\t0\t0\tнет\t\n\n"
        << "24\t1000\t1011\tST B\tRAM(XY) <= B\t0\t0\tнет\t\n\n"
        << "25\t1000\t1100\tMOV X, A\tX <= A\t0\t0\tнет\t\n\n"
        << "26\t1000\t1101\tMOV Y, A\tY <= A\t0\t0\tнет\t\n\n"
        << "27\t1000\t1110\tINC XY\tXY <= XY + 1\t0\t0\tнет\t\n\n"
        << "28\t1000\t1111\tJMP XY\tPC <= XY\t0\t0\tнет\t\n\n"
        << "29\t1001\t0000\tOUT B\toutput <= B\t0\t0\tда\t\n\n"
        << "30\t1001\tN\tOUT B + N\toutput <= B + N\t+\n\n"
        << "31\t1010\tIm\tJZ Im\tif Z==1 then PCL <= Im\t\n\n"
        << "32\t1011\tIm\tOUT Im\toutput <= Im\t0\t0\tда\t\n\n"
        << "33\t1100\tIm\tMOV Y, Im\tY <= Im\t0\t0\tнет\t\n\n"
        << "34\t1101\tIm\tMOV X, Im\tX <= Im\t0\t0\tнет\t\n\n"
        << "35\t1110\tIm\tJNC Im\tif C==0 then PCL <= Im\t\n\n"
        << "36\t1111\tIm\tJMP Im\tPCL <= Im\t\n";

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
