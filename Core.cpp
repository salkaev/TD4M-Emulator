#include "Mybitset.h"
#include "registers.h"
#include "securety_func.h"
#include "Core.h"
#include <map>
#include <iostream>
#include <string>

// Функция обработки функционала команд -- сигнатура точно совпадает с Core.h
MyBitset<4> fun(string choce, string data) {

    // Валидация входных строк для предотвращения некорректных конструкций
    if (!is_binary(choce, 4)) {
        cout << "Error: invalid instruction code '" << choce << "'. Ignoring.\n";
        return Register_A;
    }
    if (!is_binary(data, 4) && !(choce == "0001" || choce == "0100")) {
        cout << "Warning: invalid payload '" << data << "' for instruction " << choce << ". Using 0000.\n";
        data = "0000";
    }

    // 0000 ADD A,Im //
    if (choce == "0000") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        unsigned long long sum = Register_A.to_ullong() + bitset_var.to_ullong();
        if (sum > 0xF) {
            Register_A = MyBitset<4>(sum & 0xF);
            pendingC_next = true;
        }
        else {
            Register_A = MyBitset<4>(sum);
        }
        return Register_A;
    }

    // 0101 ADD B,Im//
    if (choce == "0101") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        unsigned long long sum = Register_B.to_ullong() + bitset_var.to_ullong();
        if (sum > 0xF) {
            Register_B = MyBitset<4>(sum & 0xF);
            pendingC_next = true;
        }
        else {
            Register_B = MyBitset<4>(sum);
        }
        return Register_B;
    }

    // 0011 MOV A,Im//
    if (choce == "0011") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Register_A = bitset_var;
        return Register_A;
    }

    // 0111 MOV B,Im//
    if (choce == "0111") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Register_B = bitset_var;
        return Register_B;
    }

    // 0001 MOV A,B//
    if (choce == "0001") {
        if (data == "0000") {
            Register_A = Register_B;
        }
        else {
            // если payload — immediate, применим как замещение
            Register_A = make_bitset4_safe(data);
        }
        return Register_A;
    }

    // 0100 MOV B,A//
    if (choce == "0100") {
        if (data == "0000") {
            Register_B = Register_A;
        }
        else {
            Register_B = Register_A;
            Register_B += make_bitset4_safe(data);
        }
        return Register_B;
    }

    // 1111 JMP Im (безусловный) //
    if (choce == "1111") {
        if (!is_binary(data, 4)) {
            cout << "Error: invalid JMP address '" << data << "'. Ignoring jump.\n";
            return Register_A;
        }
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Program_Counter = bitset_var;
        return Register_A;
    }

    // 1110 JNC Im //
    if (choce == "1110") {
        if (!is_binary(data, 4)) {
            cout << "Error: invalid JNC address '" << data << "'. Ignoring jump.\n";
            return Register_A;
        }
        if (C_Flag != 1) {
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            Program_Counter = bitset_var;
        }
        return Register_A;
    }

    // 0010 IN A //
    if (choce == "0010") {
        Register_A = Input_Port;
        return Register_A;
    }

    // 0110 IN B //
    if (choce == "0110") {
        Register_B = Input_Port;
        return Register_B;
    }

    // 1001 OUT B //
    if (choce == "1001") {
        Register_B += make_bitset4_safe(data);
        Output_Port = Register_B;
        return Register_B;
    }

    // 1011 OUT Im //       
    if (choce == "1011") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Output_Port = bitset_var;
        return Register_A;
    }

    // неизвестная инструкция //
    cout << "Warning: unknown instruction '" << choce << "'. Ignored.\n";
    return Register_A;
}