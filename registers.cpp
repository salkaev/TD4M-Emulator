#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <string>
#include"Mybitset.h"
#include"securety_func.h"
using namespace std;
int ok = 0;
string registers;

vector<pair<string, MyBitset<4>>> XY = {
    {"X", MyBitset<4>("0000")},
    {"Y", MyBitset<4>("0000")}
};

char ch;
MyBitset<4> a;
MyBitset<4> Program_Counter = 0;
int C_Flag = 0;
MyBitset<4> Register_A, Register_B, Output_Port, Input_Port, chose_Instruction, choce, key, nots;
vector<vector<MyBitset<8>>> mapa;
map<int, MyBitset<8>> coman;

// Флаги для установки C_Flag на следующий ход //
bool pendingC_next = false;
bool pendingC_clear_after_show = false;

int len_program = -1;
int comand = 0;
int number_posi = 0;
int cnt = 0;
string bitsett;
string bitsettT;
string stop;


/*
№
Код команды	Мнемоника команды

Краткое описание
Влияние на флаги	TD4
B7..B4	B3..B0			Z	C
1	0000	Im	ADD A, Im	A <= A + Im + +да         +
2	0001	0000	MOV A, B	A <= B	0	0	да    +
3	0001	N	ADD A, B, N	A ⇐ B + N + +да           +
4	0010	0000	IN  A 	A ⇐ input	0	0	да    +
5	0010	N	IN  A + N 	A ⇐ input + N + +да       +
6	0011	Im	MOV A, Im	A ⇐ Im	0	0	да        +
7	0100	0000	MOV B, A	B ⇐ A	0	0	да    +
8	0100	N	ADD B, A, N	B ⇐ A + N + +да           +
9	0101	Im	ADD B, Im	B ⇐ B + Im + +да          +
10	0110	0000	IN  B	B ⇐ input	0	0	да    +
11	0110	N	IN B + N	B ⇐ input + N + +да       +
12	0111	Im	MOV B, Im	B ⇐ Im	0	0	да        +
13	1000	0000	ADD A, B	A ⇐ A + B + +нет      +
14	1000	0001	NEG A	A ⇐ - A + +нет             
15	1000	0010	NOT A	A ⇐ not A + 0	нет       +
16	1000	0011	OR A, B	A ⇐ A or B + 0	нет       +
17	1000	0100	AND A, B	A ⇐ A and B + 0	нет   +
18	1000	0101	XOR A, B	A ⇐ A xor B + 0	нет   +
19	1000	0110	SUB A, B	A ⇐ A - B + +нет      +
20	1000	0111	OUT A	output ⇐ A	0	0	нет   +
21	1000	1000	LD A	A ⇐ RAM(XY)	0	0	нет
22	1000	1001	ST A	RAM(XY) ⇐ A	0	0	нет
23	1000	1010	LD B	B ⇐ RAM(XY)	0	0	нет
24	1000	1011	ST B	RAM(XY) ⇐ B	0	0	нет
25	1000	1100	MOV X, A	X ⇐ A	0	0	нет   +
26	1000	1101	MOV Y, A	Y ⇐ A	0	0	нет   +
27	1000	1110	INC XY	XY ⇐ XY + 1	0	0	нет
28	1000	1111	JMP XY	PC ⇐ XY	0	0	нет
29	1001	0000	OUT B	output ⇐ B	0	0	да   +
30	1001	N	OUT B + N	output ⇐ B + N + +  да
31	1010	Im	JZ Im	если Z = 1, то PCL ⇐ Im	0	0	нет 
32	1011	Im	OUT Im	output ⇐ Im	0	0	да       +
33	1100	Im	MOV Y, Im	Y ⇐ Im	0	0	нет      +
34	1101	Im	MOV X, Im	X ⇐ Im	0	0	нет      + 
35	1110	Im	JNC Im	если C = 0, то PCL ⇐ Im - -нет+
36	1111	Im	JMP Im	PCL ⇐ Im - -нет              +  
*/

//Все команды //
map<string, MyBitset<4>,  BitsetCompare> Instruction_Set = {
    {MyBitset<4>("0000"), "ADD A,Im"},
    {MyBitset<4>("0101"), "ADD B,Im"},
    {MyBitset<4>("0011"), "MOV A,Im"},
    {MyBitset<4>("0111"), "MOV B,Im"},
    {MyBitset<4>("0001"), "MOV A,B"},
    {MyBitset<4>("0100"), "MOV B,A"},
    {MyBitset<4>("1111"), "JMP Im"},
    {MyBitset<4>("1110"), "JNC Im"},
    {MyBitset<4>("0010"), "IN A"},
    {MyBitset<4>("0110"), "IN B"},
    {MyBitset<4>("1001"), "OUT B"},
    {MyBitset<4>("1011"), "OUT Im"},

};
 

//Наша чудо RAM память //

std::map<std::string, MyBitset<4>, BitsetCompare> RAM = {
    { "00h", MyBitset<4>("0000") }, { "01h", MyBitset<4>("0000") }, { "02h", MyBitset<4>("0000") }, { "03h", MyBitset<4>("0000") },
    { "04h", MyBitset<4>("0000") }, { "05h", MyBitset<4>("0000") }, { "06h", MyBitset<4>("0000") }, { "07h", MyBitset<4>("0000") },
    { "08h", MyBitset<4>("0000") }, { "09h", MyBitset<4>("0000") }, { "0Ah", MyBitset<4>("0000") }, { "0Bh", MyBitset<4>("0000") },
    { "0Ch", MyBitset<4>("0000") }, { "0Dh", MyBitset<4>("0000") }, { "0Eh", MyBitset<4>("0000") }, { "0Fh", MyBitset<4>("0000") },

    { "10h", MyBitset<4>("0000") }, { "11h", MyBitset<4>("0000") }, { "12h", MyBitset<4>("0000") }, { "13h", MyBitset<4>("0000") },
    { "14h", MyBitset<4>("0000") }, { "15h", MyBitset<4>("0000") }, { "16h", MyBitset<4>("0000") }, { "17h", MyBitset<4>("0000") },
    { "18h", MyBitset<4>("0000") }, { "19h", MyBitset<4>("0000") }, { "1Ah", MyBitset<4>("0000") }, { "1Bh", MyBitset<4>("0000") },
    { "1Ch", MyBitset<4>("0000") }, { "1Dh", MyBitset<4>("0000") }, { "1Eh", MyBitset<4>("0000") }, { "1Fh", MyBitset<4>("0000") },

    { "20h", MyBitset<4>("0000") }, { "21h", MyBitset<4>("0000") }, { "22h", MyBitset<4>("0000") }, { "23h", MyBitset<4>("0000") },
    { "24h", MyBitset<4>("0000") }, { "25h", MyBitset<4>("0000") }, { "26h", MyBitset<4>("0000") }, { "27h", MyBitset<4>("0000") },
    { "28h", MyBitset<4>("0000") }, { "29h", MyBitset<4>("0000") }, { "2Ah", MyBitset<4>("0000") }, { "2Bh", MyBitset<4>("0000") },
    { "2Ch", MyBitset<4>("0000") }, { "2Dh", MyBitset<4>("0000") }, { "2Eh", MyBitset<4>("0000") }, { "2Fh", MyBitset<4>("0000") },

    { "30h", MyBitset<4>("0000") }, { "31h", MyBitset<4>("0000") }, { "32h", MyBitset<4>("0000") }, { "33h", MyBitset<4>("0000") },
    { "34h", MyBitset<4>("0000") }, { "35h", MyBitset<4>("0000") }, { "36h", MyBitset<4>("0000") }, { "37h", MyBitset<4>("0000") },
    { "38h", MyBitset<4>("0000") }, { "39h", MyBitset<4>("0000") }, { "3Ah", MyBitset<4>("0000") }, { "3Bh", MyBitset<4>("0000") },
    { "3Ch", MyBitset<4>("0000") }, { "3Dh", MyBitset<4>("0000") }, { "3Eh", MyBitset<4>("0000") }, { "3Fh", MyBitset<4>("0000") },

    { "40h", MyBitset<4>("0000") }, { "41h", MyBitset<4>("0000") }, { "42h", MyBitset<4>("0000") }, { "43h", MyBitset<4>("0000") },
    { "44h", MyBitset<4>("0000") }, { "45h", MyBitset<4>("0000") }, { "46h", MyBitset<4>("0000") }, { "47h", MyBitset<4>("0000") },
    { "48h", MyBitset<4>("0000") }, { "49h", MyBitset<4>("0000") }, { "4Ah", MyBitset<4>("0000") }, { "4Bh", MyBitset<4>("0000") },
    { "4Ch", MyBitset<4>("0000") }, { "4Dh", MyBitset<4>("0000") }, { "4Eh", MyBitset<4>("0000") }, { "4Fh", MyBitset<4>("0000") },

    { "50h", MyBitset<4>("0000") }, { "51h", MyBitset<4>("0000") }, { "52h", MyBitset<4>("0000") }, { "53h", MyBitset<4>("0000") },
    { "54h", MyBitset<4>("0000") }, { "55h", MyBitset<4>("0000") }, { "56h", MyBitset<4>("0000") }, { "57h", MyBitset<4>("0000") },
    { "58h", MyBitset<4>("0000") }, { "59h", MyBitset<4>("0000") }, { "5Ah", MyBitset<4>("0000") }, { "5Bh", MyBitset<4>("0000") },
    { "5Ch", MyBitset<4>("0000") }, { "5Dh", MyBitset<4>("0000") }, { "5Eh", MyBitset<4>("0000") }, { "5Fh", MyBitset<4>("0000") },

    { "60h", MyBitset<4>("0000") }, { "61h", MyBitset<4>("0000") }, { "62h", MyBitset<4>("0000") }, { "63h", MyBitset<4>("0000") },
    { "64h", MyBitset<4>("0000") }, { "65h", MyBitset<4>("0000") }, { "66h", MyBitset<4>("0000") }, { "67h", MyBitset<4>("0000") },
    { "68h", MyBitset<4>("0000") }, { "69h", MyBitset<4>("0000") }, { "6Ah", MyBitset<4>("0000") }, { "6Bh", MyBitset<4>("0000") },
    { "6Ch", MyBitset<4>("0000") }, { "6Dh", MyBitset<4>("0000") }, { "6Eh", MyBitset<4>("0000") }, { "6Fh", MyBitset<4>("0000") },

    { "70h", MyBitset<4>("0000") }, { "71h", MyBitset<4>("0000") }, { "72h", MyBitset<4>("0000") }, { "73h", MyBitset<4>("0000") },
    { "74h", MyBitset<4>("0000") }, { "75h", MyBitset<4>("0000") }, { "76h", MyBitset<4>("0000") }, { "77h", MyBitset<4>("0000") },
    { "78h", MyBitset<4>("0000") }, { "79h", MyBitset<4>("0000") }, { "7Ah", MyBitset<4>("0000") }, { "7Bh", MyBitset<4>("0000") },
    { "7Ch", MyBitset<4>("0000") }, { "7Dh", MyBitset<4>("0000") }, { "7Eh", MyBitset<4>("0000") }, { "7Fh", MyBitset<4>("0000") },

    { "80h", MyBitset<4>("0000") }, { "81h", MyBitset<4>("0000") }, { "82h", MyBitset<4>("0000") }, { "83h", MyBitset<4>("0000") },
    { "84h", MyBitset<4>("0000") }, { "85h", MyBitset<4>("0000") }, { "86h", MyBitset<4>("0000") }, { "87h", MyBitset<4>("0000") },
    { "88h", MyBitset<4>("0000") }, { "89h", MyBitset<4>("0000") }, { "8Ah", MyBitset<4>("0000") }, { "8Bh", MyBitset<4>("0000") },
    { "8Ch", MyBitset<4>("0000") }, { "8Dh", MyBitset<4>("0000") }, { "8Eh", MyBitset<4>("0000") }, { "8Fh", MyBitset<4>("0000") },

    { "90h", MyBitset<4>("0000") }, { "91h", MyBitset<4>("0000") }, { "92h", MyBitset<4>("0000") }, { "93h", MyBitset<4>("0000") },
    { "94h", MyBitset<4>("0000") }, { "95h", MyBitset<4>("0000") }, { "96h", MyBitset<4>("0000") }, { "97h", MyBitset<4>("0000") },
    { "98h", MyBitset<4>("0000") }, { "99h", MyBitset<4>("0000") }, { "9Ah", MyBitset<4>("0000") }, { "9Bh", MyBitset<4>("0000") },
    { "9Ch", MyBitset<4>("0000") }, { "9Dh", MyBitset<4>("0000") }, { "9Eh", MyBitset<4>("0000") }, { "9Fh", MyBitset<4>("0000") },

    { "A0h", MyBitset<4>("0000") }, { "A1h", MyBitset<4>("0000") }, { "A2h", MyBitset<4>("0000") }, { "A3h", MyBitset<4>("0000") },
    { "A4h", MyBitset<4>("0000") }, { "A5h", MyBitset<4>("0000") }, { "A6h", MyBitset<4>("0000") }, { "A7h", MyBitset<4>("0000") },
    { "A8h", MyBitset<4>("0000") }, { "A9h", MyBitset<4>("0000") }, { "AAh", MyBitset<4>("0000") }, { "ABh", MyBitset<4>("0000") },
    { "ACh", MyBitset<4>("0000") }, { "ADh", MyBitset<4>("0000") }, { "AEh", MyBitset<4>("0000") }, { "AFh", MyBitset<4>("0000") },

    { "B0h", MyBitset<4>("0000") }, { "B1h", MyBitset<4>("0000") }, { "B2h", MyBitset<4>("0000") }, { "B3h", MyBitset<4>("0000") },
    { "B4h", MyBitset<4>("0000") }, { "B5h", MyBitset<4>("0000") }, { "B6h", MyBitset<4>("0000") }, { "B7h", MyBitset<4>("0000") },
    { "B8h", MyBitset<4>("0000") }, { "B9h", MyBitset<4>("0000") }, { "BAh", MyBitset<4>("0000") }, { "BBh", MyBitset<4>("0000") },
    { "BCh", MyBitset<4>("0000") }, { "BDh", MyBitset<4>("0000") }, { "BEh", MyBitset<4>("0000") }, { "BFh", MyBitset<4>("0000") },

    { "C0h", MyBitset<4>("0000") }, { "C1h", MyBitset<4>("0000") }, { "C2h", MyBitset<4>("0000") }, { "C3h", MyBitset<4>("0000") },
    { "C4h", MyBitset<4>("0000") }, { "C5h", MyBitset<4>("0000") }, { "C6h", MyBitset<4>("0000") }, { "C7h", MyBitset<4>("0000") },
    { "C8h", MyBitset<4>("0000") }, { "C9h", MyBitset<4>("0000") }, { "CAh", MyBitset<4>("0000") }, { "CBh", MyBitset<4>("0000") },
    { "CCh", MyBitset<4>("0000") }, { "CDh", MyBitset<4>("0000") }, { "CEh", MyBitset<4>("0000") }, { "CFh", MyBitset<4>("0000") },

    { "D0h", MyBitset<4>("0000") }, { "D1h", MyBitset<4>("0000") }, { "D2h", MyBitset<4>("0000") }, { "D3h", MyBitset<4>("0000") },
    { "D4h", MyBitset<4>("0000") }, { "D5h", MyBitset<4>("0000") }, { "D6h", MyBitset<4>("0000") }, { "D7h", MyBitset<4>("0000") },
    { "D8h", MyBitset<4>("0000") }, { "D9h", MyBitset<4>("0000") }, { "DAh", MyBitset<4>("0000") }, { "DBh", MyBitset<4>("0000") },
    { "DCh", MyBitset<4>("0000") }, { "DDh", MyBitset<4>("0000") }, { "DEh", MyBitset<4>("0000") }, { "DFh", MyBitset<4>("0000") },

    { "E0h", MyBitset<4>("0000") }, { "E1h", MyBitset<4>("0000") }, { "E2h", MyBitset<4>("0000") }, { "E3h", MyBitset<4>("0000") },
    { "E4h", MyBitset<4>("0000") }, { "E5h", MyBitset<4>("0000") }, { "E6h", MyBitset<4>("0000") }, { "E7h", MyBitset<4>("0000") },
    { "E8h", MyBitset<4>("0000") }, { "E9h", MyBitset<4>("0000") }, { "EAh", MyBitset<4>("0000") }, { "EBh", MyBitset<4>("0000") },
    { "ECh", MyBitset<4>("0000") }, { "EDh", MyBitset<4>("0000") }, { "EEh", MyBitset<4>("0000") }, { "EFh", MyBitset<4>("0000") },

    { "F0h", MyBitset<4>("0000") }, { "F1h", MyBitset<4>("0000") }, { "F2h", MyBitset<4>("0000") }, { "F3h", MyBitset<4>("0000") },
    { "F4h", MyBitset<4>("0000") }, { "F5h", MyBitset<4>("0000") }, { "F6h", MyBitset<4>("0000") }, { "F7h", MyBitset<4>("0000") },
    { "F8h", MyBitset<4>("0000") }, { "F9h", MyBitset<4>("0000") }, { "FAh", MyBitset<4>("0000") }, { "FBh", MyBitset<4>("0000") },
    { "FCh", MyBitset<4>("0000") }, { "FDh", MyBitset<4>("0000") }, { "FEh", MyBitset<4>("0000") }, { "FFh", MyBitset<4>("0000") }
};

