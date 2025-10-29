#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <bitset>


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
    MyBitset(const std::string& str) : bits(0)
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
     MyBitset from_string(const std::string& str) {
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