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

    // Operators
    bigInteger operator+(const bigInteger&) const; 

    // Functions
    int castToInt();
};

#endif