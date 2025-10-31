#include "registers.h"
#include "Mybitset.h"
#include "securety_func.h"
#include "Core.h"
#include <map>
#include <iostream>
#include <string>
#include<algorithm>
#include<iomanip>
#include <chrono>
#include <thread> 

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

       //MOV Y IM //
if (choce == "1100") {
    XY[1].second = make_bitset4_safe(data);
}

      //MOV X IM //
     if (choce == "1101") {
         XY[0].second = make_bitset4_safe(data);

     }


    // Команды где B7-B4 == 1000 //
     if (choce == "1000") {

         if (data == "0000") { //А <= A+B
             Register_A += Register_B;
             return(Register_A);
         }
         if (data == "0001") { //A<= -A Вот это проблема так проблема //

             string numb = "-" + Register_A.to_string();
             MyBitset<4> bitset_var(numb);
             Register_A = bitset_var;


             return (Register_A);
         }
         //NOT A//
         if (data == "0010") {
             string   data_2 = Register_A.to_string();
             for (auto i = 0; i < 4; i++) {
                 if (data[i] == '0') {
                     data_2[i] = '1';
                 }
                 else {
                     data_2[i] = '0';
                 }

             }
             MyBitset<4> bitset_var(data_2);
             Register_A = bitset_var;
             return (Register_A);
         }

         //OR A,B//
         if (data == "0011") {
             string   data_2 = Register_A.to_string();
             string   data_3 = Register_B.to_string();
             string   data_4;

             for (auto i = 0; i < 4; ++i) {
                 if (data_2[i] == '1' or data_3[i] == '1') {
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
                 if (data_2[i] == '1' and data_3[i] == '1') {
                     data_4 += '1';
                 }
                 else {
                     data_4 += '0';
                 }
             }


         }
         //XOR A,B//
         if (data == "0101") {
             string  data_2 = Register_A.to_string();
             string  data_3 = Register_B.to_string();
             string  data_4;

         }





         //NEG A //

         if (data == "0001") {
             MyBitset<4> new1 = (Register_A) * (-1);
             cout << new1;
                 

         }


         /*   //SUB A,B //
            if (data == "0110") { //А <= A-B //
                Register_A -= Register_B;
                return(Register_A);
            }
            */


            // 0111 OUT A //
         if (data == "0111") {
             Register_A += make_bitset4_safe(data);
             Output_Port = Register_A;
             return Register_A;
         }




         //1000 LD A //
         if (data == "1000") {
             MyBitset<8> xy = Gluing(XY[0].second, XY[1].second);
             string numb_2 = xy.to_string();
             std::stringstream ss;
             ss << std::hex << std::uppercase << numb_2;
             string hex_numv = ss.str();
             hex_numv += 'h';

             auto pair = RAM.find(hex_numv);
             MyBitset<4> bin_numb = pair->second;

             Register_A = bin_numb;

         }


         //1010 LD B //
         if (data == "1010") {
             MyBitset<8> xy = Gluing(XY[0].second, XY[1].second);
             string numb_2 = xy.to_string();
             std::stringstream ss;
             ss << std::hex << std::uppercase << numb_2;
             string hex_numv = ss.str();
             hex_numv += 'h';

             auto pair = RAM.find(hex_numv);
             MyBitset<4> bin_numb = pair->second;

             Register_B = bin_numb;

         }

         //1100 MOV X,A//
         if (data == "1100") {
             XY[0].second = Register_A;


         }
         //1101 MOV Y,A//
         if (data == "1100") {
             XY[1].second = Register_A;

         }
     }



   

    //  LNC XY //
     if (data == "1110") {
         MyBitset<4>one = 0001;
         XY[0].second = XY[1].second + one;
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
            std::cout << "DEBUG: Adding command at position " << number_posi << std::endl;
            std::cout << "DEBUG: Opcode: " << chose_Instruction << ", Data: ";
            std::cout << "DEBUG: Full command: " << choce << std::endl;

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
            MyBitset<8> command_and_data = { 0 };
            cout << "command_and_data" << command_and_data;
            command_and_data = Gluing(chose_Instruction, choce);
            if (coman.find(number_posi) != coman.end()) {
                coman.erase(number_posi);
            }
            std::cout << "DEBUG: Adding command at position " << number_posi << std::endl;
            std::cout << "DEBUG: Opcode: " << chose_Instruction << ", Data: ";
            std::cout << "DEBUG: Full command: " << choce << std::endl;
            std::cout << command_and_data;
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


//Обработка введённых команд из нашей таблицы //

void processing_for_command() {

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
                cout << "Zaur,error: invalid command encoding at position " << position << ". Skipping.\n";
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
                        cout << "Zaur,warning: invalid jump address '" << addr_check << "'. Ignoring jump.\n";
                    }
                    else {
                        if (new_i >= 0 && new_i < (int)sorted_coman.size()) {
                            i = new_i - 1;
                        }
                        else {
                            cout << "Zaur,warning: jump target " << new_i << " out of range. Ignored.\n";
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
}



     