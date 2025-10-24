#include "datatype.h"

//--------------------------Constructers----------------------------
bigInteger::bigInteger() {
    this->value = "0";
}

bigInteger::bigInteger(const bigInteger &number) {
    this->sign = number.sign;
    this->value = number.value;
}

bigInteger::bigInteger(const long long &number) {
    if(number < 0) {
        this->sign = '-';
        this->value = std::to_string(number).substr(1);
    } else {
        this->sign = '+';
        this->value = std::to_string(number);
    }
}

bigInteger::bigInteger(const std::string &number) {
    if(number[0] == '-') {
        this->sign = '-';
        this->value = number.substr(1);
    } else {
        this->sign = '+';
        this->value = number;
    }

    
}

//----------------------Assignment Operators--------------------------
bigInteger &bigInteger::operator=(const bigInteger &number) {
    this->value = number.value;
    this->sign = number.sign;

    return *this;
}

bigInteger &bigInteger::operator=(const long long &number) {
    *this = bigInteger(number);
    return *this;
}

bigInteger &bigInteger::operator=(const std::string &number) {
    *this = number;
    return *this;
}

//---------------------------Comparesion Operators---------------------------
bool bigInteger::operator==(const bigInteger &number) const {
    return (this->value == number.value && this->sign == number.sign);
}

bool bigInteger::operator==(const long long &number) const {
    return *this == bigInteger(number);
}

//-------------------------------Operators----------------------------------
bigInteger bigInteger::operator+(const bigInteger &number) const {
    bool doubleNegativ = false;
    
    // handle negativ addition
    if(this->sign == '-' && number.sign == '-') {
        doubleNegativ = true;
        //return -10;
    } else if (this->sign == '-') {
        return number - *this;
    } else if (number.sign == '-') {
        return *this - number;
    }

    std::string first = this->value;
    std::string second = number.value; 
    
    if(this->value.size() < number.value.size()) {
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
    bigInteger returnResult = result;
    if(doubleNegativ) {
        returnResult.sign = '-';
    }
    std::cout << doubleNegativ << " " << returnResult.sign << "\n";
    return returnResult;
}

bigInteger bigInteger::operator+(const long long &number) const {
    bigInteger first = number;
    bigInteger second = this->value;
    return first + second;
}

bigInteger operator+(const long long &first, const bigInteger &second) {
    return bigInteger(first) + second;
}

bigInteger &bigInteger::operator+=(const bigInteger &number) {
    this->value = (*this + number).value;
    return *this;
}

bigInteger &bigInteger::operator+=(const long long &number) {
    this->value = (*this + bigInteger(number)).value;
    return *this;
}

bigInteger bigInteger::operator-(const bigInteger &number) const{
    return bigInteger("0");
}

bigInteger bigInteger::operator*(const bigInteger &number) const {
    std::string first = this->value;
    std::string second = number.value;

    std::vector<int> result(first.size() + second.size(), 0);

    std::reverse(first.begin(), first.end());
    std::reverse(second.begin(), second.end());

    for(size_t i = 0; i < first.size(); i++) {
        for(size_t j = 0; j < second.size(); j++) {
            int index = i + j;
            result[index] += (first[i] - '0') * (second[j] - '0');
            if(result[index] >= 10) {
                result[index + 1] += result[index] / 10;
                result[index] %= 10;
            }
        }
    }

    while(result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    bigInteger produkt = std::string("");
    for(int i = result.size() - 1; i >= 0; i--) {
        produkt.value.push_back('0' + result[i]);
    }

    // handle negativ sign
    if(this->sign == '-' && number.sign == '-') {
        produkt.sign = '+';
    } else if(this->sign == '-' || number.sign == '-') {
        produkt.sign = '-';
    }

    return produkt;
}

bigInteger bigInteger::operator*(const long long &number) const {
    return *this * bigInteger(number);
}

bigInteger &bigInteger::operator*=(const bigInteger &number) {
   *this = *this * number;
    return *this;
}

bigInteger &bigInteger::operator*=(const long long &number) {
    *this = *this * bigInteger(number);
    return *this;
}

bigInteger operator*(const long long &first, const bigInteger &second) {
    return bigInteger(first) * second;
}

//------------------------Custom functions----------------------------------
int bigInteger::castToInt() {
    return std::stoi(this->value);
}

//------------------------std::cout instruction------------------------------
std::ostream &operator<<(std::ostream &os, const bigInteger &number) {
    if(number.sign == '-') {
        os << number.sign;
    }
    os << number.value;
    return os;
}
