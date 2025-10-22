#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>
#include <iostream>

struct bigInteger {
    std::string value;

    // constructor
    bigInteger();
    bigInteger(const bigInteger&);
    bigInteger(const long long&);
    bigInteger(const std::string&);

    // assignment oprators for all valid datatypes
    bigInteger &operator=(const bigInteger&);
    bigInteger &operator=(const long long&);
    bigInteger &operator=(const std::string&);

    // Operators
    bigInteger operator+(const bigInteger&) const;
    bigInteger operator+(const long long&) const;

    // Functions
    int castToInt();
};

// custom std::cout instruction
std::ostream &operator<<(std::ostream &os, const bigInteger&);

#endif