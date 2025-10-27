#pragma once

#include"Mybitset.h"
#include"securety_func.h"
using namespace std;
extern int ok ;
extern char ch;
extern MyBitset<4> a;
extern MyBitset<4> Program_Counter ;
extern int C_Flag ;
extern MyBitset<4> Register_A, Register_B, Output_Port, Input_Port, chose_Instruction, choce, key;
extern vector<vector<MyBitset<8>>> mapa;
extern map<int, MyBitset<8>> coman;

// Флаги для установки C_Flag на следующий ход //
extern bool pendingC_next ;
extern bool pendingC_clear_after_show ;

extern int len_program ;
extern int comand ;
extern int  number_posi ;
extern int cnt ;
extern string bitsett;
extern string bitsettT;
extern string stop;

//Все команды //
extern map<MyBitset<4>, string, BitsetCompare> Instruction_Set;
