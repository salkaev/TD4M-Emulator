#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <string>
#include"Mybitset.h"
#include"securety_func.h"
using namespace std;
int ok = 0;
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
18	1000	0101	XOR A, B	A ⇐ A xor B + 0	нет
19	1000	0110	SUB A, B	A ⇐ A - B + +нет
20	1000	0111	OUT A	output ⇐ A	0	0	нет
21	1000	1000	LD A	A ⇐ RAM(XY)	0	0	нет
22	1000	1001	ST A	RAM(XY) ⇐ A	0	0	нет
23	1000	1010	LD B	B ⇐ RAM(XY)	0	0	нет
24	1000	1011	ST B	RAM(XY) ⇐ B	0	0	нет
25	1000	1100	MOV X, A	X ⇐ A	0	0	нет
26	1000	1101	MOV Y, A	Y ⇐ A	0	0	нет
27	1000	1110	INC XY	XY ⇐ XY + 1	0	0	нет
28	1000	1111	JMP XY	PC ⇐ XY	0	0	нет
29	1001	0000	OUT B	output ⇐ B	0	0	да   +
30	1001	N	OUT B + N	output ⇐ B + N + +да
31	1010	Im	JZ Im	если Z = 1, то PCL ⇐ Im	0	0	нет 
32	1011	Im	OUT Im	output ⇐ Im	0	0	да       +
33	1100	Im	MOV Y, Im	Y ⇐ Im	0	0	нет
34	1101	Im	MOV X, Im	X ⇐ Im	0	0	нет      + 
35	1110	Im	JNC Im	если C = 0, то PCL ⇐ Im - -нет
36	1111	Im	JMP Im	PCL ⇐ Im - -нет              +
*/

//Все команды //
map<MyBitset<4>, string, BitsetCompare> Instruction_Set = {
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
