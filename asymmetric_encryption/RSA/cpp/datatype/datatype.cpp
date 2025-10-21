#include "datatype.h"

// Constructers
bigInteger::bigInteger() {
    value = "0";
}

bigInteger::bigInteger(const bigInteger &number) {
    value = number.value;
}

// Operators 
bigInteger &bigInteger::bigInteger::operator=(const bigInteger &number) {
    value = number.value;
}

bigInteger &bigInteger::bigInteger::operator+(bigInteger &number) {
    if (this->value.size() < number.value.size()) {
        this->value = std::string(number.value.size() - this->value.size(), '0') + this->value;
    } else if (number.value.size() < this->value.size()) {
       number.value = std::string(this->value.size() - number.value.size(), '0') + number.value;
    } 

    int carry = 0;
    int sum;

    std::string result(this->value.size() + 1, '0');

    // Addition digit by digit 
    for(size_t i = this->value.size() - 1; i >= 0; i--) {
        sum = (this->value[i] - '0') + (number.value[i] - '0') + carry;
        carry = sum / 10;

        result[i + 1] = ('0' + (sum % 10));
    }

    if(carry) {
        result[0] = '0' + carry;
    } else {
        result.substr(1); // remove extra zero in the front
    }

    // assign value
    this->value = result;
}
