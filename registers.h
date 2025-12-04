// registers.h
#pragma once

#ifndef REGISTERS_H
#define REGISTERS_H

#include "Mybitset.h"
#include "BitsetCompare.h"  // Добавьте эту строку
#include <map>
#include <vector>
#include <string>

using namespace std;

// Объявления переменных с ключевым словом extern
extern int ok;
extern char ch;
extern MyBitset<4> a;
extern MyBitset<4> Program_Counter;
extern int C_Flag;
extern int Z_Flag;
extern MyBitset<4> Register_A;
extern MyBitset<4> Register_B;
extern MyBitset<4> Output_Port;
extern MyBitset<4> Input_Port;
extern MyBitset<4> chose_Instruction;
extern MyBitset<4> choce;
extern MyBitset<4> key;
extern MyBitset<4> nots;
extern vector<vector<MyBitset<8>>> mapa;
extern map<int, MyBitset<8>> coman;
extern vector<pair<string, MyBitset<4>>> XY;
extern map<string, MyBitset<4>> registers;

// 8-битный регистр XY
extern MyBitset<8> bin_numb;

extern bool pendingC_next;
extern bool pendingC_clear_after_show;

extern int len_program;
extern int comand;
extern int number_posi;
extern int cnt;
extern string bitsett;
extern string bitsettT;
extern string stop;

extern map<MyBitset<4>, string, BitsetCompare> Instruction_Set;
extern map<string, MyBitset<4>, BitsetCompare> RAM;

// Объявление функции
void update_XY_from_parts();

#endif // REGISTERS_H