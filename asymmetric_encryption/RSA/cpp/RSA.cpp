#include "RSA.h"

long long modPow(long long base, unsigned long long exponent, long long modulus) {
    if(modulus == 1) {
        return 0;
    }

    long long result = 1;
    base %= modulus;

    while(exponent > 0) {
        if(exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;
}

std::string encryptRSA(long long e, long long n, std::string message) {
    long long m = 0;

    for(char letter : message) {
        m = m * 256 + static_cast<unsigned char>(letter);
    }

    long long c = modPow(m, e, n);
    return std::to_string(c);
}

std::string decryptRSA(long long d, long long n, std::string message) {
    long long c = std::stoll(message);
    long long m = modPow(c, d, n);
    std::string decryptedMessage = "";
    
    while(m > 0) {
        decryptedMessage.insert(decryptedMessage.begin(), static_cast<char>(m % 256));
        m /= 256;
    }

    return decryptedMessage;
}