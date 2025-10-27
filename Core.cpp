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
    // Команды где B7-B4 == 1000 //
    if (choce == "1000") {

        if (data == "0000") { //А <= A+B
            Register_A+= Register_B;
            return(Register_A);
        }
        if (data == "0001") { //A<= -A Вот это проблема так проблема //

            string numb ="-" + Register_A.to_string();
            MyBitset<4> bitset_var(numb);
            Register_A = bitset_var;


            return (Register_A);
        }
		//NOT A//
        if (data == "0010") {
          string   data_2 = Register_A.to_string();
            for (auto i = 0; i < 4; i++) {
                if(data[i]=='0'){
                    data_2[i]='1';
                }
                else{
                    data_2[i]='0';
				}

            }
			MyBitset<4> bitset_var(data_2);
            Register_A= bitset_var;
			return (Register_A);
        }

		//OR A,B//
        if (data == "0011") {
            string   data_2 = Register_A.to_string();
            string   data_3 = Register_B.to_string();
            string   data_4;

            for (int i = 0; i < 4; ++i) {
                if (data_2[i] == "1" or data_3[i] == "1") {
					data_4 += '1';
                }
                else {
					data_4 += '0';
                }
            }

        }

		//AND A,B//
        if (data == "0100") {
            string   data_2 = Register_A.to_string();
            string   data_3 = Register_B.to_string();
            string   data_4;

            for (int i = 0; i < 4; ++i) {
                if (data_2[i] == "1" and data_3[i] == "1") {
                    data_4 += '1';
                }
                else {
                    data_4 += '0';
                }
            }


        }
		//XOR A,B//
        if (data == "0100") {


        }
    }

    // неизвестная инструкция //
    cout << "Warning: unknown instruction '" << choce << "'. Ignored.\n";
    return Register_A;
}


void Commands_from_the_register(){

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

       }
     