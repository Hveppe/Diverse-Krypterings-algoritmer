#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

struct bigInteger {
    std::string value;

    // constructor
    bigInteger();
    bigInteger(const bigInteger&);
    bigInteger(const long long&);
    bigInteger(const std::string&);

    // assignment operators for all valid datatypes
    bigInteger &operator=(const bigInteger&);
    bigInteger &operator=(const long long&);
    bigInteger &operator=(const std::string&);

    // Comparesion operators
    bool operator==(const bigInteger&) const;
    bool operator==(const long long&) const;

    // Operators
    bigInteger operator+(const bigInteger&) const;
    bigInteger operator+(const long long&) const;
    bigInteger &operator+=(const bigInteger&);
    bigInteger &operator+=(const long long&);

    bigInteger operator-(const bigInteger&) const;
    bigInteger operator-(const long long&) const;
    bigInteger &operator-=(const bigInteger&);
    bigInteger &operator-=(const long long&);

    bigInteger operator*(const bigInteger&) const;
    bigInteger operator*(const long long&) const;
    bigInteger &operator*=(const bigInteger&);
    bigInteger &operator*=(const long long&);

    // Functions
    int castToInt();
};

// custom std::cout instruction
std::ostream &operator<<(std::ostream &os, const bigInteger&);

#endif