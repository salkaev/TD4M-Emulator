// BitsetCompare.h
#pragma once

#ifndef BITSETCOMPARE_H
#define BITSETCOMPARE_H

#include "Mybitset.h"
#include <functional>

// Функтор для сравнения MyBitset в map
struct BitsetCompare {
    bool operator()(const MyBitset<4>& lhs, const MyBitset<4>& rhs) const {
        return lhs.to_ullong() < rhs.to_ullong();
    }
    
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs < rhs;
    }
};

#endif // BITSETCOMPARE_H