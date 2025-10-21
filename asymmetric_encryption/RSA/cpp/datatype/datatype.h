#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>

struct bigInteger {
    std::string value;

    // constructor
    bigInteger();
    bigInteger(const bigInteger&);

    // Operators
    bigInteger &operator=(const bigInteger&);
    bigInteger &operator+(bigInteger&);

    // Functions
    int castToInt();
};

#endif