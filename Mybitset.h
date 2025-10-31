#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

using namespace std;

//Класс который будет эмулировать двоичный код//
template <size_t N>
class MyBitset {
private:
    int numb_posi;
    std::bitset<N> bits;

    // Вспомогательные методы для разбора строк
    static void trim_inplace(std::string& s) {
        auto notspace = [](int ch) { return !std::isspace(ch); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notspace));
        s.erase(std::find_if(s.rbegin(), s.rend(), notspace).base(), s.end());
    }

    static bool is_binary_str(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), [](char c) { return c == '0' || c == '1'; });
    }

    static bool is_hex_str(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), [](char c) { return std::isxdigit(static_cast<unsigned char>(c)); });
    }

    static unsigned long long parse_hex_to_ull(const std::string& s) {
        std::stringstream ss;
        ss << std::hex << s;
        unsigned long long val = 0;
        if (!(ss >> val)) {
            throw std::invalid_argument("MyBitset: invalid hex '" + s + "'");
        }
        return val;
    }

    // Унифицированная логика инициализации из строки
    void init_from_string(const std::string& raw) {
        std::string s = raw;
        trim_inplace(s);
        if (!s.empty() && (s.back() == 'h' || s.back() == 'H')) {
            s.pop_back();
            trim_inplace(s);
        }
        if (s.empty()) {
            throw std::invalid_argument("MyBitset: empty string");
        }
        if (is_binary_str(s)) {
            // std::bitset accepts strings with most-significant bit first.
            bits = std::bitset<N>(s);
            return;
        }
        if (is_hex_str(s)) {
            unsigned long long v = parse_hex_to_ull(s);
            bits = std::bitset<N>(v);
            return;
        }
        throw std::invalid_argument("MyBitset: input must be binary or hex (optional trailing 'h'): '" + raw + "'");
    }

public:
    // Конструкторы//
    MyBitset() : bits(0) {}

    MyBitset(const std::string& str) {
        init_from_string(str);
    }

    MyBitset(unsigned long long value) : bits(value) {}

    // Оператор присваивания из строки//
    MyBitset& operator=(const std::string& str) {
        init_from_string(str);
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
        std::cout << bits << "(" << to_ullong() << ")" << std::endl;
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

    // Оператор * //
    MyBitset& operator*(const MyBitset& other) {
        unsigned long long result = this->to_ullong() * other.to_ullong();
        bits = std::bitset<N>(result);
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, MyBitset& b) {
        std::string str;
        is >> str;
        b.init_from_string(str);
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