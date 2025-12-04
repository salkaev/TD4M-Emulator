#include "registers.h"
#include "Mybitset.h"
#include "securety_func.h"
#include "Core.h"
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <thread> 
#include <sstream>
// Вспомогательная функция для обновления 8-битного XY из X и Y
void update_XY_from_parts() {
    // Собираем X (старшие 4 бита) и Y (младшие 4 бита) в 8-битное значение
    string x_str = XY[0].second.to_string();  // X
    string y_str = XY[1].second.to_string();  // Y
    string xy_str = x_str + y_str;            // XY (8 бит)
    bin_numb = MyBitset<8>(xy_str);
}

MyBitset<4> fun(string choce, string data) {
    // Проверка корректности бинарных данных
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
        } else {
            Register_A = MyBitset<4>(sum);
        }
        Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
        return Register_A;
    }

    // 0101 ADD B,Im //
    if (choce == "0101") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        unsigned long long sum = Register_B.to_ullong() + bitset_var.to_ullong();
        if (sum > 0xF) {
            Register_B = MyBitset<4>(sum & 0xF);
            pendingC_next = true;
        } else {
            Register_B = MyBitset<4>(sum);
        }
        Z_Flag = (Register_B.to_ullong() == 0) ? 1 : 0; // +
        return Register_B;
    }

    // 0011 MOV A,Im //
    if (choce == "0011") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Register_A = bitset_var;
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_A;
    }

    // 0111 MOV B,Im //
    if (choce == "0111") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Register_B = bitset_var;
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_B;
    }

    // 0001 MOV A,B или ADD A,B,N //
    if (choce == "0001") {
        if (data == "0000") {
            // MOV A,B
            Register_A = Register_B;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
        } else {
            // ADD A,B,N
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            unsigned long long sum = Register_B.to_ullong() + bitset_var.to_ullong();
            if (sum > 0xF) {
                Register_A = MyBitset<4>(sum & 0xF);
                pendingC_next = true;
            } else {
                Register_A = MyBitset<4>(sum);
            }
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
        }
        return Register_A;
    }

    // 0100 MOV B,A или ADD B,A,N //
    if (choce == "0100") {
        if (data == "0000") {
            // MOV B,A
            Register_B = Register_A;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
        } else {
            // ADD B,A,N
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            unsigned long long sum = Register_A.to_ullong() + bitset_var.to_ullong();
            if (sum > 0xF) {
                Register_B = MyBitset<4>(sum & 0xF);
                pendingC_next = true;
            } else {
                Register_B = MyBitset<4>(sum);
            }
            Z_Flag = (Register_B.to_ullong() == 0) ? 1 : 0; // +
        }
        return Register_B;
    }

    // 1111 JMP Im //
    if (choce == "1111") {
        if (!is_binary(data, 4)) {
            cout << "Error: invalid JMP address '" << data << "'. Ignoring jump.\n";
            return Register_A;
        }
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Program_Counter = bitset_var;
        // Z и C не меняются (- -)
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
        // Z и C не меняются (- -)
        return Register_A;
    }

    // 1010 JZ Im //
    if (choce == "1010") {
        if (!is_binary(data, 4)) {
            cout << "Error: invalid JZ address '" << data << "'. Ignoring jump.\n";
            return Register_A;
        }
        if (Z_Flag == 1) {
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            Program_Counter = bitset_var;
        }
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_A;
    }

    // 0010 IN A или IN A+N //
    if (choce == "0010") {
        if (data == "0000") {
            // IN A
            Register_A = Input_Port;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
        } else {
            // IN A+N
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            unsigned long long sum = Input_Port.to_ullong() + bitset_var.to_ullong();
            if (sum > 0xF) {
                Register_A = MyBitset<4>(sum & 0xF);
                pendingC_next = true;
            } else {
                Register_A = MyBitset<4>(sum);
            }
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
        }
        return Register_A;
    }

    // 0110 IN B или IN B+N //
    if (choce == "0110") {
        if (data == "0000") {
            // IN B
            Register_B = Input_Port;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
        } else {
            // IN B+N
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            unsigned long long sum = Input_Port.to_ullong() + bitset_var.to_ullong();
            if (sum > 0xF) {
                Register_B = MyBitset<4>(sum & 0xF);
                pendingC_next = true;
            } else {
                Register_B = MyBitset<4>(sum);
            }
            Z_Flag = (Register_B.to_ullong() == 0) ? 1 : 0; // +
        }
        return Register_B;
    }

    // 1001 OUT B или OUT B+N //
    if (choce == "1001") {
        if (data == "0000") {
            // OUT B
            Output_Port = Register_B;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
        } else {
            // OUT B+N
            MyBitset<4> bitset_var = make_bitset4_safe(data);
            MyBitset<4> result = Register_B + bitset_var;
            Output_Port = result;
            Z_Flag = (result.to_ullong() == 0) ? 1 : 0; // +
            // Обработка C флага для сложения
            unsigned long long sum = Register_B.to_ullong() + bitset_var.to_ullong();
            if (sum > 0xF) {
                pendingC_next = true;
            }
        }
        return Register_B;
    }

    // 1011 OUT Im //       
    if (choce == "1011") {
        MyBitset<4> bitset_var = make_bitset4_safe(data);
        Output_Port = bitset_var;
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_A;
    }

    // 1100 MOV Y,Im //
    if (choce == "1100") {
        XY[1].second = make_bitset4_safe(data);  // Y = Im
        update_XY_from_parts();  // Обновляем 8-битный XY
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_A;
    }

    // 1101 MOV X,Im //
    if (choce == "1101") {
        XY[0].second = make_bitset4_safe(data);  // X = Im
        update_XY_from_parts();  // Обновляем 8-битный XY
        Z_Flag = 0; // 0
        C_Flag = 0; // 0
        return Register_A;
    }

    // B7-B4 == 1000 //
    if (choce == "1000") {
        // 0000 ADD A,B //
        if (data == "0000") {
            unsigned long long sum = Register_A.to_ullong() + Register_B.to_ullong();
            if (sum > 0xF) {
                Register_A = MyBitset<4>(sum & 0xF);
                pendingC_next = true;
            } else {
                Register_A = MyBitset<4>(sum);
            }
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            return Register_A;
        }

        // 0001 NEG A //
        if (data == "0001") {
            // Дополнение до двух: -A = ~A + 1
            MyBitset<4> one = 1;
            string a_str = Register_A.to_string();
            string neg_str;
            for (int i = 0; i < 4; ++i) {
                neg_str += (a_str[i] == '0') ? '1' : '0';
            }
            MyBitset<4> neg(neg_str);
            Register_A = neg + one;
            
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            // Обработка C флага для NEG
            if (Register_A.to_ullong() == 0 && a_str != "0000") {
                pendingC_next = true;
            }
            return Register_A;
        }

        // 0010 NOT A //
        if (data == "0010") {
            string a_str = Register_A.to_string();
            string not_str;
            for (auto i = 0; i < 4; i++) {
                not_str += (a_str[i] == '0') ? '1' : '0';
            }
            Register_A = MyBitset<4>(not_str);
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            C_Flag = 0; // 0 для NOT
            return Register_A;
        }

        // 0011 OR A,B //
        if (data == "0011") {
            string a_str = Register_A.to_string();
            string b_str = Register_B.to_string();
            string result_str;
            for (auto i = 0; i < 4; ++i) {
                result_str += ((a_str[i] == '1') || (b_str[i] == '1')) ? '1' : '0';
            }
            Register_A = MyBitset<4>(result_str);
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            C_Flag = 0; // 0 для логических операций
            return Register_A;
        }

        // 0100 AND A,B //
        if (data == "0100") {
            string a_str = Register_A.to_string();
            string b_str = Register_B.to_string();
            string result_str;
            for (int i = 0; i < 4; ++i) {
                result_str += ((a_str[i] == '1') && (b_str[i] == '1')) ? '1' : '0';
            }
            Register_A = MyBitset<4>(result_str);
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            C_Flag = 0; // 0 для логических операций
            return Register_A;
        }

        // 0101 XOR A,B //
        if (data == "0101") {
            string a_str = Register_A.to_string();
            string b_str = Register_B.to_string();
            string result_str;
            for (int i = 0; i < 4; ++i) {
                result_str += (a_str[i] != b_str[i]) ? '1' : '0';
            }
            Register_A = MyBitset<4>(result_str);
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            C_Flag = 0; // 0 для логических операций
            return Register_A;
        }

        // 0110 SUB A,B //
        if (data == "0110") {
            // A - B = A + (-B)
            // -B = ~B + 1 (дополнение до двух)
            MyBitset<4> one = 1;
            string b_str = Register_B.to_string();
            string neg_b_str;
            for (int i = 0; i < 4; ++i) {
                neg_b_str += (b_str[i] == '0') ? '1' : '0';
            }
            MyBitset<4> negB(neg_b_str);
            MyBitset<4> minusB = negB + one;
            
            // Выполняем сложение A + (-B)
            unsigned long long diff = Register_A.to_ullong() + minusB.to_ullong();
            if (diff > 0xF) {
                Register_A = MyBitset<4>(diff & 0xF);
                pendingC_next = true; // Заём при вычитании
            } else {
                Register_A = MyBitset<4>(diff);
            }
            Z_Flag = (Register_A.to_ullong() == 0) ? 1 : 0; // +
            return Register_A;
        }

        // 0111 OUT A //
        if (data == "0111") {
            Output_Port = Register_A;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1000 LD A //
        if (data == "1000") {
            // Используем текущий 8-битный XY как адрес
            string xy_str = bin_numb.to_string();
            std::stringstream ss;
            ss << std::hex << std::uppercase << xy_str;
            string hex_addr = ss.str();
            hex_addr += 'h';
            
            auto pair = RAM.find(hex_addr);
            if (pair != RAM.end()) {
                Register_A = pair->second;
            }
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1001 ST A //
        if (data == "1001") {
            // Используем текущий 8-битный XY как адрес
            string xy_str = bin_numb.to_string();
            std::stringstream ss;
            ss << std::hex << std::uppercase << xy_str;
            string hex_addr = ss.str();
            hex_addr += 'h';
            
            RAM[hex_addr] = Register_A;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1010 LD B //
        if (data == "1010") {
            // Используем текущий 8-битный XY как адрес
            string xy_str = bin_numb.to_string();
            std::stringstream ss;
            ss << std::hex << std::uppercase << xy_str;
            string hex_addr = ss.str();
            hex_addr += 'h';
            
            auto pair = RAM.find(hex_addr);
            if (pair != RAM.end()) {
                Register_B = pair->second;
            }
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }
        
        // 1011 ST B //
        if (data == "1011") {
            // Используем текущий 8-битный XY как адрес
            string xy_str = bin_numb.to_string();
            std::stringstream ss;
            ss << std::hex << std::uppercase << xy_str;
            string hex_addr = ss.str();
            hex_addr += 'h';
            
            RAM[hex_addr] = Register_B;
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_B;
        }

        // 1100 MOV X,A //
        if (data == "1100") {
            XY[0].second = Register_A;  // X = A
            update_XY_from_parts();  // Обновляем 8-битный XY
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1101 MOV Y,A //
        if (data == "1101") {
            XY[1].second = Register_A;  // Y = A
            update_XY_from_parts();  // Обновляем 8-битный XY
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1110 INC XY //
        if (data == "1110") {
            // Инкрементируем 8-битный XY
            bin_numb = bin_numb + MyBitset<8>(1);
            // Разбиваем обратно на X и Y
            string xy_str = bin_numb.to_string();
            XY[0].second = MyBitset<4>(xy_str.substr(0, 4));  // X (старшие 4 бита)
            XY[1].second = MyBitset<4>(xy_str.substr(4, 4));  // Y (младшие 4 бита)
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // 1111 JMP XY //
        if (data == "1111") {
            // Используем текущий 8-битный XY как адрес перехода
            // JMP XY загружает младшие 4 бита XY в PC
            string xy_str = bin_numb.to_string();
            string pcl_str = xy_str.substr(4, 4);  // Младшие 4 бита (Y)
            Program_Counter = MyBitset<4>(pcl_str);
            Z_Flag = 0; // 0
            C_Flag = 0; // 0
            return Register_A;
        }

        // Если неизвестная подкоманда для 1000
        cout << "Warning: unknown sub-instruction '" << data << "' for instruction 1000. Ignored.\n";
        return Register_A;
    }

    // Неизвестная инструкция
    cout << "Warning: unknown instruction '" << choce << "'. Ignored.\n";
    return Register_A;
}

void Commands_from_the_register(){
    // ... существующий код без изменений ...
}

void processing_for_command() {
    vector<pair<int, MyBitset<8>>> sorted_coman(coman.begin(), coman.end());
    sort(sorted_coman.begin(), sorted_coman.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

    stop = "";
    string click = "";
    
    // Инициализация XY регистра при запуске
    update_XY_from_parts();
    
    while (stop != "stop") {
        while (click != "auto" && click != "manual") {
            cout << "Zaur, do you want auto click or manual? ";
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

            // ... существующий код ввода/вывода ...

            if (pendingC_next) {
                C_Flag = 1;
                pendingC_next = false;
                pendingC_clear_after_show = true;
            }

            // ОБНОВЛЕННЫЙ ВЫВОД С ПРАВИЛЬНЫМИ ФЛАГАМИ
            cout << "|---------------Register--------------|\n";
            cout << "+-------------+-------------+---------+---------+------------\n";
            cout << "| Register A  | Register B  | Z Flag  | C Flag  | Register XY | \n";
            cout << "+-------------+-------------+---------+---------+------------\n";
            cout << "| " << setw(11) << Register_A << " | " << setw(11) << Register_B 
                 << " | " << setw(7) << Z_Flag << " | " << setw(7) << C_Flag 
                 << " | " << setw(10) << bin_numb << " |\n";
            cout << "+-------------+-------------+---------+---------+------------\n";
            cout << "| PC: " << setw(8) << Program_Counter 
                 << " | Out: " << setw(7) << Output_Port 
                 << " | In: " << setw(6) << Input_Port << " |\n";
            cout << "+-------------+---------------------------+---------------+\n";

            Output_Port = MyBitset<4>(0);
            Program_Counter += 0001;
            
            string s = val.to_string();
            if (s.size() != 8) {
                cout << "Zaur, error: invalid command encoding at position " << position << ". Skipping.\n";
                continue;
            }
            
            string instruction = s.substr(0, 4);
            string payload = s.substr(4, 4);

            try {
                fun(instruction, payload);
            } catch (const std::exception& ex) {
                cout << "Exception during instruction execution: " << ex.what() << "\n";
                continue;
            } catch (...) {
                cout << "Unknown exception during instruction execution.\n";
                continue;
            }

            // Обработка переходов
            if (instruction == "1111" || (instruction == "1110" && C_Flag != 1)) {
                int new_i = -1;
                if (!bin_to_int_safe(payload, new_i)) {
                    cout << "Zaur, warning: invalid jump address '" << payload << "'. Ignoring jump.\n";
                } else {
                    if (new_i >= 0 && new_i < (int)sorted_coman.size()) {
                        i = new_i - 1;
                    } else {
                        cout << "Zaur, warning: jump target " << new_i << " out of range. Ignored.\n";
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



     