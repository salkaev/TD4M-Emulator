#define NOMINMAX
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <locale>
#include <clocale>
#include <windows.h>
#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sstream>
#include <limits>
#include <fstream>
#include <cctype>

using namespace std;

//Класс который будет эмулировать двоичный код//

template <size_t N>
class MyBitset {
private:
    int numb_posi;

    std::bitset<N> bits;

public:
    // Конструкторы//
    MyBitset() : bits(0)
    {
    }
    MyBitset(const std::string& str) : bits(str)
    {
    }
    MyBitset(unsigned long long value) : bits(value)
    {
    }

    // Оператор присваивания из строки//
    MyBitset& operator=(const std::string& str) {
        bits = std::bitset<N>(str);
        return *this;
    }
    // Оператор [] для доступа к отдельным битам//
    bool operator[](size_t pos) const {
        return bits[pos];
    }

    // Оператор присваивания из числа//
    MyBitset& operator=(unsigned long long value) {
        bits = std::bitset<N>(value);
        return *this;
    }

    // Оператор присваивания из другого MyBitset//
    MyBitset& operator=(const MyBitset& other) {
        bits = other.bits;
        return *this;
    }

    // Арифметика: сложение//
    MyBitset operator+(const MyBitset& other) const {
        unsigned long long result = this->to_ullong() + other.to_ullong();
        return MyBitset(result);
    }

    // Арифметика: вычитание//
    MyBitset operator-(const MyBitset& other) const {
        unsigned long long result = this->to_ullong() - other.to_ullong();
        return MyBitset(result);
    }

    // Получить число//
    unsigned long long to_ullong() const {
        return bits.to_ullong();
    }

    // Получить строку//
    std::string to_string() const {
        return bits.to_string();
    }

    // Вывод//
    void print() const {
        std::cout << bits << " (" << to_ullong() << ")" << std::endl;
    }

    // Сравнение//
    bool operator==(const MyBitset& other) const {
        return bits == other.bits;
    }

    bool operator!=(const MyBitset& other) const {
        return bits != other.bits;
    }

    // Дружественные операторы для ввода/вывода//
    friend std::ostream& operator<<(std::ostream& os, const MyBitset& b) {
        os << b.to_string();
        return os;
    }

    // Преобразование из строки (статический метод)//
    static MyBitset from_string(const std::string& str) {
        return MyBitset(str);
    }
    // Оператор += //
    MyBitset& operator+=(const MyBitset& other) {
        unsigned long long result = this->to_ullong() + other.to_ullong();
        bits = std::bitset<N>(result);
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, MyBitset& b) {
        std::string str;
        is >> str;
        b = MyBitset(str);
        return is;
    }

    // Перегрузка оператора [] для диапазона битов [start, end) //
    template <size_t M> MyBitset<M> operator()(size_t start, size_t end) const {
        if (start >= N || end > N || start >= end) {
            throw std::out_of_range("Invalid bit range");
        }

        std::string range_str;
        for (size_t i = start; i < end; ++i) {
            range_str += bits[i] ? '1' : '0';
        }

        while (range_str.length() < 8) {
            range_str = "0" + range_str;
        }

        return MyBitset<M>(range_str);
    }
};

// Вспомогательные проверки и безопасные конверторы
static bool is_binary(const string& s, size_t expected_len) {
    if (s.size() != expected_len) return false;
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}

static bool bin_to_int_safe(const string& s, int& out) {
    if (!is_binary(s, s.size())) return false;
    try {
        out = std::stoi(s, nullptr, 2);
        return true;
    }
    catch (...) {
        return false;
    }
}

static MyBitset<4> make_bitset4_safe(const string& s) {
    if (!is_binary(s, 4)) {
        cout << "Warning: invalid 4-bit pattern '" << s << "'. Using 0000.\n";
        return MyBitset<4>(0);
    }
    return MyBitset<4>(s);
}

static void trim(string& s) {
    const char* ws = " \t\n\r";
    auto start = s.find_first_not_of(ws);
    auto end = s.find_last_not_of(ws);
    if (start == string::npos) { s.clear(); return; }
    s = s.substr(start, end - start + 1);
}

// Склейка двух 4-битных значений в одно 8-битное //
MyBitset<8> Gluing(MyBitset<4> v1, MyBitset<4> v2) {
    string s1 = v1.to_string();
    string s2 = v2.to_string();
    string s3 = s1 + s2;
    MyBitset<8> final(s3);

    return (final);
}

//Поддержка MAP для bitset //
struct BitsetCompare {
    bool operator()(const MyBitset<4>& a, const MyBitset<4>& b) const {
        return a.to_ullong() < b.to_ullong();
    }
};


struct BitsetHash {
    size_t operator()(const MyBitset<4>& b) const {
        return b.to_ullong();
    }
};

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


//Регистры А и В //
int ok = 0;
char ch;
MyBitset<4> a;

string graffiti =
" ####### ######  #          ####### #     # #     # #          #    ####### ####### ######  \n"
"    #    #     # #    #     #       ##   ## #     # #         # #      #    #     # #     # \n"
"    #    #     # #    #     #       # # # # #     # #        #   #     #    #     # #     # \n"
"    #    #     # #    #     #####   #  #  # #     # #       #     #    #    #     # ######  \n"
"    #    #     # #######    #       #     # #     # #       #######    #    #     # #   #   \n"
"    #    #     #      #     #       #     # #     # #       #     #    #    #     # #    #  \n"
"    #    ######       #     ####### #     #  #####  ####### #     #    #    ####### #     # \n";


MyBitset<4> Program_Counter = 0;
int C_Flag = 0;
MyBitset<4> Register_A, Register_B, Output_Port, Input_Port, chose_Instruction, choce, key;
vector<vector<MyBitset<8>>> mapa;
map<int, MyBitset<8>> coman;
int com[256];

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

inline void PrintInvalidChoice() {
    cout << "Zaur, there is no such command!" << endl;
}

//Функция обработки функционала  команд//
auto fun(string choce, string data) {

    // Валидация входных строк для предотвращения некорректных конструкций
    if (!is_binary(choce, 4)) {
        cout << "Error: invalid instruction code '" << choce << "'. Ignoring.\n";
        return Register_A;
    }
    if (!is_binary(data, 4) && !(choce == "0001" || choce == "0100")) {
        // Для MOV A,B и MOV B,A payload может быть произвольным (в вашей логике).
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
        // в вашей логике payload = "0000" означает MOV A,B, иначе присваиваете immediate
        if (data != "0000") {
            Register_A += data;
            return Register_A;
        }
        else {
            cout << "Warning: invalid payload for MOV A, immediate. Ignored.\n";
            return Register_A;
        }

        Register_A = Register_B;
        return Register_A;
    }

    // 0100 MOV B,A//
    if (choce == "0100") {
        if (data != "0000") {
            Register_B = Register_A;
            Register_B += MyBitset<4>(data);
            return Register_B;
        }
        else {
            Register_B = Register_A;
            return Register_B;
        }
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
        return Register_A;
    }

    // 1001 OUT B //
    if (choce == "1001") {
        Register_B += MyBitset<4>(data);
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



int main() {
    for (int i = 0; i < 16; i++) {
        coman[i] = MyBitset<8>(); // Создаем пустую карту //
    }
    cout << graffiti;
    cout << "\n\n\n\n\n";
    cout << "Instruction_Set\n" << "ADD A,Im 0000,\nADD B,Im 0101,\nMOV A,Im 0011,\nMOV B,Im 0111,\nMOV A,B 0001\nMOV B,A 0100\nJMP Im 1111\nJNC Im 1110\nIN A 0010\nIN B 0110\nOUT B 1001\nOUT Im 1011";

    while (true) {
        cout << "\n\n\n";
        cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur  9: read file";
        cout << "\n\n\n";

        while (true) {
            if (!(cin >> comand)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                PrintInvalidChoice();
                cout << "Zaur,Choose action 1: Clear field 2: Disassembly 3: Add command or remove command 4: leave this program and say bye  5: print full map code 6: choice numb input_port 7: start program 8: Zaur 9: read file" << endl;
                continue;
            }
            if (comand < 1 || comand > 9) {
                PrintInvalidChoice();
                continue;
            }
            break;
        }

        switch (comand)
        {

        case 9: {
            //Работа с файлом //
            string file, line, data;
            vector<string> vector_parts;


            cout << "Enter the file how you want to read\n";
            cin >> file;
            ifstream in(file);
            if (!in.is_open()) {
                cout << "Error: cannot open file '" << file << "'.\n";
                break;
            }

            // читаем весь файл в одну строку (как у вас было)
            line.clear();
            while (std::getline(in, data)) {
                if (!line.empty()) line += ",";
                line += data;
            }
            in.close();

            if (line.empty()) {
                cout << "Warning: file is empty.\n";
                break;
            }

            // безопасный разбор через stringstream и разделитель ',',
            // с защитой от переполнения и некорректных символов
            {
                string token;
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    trim(token);
                    if (!token.empty()) vector_parts.push_back(token);
                }
            }

            //Отфильруем наши данные и превратим их в двоичный код //
            int count = 0;
            for (auto part : vector_parts) {
                trim(part);
                if (part.size() >= 3 && (part[0] == '0') && (part[1] == 'x' || part[1] == 'X')) {
                    string hex_str = part.substr(2);
                    try {
                        int hex_value = std::stoi(hex_str, nullptr, 16);
                        MyBitset<8> value(static_cast<unsigned long long>(hex_value));
                        coman[count] = value;
                    }
                    catch (...) {
                        cout << "Warning: invalid hex token '" << part << "'. Using 0.\n";
                        coman[count] = MyBitset<8>(0);
                    }
                }
                else {
                    // Попробуем распознать как десятич или как hex без 0x
                    try {
                        // если содержит не-цифры — считаем как ошибка и ставим 0
                        bool all_hex = true;
                        for (char c : part) {
                            if (!isxdigit(static_cast<unsigned char>(c))) { all_hex = false; break; }
                        }
                        if (all_hex && !part.empty()) {
                            int hex_value = std::stoi(part, nullptr, 16);
                            coman[count] = MyBitset<8>(static_cast<unsigned long long>(hex_value));
                        }
                        else {
                            cout << "Warning: unrecognized token '" << part << "'. Using 0.\n";
                            coman[count] = MyBitset<8>(0);
                        }
                    }
                    catch (...) {
                        cout << "Warning: error parsing token '" << part << "'. Using 0.\n";
                        coman[count] = MyBitset<8>(0);
                    }
                }
                ++count;
                if (count >= 16) break; // защита от переполнения карты
            }
            break;
        }

        case 8:
        {

            const std::string lines[] = {
                            "ZZZZZZZZZZZZZZZZZZZ                                                      ",
                            "Z:::::::::::::::::Z                                                      ",
                            "Z:::::::::::::::::Z                                                      ",
                            "Z:::ZZZZZZZZ:::::Z                                                       ",
                            "ZZZZZ     Z:::::Z    aaaaaaaaaaaaa  uuuuuu    uuuuuu rrrrr   rrrrrrrrr   ",
                            "        Z:::::Z      a::::::::::::a u::::u    u::::u r::::rrr:::::::::r  ",
                            "       Z:::::Z       aaaaaaaaa:::::au::::u    u::::u r:::::::::::::::::r ",
                            "      Z:::::Z                 a::::au::::u    u::::u rr::::::rrrrr::::::r",
                            "     Z:::::Z           aaaaaaa:::::au::::u    u::::u  r:::::r     r:::::r",
                            "    Z:::::Z          aa::::::::::::au::::u    u::::u  r:::::r     rrrrrrr",
                            "   Z:::::Z          a::::aaaa::::::au::::u    u::::u  r:::::r            ",
                            "ZZZ:::::Z     ZZZZZa::::a    a:::::au:::::uuuu:::::u  r:::::r            ",
                            "Z::::::ZZZZZZZZ:::Za::::a    a:::::au:::::::::::::::uur:::::r            ",
                            "Z:::::::::::::::::Za:::::aaaa::::::a u:::::::::::::::ur:::::r            ",
                            "Z:::::::::::::::::Z a::::::::::aa:::a uu::::::::uu:::ur:::::r            ",
                            "ZZZZZZZZZZZZZZZZZZZ  aaaaaaaaaa  aaaa   uuuuuuuu  uuuurrrrrrr            "
            };
            for (const auto& line : lines) {
                std::cout << line << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }


            //Работа с файлом //
            string file, line, data;
            vector<string> vector_parts;
            file = "Zaur";
            ifstream in(file);
            if (!in.is_open()) {
                cout << "Error: cannot open file '" << file << "'.\n";
            }

            // читаем весь файл в одну строку (как у вас было)
            line.clear();
            while (std::getline(in, data)) {
                cout << data;
            }
            in.close();

            if (line.empty()) {
                cout << "Warning: file is empty.\n";

            }
        }

        case 6:

        {
            cout << "Zaur,choice value input_port";
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
            ok = 0; // сброс для следующего раза //
            continue;
        }
        case 4:
            cout << "Zaur,See you soon!";
            exit(0);
        case 3:

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
                        choce = MyBitset<4>::from_string(zxc);

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
            break;
        case 1:
            coman.clear();
            break;

        case 2:
            cout << "";
            break;

        case 5:
            if (coman.empty()) {
                cout << "Zaur,Memory is empty\n";
            }
            else {
                vector<pair<int, MyBitset<8>>> sorted(coman.begin(), coman.end());

                sort(sorted.begin(), sorted.end(),
                    [](const auto& a, const auto& b) {
                        return a.first < b.first;
                    });

                for (const auto& i : sorted) {
                    cout << "Position " << i.first << ": " << i.second << "\n";
                }
            }
            break;
        case 7:

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
                        cout << "Error: invalid command encoding at position " << position << ". Skipping.\n";
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
                                cout << "Warning: invalid jump address '" << addr_check << "'. Ignoring jump.\n";
                            }
                            else {
                                if (new_i >= 0 && new_i < (int)sorted_coman.size()) {
                                    i = new_i - 1;
                                }
                                else {
                                    cout << "Warning: jump target " << new_i << " out of range. Ignored.\n";
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
            break;



        }

    }
}
