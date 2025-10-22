#include "datatype.h"

// Constructers
bigInteger::bigInteger() {
    this->value = "0";
}

bigInteger::bigInteger(const bigInteger &number) {
    this->value = number.value;
}

bigInteger::bigInteger(const long long &number) {
    this->value = std::to_string(number);
}

bigInteger::bigInteger(const std::string &number) {
    this->value = number;
}

// Operators 
bigInteger &bigInteger::operator=(const bigInteger &number) {
    value = number.value;
    return *this;
}

bigInteger bigInteger::operator+(const bigInteger &number) const {
    std::string first = this->value;
    std::string second = number.value; 
    
    if (this->value.size() < number.value.size()) {
       first = std::string(number.value.size() - this->value.size(), '0') + this->value;
    } else if (number.value.size() < this->value.size()) {
       second = std::string(this->value.size() - number.value.size(), '0') + number.value;
    } 

    int carry = 0;
    int sum;

    std::string result(this->value.size() + 1, '0');

    // Addition digit by digit 
    for(int i = first.size() - 1; i >= 0; i--) {
        sum = (first[i] - '0') + (second[i] - '0') + carry;
        carry = sum / 10;

        result[i + 1] = ('0' + (sum % 10));
    }

    if(carry) {
        result[0] = '0' + carry;
    } else {
        result = result.substr(1); // remove extra zero in the front
    }

    // assign value
    bigInteger returnResult =  result;
    return returnResult;
}
