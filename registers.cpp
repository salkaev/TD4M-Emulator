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
MyBitset<4> Register_A, Register_B, Output_Port, Input_Port, chose_Instruction, choce, key;
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
