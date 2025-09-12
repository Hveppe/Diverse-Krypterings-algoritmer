#include <string>
#include <iostream>

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

std::string EncryptRSA(long long e, long long n, std::string message) {
    std::string encryptedMessage = "";
    int maxLen = std::to_string(n).length();

    for(char letter : message) {
        std::string tempString = std::to_string(modPow(static_cast<int>(letter), e, n));
        encryptedMessage.append(tempString.insert(0, maxLen - tempString.size(), '0'));
    }

    return encryptedMessage;
}

std::string decryptRSA(long long d, long long n, std::string message) {
    std::string decryptedMessage = "";
    int maxLen = std::to_string(n).length();

    for(int i = 0; i < message.size(); i += maxLen) {
        std::string tempString = message.substr(i, maxLen);
        decryptedMessage.push_back(static_cast<char>(modPow(std::stoll(tempString), d, n)));
    }

    return decryptedMessage;
}